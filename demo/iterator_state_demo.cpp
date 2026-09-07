// Iterator + State demo for TaskForge.
//
// This file is NOT built by the top-level Makefile (it has its own main()).
// It needs the Composite/Decorator side implemented (ProjectGroup::add/getCost,
// ProjectDecorator storing its target, decorator getCost). Once that lands,
// build from the repo root with:
//   g++ -std=c++11 -Wall -Wextra $(ls *.cpp | grep -v '^main.cpp$') demo/iterator_state_demo.cpp -o demo_bin
//   valgrind --leak-check=full --show-leak-kinds=all ./demo_bin
// The sections below can also be pasted into main.cpp for the practical demo.
//
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <typeinfo>
using namespace std;

#include "ProjectComponent.h"
#include "ProjectGroup.h"
#include "ProjectTask.h"
#include "ProjectDecorator.h"
#include "rushDecorator.h"
#include "hazardDecorator.h"
#include "ProjectIterator.h"
#include "ProjectState.h"
#include "ScheduledState.h"
#include "ActiveState.h"
#include "InspectionState.h"
#include "CompletedState.h"

// Labels live in the client, since components carry no name in the UML.
static map<ProjectComponent*, string> labels;
static vector<ProjectComponent*> owned;   // everything the demo allocates

template <typename T> static T* track(T* c, const string& name) {
    labels[c] = name; owned.push_back(c); return c;
}

static string stateName(ProjectTask* t) {
    ProjectState* s = t->getState();
    if (dynamic_cast<ScheduledState*>(s))  return "Scheduled";
    if (dynamic_cast<ActiveState*>(s))     return "Active";
    if (dynamic_cast<InspectionState*>(s)) return "Inspection";
    if (dynamic_cast<CompletedState*>(s))  return "Completed";
    return "?";
}

static string kind(ProjectComponent* c) {
    if (dynamic_cast<ProjectGroup*>(c))     return "Group";
    if (dynamic_cast<ProjectTask*>(c))      return "Task";
    if (dynamic_cast<ProjectDecorator*>(c)) return "Decorator";
    return "?";
}

static void printAll(ProjectComponent* root, const string& type) {
    ProjectIterator* it = root->createIIterator(type);
    if (!it) { cout << "  (no iterator for type '" << type << "')\n"; return; }
    for (it->first(); !it->isDone(); it->next()) {
        ProjectComponent* c = it->currentItem();
        cout << "  " << kind(c) << " " << labels[c] << " cost=" << c->getCost();
        if (ProjectTask* t = dynamic_cast<ProjectTask*>(c)) cout << " [" << stateName(t) << "]";
        cout << "\n";
    }
    delete it;   // caller owns the iterator; the tree is untouched
}

int main() {
    // --- 1. Hierarchy with 3 levels of nesting ------------------------------
    ProjectGroup* site        = track(new ProjectGroup(), "Site");
    ProjectGroup* foundations = track(new ProjectGroup(), "Foundations");
    ProjectGroup* structure   = track(new ProjectGroup(), "Structure");
    ProjectGroup* groundFloor = track(new ProjectGroup(), "GroundFloor");

    ProjectTask* excavation = track(new ProjectTask(500, 3),  "Excavation");
    ProjectTask* concrete   = track(new ProjectTask(1200, 5), "ConcretePour");
    ProjectTask* rebar      = track(new ProjectTask(800, 4),  "Rebar");
    ProjectTask* framing    = track(new ProjectTask(900, 6),  "Framing");
    ProjectTask* plumbing   = track(new ProjectTask(600, 2),  "PlumbingRoughIn");
    ProjectTask* roofing    = track(new ProjectTask(700, 4),  "Roofing");
    ProjectComponent* rushRebar   = track(new rushDecorator(rebar), "Rush(Rebar)");
    ProjectComponent* hazardRoof  = track(new hazardDecorator(roofing, "Working at height"), "Hazard(Roofing)");

    site->add(foundations);
    site->add(structure);
    site->add(hazardRoof);
    foundations->add(excavation);
    foundations->add(concrete);
    foundations->add(rushRebar);
    structure->add(groundFloor);
    groundFloor->add(framing);
    groundFloor->add(plumbing);

    cout << "== Depth-first traversal via createIIterator(\"depth\") ==\n";
    printAll(site, "depth");

    // --- 2. State transitions --------------------------------------------
    cout << "\n== Moving tasks through the state machine ==\n";
    concrete->startTask(nullptr);  concrete->submitForInspection(nullptr);
    plumbing->startTask(nullptr);  plumbing->submitForInspection(nullptr);
    rebar->startTask(nullptr);     rebar->submitForInspection(nullptr);
    framing->startTask(nullptr);   // stays Active, must NOT appear below

    cout << "\n== Priority inspection traversal via createIIterator(\"priority\") ==\n";
    cout << "(expect ConcretePour 1200, Rebar 800, PlumbingRoughIn 600)\n";
    printAll(site, "priority");

    // --- 3. Invalid transitions are safe no-ops ---------------------------
    cout << "\n== Invalid transitions ==\n";
    cout << "Excavation before: " << stateName(excavation) << "\n";
    excavation->completeTask(nullptr);       // Scheduled: invalid
    excavation->failInspection(nullptr);     // Scheduled: invalid
    cout << "Excavation after:  " << stateName(excavation) << "\n";

    concrete->completeTask(nullptr);         // Inspection -> Completed
    concrete->startTask(nullptr);            // Completed: invalid (terminal)
    cout << "ConcretePour now:  " << stateName(concrete) << "\n";

    plumbing->failInspection(nullptr);       // Inspection -> Active (rework)
    plumbing->startTask(nullptr);            // Active: invalid
    cout << "PlumbingRoughIn now: " << stateName(plumbing) << "\n";

    // --- 4. Snapshot policy of PriorityInspectionIterator ------------------
    cout << "\n== Snapshot policy ==\n";
    ProjectIterator* snap = site->createIIterator("priority");
    snap->first();
    cout << "Snapshot taken; now changing Rebar's state mid-traversal...\n";
    rebar->completeTask(nullptr);
    cout << "Old iterator still yields:";
    for (; !snap->isDone(); snap->next()) cout << " " << labels[snap->currentItem()];
    cout << "\n";
    delete snap;
    cout << "Fresh iterator yields:";
    ProjectIterator* fresh = site->createIIterator("priority");
    for (fresh->first(); !fresh->isDone(); fresh->next()) cout << " " << labels[fresh->currentItem()];
    cout << (fresh->isDone() ? " (none)" : "") << "\n";
    delete fresh;

    cout << "\n== Unknown iterator type ==\n";
    printAll(site, "bogus");

    cout << "\n== Leaf iterator (single task) ==\n";
    printAll(framing, "depth");

    // --- Cleanup: the demo owns every node it created ----------------------
    for (size_t i = 0; i < owned.size(); ++i) delete owned[i];
    return 0;
}

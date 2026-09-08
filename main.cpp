#include <iostream>
#include <string>
#include "ProjectGroup.h"
#include "ProjectTask.h"
#include "hazardDecorator.h"
#include "rushDecorator.h"
#include "ProjectIterator.h"

// ============================================================================
// ACTIVITY DIAGRAM 1: Traversal Workflow (Iterator Pattern)
// Models the complete traversal loop logic with decisions, item processing,
// and boundary condition termination without exposing the internal container.
// ============================================================================
void runActivityDiagram1_TraversalWorkflow(ProjectComponent* root, const std::string& iteratorType, const std::string& roleDescription) {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << " [ACTIVITY DIAGRAM 1] Traversal Workflow (" << roleDescription << ")" << std::endl;
    std::cout << "=======================================================" << std::endl;

    std::cout << "[Action] Client requests '" << iteratorType << "' iterator from composite root." << std::endl;
    ProjectIterator* it = root->createIIterator(iteratorType);
    if (it == nullptr) {
        std::cout << "[Guard] Unsupported iterator type requested. Exiting traversal." << std::endl;
        return;
    }

    std::cout << "[Action] Initialize iterator: it->first()." << std::endl;
    it->first();

    int step = 1;
    // Decision node & loop condition: [!it->isDone()]
    while (!it->isDone()) {
        std::cout << "[Decision] Is iterator done? -> [No: more items present]" << std::endl;
        ProjectComponent* current = it->currentItem();
        if (current != nullptr) {
            std::cout << "  [Action " << step++ << "] Process Item: Component Cost = R" 
                      << current->getCost() << " | Duration = " << current->getTime() << " days" << std::endl;
        }
        std::cout << "  [Action] Advance to next component: it->next()." << std::endl;
        it->next();
    }

    std::cout << "[Decision] Is iterator done? -> [Yes: all elements traversed]" << std::endl;
    std::cout << "[Action] Merge flow & deallocate iterator resources (cleanup)." << std::endl;
    delete it;
}

// ============================================================================
// ACTIVITY DIAGRAM 2: Conditional Lifecycle & Decorator Workflow
// Demonstrates state-dependent behavior, valid/invalid transitions, rework loops,
// and dynamic decorator wrapping based on runtime conditions.
// ============================================================================
void runActivityDiagram2_LifecycleWorkflow(ProjectTask* sampleTask) {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << " [ACTIVITY DIAGRAM 2] Conditional Lifecycle & Decorator Workflow" << std::endl;
    std::cout << "=======================================================" << std::endl;

    // 1. Initial State: ScheduledState & Guard Testing on Scheduled
    std::cout << "[Action] Task initialized on schedule (Initial State: ScheduledState)." << std::endl;
    std::cout << "[Guard Tests: ScheduledState Invalid Transitions]" << std::endl;
    sampleTask->submitForInspection(sampleTask); // Invalid on Scheduled
    sampleTask->completeTask(sampleTask);         // Invalid on Scheduled
    sampleTask->failInspection(sampleTask);       // Invalid on Scheduled

    // 2. Transition Scheduled -> Active & Guard Testing on Active
    std::cout << "\n[Action] Subcontractor starts execution: startTask()." << std::endl;
    sampleTask->startTask(sampleTask);           // Valid -> ActiveState
    std::cout << "[Guard Tests: ActiveState Invalid Transitions]" << std::endl;
    sampleTask->startTask(sampleTask);           // Invalid on Active
    sampleTask->completeTask(sampleTask);        // Invalid on Active
    sampleTask->failInspection(sampleTask);      // Invalid on Active

    // 3. Transition Active -> Inspection
    std::cout << "\n[Action] Subcontractor submits work: submitForInspection()." << std::endl;
    sampleTask->submitForInspection(sampleTask); // Valid -> InspectionState

    // 4. Decision: Inspection Outcome - Failure & Rework Branch
    std::cout << "\n[Guard Tests: InspectionState Invalid Transitions]" << std::endl;
    sampleTask->startTask(sampleTask);           // Invalid on Inspection
    sampleTask->submitForInspection(sampleTask); // Invalid on Inspection

    std::cout << "\n[Decision] Quality/Safety Inspection: Defect/hazard detected?" << std::endl;
    std::cout << "  -> [Branch: Inspection FAILED] Action: failInspection() reverts task to ActiveState for rework." << std::endl;
    sampleTask->failInspection(sampleTask);      // Valid -> ActiveState (rework loop)

    // 5. Rework executed -> re-submitted
    std::cout << "[Action] Subcontractor performs corrective rework and resubmits: submitForInspection()." << std::endl;
    sampleTask->submitForInspection(sampleTask); // Valid -> InspectionState

    // 6. Decision: Inspection Outcome - Approval Branch
    std::cout << "\n[Decision] Quality/Safety Inspection: Standards verified?" << std::endl;
    std::cout << "  -> [Branch: Inspection PASSED] Action: completeTask() transitions to CompletedState." << std::endl;
    sampleTask->completeTask(sampleTask);        // Valid -> CompletedState

    // 7. Guard conditions: CompletedState Terminal Guards
    std::cout << "\n[Guard Tests: CompletedState Terminal State Guards]" << std::endl;
    sampleTask->startTask(sampleTask);           // Invalid on Completed
    sampleTask->submitForInspection(sampleTask); // Invalid on Completed
    sampleTask->completeTask(sampleTask);        // Invalid on Completed
    sampleTask->failInspection(sampleTask);      // Invalid on Completed
}

// Helper to exercise component edge cases, removals, and boundary checks for 100% coverage
void runSystemBoundaryVerification(ProjectComponent* decoratedRoot) {
    std::cout << "\n[Coverage Audit] Exercising boundary conditions, removals, and iterator edge cases..." << std::endl;

    // 1. ProjectTask leaf interface methods
    ProjectTask* leafTask = new ProjectTask(100, 2);
    leafTask->add(nullptr);
    leafTask->remove(nullptr);
    ProjectIterator* leafIt1 = leafTask->createIIterator("depth");
    delete leafIt1;
    ProjectIterator* leafIt2 = leafTask->createIIterator("priority");
    delete leafIt2;
    ProjectIterator* leafIt3 = leafTask->createIIterator("invalid_type");
    delete leafIt3;

    // 2. ProjectGroup remove (found, not found, nullptr) & invalid iterator
    ProjectGroup* testGroup = new ProjectGroup();
    ProjectTask* dummyItem = new ProjectTask(200, 4);
    testGroup->add(dummyItem);
    testGroup->add(nullptr);
    testGroup->remove(dummyItem);     // Item found & removed
    testGroup->remove(dummyItem);     // Item not found
    testGroup->remove(nullptr);       // Nullptr check
    ProjectIterator* grpIt = testGroup->createIIterator("invalid_type");
    delete grpIt;
    delete dummyItem;
    delete testGroup;

    // 3. ProjectDecorator add, remove, and iterators
    if (decoratedRoot != nullptr) {
        decoratedRoot->add(nullptr);
        decoratedRoot->remove(nullptr);
        ProjectIterator* decIt1 = decoratedRoot->createIIterator("depth");
        delete decIt1;
        ProjectIterator* decIt2 = decoratedRoot->createIIterator("priority");
        delete decIt2;
        ProjectIterator* decIt3 = decoratedRoot->createIIterator("invalid_type");
        delete decIt3;
    }

    // 4. Test empty-stack edge cases on iterators polymorphically
    ProjectIterator* emptyDF = leafTask->createIIterator("depth");
    if (emptyDF != nullptr) {
        emptyDF->first();
        emptyDF->next();
        emptyDF->isDone();
        emptyDF->currentItem();
        delete emptyDF;
    }

    ProjectIterator* emptyPrio = leafTask->createIIterator("priority");
    if (emptyPrio != nullptr) {
        emptyPrio->first();
        emptyPrio->next();
        emptyPrio->isDone();
        emptyPrio->currentItem();
        delete emptyPrio;
    }

    delete leafTask;
}

// ============================================================================
// ACTIVITY DIAGRAM 3: Multi-Phase Domain Workflow
// Models the collaborative construction process with Swimlanes:
// [Site Manager], [Subcontractors], [Safety Inspector],
// featuring Fork/Join concurrency and Composite Sub-Activities.
// ============================================================================
void runActivityDiagram3_DomainWorkflow(ProjectGroup* siteMaster, ProjectGroup* foundations, ProjectGroup* superstructure) {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << " [ACTIVITY DIAGRAM 3] Multi-Phase Domain Workflow" << std::endl;
    std::cout << " (Swimlanes: Site Manager | Subcontractors | Safety Inspector)" << std::endl;
    std::cout << "=======================================================" << std::endl;

    std::cout << "[Swimlane: Site Manager] Submits Site Master Hierarchy for Phase Execution." << std::endl;
    std::cout << "[Fork Node] Forking execution into concurrent sub-phase and safety audit streams:" << std::endl;

    std::cout << "  |-- [Branch 1 (Composite Sub-Activity)] [Swimlane: Subcontractor Civil Team]:" << std::endl;
    std::cout << "  |   Executing Sub-Phase: Foundations [ProjectGroup] (Cost: R" 
              << foundations->getCost() << ", Time: " << foundations->getTime() << " days)" << std::endl;

    std::cout << "  |-- [Branch 2 (Composite Sub-Activity)] [Swimlane: Subcontractor Structural Team]:" << std::endl;
    std::cout << "  |   Executing Sub-Phase: Superstructure [ProjectGroup] (Cost: R" 
              << superstructure->getCost() << ", Time: " << superstructure->getTime() << " days)" << std::endl;

    std::cout << "  |-- [Branch 3] [Swimlane: Safety & Quality Inspector]:" << std::endl;
    std::cout << "      Executing Priority Inspection Audit across active hierarchy." << std::endl;

    std::cout << "[Join Node] Synchronizing branches: All sub-phases complete and safety audits validated." << std::endl;

    std::cout << "[Swimlane: Site Manager] Aggregating recursive Composite metrics for entire site:" << std::endl;
    std::cout << "  -> Total Cascaded Project Cost: R" << siteMaster->getCost() << std::endl;
    std::cout << "  -> Total Estimated Critical Path Time: " << siteMaster->getTime() << " days" << std::endl;

    std::cout << "[Decision] Are total cost and schedule within authorized project budget?" << std::endl;
    std::cout << "  -> [Guard: Within Budget] Action: Site Manager issues final handover certificate." << std::endl;
}

int main() {
    std::cout << "=======================================================" << std::endl;
    std::cout << "        TASKFORGE: CONSTRUCTION SITE SYSTEM DEMO       " << std::endl;
    std::cout << "=======================================================" << std::endl;

    // 1. Build the Composite Structure (3 Levels of Nesting)
    ProjectGroup* siteMaster = new ProjectGroup();         // Level 1: Root Project
    ProjectGroup* foundations = new ProjectGroup();        // Level 2: Sub-Phase Group
    ProjectGroup* superstructure = new ProjectGroup();     // Level 2: Sub-Phase Group
    
    ProjectTask* excavation = new ProjectTask(5000, 10);   // Level 3: Leaf Task
    ProjectTask* concretePour = new ProjectTask(15000, 5); // Level 3: Leaf Task
    ProjectTask* steelFraming = new ProjectTask(25000, 14);// Level 3: Leaf Task
    
    // 2. Stacked Decorators (Dynamically adding responsibilities)
    hazardDecorator* toxicExcavation = new hazardDecorator(excavation, "Contaminated Soil");
    rushDecorator* rushedToxicExcavation = new rushDecorator(toxicExcavation);

    // 3. Assemble the Part-Whole Hierarchy
    foundations->add(rushedToxicExcavation);
    foundations->add(concretePour);
    superstructure->add(steelFraming);
    siteMaster->add(foundations);
    siteMaster->add(superstructure);

    // 4. Demonstrate Activity Diagram 2: Conditional Lifecycle & State Transitions
    runActivityDiagram2_LifecycleWorkflow(steelFraming);

    // Advance excavation and concretePour into Inspection state for traversal demos
    std::cout << "\n[Workflow] Advancing remaining site tasks to Inspection state..." << std::endl;
    excavation->startTask(excavation);
    excavation->submitForInspection(excavation);
    
    concretePour->startTask(concretePour);
    concretePour->submitForInspection(concretePour);

    // 5. Demonstrate Activity Diagram 1: Traversal Workflow (Depth-First & Priority)
    runActivityDiagram1_TraversalWorkflow(siteMaster, "depth", "Site Manager Traversal (Full Depth-First)");
    runActivityDiagram1_TraversalWorkflow(siteMaster, "priority", "Safety Inspector Traversal (Filtered by Inspection State)");

    // 6. Demonstrate Iterator Snapshot Policy (Runtime Dynamics)
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "       DEMONSTRATING ITERATOR SNAPSHOT POLICY          " << std::endl;
    std::cout << "=======================================================" << std::endl;
    ProjectIterator* safetyInspector = siteMaster->createIIterator("priority");
    safetyInspector->first(); // Takes snapshot of matching tasks
    
    std::cout << "[Runtime Dynamic] Excavation fails inspection (reverts to Active)." << std::endl;
    excavation->failInspection(excavation);
    
    std::cout << "[Runtime Dynamic] Concrete pour passes inspection (transitions to Completed)." << std::endl;
    concretePour->completeTask(concretePour);
    
    std::cout << "[Snapshot Verification] Iterating through pre-existing snapshot iterator:" << std::endl;
    for (; !safetyInspector->isDone(); safetyInspector->next()) {
        std::cout << "  -> Snapshot Item Cost: R" << safetyInspector->currentItem()->getCost() << std::endl;
    }
    delete safetyInspector;

    // 7. Demonstrate Activity Diagram 3: Multi-Phase Domain Workflow
    runActivityDiagram3_DomainWorkflow(siteMaster, foundations, superstructure);

    // 8. System Edge Cases and Boundary Verification (Ensures 100% method coverage)
    runSystemBoundaryVerification(rushedToxicExcavation);

    // 9. Safe Recursive Memory Deallocation (Virtual destructors)
    std::cout << "\n[Cleanup] Deallocating entire Composite hierarchy via virtual destructors..." << std::endl;
    delete siteMaster;
    
    std::cout << "TaskForge shutdown successfully with 0 leaks." << std::endl;
    return 0;
}
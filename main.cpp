#include <iostream>
#include <string>
#include "ProjectGroup.h"
#include "ProjectTask.h"
#include "hazardDecorator.h"
#include "rushDecorator.h"
#include "ProjectIterator.h"

// Helper function to keep the main code clean 
void printTraversal(ProjectComponent* root, std::string iteratorType, std::string message) {
    std::cout << "\n--- " << message << " ---" << std::endl;
    ProjectIterator* it = root->createIIterator(iteratorType);
    if (it == nullptr) return;
    
    for (it->first(); !it->isDone(); it->next()) {
        ProjectComponent* current = it->currentItem();
        if (current != nullptr) {
            std::cout << "-> Component Cost: R" << current->getCost() 
                      << " | Time: " << current->getTime() << " days" << std::endl;
        }
    }
    delete it; // cleanup
}

int main() {
    std::cout << "========== TASKFORGE: CONSTRUCTION SITE DEMO ==========" << std::endl;

    // Build the Composite Structure (3 Levels)
    ProjectGroup* siteMaster = new ProjectGroup();         // Level 1
    ProjectGroup* foundations = new ProjectGroup();        // Level 2
    ProjectGroup* superstructure = new ProjectGroup();     // Level 2
    
    ProjectTask* excavation = new ProjectTask(5000, 10);   // Level 3
    ProjectTask* concretePour = new ProjectTask(15000, 5); // Level 3
    ProjectTask* steelFraming = new ProjectTask(25000, 14);// Level 3
    
    //  Stacked Decorators
    hazardDecorator* toxicExcavation = new hazardDecorator(excavation, "Contaminated Soil");
    rushDecorator* rushedToxicExcavation = new rushDecorator(toxicExcavation);

    //  Assemble the Tree
    foundations->add(rushedToxicExcavation);
    foundations->add(concretePour);
    superstructure->add(steelFraming);
    siteMaster->add(foundations);
    siteMaster->add(superstructure);

    //  State Transitions & Lifecycle
    std::cout << "\n[Workflow] Advancing tasks through their lifecycle..." << std::endl;
    excavation->startTask(excavation);
    excavation->submitForInspection(excavation); // Stuck in inspection
    
    concretePour->startTask(concretePour);
    concretePour->submitForInspection(concretePour); // Stuck in inspection
    
    steelFraming->startTask(steelFraming); // Just active

    //  Iterator Demonstration 1: Depth-First (Complete Tree)
    printTraversal(siteMaster, "depth", "Site Manager Traversal (Full Depth-First)");

    //  Iterator Demonstration 2: Priority (Filtered & Sorted)
    printTraversal(siteMaster, "priority", "Safety Inspector Traversal (Only Items in Inspection State)");

    //  Mid-Traversal Change (Snapshot vs Live Traversal Policy)
    std::cout << "\n--- Demonstrating Iterator Snapshot Policy ---" << std::endl;
    ProjectIterator* safetyInspector = siteMaster->createIIterator("priority");
    safetyInspector->first(); // Takes the snapshot of the tree
    
    std::cout << "[Workflow] Toxic Excavation fails inspection and reverts to Active state." << std::endl;
    excavation->failInspection(excavation);
    
    std::cout << "[Workflow] Steel Framing finishes early and submits for inspection." << std::endl;
    steelFraming->submitForInspection(steelFraming);
    
    std::cout << "Original Safety Inspector Traversal (Uses old Snapshot):" << std::endl;
    for (; !safetyInspector->isDone(); safetyInspector->next()) {
        std::cout << "-> Component Cost: R" << safetyInspector->currentItem()->getCost() << std::endl;
    }
    delete safetyInspector;

    //  Recursive Composite Math
    std::cout << "\n========== FINAL SITE CALCULATIONS ==========" << std::endl;
    std::cout << "Total Cascaded Project Cost: R" << siteMaster->getCost() << std::endl;
    
    //  Memory Deallocation
    delete siteMaster;
    
    std::cout << "TaskForge shutdown complete." << std::endl;
    return 0;
}
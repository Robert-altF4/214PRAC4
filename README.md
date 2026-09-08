# TaskForge: Hierarchical Work Processing System

**COS 214 Practical 4 (2026)**  
**Domain**: Construction Site Civil & Structural Engineering  
**Language**: C++11  

---

## 1. Project Overview

TaskForge is a cohesive C++11 work-processing application that models and executes nested hierarchical tasks on an active construction site. The system seamlessly integrates four Gang of Four (GoF) design patterns:

1. **Composite Pattern**:
   - `ProjectComponent` (Abstract Component)
   - `ProjectGroup` (Composite: e.g., Site Master, Foundations Phase, Superstructure Phase)
   - `ProjectTask` (Leaf: e.g., Excavation, Concrete Pouring, Steel Framing)
2. **Decorator Pattern**:
   - `ProjectDecorator` (Abstract Decorator wrapping `ProjectComponent`)
   - `hazardDecorator` (Multiplies cost by 15x and time by 5x due to site hazards like contaminated soil)
   - `rushDecorator` (Multiplies cost by 10x for overtime and halves estimated duration)
   - Demonstrates stacked decorators at runtime.
3. **State Pattern**:
   - `ProjectState` (Abstract State)
   - `ScheduledState` $\to$ `ActiveState` $\to$ `InspectionState` $\to$ `CompletedState`
   - Handles valid and invalid transitions, including a rework loop (`failInspection()` returning to `ActiveState`).
4. **Iterator Pattern**:
   - `ProjectIterator` (Abstract Iterator)
   - `DepthFirstIterator` (Full depth-first traversal across all groups, tasks, and decorated items)
   - `PriorityInspectionIterator` (Priority-sorted snapshot traversal filtering tasks in `InspectionState`)
   - Implements a deliberate **Snapshot Policy** to guarantee traversal consistency during runtime modifications.

---

## 2. Quick Start: Local Build & Execution

### Prerequisites
- GCC/G++ with C++11 support (`g++`)
- GNU Make
- Valgrind

### Compilation
To compile the application using the included Makefile:
```bash
make clean
make
```

### Execution
Run the executable:
```bash
./taskforge
```

### Valgrind Memory Leak Inspection
The application uses strict polymorphic memory management with virtual destructors. Verify zero memory leaks with:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./taskforge
```

---

## 3. Docker Environment

The included `Dockerfile` sets up an Ubuntu 22.04 environment configured with `build-essential`, `g++`, `make`, `gdb`, and `valgrind`.

### Build Docker Image
```bash
docker build -t taskforge:latest .
```

### Run Container
```bash
docker run -it --rm -v $(pwd):/usr/src/taskforge taskforge:latest bash
```
Inside the container, run:
```bash
make clean && make
./taskforge
valgrind --leak-check=full --show-leak-kinds=all ./taskforge
```

---

## 4. GDB Debugging Investigation

To run the application inside GDB:
```bash
gdb ./taskforge
```

Suggested debugging session:
```gdb
(gdb) break main
(gdb) break ProjectTask::setState
(gdb) run
(gdb) next
(gdb) print *sampleTask
(gdb) continue
```

---

## 5. UML Diagram Portfolio (`docs/`)

The `docs/` folder contains diagram definitions in both **PlantUML** (`.puml`) and **Mermaid.js** (in `docs/diagrams.md`):

- **Class Diagram**: [docs/class_diagram.puml](docs/class_diagram.puml)
- **Object Diagram**: [docs/object_diagram.puml](docs/object_diagram.puml)
- **State Diagram**: [docs/state_diagram.puml](docs/state_diagram.puml)
- **Activity Diagram 1 (Traversal Workflow)**: [docs/activity_diagram_1.puml](docs/activity_diagram_1.puml)
- **Activity Diagram 2 (Conditional Lifecycle & Decorator)**: [docs/activity_diagram_2.puml](docs/activity_diagram_2.puml)
- **Activity Diagram 3 (Multi-Phase Domain Workflow with Swimlanes & Fork/Join)**: [docs/activity_diagram_3.puml](docs/activity_diagram_3.puml)

### Importing into Visual Paradigm:
1. Open **Visual Paradigm**.
2. To import PlantUML: Navigate to **Tools $\to$ Code $\to$ Reverse PlantUML...** and select or paste the `.puml` file.
3. Alternatively, copy the Mermaid code from `docs/diagrams.md` into Visual Paradigm's Mermaid diagram editor or the [Mermaid Live Editor](https://mermaid.live).
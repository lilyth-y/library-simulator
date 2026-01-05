# Implementation Details (implements.md)

This document provides a technical overview of the C++ classes and systems implemented in the Library Simulator.

## Data Structures
- **[BookTypes.h](Source/LibrarySimulator/BookTypes.h)**: Defines `FBookData` (Title, CategoryID, Status, Weight, ShelfID) and `EBookStatus` enum.

## Interaction Layer
- **[BookInterface.h](Source/LibrarySimulator/BookInterface.h)**: Standardized interface (`IBookInterface`) for `Pickup`, `CheckStatus`, and `ApplyRepair`.

## Actor Classes
- **[LibraryBook.h](Source/LibrarySimulator/LibraryBook.h)**: The physical book actor.
- **[LibraryCharacter.h](Source/LibrarySimulator/LibraryCharacter.h)**: Handle-based physics interaction and inventory logic.
- **[LibraryPatron.h](Source/LibrarySimulator/LibraryPatron.h)**: NPC character with state management for AI behavior.
- **[LibraryPC.h](Source/LibrarySimulator/LibraryPC.h)**: Logic for the library's searchable database.
- **[LibraryTaskManager.h](Source/LibrarySimulator/LibraryTaskManager.h)**: Global game state and mission lifecycle.

## Components
- **[StackStabilityComponent.h](Source/LibrarySimulator/StackStabilityComponent.h)**: Tick-based overlap analysis to trigger physics "Collapse" events.

## AI Control
- **[PatronAIController.h](Source/LibrarySimulator/PatronAIController.h)**: Integration point for UE5 Behavior Trees to drive patron patterns.

## Logic Flows
Refer to the **[walkthrough.md](walkthrough.md)** for detailed mermaid diagrams and Blueprint setup guides for:
- Physics-based carrying.
- Stack collapse detection.
- Patron "Disorganizer" patterns.
- Task management and Game Over conditions.

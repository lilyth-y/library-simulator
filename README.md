# Library Simulator

A physics-based library management simulator built in Unreal Engine 5 (C++/Blueprint Hybrid).

## Core Gameplay
Players take the role of a librarian managing a chaotic library. You must organize books, assist patrons, and deal with rude "villains" who disorganize the shelves.

## Key Features
- **Physics-Based Stacking**: Realistic book physics and stack stability calculations.
- **Dynamic Interaction**: `PhysicsHandle`-based carrying system for natural movements and collisions.
- **Patron AI**: Antagonistic NPC patterns that disrupt library order.
- **Mission System**: Time-based tasks and a "Buried in Books" failure condition.
- **Library PC**: Integrated searchable database for book metadata and categorization.
- **Noise/Trash Systems**: Ambient noise and mess generation for atmosphere and penalties.
- **Loans & Overdue**: Borrowing flow with due times and overdue tracking.
- **Magic Utilities**: Book locating and auto-shelving hooks for fantasy flair.

## Tech Stack
- **Engine**: Unreal Engine 5.1+
- **Languages**: C++ (Core logic), Blueprints (Visual scripting & UI)
- **Architecture**: Modular ActorComponents and Interfaces.

## Setup
1. Clone the repository into your UE5 project's `Source` directory.
2. Regenerate Visual Studio project files.
3. Compile the project in your IDE.
4. Open the Editor and create Blueprints based on the provided C++ classes.
5. Reference the `walkthrough.md` for specific Blueprint logic implementation.

## Testing
- Follow the manual PIE checklist in `CLOUD.md`.

## Art Direction
- See `asset_style_guide.md` for the chibi cartoon 2.5D side-view style guide.

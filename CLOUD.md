# Manual Testing Checklist (UE5)

## Setup
1. Place this repository inside your UE5 project's `Source` directory.
2. Regenerate project files and build.
3. Create Blueprint subclasses for key C++ classes.
4. Add input actions `Interact` and `Shush` in Project Settings > Input.

## Required Actors in Test Map
- Player: BP derived from `ALibraryCharacter`.
- Books: BP derived from `ALibraryBook`.
- Shelf: BP derived from `ALibraryShelf`.
- Task Manager: BP derived from `ALibraryTaskManager`.
- Library PC: BP derived from `ALibraryPC`.
- Patron: BP derived from `ALibraryPatron` + `APatronAIController`.

## Scenarios
1) Book pickup and release
- Use Interact to pick up a book and drop it.
- Verify physics handle movement and collision behavior.

2) Stack stability
- Stack books until unstable and confirm collapse impulse triggers.

3) Shelf placement
- Place a book on a correct shelf and a wrong shelf.
- Confirm success/failure feedback (log or BP event).

4) PC search and barcode
- Search by exact title and partial title.
- Validate barcode with a correct and incorrect code.

5) Mission flow
- Populate MissionPool and verify mission spawn.
- Confirm mission timer updates and failure when time expires.

6) Game over
- Fill return queue to MaxReturnQueueSize and confirm OnGameOver.

7) Patron shush
- Trigger Shush and confirm patron state/behavior update.

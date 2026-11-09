# Contributing

## Git workflow

1. **Never push directly to `main`.** In GitHub, protect it under *Settings → Branches* so that changes need a pull request and a passing CI.
2. Create a branch for each task, taken from an up-to-date `main`:
   ```bash
   git switch main && git pull
   git switch -c feature/undo-move        # or fix/..., test/..., docs/..., gui/...
   ```
3. Make small commits with clear messages in the imperative mood:
   `Add undo support to Game`, `Fix conflict detection in boxes`.
4. Push and open a **pull request**. Fill in the checklist from the PR template.
5. At least **one other team member reviews** before merging. CI (build + tests) must be green.
6. Use **Squash and merge**, then delete the branch.
7. If `main` moved ahead of your branch, rebase onto it before asking for review: `git pull --rebase origin main`.

Open a GitHub issue for every task and assign it to yourself. Put `Closes #<issue>` in the PR description.

## Architecture rules

- `SudokuGUI` may include **only** headers from `SudokuLogic/include/SudokuLogic/`. Never include anything from `SudokuLogic/src/` in the GUI.
- The GUI holds **no game rules**: no checking of rows, columns or boxes, and no deciding who won. It asks the `IGame` API and reacts to `IGameListener` notifications.
- The API is made of **interfaces (`I...`), enums (`E...`) and constants**. Avoid adding structs and classes to the API. If one is unavoidable, keep it a plain data holder.
- Every new behaviour in the logic needs a **unit test**. A test should fail if the behaviour breaks.
- Use **mocks** (`SudokuTests/mocks/`) to isolate classes: `MockPuzzleGenerator` for deterministic puzzles, `MockGameListener` to verify Observer notifications.
- When the API or the class structure changes, update `docs/uml/ClassDiagram.puml` in the same PR.

## Coding conventions

| Element | Convention | Example |
|---|---|---|
| Interfaces | `I` + PascalCase | `IGame`, `IGameListener` |
| Enums | `E` + PascalCase, `enum class` | `EGameState::InProgress` |
| Classes | PascalCase | `PuzzleGenerator` |
| Methods / functions | PascalCase, verb first | `StartNewGame`, `IsCellGiven` |
| Local variables & parameters | camelCase | `selectedRow`, `cellIndex` |
| Member variables | `m_` + camelCase | `m_board`, `m_listeners` |
| Constants | `k` + PascalCase | `kBoardSize` |
| Files | named after the class they contain | `PuzzleGenerator.h/.cpp` |
| Namespace | `sudoku` (GUI: `sudoku::gui`, tests: `sudoku::test`) | |

- Use `#pragma once` in headers.
- Use full words, not abbreviations: `row` and `column`, not `r`/`c`/`col`.
- Format with **clang-format** (`.clang-format` is in the repo; Visual Studio and CLion pick it up automatically).
- Don't use magic numbers. Use the constants in `BoardConstants.h` or a named `constexpr`.
- Don't copy-paste code. If two places share logic, extract a helper (for example `Game::ApplyMove`, `Board::AnyPeer`).
- Name tests `Scenario` + `ExpectedResult`, for example `CompletingThePuzzleWinsTheGame`.

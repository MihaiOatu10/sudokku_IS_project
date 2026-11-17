# Sudoku — Software Engineering Project (Part 1)

A Sudoku game in C++20, split into three projects as the course requires:

| Project | Type | Purpose |
|---|---|---|
| `SudokuLogic` | static library | Menu flow, game state and puzzle generation. Exposes the **API** (interfaces, enums and constants) in `SudokuLogic/include/SudokuLogic/`. |
| `SudokuGUI` | executable | SFML 3 window. Talks to the logic **only** through `IMenu` and `IGame`, and listens for menu changes through `IMenuListener`. |
| `SudokuTests` | executable | Unit tests written with GoogleTest + GoogleMock. |

**Deadline:** Sunday, 6 December 2026, 23:00 · **Presentation:** Wednesday, 9 December 2026

---

## Requirements checklist

| # | Requirement | Points | Where |
|---|---|---|---|
| 1 | C++ | — | whole repo (C++20) |
| 2 | 3 separate projects (logic, GUI, tests) | 1p | `SudokuLogic/`, `SudokuGUI/`, `SudokuTests/` |
| 2c | Unit tests with GTest + GMock | 2p | `SudokuTests/` (mocks in `SudokuTests/mocks/`: `MockMenuListener`, `MockPuzzleGenerator`) |
| 3 | Logic exposes an API: interfaces, enums, minimal structs | 1p | `IMenu`, `IMenuListener`, `IGame`, `EDifficulty`, `EScreen`, `BoardConstants` |
| 4 | Observer pattern | 2p | `IMenuListener` (observer), `Menu` (subject), `MenuScreen` and `Application` (concrete observers) |
| 5a | Use Case diagram | 1p | not added yet |
| 5b | Class diagram, API coloured differently | 1p | not added yet |
| — | No duplicated code | 0.5p | code reviews |
| — | Descriptive names | 0.5p | see `CONTRIBUTING.md` |
| — | UI contains no game logic | — | `SudokuGUI` only calls `IMenu` and `IGame` and draws what they return |
| — | Good coverage; tests fail when logic breaks | — | see [Code coverage](#code-coverage) |

---

## How to play

1. Start `SudokuGUI`. The main menu shows the levels **Easy**, **Medium**, **Hard** and **Expert**.
2. Pick a level. **Play** stays locked until a level is selected.
3. Press **Play**. A new puzzle is generated for the chosen level, and the game screen shows the level name, the 9×9 board with the given digits and a 1–9 number pad. The number pad does not enter digits yet.

## Puzzle generation

`PuzzleGenerator` first fills an empty board with a randomized backtracking `Solver`. It then removes digits one by one in random order and keeps a removal only if the board still has exactly one solution. It stops when the level's number of given digits is reached: **Easy 40**, **Medium 34**, **Hard 30**, **Expert 26**.

---

## Project structure

```
.
├── Sudoku.sln                      # open this in Visual Studio
├── Sudoku.props                    # settings shared by the 3 projects (C++20, warnings, output folders)
├── SudokuLogic/                    # static library
│   ├── include/SudokuLogic/        #   PUBLIC API - the only headers the GUI may include
│   │   ├── IMenu.h, IMenuListener.h
│   │   ├── IGame.h
│   │   ├── EDifficulty.h, EScreen.h
│   │   └── BoardConstants.h
│   └── src/                        #   internal implementation
│       ├── Menu                    #     IMenu, notifies IMenuListener
│       ├── Game                    #     IGame
│       ├── Board                   #     9x9 grid of values
│       ├── Solver                  #     backtracking: fills a board and counts solutions
│       ├── PuzzleGenerator         #     IPuzzleGenerator, puzzles with a unique solution
│       └── EDifficulty.cpp         #     level names
├── SudokuGUI/                      # SFML 3 window
│   ├── assets/fonts/               #   Fredoka font + its licence
│   └── src/
│       ├── main.cpp
│       ├── Application             #   window, event loop, owns IMenu and IGame
│       ├── Background              #   paper background with doodles
│       ├── MenuScreen              #   level buttons and Play
│       ├── GameScreen              #   level name, board and number pad
│       ├── BoardView               #   board grid and digits
│       ├── NumberPad               #   1-9 buttons
│       ├── Button, TitleText       #   reusable widgets
│       ├── RoundedRectangle.h      #   shape shared by buttons and board
│       └── Theme.h                 #   colours, sizes and layout constants
├── SudokuTests/                    # GoogleTest + GoogleMock unit tests
│   ├── *Tests.cpp                  #   Board, Solver, PuzzleGenerator, Game, Menu, MenuListener, Difficulty, Button
│   ├── mocks/                      #   MockMenuListener, MockPuzzleGenerator
│   └── helpers/                    #   BoardHelpers
├── external/                       # SFML 3.0.1 and GoogleTest 1.15.2, already in the repo
└── .github/                        # CI workflow + PR template
```

---

## Building

### Prerequisites
- **Visual Studio 2022** with the *Desktop development with C++* workload.
- Nothing else. SFML and GoogleTest are already in `external/`.

### Visual Studio 2022
1. Open `Sudoku.sln`.
2. Choose **x64** and **Debug**.
3. Right click `SudokuGUI` → *Set as Startup Project* → press **F5**.
4. Run the unit tests from *Test → Test Explorer → Run All*.

The build output goes to `bin/Debug/` or `bin/Release/`.

### Command line (Developer PowerShell)
```
msbuild Sudoku.sln -p:Configuration=Debug -p:Platform=x64
bin\Debug\SudokuTests.exe
bin\Debug\SudokuGUI.exe
```

### Archive for submission
Zip the repository **without** `bin/`, `obj/` and `.vs/`. `Sudoku.sln` must be inside.

---

## Code coverage

Use [OpenCppCoverage](https://github.com/OpenCppCoverage/OpenCppCoverage):
```
OpenCppCoverage --sources SudokuLogic --export_type html:coverage -- bin\Debug\SudokuTests.exe
```

---

## Team & task split (4 members)

Fill in names and GitHub usernames. Each member writes the unit tests for their own code, and **Member 4** owns overall coverage and quality.

| Member | Area | Initial tasks |
|---|---|---|
| **Member 1** — _name_ | Logic: board & generator | Generator that guarantees a **unique solution** (a solver that counts solutions); difficulty tuning; hint support in `Board` |
| **Member 2** — _name_ | Logic: game flow & API | New API features (restart puzzle, undo, mistake counter, hints) in `IGame` / `Game`; new listener events; keeping the API small and clean |
| **Member 3** — _name_ | GUI | Menu/buttons for difficulty, win screen, highlighting same box/digit, nicer layout, bundled font. **No rules in the GUI.** |
| **Member 4** — _name_ | Tests, UML, quality | GMock tests for new features, coverage reports, keeping `docs/uml/` in sync, reviewing PRs for duplication & naming, presentation |

### Suggested timeline
| Week | Dates | Goal |
|---|---|---|
| 1 | 9 – 15 Nov | Everyone clones, builds and runs; agree on API additions; open GitHub issues for each task |
| 2 | 16 – 22 Nov | Core features: unique-solution generator, restart/undo, GUI menu |
| 3 | 23 – 29 Nov | Remaining features, GUI polish, coverage ≥ 90% on `SudokuLogic` |
| 4 | 30 Nov – 6 Dec | **Feature freeze on 3 Dec**, final UML, bug fixes, rehearse the demo. Submit before **6 Dec 23:00** |

See [`CONTRIBUTING.md`](CONTRIBUTING.md) for the Git workflow and coding conventions.

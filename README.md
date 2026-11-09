# Sudoku — Software Engineering Project (Part 1)

A Sudoku game in C++20, split into three projects as the course requires:

| Project | Type | Purpose |
|---|---|---|
| `SudokuLogic` | static library | Game rules and puzzle generation. Exposes the **API** (interfaces + enums) in `SudokuLogic/include/SudokuLogic/`. |
| `SudokuGUI` | executable | SFML 3 window. Talks to the logic **only** through `IGame` and listens for changes through `IGameListener`. |
| `SudokuTests` | executable | Unit tests written with GoogleTest + GoogleMock. |

**Deadline:** Sunday, 6 December 2026, 23:00 · **Presentation:** Wednesday, 9 December 2026

---

## Requirements checklist

| # | Requirement | Points | Where |
|---|---|---|---|
| 1 | C++ | — | whole repo (C++20) |
| 2 | 3 separate projects (logic, GUI, tests) | 1p | `SudokuLogic/`, `SudokuGUI/`, `SudokuTests/` |
| 2c | Unit tests with GTest + GMock | 2p | `SudokuTests/` (mocks in `SudokuTests/mocks/`) |
| 3 | Logic exposes an API: interfaces, enums, minimal structs | 1p | `IGame`, `IGameListener`, `EDifficulty`, `EGameState`, `EMoveResult`, `BoardConstants` |
| 4 | Observer pattern | 2p | `IGameListener` (observer), `Game` (subject), `SudokuWindow` (concrete observer) |
| 5a | Use Case diagram | 1p | `docs/uml/UseCaseDiagram.puml` |
| 5b | Class diagram, API coloured differently | 1p | `docs/uml/ClassDiagram.puml` |
| — | No duplicated code | 0.5p | code reviews |
| — | Descriptive names | 0.5p | see `CONTRIBUTING.md` |
| — | UI contains no game logic | — | `SudokuGUI` only calls `IGame` |
| — | Good coverage; tests fail when logic breaks | — | see [Code coverage](#code-coverage) |

---

## Project structure

```
.
├── CMakeLists.txt              # root: options + the 3 sub-projects
├── cmake/                      # shared CMake helpers (compiler warnings)
├── SudokuLogic/
│   ├── include/SudokuLogic/    # PUBLIC API - the only headers the GUI may include
│   │   ├── IGame.h             #   main interface + IGame::Produce() factory
│   │   ├── IGameListener.h     #   Observer interface
│   │   ├── EDifficulty.h  EGameState.h  EMoveResult.h
│   │   └── BoardConstants.h
│   └── src/                    # internal implementation
│       ├── Game.*              #   implements IGame, notifies listeners (Observer subject)
│       ├── Board.*             #   9x9 grid + placement rules
│       ├── IPuzzleGenerator.h  #   generator interface (mocked in tests)
│       ├── PuzzleGenerator.*   #   random puzzle generation (backtracking)
│       └── Grid.h              #   type alias for the 9x9 array
├── SudokuGUI/src/
│   ├── main.cpp
│   └── SudokuWindow.*          # SFML window, implements IGameListener
├── SudokuTests/
│   ├── BoardTests.cpp  GameTests.cpp  PuzzleGeneratorTests.cpp
│   ├── TestGrids.h             # known grids shared by the tests
│   └── mocks/                  # GMock mocks: MockGameListener, MockPuzzleGenerator
├── docs/uml/                   # PlantUML diagrams
└── .github/                    # CI workflow + PR template
```

### How the pieces connect

```
SudokuGUI ──uses──▶ IGame (API) ◀──implements── Game ──owns──▶ Board
    │                                            │   └─owns──▶ IPuzzleGenerator ◀── PuzzleGenerator
    └──implements──▶ IGameListener (API) ◀──notifies──┘
```

The GUI calls `IGame::Produce()`, registers itself with `AddListener`, sends player moves (`SetCellValue`, `ClearCell`, `StartNewGame`), and reads the board through the getters. `Game` reports every change through `OnNewGameStarted`, `OnCellChanged` and `OnGameStateChanged`.

---

## Building

### Prerequisites
- **CMake ≥ 3.28**
- A **C++20** compiler: Visual Studio 2022 (17.8+), GCC 12+ or Clang 15+
- **Git** and internet access the first time you configure, because CMake downloads **SFML 3.0.1** and **GoogleTest 1.15.2** through `FetchContent`. Nothing has to be installed by hand.
- Linux only, for SFML:
  `sudo apt install libxrandr-dev libxcursor-dev libxi-dev libudev-dev libfreetype-dev libgl1-mesa-dev libegl1-mesa-dev`

### Visual Studio 2022
1. *File → Open → Folder…* and pick the repo folder (VS detects `CMakeLists.txt`).
2. Wait for "CMake generation finished" (the first time takes a few minutes while SFML downloads).
3. Choose `SudokuGUI.exe` as the startup item and press F5.
4. The tests appear in *Test → Test Explorer*.

### CLion / VS Code (CMake Tools)
Open the folder; both tools pick up the CMake project automatically.

### Command line
```bash
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure     # run the unit tests
./build/bin/SudokuGUI                                     # Windows: build\bin\Debug\SudokuGUI.exe
```

Useful options:

| Option | Default | Effect |
|---|---|---|
| `SUDOKU_BUILD_GUI` | `ON` | Build the SFML GUI (turn off for a fast logic+tests build) |
| `SUDOKU_BUILD_TESTS` | `ON` | Build the unit tests |
| `SUDOKU_ENABLE_COVERAGE` | `OFF` | Add `--coverage` to `SudokuLogic` (GCC/Clang) |

### Font
The GUI uses the first font it finds from: `assets/fonts/main.ttf` (relative to the working directory), Arial or Segoe UI on Windows, DejaVu Sans on Linux. To ship your own font, add `assets/fonts/main.ttf`.

### Controls
Click a cell or use the **arrow keys** to select it · **1–9** fills it · **Delete/Backspace** clears it · **F1 / F2 / F3** starts a new Easy / Medium / Hard game.

---

## Code coverage

**Linux / WSL (gcovr):**
```bash
cmake -S . -B build-coverage -DSUDOKU_BUILD_GUI=OFF -DSUDOKU_ENABLE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build-coverage
ctest --test-dir build-coverage
gcovr -r . --filter SudokuLogic/ --html-details coverage/index.html
```

**Windows:** use [OpenCppCoverage](https://github.com/OpenCppCoverage/OpenCppCoverage):
`OpenCppCoverage --sources SudokuLogic -- build\bin\Debug\SudokuTests.exe`

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

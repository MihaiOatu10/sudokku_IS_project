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
├── Sudoku.sln                  # open this in Visual Studio
├── Sudoku.props                # settings shared by the 3 projects (C++20, warnings, output folders)
├── SudokuLogic/                # static library
│   ├── include/SudokuLogic/    #   PUBLIC API - the only headers the GUI may include
│   └── src/                    #   internal implementation
├── SudokuGUI/                  # SFML 3 window
│   └── src/
├── SudokuTests/                # GoogleTest + GoogleMock unit tests
├── external/                   # SFML 3.0.1 and GoogleTest 1.15.2, already in the repo
└── .github/                    # CI workflow + PR template
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

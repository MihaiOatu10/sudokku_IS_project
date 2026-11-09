cmake_minimum_required(VERSION 3.28)

project(Sudoku
    VERSION 0.1.0
    DESCRIPTION "Sudoku game - Software Engineering project"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Put every executable in one folder so they are easy to find after a build.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(SUDOKU_BUILD_GUI "Build the SFML graphical interface (SudokuGUI)" ON)
option(SUDOKU_BUILD_TESTS "Build the unit tests (SudokuTests)" ON)
option(SUDOKU_ENABLE_COVERAGE "Instrument SudokuLogic for code coverage (GCC/Clang only)" OFF)

include(FetchContent)
include(cmake/CompilerWarnings.cmake)

# The three projects (SudokuLogic, SudokuGUI, SudokuTests) are added here as they are created.

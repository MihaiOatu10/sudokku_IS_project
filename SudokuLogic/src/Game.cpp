#include "Game.h"

#include "PuzzleGenerator.h"
#include "Solver.h"

#include <random>
#include <stdexcept>

namespace sudoku
{

namespace
{
Board Solve(Board puzzle)
{
    if (!Solver().FillBoard(puzzle))
    {
        throw std::invalid_argument("The puzzle has no solution");
    }
    return puzzle;
}

std::size_t GetCellIndex(std::size_t row, std::size_t column)
{
    if (row >= kBoardSize || column >= kBoardSize)
    {
        throw std::out_of_range("The cell is outside the board");
    }
    return row * kBoardSize + column;
}
}

std::unique_ptr<IGame> IGame::Produce(EDifficulty difficulty)
{
    PuzzleGenerator puzzleGenerator(std::random_device{}());
    return std::make_unique<Game>(difficulty, puzzleGenerator);
}

Game::Game(EDifficulty difficulty, IPuzzleGenerator& puzzleGenerator)
    : m_difficulty(difficulty), m_puzzle(puzzleGenerator.Generate(difficulty)), m_solution(Solve(m_puzzle)),
      m_board(m_puzzle)
{
}

EDifficulty Game::GetDifficulty() const
{
    return m_difficulty;
}

int Game::GetCellValue(std::size_t row, std::size_t column) const
{
    return m_board.GetValue(row, column);
}

bool Game::IsCellGiven(std::size_t row, std::size_t column) const
{
    return !m_puzzle.IsEmpty(row, column);
}

ECellState Game::GetCellState(std::size_t row, std::size_t column) const
{
    if (IsCellGiven(row, column))
    {
        return ECellState::Given;
    }
    if (m_board.IsEmpty(row, column))
    {
        return ECellState::Empty;
    }
    return m_board.GetValue(row, column) == m_solution.GetValue(row, column) ? ECellState::Correct
                                                                             : ECellState::Wrong;
}

void Game::SelectCell(std::size_t row, std::size_t column)
{
    m_selectedCellIndex = GetCellIndex(row, column);
}

bool Game::IsCellSelected(std::size_t row, std::size_t column) const
{
    return m_selectedCellIndex == GetCellIndex(row, column);
}

void Game::EnterValue(int value)
{
    if (!m_selectedCellIndex.has_value())
    {
        return;
    }

    const std::size_t row = *m_selectedCellIndex / kBoardSize;
    const std::size_t column = *m_selectedCellIndex % kBoardSize;

    if (CanEnterValue(row, column, value))
    {
        m_board.SetValue(row, column, value);
        UpdateState(row, column);
    }
}

std::size_t Game::GetMistakeCount() const
{
    return m_mistakeCount;
}

EGameState Game::GetState() const
{
    return m_state;
}

bool Game::CanEnterValue(std::size_t row, std::size_t column, int value) const
{
    const ECellState cellState = GetCellState(row, column);
    const bool isLocked = cellState == ECellState::Given || cellState == ECellState::Correct;

    return m_state == EGameState::InProgress && !isLocked && m_board.GetValue(row, column) != value;
}

void Game::UpdateState(std::size_t row, std::size_t column)
{
    if (GetCellState(row, column) == ECellState::Wrong)
    {
        ++m_mistakeCount;
        if (m_mistakeCount >= kMaxMistakes)
        {
            m_state = EGameState::Lost;
        }
    }
    else if (m_board == m_solution)
    {
        m_state = EGameState::Won;
    }
}

}

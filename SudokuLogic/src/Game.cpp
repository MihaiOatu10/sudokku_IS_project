#include "Game.h"

namespace sudoku
{

std::unique_ptr<IGame> IGame::Produce(EDifficulty difficulty)
{
    return std::make_unique<Game>(difficulty, Board{});
}

Game::Game(EDifficulty difficulty, const Board& puzzle) : m_difficulty(difficulty), m_puzzle(puzzle)
{
}

EDifficulty Game::GetDifficulty() const
{
    return m_difficulty;
}

int Game::GetCellValue(std::size_t row, std::size_t column) const
{
    return m_puzzle.GetValue(row, column);
}

bool Game::IsCellGiven(std::size_t row, std::size_t column) const
{
    return !m_puzzle.IsEmpty(row, column);
}

}

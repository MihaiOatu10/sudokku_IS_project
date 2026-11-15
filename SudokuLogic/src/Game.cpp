#include "Game.h"

#include "PuzzleGenerator.h"

#include <random>

namespace sudoku
{

std::unique_ptr<IGame> IGame::Produce(EDifficulty difficulty)
{
    PuzzleGenerator puzzleGenerator(std::random_device{}());
    return std::make_unique<Game>(difficulty, puzzleGenerator);
}

Game::Game(EDifficulty difficulty, IPuzzleGenerator& puzzleGenerator)
    : m_difficulty(difficulty), m_puzzle(puzzleGenerator.Generate(difficulty))
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

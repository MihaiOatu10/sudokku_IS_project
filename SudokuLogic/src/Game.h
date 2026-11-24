#pragma once

#include "Board.h"
#include "IPuzzleGenerator.h"
#include "SudokuLogic/IGame.h"

namespace sudoku
{

class Game : public IGame
{
public:
    Game(EDifficulty difficulty, IPuzzleGenerator& puzzleGenerator);

    EDifficulty GetDifficulty() const override;
    int GetCellValue(std::size_t row, std::size_t column) const override;
    bool IsCellGiven(std::size_t row, std::size_t column) const override;
    ECellState GetCellState(std::size_t row, std::size_t column) const override;

private:
    EDifficulty m_difficulty;
    Board m_puzzle;
    Board m_solution;
};

}

#pragma once

#include "Board.h"
#include "IPuzzleGenerator.h"
#include "SudokuLogic/IGame.h"

#include <optional>

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

    void SelectCell(std::size_t row, std::size_t column) override;
    bool IsCellSelected(std::size_t row, std::size_t column) const override;
    void EnterValue(int value) override;

    std::size_t GetMistakeCount() const override;
    EGameState GetState() const override;

private:
    bool CanEnterValue(std::size_t row, std::size_t column, int value) const;
    void UpdateState(std::size_t row, std::size_t column);

    EDifficulty m_difficulty;
    Board m_puzzle;
    Board m_solution;
    Board m_board;
    std::optional<std::size_t> m_selectedCellIndex;
    std::size_t m_mistakeCount = 0;
    EGameState m_state = EGameState::InProgress;
};

}

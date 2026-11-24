#pragma once

#include "SudokuLogic/BoardConstants.h"
#include "SudokuLogic/ECellState.h"
#include "SudokuLogic/EDifficulty.h"
#include "SudokuLogic/EGameState.h"

#include <cstddef>
#include <memory>

namespace sudoku
{

constexpr std::size_t kMaxMistakes = 3;

class IGame
{
public:
    static std::unique_ptr<IGame> Produce(EDifficulty difficulty);

    virtual ~IGame() = default;

    virtual EDifficulty GetDifficulty() const = 0;
    virtual int GetCellValue(std::size_t row, std::size_t column) const = 0;
    virtual bool IsCellGiven(std::size_t row, std::size_t column) const = 0;
    virtual ECellState GetCellState(std::size_t row, std::size_t column) const = 0;

    virtual void SelectCell(std::size_t row, std::size_t column) = 0;
    virtual bool IsCellSelected(std::size_t row, std::size_t column) const = 0;
    virtual void EnterValue(int value) = 0;

    virtual std::size_t GetMistakeCount() const = 0;
    virtual EGameState GetState() const = 0;
};

}

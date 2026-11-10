#pragma once

#include "SudokuLogic/EDifficulty.h"

#include <memory>
#include <optional>

namespace sudoku
{

class IMenu
{
public:
    static std::unique_ptr<IMenu> Produce();

    virtual ~IMenu() = default;

    virtual void SelectDifficulty(EDifficulty difficulty) = 0;
    virtual std::optional<EDifficulty> GetSelectedDifficulty() const = 0;
    virtual bool IsPlayUnlocked() const = 0;
};

}

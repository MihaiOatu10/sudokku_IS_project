#pragma once

#include "SudokuLogic/EDifficulty.h"

namespace sudoku
{

class IMenuListener
{
public:
    virtual ~IMenuListener() = default;

    virtual void OnDifficultySelected(EDifficulty difficulty) = 0;
    virtual void OnPlayUnlocked() = 0;
};

}

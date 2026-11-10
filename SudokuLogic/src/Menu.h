#pragma once

#include "SudokuLogic/IMenu.h"

namespace sudoku
{

class Menu : public IMenu
{
public:
    void SelectDifficulty(EDifficulty difficulty) override;
    std::optional<EDifficulty> GetSelectedDifficulty() const override;
    bool IsPlayUnlocked() const override;

private:
    std::optional<EDifficulty> m_selectedDifficulty;
};

}

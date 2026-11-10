#include "Menu.h"

namespace sudoku
{

std::unique_ptr<IMenu> IMenu::Produce()
{
    return std::make_unique<Menu>();
}

void Menu::SelectDifficulty(EDifficulty difficulty)
{
    m_selectedDifficulty = difficulty;
}

std::optional<EDifficulty> Menu::GetSelectedDifficulty() const
{
    return m_selectedDifficulty;
}

bool Menu::IsPlayUnlocked() const
{
    return m_selectedDifficulty.has_value();
}

}

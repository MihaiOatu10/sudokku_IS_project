#include "Menu.h"

#include <algorithm>

namespace sudoku
{

std::unique_ptr<IMenu> IMenu::Produce()
{
    return std::make_unique<Menu>();
}

void Menu::AddListener(IMenuListener* listener)
{
    if (listener != nullptr && std::ranges::find(m_listeners, listener) == m_listeners.end())
    {
        m_listeners.push_back(listener);
    }
}

void Menu::RemoveListener(IMenuListener* listener)
{
    std::erase(m_listeners, listener);
}

void Menu::SelectDifficulty(EDifficulty difficulty)
{
    if (m_selectedDifficulty == difficulty)
    {
        return;
    }

    const bool wasPlayUnlocked = IsPlayUnlocked();
    m_selectedDifficulty = difficulty;

    NotifyListeners([difficulty](IMenuListener& listener) { listener.OnDifficultySelected(difficulty); });

    if (!wasPlayUnlocked)
    {
        NotifyListeners([](IMenuListener& listener) { listener.OnPlayUnlocked(); });
    }
}

std::optional<EDifficulty> Menu::GetSelectedDifficulty() const
{
    return m_selectedDifficulty;
}

bool Menu::IsPlayUnlocked() const
{
    return m_selectedDifficulty.has_value();
}

void Menu::NotifyListeners(const std::function<void(IMenuListener&)>& notification)
{
    for (IMenuListener* listener : m_listeners)
    {
        notification(*listener);
    }
}

}

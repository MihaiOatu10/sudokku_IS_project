#pragma once

#include "SudokuLogic/IMenu.h"

#include <functional>
#include <vector>

namespace sudoku
{

class Menu : public IMenu
{
public:
    void AddListener(IMenuListener* listener) override;
    void RemoveListener(IMenuListener* listener) override;

    void SelectDifficulty(EDifficulty difficulty) override;
    std::optional<EDifficulty> GetSelectedDifficulty() const override;
    bool IsPlayUnlocked() const override;

    void Play() override;
    EScreen GetCurrentScreen() const override;

private:
    void NotifyListeners(const std::function<void(IMenuListener&)>& notification);

    std::vector<IMenuListener*> m_listeners;
    std::optional<EDifficulty> m_selectedDifficulty;
    EScreen m_currentScreen = EScreen::MainMenu;
};

}

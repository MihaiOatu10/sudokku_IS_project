#pragma once

#include "SudokuLogic/EDifficulty.h"
#include "SudokuLogic/EScreen.h"
#include "SudokuLogic/IMenuListener.h"

#include <memory>
#include <optional>

namespace sudoku
{

class IMenu
{
public:
    static std::unique_ptr<IMenu> Produce();

    virtual ~IMenu() = default;

    virtual void AddListener(IMenuListener* listener) = 0;
    virtual void RemoveListener(IMenuListener* listener) = 0;

    virtual void SelectDifficulty(EDifficulty difficulty) = 0;
    virtual std::optional<EDifficulty> GetSelectedDifficulty() const = 0;
    virtual bool IsPlayUnlocked() const = 0;

    virtual void Play() = 0;
    virtual EScreen GetCurrentScreen() const = 0;
};

}

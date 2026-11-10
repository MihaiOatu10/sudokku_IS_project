#pragma once

#include "SudokuLogic/IMenuListener.h"

#include <gmock/gmock.h>

namespace sudoku::test
{

class MockMenuListener : public IMenuListener
{
public:
    MOCK_METHOD(void, OnDifficultySelected, (EDifficulty difficulty), (override));
    MOCK_METHOD(void, OnPlayUnlocked, (), (override));
    MOCK_METHOD(void, OnScreenChanged, (EScreen screen), (override));
};

}

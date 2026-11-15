#pragma once

#include "IPuzzleGenerator.h"

#include <gmock/gmock.h>

namespace sudoku::test
{

class MockPuzzleGenerator : public IPuzzleGenerator
{
public:
    MOCK_METHOD(Board, Generate, (EDifficulty difficulty), (override));
};

}

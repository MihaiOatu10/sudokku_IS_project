#pragma once

#include "Game.h"
#include "mocks/MockPuzzleGenerator.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

namespace sudoku::test
{

class GameCreationTests : public ::testing::Test
{
protected:
    static constexpr EDifficulty kDifficulty = EDifficulty::Hard;

    std::unique_ptr<IGame> CreateGame(const Board& puzzle)
    {
        EXPECT_CALL(m_generator, Generate(kDifficulty)).Times(1).WillOnce(::testing::Return(puzzle));
        return std::make_unique<Game>(kDifficulty, m_generator);
    }

    ::testing::StrictMock<MockPuzzleGenerator> m_generator;
};

}

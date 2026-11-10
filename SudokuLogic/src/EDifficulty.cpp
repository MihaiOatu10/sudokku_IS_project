#include "SudokuLogic/EDifficulty.h"

#include <cstddef>

namespace sudoku
{

namespace
{
constexpr std::array<std::string_view, kAllDifficulties.size()> kDifficultyNames{"Easy", "Medium", "Hard", "Expert"};
}

std::string_view GetDifficultyName(EDifficulty difficulty)
{
    return kDifficultyNames[static_cast<std::size_t>(difficulty)];
}

}

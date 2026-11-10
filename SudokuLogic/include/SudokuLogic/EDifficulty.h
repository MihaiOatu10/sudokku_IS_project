#pragma once

#include <array>
#include <string_view>

namespace sudoku
{

enum class EDifficulty
{
    Easy,
    Medium,
    Hard,
    Expert
};

constexpr std::array kAllDifficulties{EDifficulty::Easy, EDifficulty::Medium, EDifficulty::Hard, EDifficulty::Expert};

std::string_view GetDifficultyName(EDifficulty difficulty);

}

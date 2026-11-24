#pragma once

#include "BoardView.h"
#include "EndPanel.h"
#include "NumberPad.h"
#include "TitleText.h"

#include "SudokuLogic/IGame.h"
#include "SudokuLogic/IMenu.h"

#include <SFML/Graphics.hpp>

namespace sudoku::gui
{
class GameScreen
{
  public:
    GameScreen(IMenu& menu, const sf::Font& font);

    void Draw(sf::RenderTarget& target, const IGame& game) const;
    void HandleMouseMove(sf::Vector2f mousePosition, const IGame& game);
    void HandleClick(sf::Vector2f mousePosition, IGame& game);

  private:
    sf::Vector2f GetBoardTopLeft() const;
    sf::Vector2f GetNumberPadTopLeft() const;
    void DrawDifficultyTitle(sf::RenderTarget& target, const IGame& game) const;
    void DrawMistakes(sf::RenderTarget& target, const IGame& game) const;
    void HandleBoardClick(sf::Vector2f mousePosition, IGame& game);
    void HandleEndPanelClick(sf::Vector2f mousePosition);

    IMenu& m_menu;
    const sf::Font& m_font;
    BoardView m_boardView;
    NumberPad m_numberPad;
    TitleText m_title;
    EndPanel m_endPanel;
};
} 

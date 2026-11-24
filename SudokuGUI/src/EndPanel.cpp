#include "EndPanel.h"

#include "RoundedRectangle.h"
#include "Theme.h"

#include <string>

namespace sudoku::gui
{
namespace
{
constexpr sf::Vector2f kPanelCenter{static_cast<float>(kWindowWidth) / kHalf,
                                    static_cast<float>(kWindowHeight) / kHalf};

std::string_view GetEndMessage(EGameState state)
{
    switch (state)
    {
    case EGameState::Won:
        return kWinMessage;
    case EGameState::Lost:
    default:
        return kLoseMessage;
    }
}
}

EndPanel::EndPanel(const sf::Font& font)
    : m_font(font), m_panel(CreateRoundedRectangle({kEndPanelWidth, kEndPanelHeight}, kEndPanelCornerRadius)),
      m_menuButton(font, std::string(kMenuButtonLabel), kPanelCenter + sf::Vector2f(0.f, kMenuButtonOffsetY),
                   {kMenuButtonWidth, kMenuButtonHeight})
{
    m_panel.setPosition(kPanelCenter);
    m_panel.setFillColor(kEndPanelColor);
    m_panel.setOutlineColor(kInkColor);
    m_panel.setOutlineThickness(kButtonOutlineThickness);
}

void EndPanel::HandleMouseMove(sf::Vector2f mousePosition)
{
    m_menuButton.UpdateHover(mousePosition);
}

bool EndPanel::IsMenuClicked(sf::Vector2f position) const
{
    return m_menuButton.Contains(position);
}

void EndPanel::Draw(sf::RenderTarget& target, EGameState state) const
{
    target.draw(m_panel);
    DrawMessage(target, GetEndMessage(state));
    m_menuButton.Draw(target);
}

void EndPanel::DrawMessage(sf::RenderTarget& target, std::string_view message) const
{
    sf::Text text(m_font, std::string(message), kEndMessageFontSize);
    text.setFillColor(kInkColor);
    text.setStyle(sf::Text::Bold);
    text.setOrigin(text.getLocalBounds().getCenter());
    text.setPosition(kPanelCenter + sf::Vector2f(0.f, kEndMessageOffsetY));
    target.draw(text);
}
}

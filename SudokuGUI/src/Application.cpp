#include "Application.h"

#include "Theme.h"

#include <SFML/Window/Event.hpp>

#include <optional>
#include <stdexcept>
#include <string>

namespace sudoku::gui
{
namespace
{
sf::Font LoadFont()
{
    sf::Font font;
    if (!font.openFromFile(std::string(kFontPath)))
    {
        throw std::runtime_error("Could not load the font from " + std::string(kFontPath));
    }
    return font;
}
} 

Application::Application()
    : m_window(sf::VideoMode({kWindowWidth, kWindowHeight}), std::string(kWindowTitle),
               sf::Style::Titlebar | sf::Style::Close),
      m_font(LoadFont()),
      m_background(sf::Vector2f(static_cast<float>(kWindowWidth), static_cast<float>(kWindowHeight)), m_font),
      m_menu(IMenu::Produce()), m_menuScreen(*m_menu, m_font), m_currentScreen(m_menu->GetCurrentScreen()),
      m_gameScreen(m_font)
{
    m_window.setFramerateLimit(kFrameRateLimit);
    m_menu->AddListener(this);
}

Application::~Application()
{
    m_menu->RemoveListener(this);
}

void Application::Run()
{
    while (m_window.isOpen())
    {
        ProcessEvents();
        Render();
    }
}

void Application::OnDifficultySelected(EDifficulty) {}

void Application::OnPlayUnlocked() {}

void Application::OnScreenChanged(EScreen screen)
{
    m_currentScreen = screen;
    if (IsGameShown())
    {
        StartGame();
    }
}

void Application::ProcessEvents()
{
    while (const std::optional<sf::Event> event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
        }
        else
        {
            HandleEvent(*event);
        }
    }
}

void Application::HandleEvent(const sf::Event& event)
{
    if (const auto* mouseMove = event.getIf<sf::Event::MouseMoved>())
    {
        HandleMouseMove(m_window.mapPixelToCoords(mouseMove->position));
    }
    else if (const auto* mouseButton = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseButton->button == sf::Mouse::Button::Left)
        {
            HandleClick(m_window.mapPixelToCoords(mouseButton->position));
        }
    }
}

void Application::HandleMouseMove(sf::Vector2f mousePosition)
{
    if (IsMainMenuShown())
    {
        m_menuScreen.HandleMouseMove(mousePosition);
    }
    else if (IsGameShown())
    {
        m_gameScreen.HandleMouseMove(mousePosition);
    }
}

void Application::HandleClick(sf::Vector2f mousePosition)
{
    if (IsMainMenuShown())
    {
        m_menuScreen.HandleClick(mousePosition);
    }
    else if (IsGameShown())
    {
        m_gameScreen.HandleClick(mousePosition);
    }
}

void Application::Render()
{
    m_window.clear();
    m_background.Draw(m_window);
    if (IsMainMenuShown())
    {
        m_menuScreen.Draw(m_window);
    }
    else if (IsGameShown())
    {
        m_gameScreen.Draw(m_window);
    }
    m_window.display();
}

bool Application::IsMainMenuShown() const
{
    return m_currentScreen == EScreen::MainMenu;
}

bool Application::IsGameShown() const
{
    return m_currentScreen == EScreen::Game;
}

void Application::StartGame()
{
    m_game = IGame::Produce(*m_menu->GetSelectedDifficulty());
    m_gameScreen.ShowGame(*m_game);
}
}

#include "Application.h"
#include "Theme.h"
#include <SFML/Window/Event.hpp>
#include <stdexcept>
#include <string>

namespace sudoku::gui
{
namespace
{
constexpr unsigned kFrameRateLimit = 60;

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
    : m_window(sf::VideoMode({kWindowWidth, kWindowHeight}), "Sudoku"), m_font(LoadFont()),
      m_background(sf::Vector2f(static_cast<float>(kWindowWidth), static_cast<float>(kWindowHeight)), m_font),
      m_menu(IMenu::Produce()), m_menuScreen(*m_menu, m_font), m_currentScreen(m_menu->GetCurrentScreen())
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

void Application::OnDifficultySelected(EDifficulty difficulty) {}

void Application::OnPlayUnlocked() {}

void Application::OnScreenChanged(EScreen screen)
{
    m_currentScreen = screen;
}

void Application::ProcessEvents()
{
    while (const std::optional<sf::Event> event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
        }
        else if (const auto* mouseMove = event->getIf<sf::Event::MouseMoved>())
        {
            HandleMouseMoved(m_window.mapPixelToCoords(mouseMove->position));
        }
        else if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseButton->button == sf::Mouse::Button::Left)
            {
                HandleMouseButtonPressed(m_window.mapPixelToCoords(mouseButton->position));
            }
        }
    }
}

void Application::HandleMouseMoved(sf::Vector2f mousePosition)
{
    if (m_currentScreen == EScreen::MainMenu)
    {
        m_menuScreen.HandleMouseMove(mousePosition);
    }
}

void Application::HandleMouseButtonPressed(sf::Vector2f mousePosition)
{
    if (m_currentScreen == EScreen::MainMenu)
    {
        m_menuScreen.HandleClick(mousePosition);
    }
}

void Application::Render()
{
    m_window.clear();
    m_background.Draw(m_window);
    if (m_currentScreen == EScreen::MainMenu)
    {
        m_menuScreen.Draw(m_window);
    }
    m_window.display();
}
} 

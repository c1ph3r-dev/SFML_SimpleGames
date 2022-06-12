#include "SwagBall.h"

void SwagBall::InitShape(const sf::RenderWindow& window)
{
    m_Shape.setRadius(static_cast<float>(rand() % 10 + 10));
    const sf::Color color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
    
    switch (m_Type)
    {
    case DEFAULT:
        m_Shape.setFillColor(color);
        break;
    case DAMAGING:
        m_Shape.setFillColor(sf::Color::Red);
        m_Shape.setOutlineColor(sf::Color::White);
        m_Shape.setOutlineThickness(2.f);
        break;
    case HEALING:
        m_Shape.setFillColor(sf::Color::Green);
        m_Shape.setOutlineColor(sf::Color::White);
        m_Shape.setOutlineThickness(2.f);
        break;
    }
    
    m_Shape.setPosition(
        sf::Vector2f(
            static_cast<float>((rand() % window.getSize().x + m_Shape.getRadius())- m_Shape.getGlobalBounds().width),
            static_cast<float>((rand() % window.getSize().y + m_Shape.getRadius()) - m_Shape.getGlobalBounds().height)
            ));
}

SwagBall::SwagBall(const sf::RenderWindow& window, const int& type) :
    m_Type(type)
{
    InitShape(window);
}


void SwagBall::Render(sf::RenderTarget& target) const
{
    target.draw(m_Shape);
}

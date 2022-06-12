#include "Player.h"

void Player::InitVariables(const int& health)
{
    m_MovementSpeed = 10.f;
    m_HealthMax = health;
    m_Health = m_HealthMax;
}

void Player::InitShape(const float& x, const float& y)
{
    m_Shape.setPosition(x, y);
    m_Shape.setFillColor(sf::Color::Green);
    m_Shape.setSize(sf::Vector2f(50.f, 50.f));
}

Player::Player(const int& health, const float& x, const float& y)
{
    InitVariables(health);
    InitShape(x, y);
}

void Player::UpdateInput()
{
    // Keyboard input
    // Left
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
            m_Shape.move(-m_MovementSpeed, 0.f);
    }
    // Right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
            m_Shape.move(m_MovementSpeed, 0.f);
    }
    // Up
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
            m_Shape.move(0.f, -m_MovementSpeed);
    }
    // Down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
            m_Shape.move(0.f, m_MovementSpeed);
    }
    
}

void Player::UpdateWindowBoundsCollision(const sf::RenderTarget* target)
{
    // Left
    if(m_Shape.getGlobalBounds().left <= 0.f)
        m_Shape.setPosition(0.f, m_Shape.getGlobalBounds().top);
    // Right
    else if(m_Shape.getGlobalBounds().left + m_Shape.getGlobalBounds().width >= target->getSize().x)
        m_Shape.setPosition(target->getSize().x - m_Shape.getGlobalBounds().width, m_Shape.getGlobalBounds().top);
    // Top
    if(m_Shape.getGlobalBounds().top <= 0.f)
        m_Shape.setPosition(m_Shape.getGlobalBounds().left, 0.f);
    // Bottom
    else if(m_Shape.getGlobalBounds().top + m_Shape.getGlobalBounds().height >= target->getSize().y)
        m_Shape.setPosition(m_Shape.getGlobalBounds().left, target->getSize().y - m_Shape.getGlobalBounds().height);
}

void Player::UpdateHealth(const int& amount)
{
    if (amount == 0) return;
    
    if (amount < 0)
    {
        if(m_Health > 0)
            m_Health += amount;
        if(m_Health < 0)
            m_Health = 0;
    }
    else
    {
        if(m_Health < m_HealthMax)
            m_Health += amount;
        if(m_Health > m_HealthMax)
            m_Health = m_HealthMax;
    }
}

void Player::Update(const sf::RenderTarget* target)
{
    UpdateInput();

    // Window bounds collision
    UpdateWindowBoundsCollision(target);
}

void Player::Render(sf::RenderTarget* target)
{
    target->draw(m_Shape);
}

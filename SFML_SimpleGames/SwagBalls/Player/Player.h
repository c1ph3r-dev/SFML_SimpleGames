#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player
{
private:
    sf::RectangleShape m_Shape;

    float m_MovementSpeed;
    int m_Health;
    int m_HealthMax;

    void InitVariables(const int& health);
    void InitShape(const float& x, const float& y);
    void UpdateInput();
    void UpdateWindowBoundsCollision(const sf::RenderTarget* target);
public:
    explicit Player(const int& health = 10, const float& x = 0.f, const float& y = 0.f);

    // Accessors
    inline sf::RectangleShape GetShape() const { return m_Shape; }
    inline int GetHealth() const { return m_Health; }
    inline int GetMaxHealth() const { return m_HealthMax; }

    // Functions
    void UpdateHealth(const int& amount);
    
    void Update(const sf::RenderTarget* target);
    void Render(sf::RenderTarget* target);
};

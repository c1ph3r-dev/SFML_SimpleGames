#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
private:
    sf::CircleShape m_Shape;
    int m_Type;
    int m_Health;
    int m_HealthMax;
    int m_Damage;
    int m_Points;

    void InitShape(const float pos_x, const float pos_y);
    void InitVariables();
public:
    Enemy(const float pos_x, const float pos_y);
    ~Enemy() = default;

    // Functions
    void Update();
    void Render(sf::RenderTarget& target);
};

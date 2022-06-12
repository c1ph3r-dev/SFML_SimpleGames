#include "Enemy.h"

void Enemy::InitShape(const float pos_x, const float pos_y)
{
    m_Shape.setPosition(pos_x, pos_y);
    m_Shape.setRadius(static_cast<float>(rand() % 20 + 20));
    m_Shape.setPointCount(rand() % 100 + 3);
    m_Shape.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
}

void Enemy::InitVariables()
{
    m_Type = 0;
    m_HealthMax = 10;
    m_Health = 0;
    m_Damage = 1;
    m_Points = 5;
}

Enemy::Enemy(const float pos_x, const float pos_y)
{
    InitShape(pos_x, pos_y);
    InitVariables();
}

void Enemy::Update()
{
}

void Enemy::Render(sf::RenderTarget& target)
{
    target.draw(m_Shape);
}

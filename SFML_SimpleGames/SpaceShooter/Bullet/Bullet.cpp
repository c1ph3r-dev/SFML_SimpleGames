#include "Bullet.h"
#include "../../Engine/Engine.h"

Bullet::Bullet(sf::Texture* texture, const float pos_x, const float pos_y, const float dir_x, const float dir_y, const float movement_speed)
{
    m_Sprite.setTexture(*texture);
    m_Sprite.scale(0.95f, 0.95f);
    m_Sprite.setPosition(pos_x, pos_y);
    
    m_Direction.x = dir_x;
    m_Direction.y = dir_y;
    m_MovementSpeed = movement_speed;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
    m_Sprite.move(m_MovementSpeed * m_Direction);  
}

void Bullet::Render(sf::RenderTarget& target)
{
    target.draw(m_Sprite);
}


#pragma once
#include "../../Engine/SFML.h"

class Bullet
{
private:
    sf::Sprite m_Sprite;

    sf::Vector2f m_Direction;
    float m_MovementSpeed;
    
public:
    Bullet(sf::Texture* texture, const float pos_x, const float pos_y, const float dir_x, const float dir_y, const float movement_speed);
    virtual ~Bullet();

    // Accessor
    inline const sf::FloatRect GetBounds() const { return m_Sprite.getGlobalBounds(); }

    void Update();
    void Render(sf::RenderTarget& target);
};

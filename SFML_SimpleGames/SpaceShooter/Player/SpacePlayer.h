#pragma once

#include "../../Engine/SFML.h"

class SpacePlayer
{
private:
    sf::Sprite m_Sprite;
    sf::Texture m_Texture;

    float m_MovementSpeed;

    float m_AttackCooldown;
    float m_AttackCooldownMax;

    // Private Functions
    void InitVariables();
    void InitTexture();
    void InitSprite();
public:
    SpacePlayer();
    virtual ~SpacePlayer();

    // Functions
    void Move(const float dir_x, const float dir_y);
    bool CanAttack();

    // Accessor
    inline const sf::Vector2f& GetPos() const { return m_Sprite.getPosition(); }

    // Functions
    void UpdateAttack();
    void Update();
    void Render(sf::RenderTarget& target);
    
};

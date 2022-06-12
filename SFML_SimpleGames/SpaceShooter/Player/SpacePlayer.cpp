#include "SpacePlayer.h"
#include "../../Engine/Engine.h"

void SpacePlayer::InitVariables()
{
    m_MovementSpeed = 2.5f;
    m_AttackCooldownMax = 20.f;
    m_AttackCooldown = m_AttackCooldownMax;
}

void SpacePlayer::InitTexture()
{
    if(!m_Texture.loadFromFile("Textures/ship.png"))
    {
        LOG("Failed to Load Texture ship.png")
        throw std::runtime_error("Failed to Load Texture ship.png");
    }
}

void SpacePlayer::InitSprite()
{
    // Set texture
    m_Sprite.setTexture(m_Texture);

    // Resize sprite
    m_Sprite.scale(0.175f, 0.175f);
}

SpacePlayer::SpacePlayer()
{
    InitVariables();
    
    try
    {
        InitTexture();
    }
    catch (std::runtime_error& e)
    {
        throw e;
    }
    
    InitSprite();
}

SpacePlayer::~SpacePlayer()
{
}

void SpacePlayer::Move(const float dir_x, const float dir_y)
{
    m_Sprite.move(m_MovementSpeed * dir_x, m_MovementSpeed * dir_y);
}

bool SpacePlayer::CanAttack()
{
    if(m_AttackCooldown >= m_AttackCooldownMax)
    {
        m_AttackCooldown = 0.f;
        return true;
    }
    return false;
}

void SpacePlayer::UpdateAttack()
{
    if(m_AttackCooldown < m_AttackCooldownMax)
        m_AttackCooldown += 1.f;
}

void SpacePlayer::Update()
{
    UpdateAttack();
}

void SpacePlayer::Render(sf::RenderTarget& target)
{
    target.draw(m_Sprite);
}

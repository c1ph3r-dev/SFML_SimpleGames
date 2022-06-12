#pragma once
#include <map>

#include "../Engine/Engine.h"
#include "Bullet/Bullet.h"
#include "Player/SpacePlayer.h"
#include "Enemy/Enemy.h"

class SpaceShooter final : public Engine
{
private:
    SpacePlayer* m_Player;

    Enemy* m_Enemy;

    // Resources
    std::map<std::string, sf::Texture*> m_Textures;
    std::vector<Bullet*> m_Bullets;

    void InitPlayer();
    void InitTextures();
    void UpdateInput();
    void UpdateBullets();
public:
    // Constructor
    SpaceShooter();
    ~SpaceShooter();
    
protected:
    // Overriden Functions
    //void InitVariables() override;
    void InitVariables() override;
    void Update() override;
    void DrawGame() override;
    void PollEvents() override;
};

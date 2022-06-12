#pragma once

#include "../Engine/Engine.h"
#include <vector>

class BlockClicker final : public Engine
{
private:
    EDifficulty m_Difficulty;
    
    // Game Objects
    std::vector<sf::RectangleShape> m_Enemies;
    sf::RectangleShape m_Enemy;

    // Text
    sf::Text m_UiText;

    // Game Logic
    unsigned m_Points;
    int m_Health;
    float m_EnemySpawnTimer;
    float m_EnemySpawnTimerMax;
    int m_MaxEnemies;
    bool bMouseHeld;
    
    // Private Functions
    void InitVariables(const EDifficulty difficulty);
    void InitText();
    void InitEnemies();
    void SpawnEnemy();
    void UpdateEnemies();
    void RenderEnemies(sf::RenderTarget& target) const;
    void UpdateText();
    void RenderText(sf::RenderTarget& target) const;
protected:
    void Update() override;
    void DrawGame() override;
    void PollEvents() override;
    
public:
    explicit BlockClicker(const EDifficulty difficulty = EDifficulty::Normal);
    
};

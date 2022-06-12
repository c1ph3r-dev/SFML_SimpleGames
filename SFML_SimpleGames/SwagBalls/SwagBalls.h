#pragma once
#include "../Engine/Engine.h"
#include "Player/Player.h"
#include "SwagBall/SwagBall.h"

#include <vector>

class SwagBalls final : public Engine
{
private:
    // Variables
    Player m_Player;

    std::vector<SwagBall> m_SwagBalls;
    float m_SpawnTimerMax{};
    float m_SpawnTimer{};
    int m_MaxSwagBalls{};

    int m_Points{};

    sf::Text m_Text;
    sf::Text m_EndGameText;

    // Private Functions
    void SpawnSwagBalls();
    int RandomizeType() const;
    void UpdatePlayer();
    void UpdateCollision();
    void InitText();
    void UpdateGui();
    void RenderGui(sf::RenderTarget* target) const;
public:
    // Constructor
    SwagBalls();

protected:
    // Overriden Functions
    void InitVariables() override;
    void Update() override;
    void DrawGame() override;
    void PollEvents() override;
    
};

#pragma once
#include <SFML/Graphics.hpp>

enum class EGame : uint8_t
{
    BlockClicker,
    SwagBalls,
    SpaceShooter,

    DefaultMAX
};

class Launcher
{
private:
    sf::RenderWindow* m_Window;
    sf::Event m_Event;

    sf::Sprite m_Buttons[3];
    sf::Texture m_Textures[3];

    int m_Game = -1;

    void InitButtons();
    void InitWindow();

    void PollEvents();

    void Update();
    void Render();
public:
    Launcher();
    ~Launcher();

    void Run(EGame& game);
};

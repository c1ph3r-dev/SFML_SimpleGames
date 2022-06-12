#include "Launcher.h"

void Launcher::InitButtons()
{
    m_Textures[0].loadFromFile("Engine/Textures/BlockClicker.png");
    m_Textures[1].loadFromFile("Engine/Textures/SwagBalls.png");
    m_Textures[2].loadFromFile("Engine/Textures/SpaceShooter.png");
    for(size_t i = 0; i < 3; i++)
    {
        m_Buttons[i].setTexture(m_Textures[i]);
    }

    m_Buttons[0].setPosition(25.f, 25.f);
    m_Buttons[1].setPosition(25.f, 150.f);
    m_Buttons[2].setPosition(25.f, 275.f);
}

void Launcher::InitWindow()
{
    sf::VideoMode VideoMode;
    VideoMode.width = 800;
    VideoMode.height = 600;

    sf::ContextSettings Settings;
    Settings.antialiasingLevel = 16;

    m_Window = new sf::RenderWindow(VideoMode, "Launcher", sf::Style::Close | sf::Style::Titlebar, Settings);
    m_Window->setFramerateLimit(144);
    m_Window->setVerticalSyncEnabled(false);
}

void Launcher::PollEvents()
{
    int count = 0;
    // Event polling
    while (m_Window->pollEvent(m_Event))
    {
        switch (m_Event.type)
        {
        case sf::Event::Closed:
            m_Window->close();
            break;
        case sf::Event::KeyPressed:
            if(m_Event.key.code == sf::Keyboard::Escape)
                m_Window->close();
            break;
        case sf::Event::MouseButtonPressed:
            const sf::Vector2i mousePos = sf::Mouse::getPosition( *m_Window );
            sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
            for (const auto& i : m_Buttons)
            {
                if(i.getGlobalBounds().contains(mousePosF))
                {
                    m_Game = count;
                    break;
                }
                ++count;
            }
            break;
        }
    }
}

void Launcher::Update()
{
    PollEvents();
}

void Launcher::Render()
{
    m_Window->clear();

    /*
    for (const auto& i : m_Buttons)
    {
        m_Window->draw(i);
    }
    for (const auto& i : m_Texts)
    {
        m_Window->draw(i);
    }
    */

    for (const auto& i : m_Buttons)
        m_Window->draw(i);
    
    m_Window->display();
}

Launcher::Launcher()
{
    InitButtons();
    InitWindow();
}

Launcher::~Launcher()
{
    delete m_Window;
}

void Launcher::Run(EGame& game)
{
    while (m_Window->isOpen())
    {
        Update();

        Render();

        if(m_Game != -1)
        {
            switch (m_Game)
            {
            case 0:
                game = EGame::BlockClicker;
                break;
            case 1:
                game = EGame::SwagBalls;
                break;
            case 2:
                game = EGame::SpaceShooter;
                break;
            }

            m_Window->close();
        }
        else
        {
            game = EGame::DefaultMAX;
        }
        
    }
}

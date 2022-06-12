#include "SpaceShooter.h"

void SpaceShooter::InitPlayer()
{
    try
    {
        m_Player = new SpacePlayer{};
    }
    catch (std::runtime_error)
    {
        LOG_EXT("Warning", "GAME::PLAYER", "Failed to Load Texture ship.png")
    }

    m_Enemy = new Enemy{20.f, 20.f};
}

void SpaceShooter::InitTextures()
{
    m_Textures["BULLET"] = new sf::Texture();
    
    if(!m_Textures["BULLET"]->loadFromFile("Textures/bullet.png"))
        LOG_EXT("Warning", "GAME", "Failed to Load Texture bullet.png")
}

void SpaceShooter::UpdateInput()
{
    float x = 0, y = 0;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        x += -1.f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        x += 1.f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        y += -1.f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        y += 1.f;
    
    m_Player->Move(x, y);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_Player->CanAttack())
    {
        m_Bullets.push_back(new Bullet(m_Textures["BULLET"], m_Player->GetPos().x, m_Player->GetPos().y, 0.f, -1.f, 3.f));
    }
        
}

void SpaceShooter::UpdateBullets()
{
    unsigned counter = 0;
    for (auto *bullet : m_Bullets)
    {
        bullet->Update();

        // Bullet culling (top of screen)
        if(bullet->GetBounds().top + bullet->GetBounds().height < 0.f)
        {
            // Delete Bullet
            delete m_Bullets.at(counter);
            m_Bullets.erase(m_Bullets.begin() + counter);
            --counter;
        }

        ++counter;
    }
}

SpaceShooter::SpaceShooter()
{
    EngineSettings Settings;
    Settings.GameName = "SpaceShooter";
    Settings.FramerateLimit = 144;
    InitEngine(Settings);

    InitTextures();
    InitPlayer();
}

SpaceShooter::~SpaceShooter()
{
    delete m_Player;

    for(auto &i: m_Textures)
    {
        delete i.second;
    }

    for(auto *i : m_Bullets)
    {
        delete i;
    }
}

void SpaceShooter::InitVariables()
{
    Engine::InitVariables();
}

void SpaceShooter::Update()
{
    Engine::Update();

    UpdateInput();

    m_Player->Update();
    UpdateBullets();
    m_Enemy->Update();
    
}

void SpaceShooter::DrawGame()
{
    m_Player->Render(*GetWindow());
    m_Enemy->Render(*GetWindow());

    for (auto *bullet : m_Bullets)
    {
        bullet->Render(*GetWindow());
    }
}

void SpaceShooter::PollEvents()
{
    // Event polling
    while (GetWindow()->pollEvent(Event))
    {
        switch (Event.type)
        {
        case sf::Event::Closed:
            GetWindow()->close();
            break;
        case sf::Event::KeyPressed:
            if(Event.key.code == sf::Keyboard::Escape)
                GetWindow()->close();
            break;
        default:
            break;
        }
    }
}

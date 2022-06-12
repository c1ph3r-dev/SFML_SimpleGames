#include "BlockClicker.h"
#include <string>

void BlockClicker::InitVariables(const EDifficulty difficulty)
{
    InitText();
    switch (difficulty)
    {
    case EDifficulty::DefaultMAX:
    case EDifficulty::Normal:
        m_EnemySpawnTimerMax = 20.f;
        m_EnemySpawnTimer = m_EnemySpawnTimerMax;
        m_MaxEnemies = 5;
        m_Health = 10;
        break;
    case EDifficulty::Easy:
        m_EnemySpawnTimerMax = 30.f;
        m_EnemySpawnTimer = m_EnemySpawnTimerMax;
        m_MaxEnemies = 5;
        m_Health = 20;
        break;
    case EDifficulty::Hard:
        m_EnemySpawnTimerMax = 20.f;
        m_EnemySpawnTimer = m_EnemySpawnTimerMax;
        m_MaxEnemies = 10;
        m_Health = 10;
        break;
    case EDifficulty::Insane:
        m_EnemySpawnTimerMax = 10.f;
        m_EnemySpawnTimer = m_EnemySpawnTimerMax;
        m_MaxEnemies = 15;
        m_Health = 5;
        break;
    }
    m_Points = 0;
    bMouseHeld = false;

    InitEnemies();
}

void BlockClicker::InitText()
{
    m_UiText.setFont(m_Font_ka1);
    m_UiText.setCharacterSize(18);
    m_UiText.setFillColor(sf::Color::White);
    m_UiText.setString("NONE");
}

void BlockClicker::InitEnemies()
{
    m_Enemy.setPosition(375, 275);
    m_Enemy.setSize(sf::Vector2f(100.f, 100.f));
    m_Enemy.setFillColor(sf::Color::Cyan);
}

void BlockClicker::SpawnEnemy()
{
    LOG_EXT("TEMP", "Game1", "Spawned Enemy")
    m_Enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(GetWindow()->getSize().x - m_Enemy.getSize().x)),  // NOLINT(concurrency-mt-unsafe)
        0.f
    );

    // Randomize enemy type
    const int type = rand() % 5;

    switch (type)
    {
    case 0:
        m_Enemy.setSize(sf::Vector2f(20.f, 20.f));
        m_Enemy.setFillColor(sf::Color::Magenta);
        break;
    case 1:
        m_Enemy.setSize(sf::Vector2f(35.f, 35.f));
        m_Enemy.setFillColor(sf::Color::Red);
        break;
    case 2:
        m_Enemy.setSize(sf::Vector2f(50.f, 50.f));
        m_Enemy.setFillColor(sf::Color::Cyan);
        break;
    case 3:
        m_Enemy.setSize(sf::Vector2f(70.f, 70.f));
        m_Enemy.setFillColor(sf::Color::Yellow);
        break;
    case 4:
        m_Enemy.setSize(sf::Vector2f(100.f, 100.f));
        m_Enemy.setFillColor(sf::Color::Green);
        break;
    default:
        m_Enemy.setSize(sf::Vector2f(100.f, 100.f));
        m_Enemy.setFillColor(sf::Color::Blue);
        break;
    }

    // Spawn the enemy
    m_Enemies.push_back(m_Enemy);
}

void BlockClicker::UpdateEnemies()
{
    // Updating the timer for enemy spawning
    if (m_Enemies.size() < m_MaxEnemies)
    {
        if(m_EnemySpawnTimer >= m_EnemySpawnTimerMax)
        {
            // Spawn the enemy and reset the timer
            SpawnEnemy();
            m_EnemySpawnTimer = 0.f;
        }
        else
        {
            m_EnemySpawnTimer += 1.f;
        }
    }

    // Moving and Updating Enemies
    for (int i = 0; i < m_Enemies.size(); i++)
    {
        m_Enemies[i].move(0.f, 2.5f);
        
        if(m_Enemies[i].getPosition().y > GetWindow()->getSize().y)
        {
            LOG("Enemy Attacked Player")
            m_Enemies.erase(m_Enemies.begin() + i);
            std::stringstream ss;
            m_Health -= 1;
            ss << "Health: " << m_Health;
            LOG(ss.str())
        }
    }

    // Check if clicked upon
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(bMouseHeld == false)
        {
            bMouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < m_Enemies.size() && deleted == false; i++)
            {
                if(m_Enemies[i].getGlobalBounds().contains(GetMousePosView()))
                {
                    LOG("Enemy Killed by Player")
                
                    // Gain points
                    if(m_Enemies[i].getFillColor() == sf::Color::Magenta)
                        m_Points += 10;
                    else if (m_Enemies[i].getFillColor() == sf::Color::Red)
                        m_Points += 5;
                    else if (m_Enemies[i].getFillColor() == sf::Color::Cyan)
                        m_Points += 3;
                    else if (m_Enemies[i].getFillColor() == sf::Color::Yellow)
                        m_Points += 2;
                    else if (m_Enemies[i].getFillColor() == sf::Color::Green)
                        m_Points += 1;
                    
                    std::stringstream ss;
                    ss << "Points: " << m_Points;
                    LOG(ss.str())

                    deleted = true;
                    m_Enemies.erase(m_Enemies.begin() + i);
                }
            }
        }
    }
    else
    {
        bMouseHeld = false;
    }
}

void BlockClicker::RenderEnemies(sf::RenderTarget& target) const
{
    for (auto &e : m_Enemies)
    {
        target.draw(e);
    }
}

void BlockClicker::UpdateText()
{
    std::stringstream ss;

    ss << "Points: " << m_Points << "\n"
        << "Health: " << m_Health;
    
    m_UiText.setString(ss.str());
}

void BlockClicker::RenderText(sf::RenderTarget& target) const
{
    target.draw(m_UiText);
}

void BlockClicker::Update()
{
    Engine::Update();
    if (!bEndGame)
    {
        UpdateText();
        
        UpdateEnemies();
    }

    if(m_Health <= 0)
        bEndGame = true;
}

void BlockClicker::DrawGame()
{
    RenderEnemies(*GetWindow());
    RenderText(*GetWindow());
}

void BlockClicker::PollEvents()
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

BlockClicker::BlockClicker(const EDifficulty difficulty)
{
    EngineSettings Settings;
    Settings.GameName = "BlockClicker";
    InitEngine(Settings);
    InitVariables(difficulty);
}

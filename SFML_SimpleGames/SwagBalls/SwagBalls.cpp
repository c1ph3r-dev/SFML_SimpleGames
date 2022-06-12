#include "SwagBalls.h"

// Private Functions
void SwagBalls::SpawnSwagBalls()
{
    // Timer
    if(m_SpawnTimer < m_SpawnTimerMax)
        m_SpawnTimer += 1.f;
    else
    {
        if(m_SwagBalls.size() < m_MaxSwagBalls)
        {
            m_SwagBalls.emplace_back(*GetWindow(), RandomizeType());
            m_SpawnTimer = 0.f;
        }
    }
}

int SwagBalls::RandomizeType() const
{
    int type = EType::DEFAULT;
    const int randValue = rand() % 100 + 1;

    if (randValue > 60 && randValue <= 80)
        type = EType::DAMAGING;
    else if (randValue > 80)
        type = EType::HEALING;

    return type;
}

void SwagBalls::UpdatePlayer()
{
    m_Player.Update(GetWindow());

    if(m_Player.GetHealth() <= 0)
        bEndGame = true;
}

void SwagBalls::UpdateCollision()
{
    // Check the collision
    for (size_t i = 0; i < m_SwagBalls.size(); i++)
    {
        if(m_Player.GetShape().getGlobalBounds().intersects(m_SwagBalls[i].GetShape().getGlobalBounds()))
        {
            switch (m_SwagBalls[i].GetType())
            {
            case EType::DEFAULT:
                m_Points++;
                break;
            case EType::HEALING:
                m_Player.UpdateHealth(1);
                break;
            case EType::DAMAGING:
                m_Player.UpdateHealth(-1);
                break;
            }

            // Remove the ball
            m_SwagBalls.erase(m_SwagBalls.begin() + i);
        }
    }
    
}

void SwagBalls::InitText()
{
    m_Text.setFont(m_Font_ka1);
    m_Text.setFillColor(sf::Color::White);
    m_Text.setCharacterSize(24);
    m_Text.setString("TEST");

    m_EndGameText.setFont(m_Font_Bitmgothic);
    m_EndGameText.setFillColor(sf::Color::Red);
    m_EndGameText.setCharacterSize(60);
    m_EndGameText.setPosition(sf::Vector2f(50.f, 100.f));
    m_EndGameText.setString("Game Over!");
}

void SwagBalls::UpdateGui()
{
    std::stringstream ss;

    ss << "Points: " << m_Points << "\n"
        << "Health: " << m_Player.GetHealth() << " / " << m_Player.GetMaxHealth();
    
    m_Text.setString(ss.str());
}

void SwagBalls::RenderGui(sf::RenderTarget* target) const
{
    target->draw(m_Text);
}

// Constructor
SwagBalls::SwagBalls(): Engine()
{
    EngineSettings Settings;
    Settings.GameName = "SwagBalls";
    Settings.bUseEndGame = false;
    InitEngine(Settings);
}

// Overriden Functions
void SwagBalls::InitVariables()
{
    Engine::InitVariables();

    m_SpawnTimerMax = 10.f;
    m_SpawnTimer = m_SpawnTimerMax;
    m_MaxSwagBalls = 10;
    m_Points = 0;

    InitText();    
}

void SwagBalls::Update()
{
    Engine::Update();

    if(bEndGame == false)
    {
        SpawnSwagBalls();
        UpdatePlayer();
        UpdateCollision();
        UpdateGui();
    }
}

void SwagBalls::DrawGame()
{
    m_Player.Render(GetWindow());

    for (auto& i : m_SwagBalls)
    {
        i.Render(*GetWindow());
    }

    RenderGui(GetWindow());

    if(bEndGame)
    {
        GetWindow()->draw(m_EndGameText);
    }
}

void SwagBalls::PollEvents()
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

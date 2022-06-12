#include "Engine.h"

// Private Functions
void Engine::InitVariables()
{
    m_Window = nullptr;
    bEndGame = false;
    InitFonts();
}

void Engine::InitWindow(const unsigned width, const unsigned height, const sf::Uint32 style, const unsigned framerate_limit, const bool v_sync)
{
    sf::VideoMode VideoMode;
    VideoMode.height = height;
    VideoMode.width = width;

    sf::ContextSettings Settings;
    Settings.antialiasingLevel = 16;
    
    m_Window = new sf::RenderWindow(VideoMode, m_GameName, style, Settings);

    GetWindow()->setFramerateLimit(framerate_limit);
    GetWindow()->setVerticalSyncEnabled(v_sync);

    LOG_EXT("INIT", "Engine", "Window Initialized!")
}

void Engine::InitFonts()
{
    if(!(m_Font_ka1.loadFromFile("Fonts/ka1.ttf")))
    {
        LOG("Failed to load font ka1.ttf")
        LOG_EXT("ERROR", "Engine", "Failed to load font ka1.ttf!")
    }
    if(!(m_Font_Bitmgothic.loadFromFile("Fonts/Bitmgothic.ttf")))
    {
        LOG("Failes to load font Bitmgothic.ttf.ttf!")
        LOG_EXT("ERROR", "Engine", "Failed to load font Bitmgothic.ttf!")
    }
    if(!(m_Font_PixelFjVerdana.loadFromFile("Fonts/PixelFJVerdana12pt.ttf")))
    {
        LOG("Failes to load font PixelFJVerdana12pt.ttf!")
        LOG_EXT("ERROR", "Engine", "Failed to load font PixelFJVerdana12pt.ttf!")
    }
}

// Constructors / Destructors
Engine::~Engine()
{
    delete m_Clock;
    delete GetWindow();
    m_Log.close();
}

void Engine::IntLog(const std::string& verbosity, const std::string& category, const std::string& message)
{
    m_Log << verbosity << ": " << category << ": " << message << "\n";
}

void Engine::UpdateMousePositions()
{
    m_MousePosWindow = sf::Mouse::getPosition(*m_Window);
    m_MousePosView = m_Window->mapPixelToCoords(m_MousePosWindow);
}

void Engine::InitEngine(const EngineSettings& settings)
{
    std::srand(static_cast<unsigned>(time(nullptr)));
    bDelta = false;
    
    bUseEndGame = settings.bUseEndGame;
    InitGameName(settings.GameName);
    InitVariables();
    InitWindow(settings.Width, settings.Height, settings.Style, settings.FramerateLimit, settings.bUseVerticalSync);
}

void Engine::InitGameName(const std::string& name)
{
    m_GameName = name;
    
    std::stringstream ss;
    ss << "Logs/" << name << ".log";
    m_Log.open(ss.str(), std::ios_base::out);
}

// Functions
void Engine::Update()
{
    PollEvents();

    if(!bEndGame)
    {
        UpdateMousePositions();
    }
}

void Engine::Render()
{
    /*
     *  @return void
     *  
     *  - clear old frame
     *  - render objects
     *  - display frame in window
     *  
     *  Renders the game objects.
    */
    
    GetWindow()->clear(); // Clear old frame

    // Draw game
    DrawGame();
    
    GetWindow()->display(); // Tell app that window is done drawing
}


void Engine::Run()
{
    std::stringstream ss;
    ss << m_GameName << " is currently running!";
    LOG(ss.str())
    
    m_Clock = new sf::Clock;
    while (Running())
    {
        if(bUseEndGame && bEndGame) break;
        // Update
        Update();
        // Render
        Render();
        
        m_DeltaTime = m_Clock->restart();
        bDelta = true;
    }

    ss.str(std::string());
    ss << m_GameName << " has exited!";
    LOG(ss.str())
}

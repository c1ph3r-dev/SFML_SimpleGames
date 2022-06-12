#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

#define LOG(message) std::cout << (message) << "\n";

enum class EDifficulty : uint8_t
{
    Easy,
    Normal,
    Hard,
    Insane,

    DefaultMAX
};

#include "SFML.h"

struct EngineSettings
{
    std::string GameName = "Default Name";
    unsigned Width = 800;
    unsigned Height = 600;
    sf::Uint32 Style = sf::Style::Close | sf::Style::Titlebar;
    unsigned FramerateLimit = 60;
    bool bUseVerticalSync = false;
    bool bUseEndGame = true;
};

/*
 * Class that acts as the game engine
 * Wrapper class.
 */

class Engine
{
private:
    // Variables
    // / Window
    sf::RenderWindow* m_Window;
    std::fstream m_Log;
    std::string m_GameName;
    bool bUseEndGame;
    bool bDelta;

    sf::Vector2i m_MousePosWindow;
    sf::Vector2f m_MousePosView;

    sf::Clock* m_Clock;
    sf::Time m_DeltaTime;
    
    // Private Functions
    void InitGameName(const std::string& name);
    void InitWindow(const unsigned width, const unsigned height, const sf::Uint32 style, const unsigned framerate_limit, const bool v_sync);
    void InitFonts();
    void Render();
    void UpdateMousePositions();

protected:
    sf::Event Event;
    bool bEndGame;

    // Resources
    // Fonts
    sf::Font m_Font_ka1;
    sf::Font m_Font_Bitmgothic;
    sf::Font m_Font_PixelFjVerdana;

    // Functions
    void InitEngine(const EngineSettings& settings = EngineSettings{});
    inline bool Running() const { return m_Window->isOpen(); }

    // Overrideable Functions
    virtual void InitVariables();
    virtual void Update();
    virtual void DrawGame() = 0;
    virtual void PollEvents() = 0;

    // Protected Accessors
    inline sf::RenderWindow* GetWindow() const { return m_Window; }
    inline sf::Vector2i GetMousePosWindow() const { return m_MousePosWindow; }
    inline sf::Vector2f GetMousePosView() const { return m_MousePosView; }
    inline float GetDeltaTime() const { return bDelta ? m_DeltaTime.asSeconds() : 0.f; }
public:
    // Constructors / Destructors
    virtual ~Engine();
    
    // Log
    void IntLog(const std::string& verbosity, const std::string& category, const std::string& message);
#define LOG_EXT(verbosity, category, message) Engine::IntLog(verbosity, category, message);
    
    // Functions
    void Run();
};
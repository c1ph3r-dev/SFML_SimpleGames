#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum EType
{
    DEFAULT = 0,
    DAMAGING,
    HEALING,
    NROFTYPES
};

class SwagBall final
{
private:
    sf::CircleShape m_Shape;
    int m_Type;

    void InitShape(const sf::RenderWindow& window);
public:
    explicit SwagBall(const sf::RenderWindow& window, const int& type);

    // Accessors
    inline sf::CircleShape GetShape() const { return m_Shape; }
    inline int GetType() const { return m_Type; }
    
    // Functions
    void Render(sf::RenderTarget& target) const;
};

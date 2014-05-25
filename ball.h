#ifndef __special_pong__ball__
#define __special_pong__ball__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "globalVariables.h"

class cBall {
public:
    cBall();
    
    void                render(sf::RenderWindow&);
    sf::Vector2f        update(sf::Time);
    void                collide(sf::Vector2f, bool);
    inline sf::Vector2f getPosition() const { return position; }

private:
    void                init();
    
public:
    bool                boost { false };
    int                 losingPlayer { 0 };

    
private:
    sf::Vector2f        position;
    sf::Vector2f        velocity;
    sf::CircleShape     shape;
    
    sf::Texture         tex;
    sf::Sprite          sprite;
    sf::Time            boostCoolDown { gBoostCoolDown };
};

#endif /* defined(__special_pong__ball__) */

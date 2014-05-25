#ifndef __special_pong__entity__
#define __special_pong__entity__

#include <SFML/Graphics.hpp>
#include "globalVariables.h"

class cPlayer {
public:
    cPlayer(sf::Vector2f, bool vertical = true);
    
    void                    setVelocity(bool, bool);
    void                    render(sf::RenderWindow&);
    sf::Vector2f            update(sf::Time);
    bool                    inverts();
    bool                    boosts();
    inline sf::Vector2f     getVelocity() const { return velocity; }
    void                    save(float);
    
public:
    bool                inverted { false };
    int                 score { 0 };
    bool                vert { true };
    
private:
    sf::Vector2f        position;
    sf::Vector2f        velocity;
    sf::RectangleShape  shape;
    
    sf::Texture         tex;
    sf::Sprite          sprite;
    
    sf::RectangleShape  invBar;
    sf::RectangleShape  boostBar;
    sf::RectangleShape  saveBar;
    
    bool                amIinverting { false };
    bool                amIboosting { false };
    bool                amIsaving { false };
    
    sf::Time            invCoolDown { gInvertCoolDown };
    
    sf::Time            keyInvertCoolDown { gKeyInvertCoolDown };
    sf::Time            keyBoostCoolDown { gKeyBoostCoolDown };
    sf::Time            keySaveCoolDown { gKeySaveCoolDown };
};

#endif /* defined(__special_pong__entity__) */

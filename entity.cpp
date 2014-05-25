#include "entity.h"
#include "globalVariables.h"
#include "ResourcePath.hpp"

cPlayer::cPlayer(sf::Vector2f pos, bool vertical):
position { pos },
vert { vertical }
{
    if ( vertical )
    {
        shape.setFillColor(sf::Color::White);
        shape.setSize(sf::Vector2f(15, 150));
        shape.setOrigin(7.5, 75);
        
        tex.loadFromFile(resourcePath()+"paddle_vertical.png");
        sprite.setTexture(tex);
        sprite.setOrigin(7.5, 75);
    }
    else
    {
        shape.setFillColor(sf::Color::White);
        shape.setSize(sf::Vector2f(150, 15));
        shape.setOrigin(75, 7.5);
        tex.loadFromFile(resourcePath()+"paddle_horizontal.png");
        sprite.setTexture(tex);
        sprite.setOrigin(75, 7.5);
    }
    
    invBar.setFillColor(sf::Color::Yellow);
    boostBar.setFillColor(sf::Color::Cyan);
    saveBar.setFillColor(sf::Color::Green);
    score = 10;
    
}

void cPlayer::render(sf::RenderWindow& window)
{
    // Render paddle
    shape.setPosition(position);
    sprite.setPosition(position);
    if ( inverted )
    {
        shape.setFillColor(sf::Color::Red);
        sprite.setColor(sf::Color::Red);
    }
    else
    {
        shape.setFillColor(sf::Color::White);
        sprite.setColor(sf::Color::White);
    }
    
    // Render inv bar
    float ratio = keyInvertCoolDown.asSeconds() / gKeyInvertCoolDown.asSeconds();
    float otherRatio = keyBoostCoolDown.asSeconds() / gKeyBoostCoolDown.asSeconds();
    float thirdRatio = keySaveCoolDown.asSeconds() / gKeySaveCoolDown.asSeconds();
    
    invBar.setSize(sf::Vector2f(300 * ratio, 10));
    boostBar.setSize(sf::Vector2f(300 * otherRatio, 10));
    saveBar.setSize(sf::Vector2f(300 * thirdRatio, 10));
    
    if ( position.x < 600 )
    {
        // Left side of screen
        invBar.setPosition(550 - invBar.getSize().x, 740);
        boostBar.setPosition(550 - boostBar.getSize().x, 760);
        saveBar.setPosition(550 - saveBar.getSize().x, 780);
    }
    else
    {
        invBar.setPosition(650, 740);
        boostBar.setPosition(650, 760);
        saveBar.setPosition(650, 780);
    }
    
    // window.draw(invBar);
    // window.draw(boostBar);
    // window.draw(saveBar);
    
    window.draw(sprite);
    
    // window.draw(shape);
}

sf::Vector2f cPlayer::update(sf::Time delta)
{
    position += velocity * delta.asSeconds();
    
    if ( inverted )
    {
        invCoolDown -= delta;
        if ( invCoolDown <= sf::Time::Zero )
        {
            inverted = false;
            invCoolDown = gInvertCoolDown;
        }
    }
    
    if ( amIinverting )
    {
        keyInvertCoolDown -= delta;
        if ( keyInvertCoolDown <= sf::Time::Zero )
        {
            keyInvertCoolDown = gKeyInvertCoolDown;
            amIinverting = false;
        }
    }
    
    if ( amIboosting )
    {
        keyBoostCoolDown -= delta;
        if ( keyBoostCoolDown <= sf::Time::Zero )
        {
            keyBoostCoolDown = gKeyBoostCoolDown;
            amIboosting = false;
        }
    }
    
    if ( amIsaving )
    {
        keySaveCoolDown -= delta;
        if ( keySaveCoolDown <= sf::Time::Zero )
        {
            keySaveCoolDown = gKeySaveCoolDown;
            amIsaving = false;
        }
    }
    
    if ( vert )
    {
        if ( position.y < 175 ) { position.y = 175; velocity.y = 0; }
        if ( position.y > 625 ) { position.y = 625; velocity.y = 0; };
    }
    else
    {
        if ( position.x < 375 ) { position.x = 375; velocity.x = 0; };
        if ( position.x > 825 ) { position.x = 825; velocity.x = 0; };
    }
    
    return position;
}

void cPlayer::setVelocity(bool up, bool down)
{
    if ( vert )
    {
        if ( up ) velocity.y = -gPlayerSpeed;
        if ( down ) velocity.y = gPlayerSpeed;
    
        if ( inverted ) velocity.y *= -1;
    
        if ( !up && !down ) velocity.y = 0;
    }
    else
    {
        if ( up ) velocity.x = -gPlayerSpeed;
        if ( down ) velocity.x = gPlayerSpeed;
        
        if ( inverted ) velocity.x *= -1;
        
        if ( !up && !down ) velocity.x = 0;
    }
}

bool cPlayer::inverts()
{
    if ( keyInvertCoolDown == gKeyInvertCoolDown )
    {
        amIinverting = true;
        return true;
    }

    return false;
}

bool cPlayer::boosts()
{
    if ( keyBoostCoolDown == gKeyBoostCoolDown )
    {
        amIboosting = true;
        return true;
    }
    
    return false;
}

void cPlayer::save(float value)
{
    if ( !amIsaving )
    {
        if ( vert ) position.y = value;
        else position.x = value;
        amIsaving = true;
    }
}
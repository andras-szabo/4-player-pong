#include "ball.h"
#include "globalVariables.h"
#include <cmath>
#include "ResourcePath.hpp"

cBall::cBall()
{
    shape.setFillColor(sf::Color::White);
    shape.setRadius(gBallSize);
    shape.setOrigin(gBallSize, gBallSize);

    tex.loadFromFile(resourcePath() + "ball.png");
    sprite.setTexture(tex);
    sprite.setOrigin(gBallSize, gBallSize);

    init();
}

void cBall::init()
{
    position = sf::Vector2f(600, 400);

    float vx = static_cast<float>(rand() % static_cast<int>(gBallSpeed*2)) - gBallSpeed;
    float vy = static_cast<float>(rand() % static_cast<int>(gBallSpeed*2)) - gBallSpeed;
    
    float norm = sqrt(pow(vx,2) + pow(vy,2));
    
    vx = vx*gBallSpeed/norm;
    vy = vy*gBallSpeed/norm;
    
  /*  if ( abs(vx) < abs(vy) )
    {
        float tmp = vx;
        vx = vy;
        vy = tmp;
    }*/
    
    velocity = sf::Vector2f(vx, vy);
}


void cBall::render(sf::RenderWindow& window)
{
    // shape.setPosition(position);
    sprite.setPosition(position);
    //window.draw(shape);
    window.draw(sprite);
}

sf::Vector2f cBall::update(sf::Time delta)
{
    position += (velocity + static_cast<float>(boost) * (velocity * static_cast<float>(0.5)) ) * delta.asSeconds();
    
    if ( boost )
    {
        boostCoolDown -= delta;
        if ( boostCoolDown <= sf::Time::Zero )
        {
            boost = false;
            boostCoolDown = gBoostCoolDown;
        }
    }
    
    if ( position.x > 200 && position.x < 1000 )
    {
        if ( position.y < gBallSize || position.y > (800 - gBallSize) )
        {
            if ( position.y < gBallSize ) losingPlayer = 3;
            else losingPlayer = 4;
            init();
        }
    }
    else
    {
        if ( position.x < 200 ) losingPlayer = 1;
        if ( position.x > 1000 ) losingPlayer = 2;
        init();
    }
    
    return position;
}

void cBall::collide(sf::Vector2f vel, bool vertical)
{
    if ( vertical )
    {
        velocity.x *= -1;
        if ( velocity.y < 0 )
        {
            velocity.y -= (abs(vel.y) * 0.2);
        }
        else
        {
            velocity.y += (abs(vel.y) * 0.2);
        }
    }
    else
    {
        velocity.y *= -1;
        if ( velocity.x < 0 )
        {
            velocity.x -= (abs(vel.x) * 0.2);
        }
        else
        {
            velocity.x += (abs(vel.x) * 0.2);
        }
    }
    
}
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ball.h"
#include "entity.h"
#include <random>
#include "ResourcePath.hpp"
#include <string>

int main()
{
    
    srand(time(NULL));
    
    sf::RenderWindow        window;
    sf::View                view;
    cBall                   ball;
    
    cPlayer                 playerOne(sf::Vector2f(300, 400));
    cPlayer                 playerTwo(sf::Vector2f(900, 400));
    cPlayer                 playerThree(sf::Vector2f(600,100), false);
    cPlayer                 playerFour(sf::Vector2f(600, 700), false);
    
    sf::Text                tScore;
    
    sf::Text                tBarText;
    
    sf::Text                tCredits;
    
    sf::Font                font;
    
    sf::Texture             bgTex;
    sf::Sprite              background;
    
    bgTex.loadFromFile(resourcePath() + "bg_guys.png");
    background.setTexture(bgTex);
    
    font.loadFromFile(resourcePath() + "sansation.ttf");
    
    tScore.setFont(font);
    tScore.setCharacterSize(30);
    tScore.setPosition(300, 300);
    tScore.setColor(sf::Color::Cyan);
    
    tCredits.setFont(font);
    tCredits.setCharacterSize(14);
    tCredits.setColor(sf::Color::Black);
    tCredits.setPosition(800, 710);
    tCredits.setString("Andrei Ursan // Jalyna Schroeder // Eva Bronisch-Holtze\nZoe Tokoutsi // Nahel Abdi // Andras Szabo (c) 2014\nBerlin Mini Game Jam");
    
    tBarText.setFont(font);
    tBarText.setCharacterSize(14);
    
    window.create(sf::VideoMode(sf::VideoMode::getDesktopMode()), "Pong window yay");
    window.setVerticalSyncEnabled(true);
    
    view.setSize(1200, 800);
    view.setCenter(600, 400);
    view.setViewport(sf::FloatRect(0,0,1.0,1.0));
    
    window.setView(view);
    
    sf::Event event;
    
    sf::Clock   clock;
    sf::Time    timeSinceLastUpdate { sf::Time::Zero };
    
    sf::Vector2f    ballPosition = ball.update(timeSinceLastUpdate);
    sf::Vector2f    pOnePosition = playerOne.update(timeSinceLastUpdate);
    sf::Vector2f    pTwoPosition = playerTwo.update(timeSinceLastUpdate);
    sf::Vector2f    pThreePosition = playerThree.update(timeSinceLastUpdate);
    sf::Vector2f    pFourPosition = playerFour.update(timeSinceLastUpdate);
    
    sf::Joystick::update();
    
    while ( window.isOpen() )
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            // Player two
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                bool inv = playerTwo.inverts();
                playerOne.inverted = inv;
                playerThree.inverted = inv;
                playerFour.inverted = inv;
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                ball.boost = playerTwo.boosts();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::RShift) {
                playerTwo.save(ball.getPosition().y);
            }
            ///////////////////////////
            
            // Player one
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
                ball.boost = playerOne.boosts();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
                bool inv = playerOne.inverts();
                playerTwo.inverted = inv;
                playerThree.inverted = inv;
                playerFour.inverted = inv;
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
                playerOne.save(ball.getPosition().y);
            }
            
            // Player three
            
            if (event.type == sf::Event::JoystickButtonPressed &&
                event.joystickButton.joystickId == 0 && event.joystickButton.button == 1) {
                ball.boost = playerThree.boosts();
            }
            
            if (event.type == sf::Event::JoystickButtonPressed &&
                event.joystickButton.joystickId == 0 && event.joystickButton.button == 0) {
               
                bool inv = playerThree.inverts();
                playerTwo.inverted = inv;
                playerOne.inverted = inv;
                playerFour.inverted = inv;
            }
            
            if (event.type == sf::Event::JoystickButtonPressed &&
                event.joystickButton.joystickId == 0 && event.joystickButton.button == 2) {
                playerThree.save(ball.getPosition().x);
            }
            
            // Player four
            
            if (event.type == sf::Event::JoystickButtonPressed &&
                event.joystickButton.joystickId == 1 && event.joystickButton.button == 1) {
                ball.boost = playerFour.boosts();
            }
            
            if (event.type == sf::Event::JoystickButtonPressed &&
                event.joystickButton.joystickId == 1 && event.joystickButton.button == 0) {
                
                bool inv = playerFour.inverts();
                playerTwo.inverted = inv;
                playerOne.inverted = inv;
                playerThree.inverted = inv;
            }
            
            if (event.type == sf::Event::JoystickButtonPressed &&
                event.joystickButton.joystickId == 1 && event.joystickButton.button == 2) {
                playerFour.save(ball.getPosition().x);
            }
            
        }
        
        playerOne.setVelocity(sf::Keyboard::isKeyPressed(sf::Keyboard::W),
                              sf::Keyboard::isKeyPressed(sf::Keyboard::S));
        
        playerTwo.setVelocity(sf::Keyboard::isKeyPressed(sf::Keyboard::Up),
                              sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
        
        playerThree.setVelocity(sf::Joystick::isButtonPressed(0, 4),
                                sf::Joystick::isButtonPressed(0, 5));
     
        playerFour.setVelocity(sf::Joystick::isButtonPressed(1, 4),
                                sf::Joystick::isButtonPressed(1, 5));
        
        // logic goes here
        
        timeSinceLastUpdate = clock.restart();
        
        // Collision check:
        
        sf::IntRect     ballRect(ballPosition.x - gBallSize,
                                 ballPosition.y - gBallSize,
                                 gBallSize * 2, gBallSize * 2);
        sf::IntRect     playerRect(pOnePosition.x - 7.5, pOnePosition.y - 75, 15, 150);
        
        bool collide { false };
        
        if ( ballRect.intersects(playerRect) )
        {
            collide = true;
            ball.collide(playerOne.getVelocity(), true);
            
            ballPosition = ball.update(timeSinceLastUpdate);
            ballRect = sf::IntRect(ballPosition.x - gBallSize, ballPosition.y - gBallSize,
                                   gBallSize * 2, gBallSize * 2);
            
            while ( ballRect.intersects(playerRect) )
            {
                ballPosition = ball.update(timeSinceLastUpdate);
                ballRect = sf::IntRect(ballPosition.x - gBallSize, ballPosition.y - gBallSize,
                                       gBallSize * 2, gBallSize * 2);
            }
            
        }
        
        playerRect = sf::IntRect(pTwoPosition.x - 7.5, pTwoPosition.y - 75, 15, 150);
        
        if ( ballRect.intersects(playerRect) )
        {
            collide = true;
            ball.collide(playerTwo.getVelocity(), true);
            
            ballPosition = ball.update(timeSinceLastUpdate);
            ballRect = sf::IntRect(ballPosition.x - gBallSize, ballPosition.y - gBallSize,
                                   gBallSize * 2, gBallSize * 2);
            
            while ( ballRect.intersects(playerRect) )
            {
                ballPosition = ball.update(timeSinceLastUpdate);
                ballRect = sf::IntRect(ballPosition.x - gBallSize, ballPosition.y - gBallSize,
                                       gBallSize * 2, gBallSize * 2);
            }
        }
        
        playerRect = sf::IntRect(pThreePosition.x - 75, pThreePosition.y - 7.5, 150, 15);
        
        if ( ballRect.intersects(playerRect) )
        {
            collide = true;
            ball.collide(playerThree.getVelocity(), false);
            
            ballPosition = ball.update(timeSinceLastUpdate);
            ballRect = sf::IntRect(ballPosition.x - gBallSize, ballPosition.y - gBallSize,
                                   gBallSize * 2, gBallSize * 2);
            
            while ( ballRect.intersects(playerRect) )
            {
                ballPosition = ball.update(timeSinceLastUpdate);
                ballRect = sf::IntRect(ballPosition.x - gBallSize, ballPosition.y - gBallSize,
                                       gBallSize * 2, gBallSize * 2);
            }
            
        }
        
        playerRect = sf::IntRect(pFourPosition.x - 75, pFourPosition.y - 7.5, 150, 15);
        
        if ( ballRect.intersects(playerRect) )
        {
            collide = true;
            ball.collide(playerFour.getVelocity(), false);
            
            ballPosition = ball.update(timeSinceLastUpdate);
            ballRect = sf::IntRect(ballPosition.x - gBallSize, ballPosition.y - gBallSize,
                                   gBallSize * 2, gBallSize * 2);
            
            while ( ballRect.intersects(playerRect) )
            {
                ballPosition = ball.update(timeSinceLastUpdate);
                ballRect = sf::IntRect(ballPosition.x - gBallSize, ballPosition.y - gBallSize,
                                       gBallSize * 2, gBallSize * 2);
            }
            
        }
        
        if ( !collide )
        {
            ballPosition = ball.update(timeSinceLastUpdate);
        }
        
        pOnePosition = playerOne.update(timeSinceLastUpdate);
        pTwoPosition = playerTwo.update(timeSinceLastUpdate);
        
        pThreePosition = playerThree.update(timeSinceLastUpdate);
        pFourPosition = playerFour.update(timeSinceLastUpdate);

        switch ( ball.losingPlayer ) {
            case 0: break;
            case 1: {
                --playerOne.score;
                ball.losingPlayer = 0;
                break;
            }
            case 2: {
                --playerTwo.score;
                ball.losingPlayer = 0;
                break;
            }
            case 3: {
                --playerThree.score;
                ball.losingPlayer = 0;
                break;
            }
            case 4: {
                --playerFour.score;
                ball.losingPlayer = 0;
                break;
            }
        }
        
        window.clear();
        
        window.draw(background);
        
        window.draw(tCredits);
        
        tScore.setString(std::to_string(playerOne.score));
        tScore.setPosition(545, 400);
        window.draw(tScore);

        tScore.setString(std::to_string(playerTwo.score));
        tScore.setPosition(650, 400);
        window.draw(tScore);

        tScore.setString(std::to_string(playerThree.score));
        tScore.setPosition(600, 340);
        window.draw(tScore);
        
        tScore.setString(std::to_string(playerFour.score));
        tScore.setPosition(600, 450);
        window.draw(tScore);

        tBarText.setString("Nastiness");
        tBarText.setPosition(565, 735);
        tBarText.setColor(sf::Color::Yellow);
        
        // window.draw(tBarText);
        
        tBarText.setString("Speed buff");
        tBarText.setPosition(565, 755);
        tBarText.setColor(sf::Color::Cyan);
        // window.draw(tBarText);
        
        tBarText.setString("Safeguard");
        tBarText.setPosition(565, 775);
        tBarText.setColor(sf::Color::Green);
        // window.draw(tBarText);
        
        ball.render(window);
        playerOne.render(window);
        playerTwo.render(window);
        playerThree.render(window);
        playerFour.render(window);
        
        window.display();
        
    }
    
    
    return 0;
}
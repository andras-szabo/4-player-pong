#ifndef special_pong_globalVariables_h
#define special_pong_globalVariables_h

const float     gPlayerSpeed { 1000 };
const float     gBallSpeed { 400 };
const sf::Time  gInvertCoolDown { sf::seconds(2.0) };
const sf::Time  gBoostCoolDown { sf::seconds(0.5) };

const sf::Time  gKeyInvertCoolDown { sf::seconds(5.0) };
const sf::Time  gKeyBoostCoolDown { sf::seconds(3.5) };
const sf::Time  gKeySaveCoolDown { sf::seconds(10) };

const float     gBallSize { 10 };

#endif

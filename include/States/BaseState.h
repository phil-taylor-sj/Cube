#pragma once
#include <SFML/Graphics.hpp>

class BaseState
{
public:
    void virtual updateState();
    void virtual displayState(sf::RenderWindow& window,
                              sf::View& playerView);

    BaseState();
};
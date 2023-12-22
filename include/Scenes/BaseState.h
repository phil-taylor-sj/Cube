#pragma once
#include <SFML/Graphics.hpp>

class BaseScene
{
public:
    void virtual updateScene();
    void virtual displayScene(sf::RenderWindow& window,
                              sf::View& playerView);

    BaseScene();
};
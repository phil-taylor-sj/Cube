#pragma once
#include <SFML/Graphics.hpp>

namespace Scenes
{
    class Scene
    {
    public:
        void virtual updateScene() = 0;
        void virtual renderScene() = 0;

        void setRenderWindow(std::shared_ptr<sf::RenderWindow> window);
        void setView(std::shared_ptr<sf::View> view);

        Scene();

    protected:
        std::shared_ptr<sf::RenderWindow> m_window;
        std::shared_ptr<sf::View> m_view; 
    };
}
#pragma once
#include <SFML/Graphics.hpp>
#include "Engine/Action.h"
#include "Scenes/SceneNames.h"
#include "Scenes/GameSceneActions.h"
#include "Scenes/TitleSceneActions.h"


namespace Scenes
{
    class Scene
    {
    public:
        GameSceneActions virtual checkInput(sf::Keyboard::Key) = 0;
        void virtual processAction(Engine::Action action) = 0;
        void virtual updateScene() = 0;
        void virtual renderScene() = 0;
        void virtual setDeltaTime(float deltaTime) = 0;

        SceneNames checkNextScene();

        void setRenderWindow(std::shared_ptr<sf::RenderWindow> window);
        void setView(std::shared_ptr<sf::View> view);

        Scene();

    protected:
        std::shared_ptr<sf::RenderWindow> m_window;
        std::shared_ptr<sf::View> m_view;
        SceneNames m_nextScene = SceneNames::NONE;
    };
}
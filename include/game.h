#ifndef GAME_H
#define GAME_H

#include "gameobject.h"

#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class GameObject;

class Game
{
    public:
        Game();
        virtual ~Game();

        virtual void createGame(std::shared_ptr<Game>) {}
        virtual void loop() {}

        sf::RenderWindow& getWindow() { return m_window; }
        void printStatus() const;

        void registerObject(std::shared_ptr<GameObject> pObject);
    protected:
        sf::RenderWindow m_window;
        std::unordered_map<int, std::shared_ptr<GameObject>> m_objects;

        void renderGame();
    private:
        int m_nObject;
};

#endif // GAME_H

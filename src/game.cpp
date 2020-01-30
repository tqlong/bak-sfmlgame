#include "game.h"

Game::Game()
    : m_window(sf::VideoMode(800, 800), "SFML works!"), m_nObject(0)
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::registerObject(std::shared_ptr<GameObject> pObject)
{
    int id = m_nObject;
    m_nObject++;

    m_objects[id] = pObject;
    pObject->setID(id);
}

void Game::printStatus() const
{
    for (const auto& p : m_objects) {
        p.second->printStatus();
    }
}

void Game::renderGame()
{
    m_window.clear();

    for (const auto& p : m_objects) {
        p.second->draw(m_window);
    }

    m_window.display();
}

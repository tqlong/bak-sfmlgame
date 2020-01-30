#include "pingponggame.h"
#include <iostream>
#include <random>

using namespace std;

PingPongGame::PingPongGame()
{

}

PingPongGame::~PingPongGame()
{
    //dtor
}

void PingPongGame::createGame(std::shared_ptr<Game> pGame)
{
    int n_balls = 100;
    default_random_engine generator(42);
    uniform_real_distribution<float> distribution(0.2f, 0.8f);
    uniform_int_distribution<int> color_distribution(128, 255);
    uniform_real_distribution<float> velocity_distribution(-0.1f, 0.1f);

    for (int i = 0; i < n_balls; i++) {
        ptrPingPongBall ball = make_shared<PingPongBall>(pGame);
        ball->setRadius(0.02f);
        ball->setPosition(distribution(generator), distribution(generator));
        ball->setColor(color_distribution(generator), color_distribution(generator), color_distribution(generator));
        ball->setVelocity(velocity_distribution(generator), velocity_distribution(generator));

        m_balls.push_back(ball);
        pGame->registerObject(ball);
    }

}

void PingPongGame::loop()
{
    sf::Clock clock;
    while (m_window.isOpen())
    {
        //this->printStatus();
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            //sf::Vector2i localPosition = sf::Mouse::getPosition(m_window);
            //m_pBall->setPosition(localPosition.x, localPosition.y);
        }

        sf::Time elapsed = clock.restart();
        step(elapsed.asSeconds());
        renderGame();
    }
    cout << "Done loop" << endl;
}

void PingPongGame::step(float dt)
{
    for (auto ball : m_balls) {
        pair<sf::Vector2f, sf::Vector2f> pos_velo = ball->getPredictedPosition(dt);
        sf::Vector2f pos = pos_velo.first, velo = pos_velo.second;
        ball->setPosition(pos.x, pos.y);
        ball->setVelocity(velo.x, velo.y);
    }
}

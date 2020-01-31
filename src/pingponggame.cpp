#include "pingponggame.h"
#include <iostream>
#include <random>
#include <cassert>

using namespace std;

PingPongGame::PingPongGame()
    : m_currentTime(0.f)
{

}

PingPongGame::~PingPongGame()
{
    //dtor
}

void PingPongGame::createGame(std::shared_ptr<Game> pGame)
{
    int n_balls = 1000;
    default_random_engine generator(42);
    uniform_real_distribution<float> distribution(0.2f, 0.8f);
    uniform_int_distribution<int> color_distribution(128, 255);
    uniform_real_distribution<float> velocity_distribution(-0.1f, 0.1f);

    for (int i = 0; i < n_balls; i++) {
        ptrPingPongBall ball = make_shared<PingPongBall>(pGame);
        ball->setRadius(0.005f);
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
    for (auto ball : m_balls) predict(ball);
    float oldTime = 0.f;
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

        float dt = clock.restart().asSeconds();
        step(dt);
        if (m_currentTime > oldTime + 1.0f) {
            oldTime = m_currentTime;
            cout << "queue " << m_eventQueue.size() << endl;
        }
        renderGame();
    }
    cout << "Done loop" << endl;
}

void PingPongGame::step(float dt)
{
    float nextTime = m_currentTime + dt;

    while (!m_eventQueue.empty()) {
        Event e = m_eventQueue.top();
        if (!e.isValid()) {
//            cout << "event invalid " << e.m_t << endl;
            m_eventQueue.pop();
        } else {
            if (e.m_t > nextTime) { // event is too far in future, move all particles to nextTime
                moveBalls(dt);
                return; // get out of the loop to render
            } else { // event happens inside [m_currentTime, nextTime]
//                cout << "event " << e.m_t << " " << m_currentTime << " " << nextTime << endl;
                moveBalls(e.m_t-m_currentTime);

                ptrPingPongBall pA = e.pA.lock(), pB = e.pB.lock();
                if (pA && pB) {}
                else if (pA && !pB) pA->bounceOffVerticalWall();
                else if (!pA && pB) pB->bounceOffHorizontalWall();
                else {}
                m_eventQueue.pop(); // remove this event to process next event
                predict(pA);
                predict(pB);
            }
        }
    }

    if (m_currentTime < nextTime) moveBalls(nextTime-m_currentTime);
}

bool operator< (const Event& a, const Event& b) {
    return a.m_t > b.m_t;
}

void PingPongGame::predict(ptrPingPongBall pBall, float limit)
{
    if (!pBall) return;
    double dtX = pBall->getTimeToHitVerticalWall();
    double dtY = pBall->getTimeToHitHorizontalWall();
    assert(dtX >= 0 && dtY >= 0);
    Event verticalWallEvent(m_currentTime + dtX, pBall, nullptr), horizontalWallEvent(m_currentTime + dtY, nullptr, pBall);

    if (m_currentTime + dtX < limit) m_eventQueue.push(verticalWallEvent);
    if (m_currentTime + dtY < limit) m_eventQueue.push(horizontalWallEvent);
}

void PingPongGame::moveBalls(float dt)
{
    for (auto ball : m_balls) {
        pair<sf::Vector2f, sf::Vector2f> pos_velo = ball->getPredictedPosition(dt);
        sf::Vector2f pos = pos_velo.first, velo = pos_velo.second;
        ball->setPosition(pos.x, pos.y);
        ball->setVelocity(velo.x, velo.y);
//        ball->printStatus();
    }
    m_currentTime += dt;
}

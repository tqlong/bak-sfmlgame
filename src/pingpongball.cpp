#include "pingpongball.h"
#include <iostream>
using namespace std;

PingPongBall::PingPongBall(std::shared_ptr<Game> pGame)
    : GameObject(pGame), m_x(0.f), m_y(0.f), m_r(0.02f)
{
    setColor(0, 255, 0);
    setRadius(m_r);
    setPosition(m_x, m_y);
}

PingPongBall::~PingPongBall()
{
    //dtor
}

void PingPongBall::draw(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}

void PingPongBall::setPosition(float x, float y)
{
    m_x = x, m_y = y;

    x *= shared_ptr<Game>(m_pGame)->getWindow().getSize().x, y *= shared_ptr<Game>(m_pGame)->getWindow().getSize().y;

    //cout << "x " << x << " y " << y << endl;
    m_shape.setPosition(x, y);
}

void PingPongBall::setRadius(float r)
{
    m_r = r;
    float radius = m_r*shared_ptr<Game>(m_pGame)->getWindow().getSize().x;
    m_shape.setRadius(radius);
    m_shape.setOrigin(radius, radius);

    //cout << "r " << radius << endl;
}

void PingPongBall::setColor(int r, int g, int b, int a)
{
    m_shape.setFillColor(sf::Color(r, g, b, a));
}

void PingPongBall::setVelocity(float vx, float vy)
{
    m_vx = vx, m_vy = vy;
}

void PingPongBall::printStatus() const
{
    cout << "id " << m_id << " x " << m_x << " y " << m_y << " vx " << m_vx << " vy " << m_vy << endl;
}

pair<sf::Vector2f, sf::Vector2f> PingPongBall::getPredictedPosition(float dt) const
{
    float vx = m_vx, vy = m_vy;
    if ( m_x+dt*m_vx < m_r || m_x+dt*m_vx > 1.0f - m_r ) vx = -m_vx;
    if ( m_y+dt*m_vy < m_r || m_y+dt*m_vy > 1.0f - m_r ) vy = -m_vy;
    return make_pair(sf::Vector2f(m_x+dt*vx, m_y+dt*vy), sf::Vector2f(vx, vy));
}
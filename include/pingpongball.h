#ifndef PINGPONGBALL_H
#define PINGPONGBALL_H

#include "gameobject.h"
#include <memory>

class PingPongBall : public GameObject
{
    public:
        PingPongBall(std::shared_ptr<Game> pGame);
        virtual ~PingPongBall();

        void draw(sf::RenderWindow& window) const;

        void setPosition(float x, float y);
        void setRadius(float r);
        void setColor(int r, int g, int b, int a = 255);
        void setVelocity(float vx, float vy);

        std::pair<sf::Vector2f, sf::Vector2f> getPredictedPosition(float dt) const;

        void printStatus() const;

        float getTimeToHitVerticalWall() const;
        float getTimeToHitHorizontalWall() const;
        void bounceOffVerticalWall();
        void bounceOffHorizontalWall();
        int getCount() const { return m_count; }
    protected:
        float m_x;
        float m_y;
        float m_r;
        float m_vx;
        float m_vy;
        int m_count;

        sf::Vector2u m_windowSize;
        sf::CircleShape m_shape;

    private:
};

typedef std::shared_ptr<PingPongBall> ptrPingPongBall;

#endif // PINGPONGBALL_H

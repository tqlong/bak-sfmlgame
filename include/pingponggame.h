#ifndef PINGPONGGAME_H
#define PINGPONGGAME_H

#include "game.h"
#include "pingpongball.h"
#include <vector>

class PingPongGame : public Game
{
    public:
        PingPongGame();
        virtual ~PingPongGame();

        void createGame(std::shared_ptr<Game> pGame);
        void loop();
    protected:
        std::vector<ptrPingPongBall> m_balls;
    private:
        void step(float dt);
};

#endif // PINGPONGGAME_H

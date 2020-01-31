#include <SFML/Graphics.hpp>
#include "pingponggame.h"
#include <memory>

using namespace std;

int main() {
    shared_ptr<Game> game = make_shared<PingPongGame>("Collision System", 2000, 3.f);
    game->createGame(game);
    game->loop();
    return 0;
}

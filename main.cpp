#include <SFML/Graphics.hpp>
#include "pingponggame.h"
#include <memory>

using namespace std;

int main() {
    shared_ptr<Game> game = make_shared<PingPongGame>(5000, 1.0f);
    game->createGame(game);
    game->loop();
    return 0;
}

#include <SFML/Graphics.hpp>
#include "pingponggame.h"
#include <memory>

using namespace std;

int main() {
    shared_ptr<Game> game = make_shared<PingPongGame>();
    game->createGame(game);
    //game->printStatus();
    game->loop();
    return 0;
}

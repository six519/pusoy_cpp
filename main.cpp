#include <iostream>
#include "game.hpp"
#include "exception.hpp"

using namespace std;

int main() {
    Game game;

    try {
        game.run();
    } catch(FileGameException exception) {
        cout << exception.message();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
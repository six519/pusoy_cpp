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
        return -1;
    }
    return 0;
}
#include <string>
#include "exception.hpp"
using namespace std;

string GameException::message() {
    return "GameException error occurred...\n";
}

string FileGameException::message() {
    return "Unable to load file...\n";
}
#ifndef _GAME_H_
#define _GAME_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "room.hpp"
#include "resource.hpp"

using namespace std;

const int GAME_WIDTH = 1024;
const int GAME_HEIGHT = 600;
const string GAME_TITLE = "Pusoy Dos";
const int GAME_STATE_MAIN = 0;
const int GAME_STATE_PLAY = 1;

const vector<string> CARD_SUITES = {
    "clubs",
    "spades",
    "hearts",
    "diamonds"
};

const vector<string> CARD_PIPS = {
    "3",
    "4",
    "5",
    "6"
    "7",
    "8",
    "9"
    "10",
    "jack",
    "queen",
    "king",
    "ace",
    "2"
};

class Game {
    public:
        sf::RenderWindow* window;
        sf::Event* event;
        vector<GameSprite*> sprites;
        vector<sf::Texture> textures;
        vector<GameMusic*> musics;
        vector<GameSound*> sounds;
        bool is_music_on;
        
        MainRoom* main_room;
        PlayRoom* play_room;

        int state;
        void run();
        int add_sprite(string filename, bool is_tiled = false);
        int add_music(string filename);

        void add_sounds(string src);

    private:
        void init();
};

#endif
#ifndef _GAME_H_
#define _GAME_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "room.hpp"

using namespace std;

const int GAME_WIDTH = 1024;
const int GAME_HEIGHT = 600;
const string GAME_TITLE = "Pusoy Dos";
const int GAME_STATE_MAIN = 0;
const int GAME_STATE_PLAY = 1;

class Game {
    public:
        sf::RenderWindow* window;
        sf::Event* event;
        vector<sf::Sprite> sprites;
        vector<sf::Texture> textures;
        vector<string> musics;
        sf::Music* music_objects;
        
        MainRoom* main_room;
        PlayRoom* play_room;

        int state;
        void run();
        void init_musics();
        int add_sprite(string filename, bool is_tiled = false);
        int add_music(string filename);
    private:
        void init();
};

#endif
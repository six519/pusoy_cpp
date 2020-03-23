#ifndef _ROOM_H_
#define _ROOM_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

using namespace std;

class Game;

class Room {
    public:
        Room(Game* game);
        int play();
        void stop_all_musics(vector<int> ignore_stop);
        bool is_sprite_clicked(sf::Sprite sprite);
    protected:
        Game* game;
};

class MainRoom: public Room {
    public:
        MainRoom(Game* game);
        int play();
};

class PlayRoom: public Room {
    public:
        PlayRoom(Game* game);
        int play();
};

#endif
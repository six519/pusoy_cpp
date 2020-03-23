#ifndef _ROOM_H_
#define _ROOM_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

using namespace std;

class Game;

class GameSound {
    private:
        sf::SoundBuffer buffer;
        sf::Sound sound;
        string _src;
    public:
        void init(string src);
        void play();
        void stop();
};

class GameSprite {
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        string _src;
    public:
        void init(string src, bool is_tiled = false);
        sf::Sprite get_sprite();
        void set_position(sf::Vector2f position);
};

class Room {
    public:
        Room(Game* game);
        int play();
        void stop_all_musics(vector<string> musics, sf::Music* music_objects, vector<int> ignore_stop);
        bool is_sprite_clicked(sf::Sprite sprite, sf::RenderWindow *window);
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
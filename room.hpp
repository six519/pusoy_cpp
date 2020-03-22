#ifndef _ROOM_H_
#define _ROOM_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

using namespace std;

sf::Sprite refreshTexture(int index, vector<sf::Sprite> sprites, vector<sf::Texture> textures);

class Room {
    public:
        void play(sf::RenderWindow* window, vector<sf::Sprite> sprites, vector<sf::Texture> textures, sf::Music* music_objects, vector<string> musics);
        void stop_all_musics(vector<string> musics, sf::Music* music_objects, vector<int> ignore_stop);
};

class MainRoom: public Room {
    public:
        void play(sf::RenderWindow* window, vector<sf::Sprite> sprites, vector<sf::Texture> textures, sf::Music* music_objects, vector<string> musics);
};

#endif
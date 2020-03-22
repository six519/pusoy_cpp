#ifndef _ROOM_H_
#define _ROOM_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

using namespace std;

class GameSound {
    private:
        sf::SoundBuffer buffer;
        sf::Sound sound;
        std::string _src;
    public:
        void init(std::string src);
        void play();
        void stop();
};

sf::Sprite refreshTexture(int index, vector<sf::Sprite> sprites, vector<sf::Texture> textures);

class Room {
    public:
        int play(sf::RenderWindow* window, vector<sf::Sprite> sprites, vector<sf::Texture> textures, sf::Music* music_objects, vector<string> musics, vector<GameSound*> sounds);
        void stop_all_musics(vector<string> musics, sf::Music* music_objects, vector<int> ignore_stop);
        bool isSpriteClicked(sf::Sprite *sprite, sf::RenderWindow *window);
};

class MainRoom: public Room {
    public:
        int play(sf::RenderWindow* window, vector<sf::Sprite> sprites, vector<sf::Texture> textures, sf::Music* music_objects, vector<string> musics, vector<GameSound*> sounds);
};

class PlayRoom: public Room {
    public:
        int play(sf::RenderWindow* window, vector<sf::Sprite> sprites, vector<sf::Texture> textures, sf::Music* music_objects, vector<string> musics, vector<GameSound*> sounds);
};

#endif
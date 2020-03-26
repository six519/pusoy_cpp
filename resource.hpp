#ifndef _RESOURCE_H_
#define _RESOURCE_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

using namespace std;

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

class GameMusic {
    private:
        sf::Music music;
        string _src;
    public:
        void init(string src);
        void play();
        void stop();
        void pause();
        bool is_playing();
        void set_loop(bool is_loop);
};

#endif
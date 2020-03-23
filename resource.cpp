#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "resource.hpp"
#include "game.hpp"
#include "exception.hpp"

using namespace std;

void GameSound::init(string src) {
    _src = src;
    if(!buffer.loadFromFile(src)) {
        throw FileGameException();
    }
    sound.setBuffer(buffer);
}
void GameSound::play(){
    sound.play();
}
void GameSound::stop(){
    sound.stop();
}

void GameSprite::init(string src, bool is_tiled) {
    _src = src;
    if(!texture.loadFromFile(src)) {
        throw FileGameException();
    }        
    sprite.setTexture(texture);
    if (is_tiled) {
        texture.setRepeated(true);
        sprite.setTextureRect(sf::IntRect(0, 0, GAME_WIDTH, GAME_HEIGHT));
    }
}

sf::Sprite GameSprite::get_sprite() {
    return sprite;
}

void GameSprite::set_position(sf::Vector2f position) {
    sprite.setPosition(position);
}

void GameMusic::init(string src) {
    _src = src;
    if(!music.openFromFile(src))
        throw FileGameException();
}

void GameMusic::play() {
    music.play();
}

void GameMusic::stop() {
    music.stop();
}

bool GameMusic::is_playing() {
    if(music.getStatus() == sf::Music::Status::Playing)
        return true;
    return false;
}

void GameMusic::set_loop(bool is_loop) {
    music.setLoop(is_loop);
}
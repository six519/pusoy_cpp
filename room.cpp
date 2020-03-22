#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>
#include "room.hpp"
#include "game.hpp"
#include "exception.hpp"

using namespace std;

void GameSound::init(std::string src) {
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

sf::Sprite refreshTexture(int index, vector<sf::Sprite> sprites, vector<sf::Texture> textures) {
    sprites[index].setTexture(textures[index]);
    return sprites[index];
}

int Room::play(sf::RenderWindow* window, vector<sf::Sprite> sprites, vector<sf::Texture> textures, sf::Music* music_objects, vector<string> musics, vector<GameSound*> sounds) {

    return GAME_STATE_MAIN;
}

void Room::stop_all_musics(vector<string> musics, sf::Music* music_objects, vector<int> ignore_stop) {
    for(int x=0; x < musics.size(); x++) {
        if(!any_of(ignore_stop.begin(), ignore_stop.end(), [&x](int i){return i==x;})) {
            music_objects[x].stop();
        }
    }
}

bool Room::isSpriteClicked(sf::Sprite *sprite, sf::RenderWindow *window) {
    auto mouse_pos = sf::Mouse::getPosition(*window);
    auto translated_pos = window->mapPixelToCoords(mouse_pos);

    if(sprite->getGlobalBounds().contains(translated_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        return true;
    }

    return false;
}

int MainRoom::play(sf::RenderWindow* window, vector<sf::Sprite> sprites, vector<sf::Texture> textures, sf::Music* music_objects, vector<string> musics, vector<GameSound*> sounds) {
    //stop all sounds
    //this is a mandatory call for any room play
    vector<int> ignore = {0};
    stop_all_musics(musics, music_objects, ignore);

    //play bg sound
    music_objects[0].setLoop(true);
    if (music_objects[0].getStatus() != sf::Music::Status::Playing)
        music_objects[0].play();

    window->draw(refreshTexture(0, sprites, textures));

    //center title
    sprites[1].setPosition(sf::Vector2f((GAME_WIDTH - sprites[1].getLocalBounds().width) / 2, (GAME_HEIGHT - sprites[1].getLocalBounds().height) / 2));

    window->draw(refreshTexture(1, sprites, textures));

    if(isSpriteClicked(&sprites[1], window)) {
        sounds[0]->play();
        return GAME_STATE_PLAY;
    }

    return GAME_STATE_MAIN;
}

int PlayRoom::play(sf::RenderWindow* window, vector<sf::Sprite> sprites, vector<sf::Texture> textures, sf::Music* music_objects, vector<string> musics, vector<GameSound*> sounds) {
    vector<int> ignore = {};
    stop_all_musics(musics, music_objects, ignore);

    return GAME_STATE_PLAY;
}
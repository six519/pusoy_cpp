#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>
#include "room.hpp"
#include "game.hpp"
#include "exception.hpp"

using namespace std;

sf::Sprite refreshTexture(int index, vector<sf::Sprite> sprites, vector<sf::Texture> textures) {
    sprites[index].setTexture(textures[index]);
    return sprites[index];
}

void Room::play(sf::RenderWindow* window, vector<sf::Sprite> sprites, vector<sf::Texture> textures, sf::Music* music_objects, vector<string> musics) {
}

void Room::stop_all_musics(vector<string> musics, sf::Music* music_objects, vector<int> ignore_stop) {
    for(int x=0; x < musics.size(); x++) {
        if(!any_of(ignore_stop.begin(), ignore_stop.end(), [&x](int i){return i==x;})) {
            music_objects[x].stop();
        }
    }
}

void MainRoom::play(sf::RenderWindow* window, vector<sf::Sprite> sprites, vector<sf::Texture> textures, sf::Music* music_objects, vector<string> musics) {
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
}
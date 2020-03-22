#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "room.hpp"
#include "game.hpp"
#include "exception.hpp"
using namespace std;

sf::Sprite refreshTexture(int index, vector<sf::Sprite> sprites, vector<sf::Texture> textures) {
    sprites[index].setTexture(textures[index]);
    return sprites[index];
}

void Room::play(sf::RenderWindow* window, vector<sf::Sprite> sprites, vector<sf::Texture> textures, sf::Music* music_objects) {
}

void MainRoom::play(sf::RenderWindow* window, vector<sf::Sprite> sprites, vector<sf::Texture> textures, sf::Music* music_objects) {
    //play bg sound
    music_objects[0].setLoop(true);
    if (music_objects[0].getStatus() != sf::Music::Status::Playing)
        music_objects[0].play();

    window->draw(refreshTexture(0, sprites, textures));

    //center title
    sprites[1].setPosition(sf::Vector2f((GAME_WIDTH - sprites[1].getLocalBounds().width) / 2, (GAME_HEIGHT - sprites[1].getLocalBounds().height) / 2));

    window->draw(refreshTexture(1, sprites, textures));
}
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "game.hpp"
#include "exception.hpp"

void Game::init() {
    //initialization of all vars and other stuff here
    window = new sf::RenderWindow(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), GAME_TITLE, sf::Style::Titlebar | sf::Style::Close);
    state = GAME_STATE_MAIN;

    add_sprite("sprites/p2.jpg", true);
    add_sprite("sprites/title.png");

    add_music("sounds/bg_sound.ogg");

    init_musics();
    main_room = new MainRoom();
    play_room = new PlayRoom();
}

void Game::run() {
    //initialize game
    init();

    while (window->isOpen()) {
        event = new sf::Event();

        while (window->pollEvent(*event)){
            if (event->type == sf::Event::Closed) {
                window->close();
            }
        }

        window->clear();
        // draw sprites and stuff here
        switch(state) {
            case GAME_STATE_PLAY:
                state = play_room->play(window, sprites, textures, music_objects, musics);
            break;
            default:
                state = main_room->play(window, sprites, textures, music_objects, musics);
        }
        window->display();
    }
}

int Game::add_sprite(string filename, bool is_tiled) {
    sf::Texture texture;
    sf::Sprite sprite;

    if(!texture.loadFromFile(filename)) {
        throw FileGameException();
    }        
    sprite.setTexture(texture);
    if (is_tiled) {
        texture.setRepeated(true);
        sprite.setTextureRect(sf::IntRect(0, 0, GAME_WIDTH, GAME_HEIGHT));
    }
    sprites.push_back(sprite);
    textures.push_back(texture);

    return sprites.size() - 1;
}

int Game::add_music(string filename) {
    musics.push_back(filename);
    return musics.size() - 1;
}

void Game::init_musics() {
    music_objects = new sf::Music[musics.size()];

    for (int x=0; x < musics.size(); x++) {
        if(!music_objects[x].openFromFile(musics[x])) {
            throw FileGameException();
        }
    }
}
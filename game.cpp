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

    add_sounds("sounds/push2.ogg");

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
                state = play_room->play(window, sprites, textures, music_objects, musics, sounds);
            break;
            default:
                state = main_room->play(window, sprites, textures, music_objects, musics, sounds);
        }
        window->display();
    }
}

int Game::add_sprite(string filename, bool is_tiled) {
    sprites.push_back(new GameSprite());
    sprites.back()->init(filename, is_tiled);
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

void Game::add_sounds(string src) {
    sounds.push_back(new GameSound());
    sounds.back()->init(src);
}

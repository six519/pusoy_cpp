#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include "game.hpp"
#include "exception.hpp"
#include "resource.hpp"

void Game::init() {
    //initialization of all vars and other stuff here
    window = new sf::RenderWindow(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), GAME_TITLE, sf::Style::Titlebar | sf::Style::Close);
    state = GAME_STATE_MAIN;
    is_music_on = true;

    add_sprite("sprites/p2.jpg", true);
    add_sprite("sprites/title.png");
    add_sprite("sprites/button_sound_on.png");
    add_sprite("sprites/button_sound_off.png");
    add_sprite("sprites/button_reset.png");
    add_sprite("sprites/button_move.png");
    add_sprite("sprites/button_pass.png");

    //load card sprites and map it
    load_cards(CARD_PIPS, cards, true);
    load_cards(CARD_PIPS_STRAIGHT, cards_straight);
    load_cards(CARD_PIPS_FLUSH, cards_flush);

    add_music("sounds/bg_sound.ogg");

    add_sounds("sounds/push2.ogg");

    main_room = new MainRoom(this);
    play_room = new PlayRoom(this);
}

void Game::load_cards(vector<string> pips, vector<GameCard> &game_card, bool make_map) {
    for(int x=0; x<pips.size(); x++) {
        for(int x2=0; x2<CARD_SUITES.size(); x2++) {
            if (make_map) {
                int index = add_sprite("sprites/cards/" + pips[x] + "_of_" + CARD_SUITES[x2] + ".png");
                sprite_mappings.insert(pair<string, int>(pips[x] + CARD_SUITES[x2], index));
            }
            GameCard this_card;
            this_card.name = pips[x];
            this_card.suit = CARD_SUITES[x2];
            game_card.push_back(this_card);
        }
    }
}

void Game::run() {
    //initialize game
    init();
    //init main room
    main_room->init();

    while (window->isOpen()) {
        event = new sf::Event();

        while (window->pollEvent(*event)){
            if (event->type == sf::Event::Closed) {
                window->close();
            }
            if(event->type == sf::Event::MouseButtonPressed) {
                switch(state) {
                    case GAME_STATE_PLAY:
                        play_room->click();
                    break;
                    default:
                        main_room->click();
                }
            }
        }

        window->clear();
        // draw sprites here
        switch(state) {
            case GAME_STATE_PLAY:
                play_room->draw();
            break;
            default:
                main_room->draw();
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
    musics.push_back(new GameMusic());
    musics.back()->init(filename);
    return musics.size() - 1;
}

void Game::add_sounds(string src) {
    sounds.push_back(new GameSound());
    sounds.back()->init(src);
}

vector<int> Game::shuffle_cards() {
    vector<int> index_cards;

    while (index_cards.size() < 52) {
        int x = rand() % (52 - 0) +  0;
        if(!any_of(index_cards.begin(), index_cards.end(), [&x](int i){return i==x;})) {
            index_cards.push_back(x);
        }
    }

    return index_cards;
}
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include "room.hpp"
#include "game.hpp"
#include "exception.hpp"

using namespace std;

Room::Room(Game* game) {
    this->game = game;
}

void Room::draw() {}

void Room::stop_all_musics(vector<int> ignore_stop) {
    for(int x=0; x < game->musics.size(); x++) {
        if(!any_of(ignore_stop.begin(), ignore_stop.end(), [&x](int i){return i==x;})) {
            game->musics[x]->stop();
        }
    }
}

bool Room::is_sprite_clicked(sf::Sprite sprite) {
    auto mouse_pos = sf::Mouse::getPosition(*game->window);
    auto translated_pos = game->window->mapPixelToCoords(mouse_pos);

    if(sprite.getGlobalBounds().contains(translated_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        return true;
    }

    return false;
}

MainRoom::MainRoom(Game* game): Room(game) {}

void MainRoom::init() {
    vector<int> ignore = {0};
    stop_all_musics(ignore);

    //play bg sound
    game->musics[0]->set_loop(true);
    if (!game->musics[0]->is_playing())
        game->musics[0]->play();

    //center title
    game->sprites[1]->set_position(sf::Vector2f((GAME_WIDTH - game->sprites[1]->get_sprite().getLocalBounds().width) / 2, (GAME_HEIGHT - game->sprites[1]->get_sprite().getLocalBounds().height) / 2));
}

void MainRoom::click() {
    if(is_sprite_clicked(game->sprites[1]->get_sprite())) {
        game->sounds[0]->play();
        game->play_room->init();
        game->state = GAME_STATE_PLAY;
    }
}

void MainRoom::draw() {
    //main background
    game->window->draw(game->sprites[0]->get_sprite());
    game->window->draw(game->sprites[1]->get_sprite());
}

PlayRoom::PlayRoom(Game* game): Room(game) {}

void PlayRoom::init() {
    //generate random cards
    vector<int> random_cards = game->shuffle_cards();
    vector<int> temporary_cards;
    int current_x = (GAME_WIDTH / 2) - (CARD_TOTAL_WIDTH / 2);
    int current_y = CARD_PLAYER_Y;

    game->player_cards.clear();

    //generate card for the user
    for(int x=0; x < 13; x++) {
        int index = random_cards.back();
        random_cards.pop_back();
        temporary_cards.push_back(index);
    }

    //sort cards from lowest to highest
    sort(temporary_cards.begin(), temporary_cards.end());

    //push card indexes for user
    game->player_cards.push_back(temporary_cards);
    temporary_cards.clear();

    //set initial positions of the user cards
    for(int x=0; x < 13; x++) {
        //get card reference first
        GameCard this_card = game->cards[game->player_cards[0][x]];
        //get sprite mapping
        int sprite_index = game->sprite_mappings[this_card.name + this_card.suit];
        game->sprites[sprite_index]->set_position(sf::Vector2f(current_x, current_y));

        current_x += CARD_PEEK_WIDTH;

        if(x == 12) {
            int total_player_x = current_x + (CARD_WIDTH - CARD_PEEK_WIDTH);
            //pass button
            int last_current_x = ((GAME_WIDTH - total_player_x) / 2) - (game->sprites[6]->get_sprite().getLocalBounds().width / 2);
            int last_current_y = (((GAME_HEIGHT - current_y) /2) - (game->sprites[6]->get_sprite().getLocalBounds().height / 2)) + current_y;
            game->sprites[6]->set_position(sf::Vector2f(last_current_x, last_current_y));
            //move button
            last_current_x = (((GAME_WIDTH - total_player_x) / 2) - (game->sprites[5]->get_sprite().getLocalBounds().width / 2)) + total_player_x;
            last_current_y = (((GAME_HEIGHT - current_y) /2) - (game->sprites[5]->get_sprite().getLocalBounds().height / 2)) + current_y; 
            game->sprites[5]->set_position(sf::Vector2f(last_current_x, last_current_y));
        }
    }

    //music on/off button
    game->sprites[2]->set_position(sf::Vector2f(10, 10));
    game->sprites[3]->set_position(sf::Vector2f(10, 10));

    //reset button
    game->sprites[4]->set_position(sf::Vector2f(20 + game->sprites[2]->get_sprite().getLocalBounds().width, 10));
}

void PlayRoom::click() {
    if(is_sprite_clicked(game->sprites[2]->get_sprite())) {
        game->sounds[0]->play();
        if(game->is_music_on) {
            game->is_music_on = false;
            game->musics[0]->pause();
        } else {
            game->is_music_on = true;
            game->musics[0]->play();
        }
    }

    if(is_sprite_clicked(game->sprites[4]->get_sprite())) {
        //reset button
        game->sounds[0]->play();
        //reset all here
        game->play_room->init();
    }
}

void PlayRoom::draw() {
    //main background
    game->window->draw(game->sprites[0]->get_sprite());
    //music button
    if(game->is_music_on) {
        game->window->draw(game->sprites[2]->get_sprite());
    } else {
        game->window->draw(game->sprites[3]->get_sprite());
    }
    //reset button
    game->window->draw(game->sprites[4]->get_sprite());

    //draw cards
    //draw user cards
    for(int x=0; x < game->player_cards[0].size(); x++) {
        GameCard this_card = game->cards[game->player_cards[0][x]];
        int sprite_index = game->sprite_mappings[this_card.name + this_card.suit];

        if(this_card.show)
        game->window->draw(game->sprites[sprite_index]->get_sprite());
    }

    //draw game buttons
    game->window->draw(game->sprites[5]->get_sprite());
    game->window->draw(game->sprites[6]->get_sprite());
}
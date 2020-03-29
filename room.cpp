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

    //set title y to out of screen
    game->title_y = 0 - game->sprites[1]->get_sprite().getLocalBounds().height;
    game->sprites[1]->set_position(sf::Vector2f((GAME_WIDTH - game->sprites[1]->get_sprite().getLocalBounds().width) / 2, game->title_y));
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
    //title sprite
    float center_y = (GAME_HEIGHT - game->sprites[1]->get_sprite().getLocalBounds().height) / 2;

    if (game->title_y < center_y) {
        //sliding in title
        game->title_y += 0.1;
        game->sprites[1]->set_position(sf::Vector2f((GAME_WIDTH - game->sprites[1]->get_sprite().getLocalBounds().width) / 2, game->title_y));
    }
        
    game->window->draw(game->sprites[1]->get_sprite());
}

PlayRoom::PlayRoom(Game* game): Room(game) {}

void PlayRoom::init() {
    //generate random cards
    vector<int> random_cards = game->shuffle_cards();
    vector<int> temporary_cards;
    int current_x = (GAME_WIDTH / 2) - (CARD_TOTAL_WIDTH / 2);
    int current_y = CARD_PLAYER_Y;

    //tracker of what current suit/current turn/last turn/status text show
    game->whos_turn = -1;
    game->last_turn = -1;
    game->suite_turn = -1;
    game->show_status = false;
    game->timer_running = false;
    game->play_state = PLAY_STATE_SHOW_WHOS_TURN;

    //clear distribution of cards to players
    game->player_cards.clear();

    //clear selected cards
    game->selected_cards_index.clear();

    //generate random opponent names
    game->scramble_names();
    //set names text options
    game->text_name.setFont(game->fonts[0]);
    game->text_name.setCharacterSize(24); //24px
    game->text_name.setFillColor(sf::Color::Black);
    game->text_name.setStyle(sf::Text::Bold);
    game->text_name.setOutlineColor(sf::Color::White);
    game->text_name.setOutlineThickness(3);

    //status text from center
    game->text_status.setFont(game->fonts[0]);
    game->text_status.setCharacterSize(50); //50px
    game->text_status.setFillColor(sf::Color::Black);
    game->text_status.setStyle(sf::Text::Bold);
    game->text_status.setOutlineColor(sf::Color::White);
    game->text_status.setOutlineThickness(3);

    //distribute cards
    for(int x2=0; x2<4; x2++) {
        //generate card per player
        for(int x=0; x < 13; x++) {
            int index = random_cards.back();
            random_cards.pop_back();
            temporary_cards.push_back(index);

            //determine first move
            if (index == 0)
                game->whos_turn = x2;
        }

        //sort cards from lowest to highest
        sort(temporary_cards.begin(), temporary_cards.end());

        //push card indexes per player
        game->player_cards.push_back(temporary_cards);
        temporary_cards.clear();
    }

    //reset GameCard objects property to default
    for(int x=0; x < game->cards.size();x++) {
        game->cards[x].show = true;
        game->cards[x].is_selected = false;
    }

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
    //back to main button
    game->sprites[8]->set_position(sf::Vector2f(90 + game->sprites[8]->get_sprite().getLocalBounds().width, 10));

    //start processing of play state
    process_state();
    start_timer();
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

    if(is_sprite_clicked(game->sprites[8]->get_sprite())) {
        //return to main button
        game->sounds[0]->play();
        game->main_room->init();
        game->state = GAME_STATE_MAIN;
    }

    //your cards click events
    //reverse loop
    for(int x=game->player_cards[0].size()-1; x >= 0; x--) {

        if (game->cards[game->player_cards[0][x]].show) {
            int sprite_index = game->sprite_mappings[game->cards[game->player_cards[0][x]].name + game->cards[game->player_cards[0][x]].suit];
            if(is_sprite_clicked(game->sprites[sprite_index]->get_sprite())) {
                cout << game->cards[game->player_cards[0][x]].name << game->cards[game->player_cards[0][x]].suit << endl;
                if (game->cards[game->player_cards[0][x]].is_selected) {
                    //card selected, make it unselected
                    game->cards[game->player_cards[0][x]].is_selected = false;
                    //remove the card from selected cards
                    game->selected_cards_index.erase(remove(game->selected_cards_index.begin(), game->selected_cards_index.end(), x), game->selected_cards_index.end());
                    game->sounds[1]->play();
                } else {
                    //card unselected, make it selected
                    if (game->selected_cards_index.size() < 5) {
                        // ok to select
                        game->cards[game->player_cards[0][x]].is_selected = true;
                        game->selected_cards_index.push_back(x);
                        game->sounds[1]->play();
                    } else {
                        //do nothing, just play invalid sound
                        game->sounds[2]->play();
                    }
                }
                break; //to stop clicking card from the bottom
            }   
        }
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
    //back to main button
    game->window->draw(game->sprites[8]->get_sprite());

    //draw cards
    //draw user cards
    for(int x=0; x < game->player_cards[0].size(); x++) {
        GameCard this_card = game->cards[game->player_cards[0][x]];
        int sprite_index = game->sprite_mappings[this_card.name + this_card.suit];

        if(this_card.show) {
            float current_x = game->sprites[sprite_index]->get_sprite().getPosition().x;
            if (this_card.is_selected) {
                game->sprites[sprite_index]->set_position(sf::Vector2f(current_x, CARD_PLAYER_Y - CARD_SELECTED_Y));
            } else {
                game->sprites[sprite_index]->set_position(sf::Vector2f(current_x, CARD_PLAYER_Y));
            }
            game->window->draw(game->sprites[sprite_index]->get_sprite());
        }
    }

    //draw cards and names for AI
    for(int x=0; x < 3; x++) {
        int current_x;
        int current_y;
        int name_x;

        game->text_name.setString(AI_PLAYER_NAMES_LIST[game->player_names[x]]);

        if(x == 0) {
            //AI 1
            current_x = GAME_EDGE_PADDING;
            current_y = (GAME_HEIGHT / 2) - (CARD_BACK_HEIGHT / 2);
            name_x = (((CARD_PEEK_WIDTH_AI * 12 + CARD_BACK_WIDTH) / 2) - (game->text_name.getLocalBounds().width / 2)) + GAME_EDGE_PADDING;
        } else if(x == 1) {
            //AI 2
            current_x = (GAME_WIDTH / 2) - ((CARD_PEEK_WIDTH_AI * 12 + CARD_BACK_WIDTH) / 2);
            current_y = GAME_EDGE_PADDING;
            name_x = (GAME_WIDTH / 2) - (game->text_name.getLocalBounds().width / 2);
        } else {
            //AI 3
            current_x = GAME_WIDTH - (CARD_PEEK_WIDTH_AI * 12 + CARD_BACK_WIDTH) - GAME_EDGE_PADDING;
            current_y = (GAME_HEIGHT / 2) - (CARD_BACK_HEIGHT / 2);
            int additional_width = GAME_WIDTH - (CARD_PEEK_WIDTH_AI * 12 + CARD_BACK_WIDTH + GAME_EDGE_PADDING);
            name_x = (((CARD_PEEK_WIDTH_AI * 12 + CARD_BACK_WIDTH) / 2) - (game->text_name.getLocalBounds().width / 2)) + additional_width;
        }

        //draw cards
        for(int x2=0; x2 < game->player_cards[x+1].size(); x2++) {
            game->sprites[7]->set_position(sf::Vector2f(current_x, current_y));
            game->window->draw(game->sprites[7]->get_sprite());
            current_x += CARD_PEEK_WIDTH_AI;
        }

        game->text_name.setPosition(name_x, current_y + CARD_BACK_HEIGHT + GAME_EDGE_PADDING);
        game->window->draw(game->text_name);
    }

    //draw game buttons
    game->window->draw(game->sprites[5]->get_sprite());
    game->window->draw(game->sprites[6]->get_sprite());

    //handle timer
    if (game->timer_running) {
        if ((int)game->timer.getElapsedTime().asSeconds() == 1) {
            process_state();
            game->timer.restart();
        }
    }

    //draw status text
    if (game->show_status) {
        game->text_status.setPosition((GAME_WIDTH / 2) - (game->text_status.getLocalBounds().width / 2), (GAME_HEIGHT / 2) - (game->text_name.getLocalBounds().height / 2));
        game->window->draw(game->text_status);
    }
}

void PlayRoom::process_state() {
    string whos_turn_status;
    string with_control;
    if (game->play_state == PLAY_STATE_SHOW_WHOS_TURN) {
        //show status who's turn it is
        if (game->suite_turn == -1 || game->last_turn == game->whos_turn)
            with_control = " & control";

        if (game->whos_turn > 0) {
            //AI
            game->text_status.setString(AI_PLAYER_NAMES_LIST[game->player_names[game->whos_turn - 1]] + "\'s turn" + with_control + "...");
        } else {
            //Your turn
            game->text_status.setString("Your turn" + with_control + "...");
        }
        game->play_state = PLAY_STATE_CARD_PLACE;
        game->show_status = true; //to show the status in draw function
        game->sounds[2]->play();
    } else {
        //PLAY_STATE_CARD_PLACE
        //place AI card on the board
        game->show_status = false; //hide status
    }
}

void PlayRoom::start_timer() {
    game->timer_running = true;
    game->timer.restart();
}

void PlayRoom::stop_timer() {
    game->timer_running = false;
}
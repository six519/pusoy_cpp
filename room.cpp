#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>
#include "room.hpp"
#include "game.hpp"
#include "exception.hpp"

using namespace std;

Room::Room(Game* game) {
    this->game = game;
}

int Room::play() {

    return GAME_STATE_MAIN;
}

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

MainRoom::MainRoom(Game* game): Room(game) {

}

int MainRoom::play() {
    vector<int> ignore = {0};
    stop_all_musics(ignore);

    //play bg sound
    game->musics[0]->set_loop(true);
    if (!game->musics[0]->is_playing())
        game->musics[0]->play();

    //main background
    game->window->draw(game->sprites[0]->get_sprite());

    //center title
    game->sprites[1]->set_position(sf::Vector2f((GAME_WIDTH - game->sprites[1]->get_sprite().getLocalBounds().width) / 2, (GAME_HEIGHT - game->sprites[1]->get_sprite().getLocalBounds().height) / 2));

    game->window->draw(game->sprites[1]->get_sprite());

    if(is_sprite_clicked(game->sprites[1]->get_sprite())) {
        game->sounds[0]->play();
        return GAME_STATE_PLAY;
    }

    return GAME_STATE_MAIN;
}

PlayRoom::PlayRoom(Game* game): Room(game) {

}

int PlayRoom::play() {
    //main background
    game->window->draw(game->sprites[0]->get_sprite());

    return GAME_STATE_PLAY;
}
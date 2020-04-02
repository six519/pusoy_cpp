#ifndef _ROOM_H_
#define _ROOM_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "resource.hpp"

using namespace std;

class Game;

class Room {
    public:
        Room(Game* game);
        void draw();
        void init();
        void click();
        void stop_all_musics(vector<int> ignore_stop);
        bool is_sprite_clicked(sf::Sprite sprite);
    protected:
        Game* game;
};

class MainRoom: public Room {
    public:
        MainRoom(Game* game);
        void draw();
        void init();
        void click();
};

class PlayRoom: public Room {
    public:
        PlayRoom(Game* game);
        void draw();
        void init();
        void click();
        void process_state();
        void start_timer();
        void stop_timer();
        int get_card_index(vector<GameCard> cards_to_check, int card_index);
        int get_string_index(vector<string> vector_to_check, string value);
        void check_whos_turn();
        bool sort_straight(int n1, int n2);
        bool sort_flush(int n1, int n2);
        int get_card_index_by_gamecard(GameCard gc);
        void your_control_turn(bool &is_valid_turn);
        void enemy_control_turn();
};

#endif
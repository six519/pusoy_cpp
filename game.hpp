#ifndef _GAME_H_
#define _GAME_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <map>
#include "room.hpp"
#include "resource.hpp"

using namespace std;

const string GAME_TITLE = "Pusoy Dos";
const int GAME_WIDTH = 1024;
const int GAME_HEIGHT = 600;
const int GAME_STATE_MAIN = 0;
const int GAME_STATE_PLAY = 1;
const int GAME_EDGE_PADDING = 5;
const int CARD_PEEK_WIDTH = 30;
const int CARD_PEEK_WIDTH_AI = 10;
const int CARD_SELECTED_Y = 20;
const int CARD_WIDTH = 120;
const int CARD_HEIGHT = 174;
const int CARD_TOTAL_WIDTH = CARD_PEEK_WIDTH * 12 + CARD_WIDTH;
const int CARD_PLAYER_Y = GAME_HEIGHT - CARD_HEIGHT - GAME_EDGE_PADDING;
const int CARD_BACK_WIDTH = 110;
const int CARD_BACK_HEIGHT = 160;
const int PLAY_STATE_NONE = 0;
const int PLAY_STATE_SHOW_WHOS_TURN = 1;
const int PLAY_STATE_CARD_PLACE = 2;
const int TURN_SINGLE = 0;
const int TURN_PAR = 1;
const int TURN_TRIO = 2;
const int TURN_STRAIGHT = 3;
const int TURN_FLUSH = 4;
const int TURN_FULL_HOUSE = 5;
const int TURN_QUADRA = 6;
const int TURN_ROYAL_FLUSH = 7;

const vector<string> CARD_SUITES = {
    "clubs",
    "spades",
    "hearts",
    "diamonds"
};

const vector<string> CARD_PIPS = {
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "jack",
    "queen",
    "king",
    "ace",
    "2"
};

const vector<string> CARD_PIPS_STRAIGHT = {
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "jack",
    "queen",
    "king",
    "ace"
};

const vector<string> CARD_PIPS_FLUSH = {
    "ace",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "jack",
    "queen",
    "king"
};

const vector<string> AI_PLAYER_NAMES_LIST = {
    "Uriel",
    "Patrick",
    "Umiko",
    "Charmaine",
    "Buboy",
    "Unisse",
    "Rodolfo",
    "Aurora",
    "Ruel",
    "Fernando",
    "Ferdinand",
    "Yannah",
    "Yenyen",
    "Joan",
    "Rodel",
    "Tim",
    "Trisha",
    "Chat",
    "Myrna",
    "Venus",
    "Unica"
};

class Game {
    public:
        sf::RenderWindow* window;
        sf::Event* event;
        vector<GameSprite*> sprites;
        vector<sf::Texture> textures;
        vector<GameMusic*> musics;
        vector<GameSound*> sounds;
        bool is_music_on;
        vector<GameCard> cards;
        vector<int> player_names;
        vector<GameCard> cards_straight;
        vector<GameCard> cards_flush;
        map<string, int> sprite_mappings;
        vector<vector<int>> player_cards;
        vector<sf::Font> fonts;
        sf::Text text_name;
        sf::Text text_status;
        float title_y;
        vector<int> selected_cards_index;
        vector<int> placed_cards_index;
        int whos_turn;
        int last_turn;
        int suite_turn;
        int play_state;
        bool show_status;
        sf::Clock timer;
        bool timer_running;
        
        MainRoom* main_room;
        PlayRoom* play_room;

        int state;
        void run();
        int add_sprite(string filename, bool is_tiled = false);
        int add_music(string filename);
        int add_font(string filename);

        void add_sounds(string src);
        void load_cards(vector<string> pips, vector<GameCard> &game_card, bool make_map = false);
        void scramble_names();
        vector<int> shuffle_cards();

    private:
        void init();
};

#endif
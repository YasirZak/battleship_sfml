#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <string>


// Scalling constant for all game entities (sprites)
const float global_scale = 3.0f;

enum class GameState{
    Preparation,
    Shooting
};

class Grid {

private:

    // Grid sprite and texture
    float x; float y;
    sf::Texture grid_texture;
    sf::Sprite grid;

    sf::Texture white_peg_texture;
    sf::Sprite white_peg;
    std::vector<sf::Sprite> white_pegs;

    sf::Texture red_peg_texture;
    sf::Sprite red_peg;
    std::vector<sf::Sprite> red_pegs;

    // Ships

    bool orientation_vertical;
    std::vector<sf::Sprite> ships;
    sf::RectangleShape place_holder;

    sf::Sprite carrier;
    sf::Sprite battleship;
    sf::Sprite cruiser;
    sf::Sprite submarine;
    sf::Sprite destroyer;

    sf::Texture carrier_texture;
    sf::Texture battleship_texture;
    sf::Texture cruiser_texture;
    sf::Texture submarine_texture;
    sf::Texture destroyer_texture;

    // Initializations
    void init_variables();
    void init_pegs();
    void init_ships();

public:
    // Constructors / Destructors
    Grid(float x, float y);
    // virtual ~Grid();

    // Drawing grid
    void draw_grid(sf::RenderWindow* window);

    // Placing pegs
    void place_white_peg(int x, int y);
    void place_red_peg(int x, int y);

    // Placing ships
    void place_ship(int x, int y);

    void place_carrier(int x, int y);
    void place_battleship(int x, int y);
    void place_cruiser(int x, int y);
    void place_submarine(int x, int y);
    void place_destroyer(int x, int y);

    bool all_ships_placed();

    // Drawing pegs
    void draw_pegs(sf::RenderWindow* window);

    // Update place holder
    void update_place_holder(int x, int y);

    // Draw place holder
    void draw_place_holder(sf::RenderWindow* window);

    // Drawing ships
    void draw_ships(sf::RenderWindow* window);

    // Change orientation
    void change_orientation();

    // Within grid
    bool is_within(sf::Vector2f position);

    // ships size
    int ships_size();

    // Get relative position
    std::pair<int,int> get_rel_pos(sf::Vector2f position);

};

class Game {

private:

    // Variables

    sf::RenderWindow* window;
    sf::VideoMode video_mode;
    sf::Event event;

    // Mouse position
    sf::Vector2i mouse_position_window;
    sf::Vector2f mouse_position_view;

    // Game objects
    Grid player_grid;
    Grid opponent_grid;

    // Game text
    sf::Font font;

    // Status texts
    sf::Text place_carrier_text;
    sf::Text place_battleship_text;
    sf::Text place_cruiser_text;
    sf::Text place_submarine_text;
    sf::Text place_destroyer_text;
    sf::Text rotate_text;

    sf::Text your_turn;
    sf::Text opponent_turn;

    // Initializations

    void init_variables();
    void init_window();
    void init_text();


public:

    // Game state variable
    GameState state;

    // Constructor / Destructor
    Game();
    virtual ~Game();

    // Accessors
    bool running();

    // Event polling
    void poll_events();

    // Update Mouse position
    void update_mouse_position();

    // Processign mouse input
    void process_mouse_input();

    // Update and render the game
    void update();
    void render();
    
};
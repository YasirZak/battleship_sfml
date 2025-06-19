#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>


// Scalling constant for all game entities (sprites)
const float global_scale = 3.0f;

enum class GameState{
    Menu,
    Playing,
    GameOver
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

    // Initializations
    void init_variables();
    void init_pegs();

public:
    // Constructors / Destructors
    Grid(float x, float y);
    // virtual ~Grid();

    // Drawing grid
    void draw_grid(sf::RenderWindow* window);

    // Placing pegs
    void place_white_peg(int x, int y);
    void place_red_peg(int x, int y);

    // Drawing pegs
    void draw_pegs(sf::RenderWindow* window);

    // Within grid
    bool is_within(sf::Vector2f position);

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


    // Initializations

    void init_variables();
    void init_window();


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
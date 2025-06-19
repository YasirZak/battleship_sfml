#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>


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

};

class Game {

private:

    // Variables

    sf::RenderWindow* window;
    sf::VideoMode video_mode;
    sf::Event event;

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

    // Update and render the game
    void update();
    void render();
    
};
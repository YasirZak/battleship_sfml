#include "Classes.hpp"

/*
    Definition of functions in the Game class
*/

// Constructor / Destructor

Game::Game() 
:opponent_grid(5.0f * global_scale,10.0f * global_scale) ,player_grid(5.0f * global_scale,131.0f*global_scale)
{

    // Initializing everything

    this->init_variables();
    this->init_window();
}

Game::~Game() {
    delete this->window;
}

// Private functions

void Game::init_variables() {
    this->window = nullptr;
    this->state = GameState::Playing;
}


void Game::init_window() {

    // Setting window dimensions
    this->video_mode.height = 252*3; // Scaled 3x
    this->video_mode.width = 121*3;

    // initializing window
    this->window = new sf::RenderWindow(this->video_mode, "Battleship");
    this->window->setFramerateLimit(60);
}

// Public funcitons

// Accesor

bool Game::running(){
    return this->window->isOpen();
}

// Event polling

void Game::poll_events() {
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        
        default:
            break;
        }
    }
    
}

// Update and Render

void Game::update() {

}

void Game::render() {
    this->window->clear();

    // Draw elements here

    // Grid
    this->player_grid.draw_grid(this->window);
    this->opponent_grid.draw_grid(this->window);

    // Pegs
    this->player_grid.draw_pegs(this->window);
    this->opponent_grid.draw_pegs(this->window);

    this->window->display();
}
#include "Classes.hpp"

/*
    Definition of functions in the Game class
*/

// Constructor / Destructor

Game::Game() 
:opponent_grid(5.0f * global_scale,10.0f * global_scale + 50) ,player_grid(5.0f * global_scale,131.0f*global_scale + 50)
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
    this->state = GameState::Preparation;
}

void Game::init_window() {

    // Setting window dimensions
    this->video_mode.height = 252*3 + 50; // Scaled 3x
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

// Update Mouse position
void Game::update_mouse_position(){
    /*
        Updating mouse position
    */
    this->mouse_position_window = sf::Mouse::getPosition(*this->window);
    this->mouse_position_view = this->window->mapPixelToCoords(mouse_position_window);
}

// Processing mouse input
void Game::process_mouse_input() {
    /*
        Game behaviour based on clicking position
    */
   switch (this->state)
   {

    // Initial preperation stage
    case GameState::Preparation:
        if(this->player_grid.is_within(mouse_position_view)) {
            // Getting relative position
            std::pair<int,int> rel_mouse_pos = this->player_grid.get_rel_pos(mouse_position_view);
            this->player_grid.place_ship(rel_mouse_pos.first,rel_mouse_pos.second);

            // Switching game state after 
            if(this->player_grid.all_ships_placed()) {
                std::cout << "Game state : Shooting\n";
                this->state = GameState::Shooting;
            }
        }
        break;
   
    // Second shooting stage
   case GameState::Shooting:
        if(this->player_grid.is_within(mouse_position_view)) {
            std::pair<int,int> rel_mouse_pos = this->player_grid.get_rel_pos(mouse_position_view);
            this->player_grid.place_white_peg(rel_mouse_pos.first,rel_mouse_pos.second);
        }

        if(this->opponent_grid.is_within(mouse_position_view)) {
            std::pair<int,int> rel_mouse_pos = this->opponent_grid.get_rel_pos(mouse_position_view);
            this->opponent_grid.place_red_peg(rel_mouse_pos.first,rel_mouse_pos.second);
        }
        break;
   }
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
        
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::R) {
                this->player_grid.change_orientation();
            }

            break;

        case sf::Event::MouseButtonPressed:

            if(event.mouseButton.button == sf::Mouse::Left) {
                this->process_mouse_input();
            }

            break;

        default:
            break;
        }
    }
    
}

// Update and Render

void Game::update() {
    /*
        Updating game state
    */
    
    if(this->state == GameState::Preparation) {
        if(this->player_grid.is_within(mouse_position_view)) {
                // Getting relative position
                std::pair<int,int> rel_mouse_pos = this->player_grid.get_rel_pos(mouse_position_view);
                this->player_grid.update_place_holder(rel_mouse_pos.first,rel_mouse_pos.second);
        }
    }
    
    this->update_mouse_position();
}

void Game::render() {
    /*
        Rendering game objects
    */
   
    this->window->clear();

    // Draw elements here

    // Grid
    this->player_grid.draw_grid(this->window);
    this->opponent_grid.draw_grid(this->window);

    if(this->state == GameState::Preparation && this->player_grid.is_within(mouse_position_view)) {
        this->player_grid.draw_place_holder(this->window);
    }

    // Ships
    this->player_grid.draw_ships(this->window);

    // Pegs
    this->player_grid.draw_pegs(this->window);
    this->opponent_grid.draw_pegs(this->window);

    this->window->display();
}
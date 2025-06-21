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
    this->init_text();

    // Automatically place carriers for opponent
    this->opponent_grid.auto_place_ship();
}

Game::~Game() {
    delete this->window;
}

// Private functions

void Game::init_variables() {
    this->window = nullptr;
    this->state = GameState::Preparation;
    this->player_turn = true;
}

void Game::init_window() {

    // Setting window dimensions
    this->video_mode.height = 252*3 + 50; // Scaled 3x
    this->video_mode.width = 121*3;

    // initializing window
    this->window = new sf::RenderWindow(this->video_mode, "Battleship");
    this->window->setFramerateLimit(60);
}

void Game::init_text() {

    // Status texts

    sf::Vector2u window_size = this->window->getSize();

    if(!this->font.loadFromFile("ARIAL.TTF")) {
        std::cout << "Failed to load font\n";
    }

    this->place_carrier_text.setFont(font);
    this->place_carrier_text.setStyle(sf::Text::Bold);
    this->place_carrier_text.setFillColor(sf::Color::White);
    this->place_carrier_text.setCharacterSize(24);
    this->place_carrier_text.setString("Place your Carrier");

    sf::FloatRect startBounds = this->place_carrier_text.getGlobalBounds();
    this->place_carrier_text.setOrigin(      // setting origin of text to center of text
        startBounds.left + startBounds.width / 2.f,
        startBounds.top + startBounds.height / 2.f
    );

    this->place_carrier_text.setPosition(window_size.x /2.f,25);

    this->place_battleship_text.setFont(font);
    this->place_battleship_text.setStyle(sf::Text::Bold);
    this->place_battleship_text.setFillColor(sf::Color::White);
    this->place_battleship_text.setCharacterSize(24);
    this->place_battleship_text.setString("Place your Battleship");

    startBounds = this->place_battleship_text.getGlobalBounds();
    this->place_battleship_text.setOrigin(      // setting origin of text to center of text
        startBounds.left + startBounds.width / 2.f,
        startBounds.top + startBounds.height / 2.f
    );

    this->place_battleship_text.setPosition(window_size.x /2.f,25);
;
    this->place_cruiser_text.setFont(font);
    this->place_cruiser_text.setStyle(sf::Text::Bold);
    this->place_cruiser_text.setFillColor(sf::Color::White);
    this->place_cruiser_text.setCharacterSize(24);
    this->place_cruiser_text.setString("Place your Cruiser");

    startBounds = this->place_cruiser_text.getGlobalBounds();
    this->place_cruiser_text.setOrigin(      // setting origin of text to center of text
        startBounds.left + startBounds.width / 2.f,
        startBounds.top + startBounds.height / 2.f
    );

    this->place_cruiser_text.setPosition(window_size.x /2.f,25);

    this->place_submarine_text.setFont(font);
    this->place_submarine_text.setStyle(sf::Text::Bold);
    this->place_submarine_text.setFillColor(sf::Color::White);
    this->place_submarine_text.setCharacterSize(24);
    this->place_submarine_text.setString("Place your Submarine");

    startBounds = this->place_submarine_text.getGlobalBounds();
    this->place_submarine_text.setOrigin(      // setting origin of text to center of text
        startBounds.left + startBounds.width / 2.f,
        startBounds.top + startBounds.height / 2.f
    );

    this->place_submarine_text.setPosition(window_size.x /2.f,25);

    this->place_destroyer_text.setFont(font);
    this->place_destroyer_text.setStyle(sf::Text::Bold);
    this->place_destroyer_text.setFillColor(sf::Color::White);
    this->place_destroyer_text.setCharacterSize(24);
    this->place_destroyer_text.setString("Place your Destroyer");

    startBounds = this->place_destroyer_text.getGlobalBounds();
    this->place_destroyer_text.setOrigin(      // setting origin of text to center of text
        startBounds.left + startBounds.width / 2.f,
        startBounds.top + startBounds.height / 2.f
    );

    this->place_destroyer_text.setPosition(window_size.x /2.f,25);

    this->rotate_text.setFont(font);
    this->rotate_text.setFillColor(sf::Color::White);
    this->rotate_text.setCharacterSize(18);
    this->rotate_text.setString("Press R to rotate");

    startBounds = this->rotate_text.getGlobalBounds();
    this->rotate_text.setOrigin(      // setting origin of text to center of text
        startBounds.left + startBounds.width / 2.f,
        startBounds.top + startBounds.height / 2.f
    );

    this->rotate_text.setPosition(window_size.x /2.f,50);

    this->your_turn.setFont(font);
    this->your_turn.setStyle(sf::Text::Bold);
    this->your_turn.setFillColor(sf::Color::White);
    this->your_turn.setCharacterSize(24);
    this->your_turn.setString("Shoot!");

    startBounds = this->your_turn.getGlobalBounds();
    this->your_turn.setOrigin(      // setting origin of text to center of text
        startBounds.left + startBounds.width / 2.f,
        startBounds.top + startBounds.height / 2.f
    );

    this->your_turn.setPosition(window_size.x /2.f,25);

    this->opponent_turn.setFont(font);
    this->opponent_turn.setStyle(sf::Text::Bold);
    this->opponent_turn.setFillColor(sf::Color::White);
    this->opponent_turn.setCharacterSize(24);
    this->opponent_turn.setString("Opponent is thinking");

    startBounds = this->opponent_turn.getGlobalBounds();
    this->opponent_turn.setOrigin(      // setting origin of text to center of text
        startBounds.left + startBounds.width / 2.f,
        startBounds.top + startBounds.height / 2.f
    );

    this->opponent_turn.setPosition(window_size.x /2.f,25);
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
        if(this->opponent_grid.is_within(mouse_position_view)) {
            if(this->opponent_grid.shoot(this->mouse_position_view)) {
                this->player_grid.noob_opponent_shoot();
            };
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

    // Text
    switch (this->player_grid.ships_size())
    {
    case 0:
        this->window->draw(place_carrier_text);
        this->window->draw(rotate_text);
        break;

    case 1:
        this->window->draw(place_battleship_text);
        this->window->draw(rotate_text);
        break;

    case 2:
        this->window->draw(place_cruiser_text);
        this->window->draw(rotate_text);
        break;

    case  3:
        this->window->draw(place_submarine_text);
        this->window->draw(rotate_text);
        break;

    case 4:
        this->window->draw(place_destroyer_text);
        this->window->draw(rotate_text);
        break;
    
    default:
        this->window->draw(your_turn);
        break;
    }

    // Grid
    this->player_grid.draw_grid(this->window);
    this->opponent_grid.draw_grid(this->window);

    if(this->state == GameState::Preparation && this->player_grid.is_within(mouse_position_view)) {
        this->player_grid.draw_place_holder(this->window);
    }

    // Ships
    this->player_grid.draw_ships(this->window);
    // this->opponent_grid.draw_ships(this->window);

    // Pegs
    this->player_grid.draw_pegs(this->window);
    this->opponent_grid.draw_pegs(this->window);

    this->window->display();
}
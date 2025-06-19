#include "Classes.hpp"

/*
    Definitions of the funtions in the Grid class
*/

// Constructors / Destructors


Grid::Grid(float x, float y) {
    this->x = x; 
    this->y = y;
    this->init_variables();
    this->init_pegs();
}


// Private funcitons

// Initializations

void Grid::init_variables(){

    // loading texture from file
    if(!this->grid_texture.loadFromFile("assets/board.png")) {
        std::cout << "Unable to load grid texture";
    }

    // Setting up grid
    this->grid.setTexture(this->grid_texture);
    this->grid.setScale(global_scale,global_scale);
    this->grid.setPosition(sf::Vector2f(this->x, this->y));
}

void Grid::init_pegs() {
    /*
        Initializing texture and position of pegs
    */
   if(!this->white_peg_texture.loadFromFile("assets/white-peg.png")) {
    std::cout << "Unable to load white peg texture";
   }

   this->white_peg.setTexture(this->white_peg_texture);
   this->white_peg.setScale(global_scale,global_scale);

   if(!this->red_peg_texture.loadFromFile("assets/red-peg.png")) {
    std::cout << "Unable to load red peg texture";
   }

   this->red_peg.setTexture(this->red_peg_texture);
   this->red_peg.setScale(global_scale,global_scale);
}

// Public functions

void Grid::draw_grid(sf::RenderWindow* window){
    /*
        Function for drawing grid onto the given window
    */
    window->draw(this->grid);
}

void Grid::place_white_peg(int x, int y) {
    /*
        To place a white peg on the board
    */

    this->white_peg.setPosition
    (
        this->grid.getPosition() + sf::Vector2f
        (
            (11.0f * (x-1) + 1.0f) * global_scale, (11.0f * (y-1) + 1.0f) * global_scale
        )
    );

    this->white_pegs.push_back(this->white_peg);
}

void Grid::place_red_peg(int x, int y) {
    /*
        To place a red peg on the board
    */

    this->red_peg.setPosition
    (
        this->grid.getPosition() + sf::Vector2f
        (
            (11.0f * (x-1) + 1.0f) * global_scale, (11.0f * (y-1) + 1.0f) * global_scale
        )
    );

    this->red_pegs.push_back(this->red_peg);
}

void Grid::draw_pegs(sf::RenderWindow* window) {

    // Drawing white pegs
    for (auto &wp : this->white_pegs) {
        window->draw(wp);
    }

    // Drawing red pegs
    for (auto &rp : this->red_pegs) {
        window->draw(rp);
    }
}

// Within grid
bool Grid::is_within(sf::Vector2f position) {
    return this->grid.getGlobalBounds().contains(position);
}

// Get relative position
std::pair<int,int> Grid::get_rel_pos(sf::Vector2f position) {

    sf::Vector2f grid_pos = this->grid.getPosition();

    int x = std::floor((((position.x - grid_pos.x) / global_scale - 1.0f) / 11.0f) + 1.0f);
    int y = std::floor((((position.y - grid_pos.y) / global_scale - 1.0f) / 11.0f) + 1.0f);

    return std::make_pair(x,y);
}
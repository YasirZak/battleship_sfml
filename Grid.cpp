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
    this->init_ships();
}


// Private funcitons

// Initializations

void Grid::init_variables(){

    // loading texture from file
    if(!this->grid_texture.loadFromFile("assets/board.png")) {
        std::cout << "Unable to load grid texture\n";
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
    std::cout << "Unable to load white peg texture\n";
   }

   this->white_peg.setTexture(this->white_peg_texture);
   this->white_peg.setScale(global_scale,global_scale);

   if(!this->red_peg_texture.loadFromFile("assets/red-peg.png")) {
    std::cout << "Unable to load red peg texture\n";
   }

   this->red_peg.setTexture(this->red_peg_texture);
   this->red_peg.setScale(global_scale,global_scale);
}

void Grid::init_ships() {
    /* 
        Initializing ship sprites with corresponding texture
    */

    // Orientation variable
    this->orientation_vertical = false;

    // Place holder
    this->place_holder.setFillColor(sf::Color::Green);
    this->place_holder.setSize(sf::Vector2f((11.f * 5 + 1) * global_scale, 11.f * global_scale));
    sf::FloatRect place_holder_bounds = this->place_holder.getGlobalBounds();
    this->place_holder.setOrigin(
        place_holder_bounds.left + (5.5f * global_scale),
        place_holder_bounds.top + (5.5f * global_scale)
    );

    // Carrier
    if(!this->carrier_texture.loadFromFile("assets/carrier-5.png")) {
        std::cout << "Unable to load carrier texture\n";
    }

    this->carrier.setTexture(this->carrier_texture);
    this->carrier.setScale(global_scale,global_scale);

    sf::FloatRect carrier_bounds = this->carrier.getGlobalBounds();
    this->carrier.setOrigin(
        carrier_bounds.left + 6,
        carrier_bounds.top + 5
    );

    // Battleship
    if(!this->battleship_texture.loadFromFile("assets/battleship-4.png")) {
        std::cout << "Unable to load battleship texture\n";
    }

    this->battleship.setTexture(this->battleship_texture);
    this->battleship.setScale(global_scale,global_scale);

    sf::FloatRect battleship_bounds = this->battleship.getGlobalBounds();
    this->battleship.setOrigin(
        battleship_bounds.left + 6,
        battleship_bounds.top + 5
    );

    // Cruiser
    if(!this->cruiser_texture.loadFromFile("assets/cruiser-3.png")) {
        std::cout << "Unable to load cruiser texture\n";
    }

    this->cruiser.setTexture(this->cruiser_texture);
    this->cruiser.setScale(global_scale,global_scale);

    sf::FloatRect cruiser_bounds = this->cruiser.getGlobalBounds();
    this->cruiser.setOrigin(
        cruiser_bounds.left + 6,
        cruiser_bounds.top + 5
    );


    // Submarine
    if(!this->submarine_texture.loadFromFile("assets/submarine-3.png")) {
        std::cout << "Unable to load submarine texture\n";
    }

    this->submarine.setTexture(this->submarine_texture);
    this->submarine.setScale(global_scale,global_scale);

    sf::FloatRect submarine_bounds = this->submarine.getGlobalBounds();
    this->submarine.setOrigin(
        submarine_bounds.left + 6,
        submarine_bounds.top + 5
    );

    // Destroyer
    if(!this->destroyer_texture.loadFromFile("assets/destroyer-2.png")) {
        std::cout << "Unable to load destroyer texture\n";
    }

    this->destroyer.setTexture(this->destroyer_texture);
    this->destroyer.setScale(global_scale,global_scale);

    sf::FloatRect destroyer_bounds = this->destroyer.getGlobalBounds();
    this->destroyer.setOrigin(
        destroyer_bounds.left + 6,
        destroyer_bounds.top + 5
    );

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

// Place ships
void Grid::place_ship(int x, int y) {
    switch (this->ships.size())
    {
    case 0:
        this->place_carrier(x, y);
        break;
    case 1:
        this->place_battleship(x,y);
        break;
    case 2:
        this->place_cruiser(x,y);
        break;
    case 3:
        this->place_submarine(x,y);
        break;
    case 4:
        this->place_destroyer(x,y);
        break;
    default:
        break;
    }
}

void Grid::place_carrier(int x, int y) {

    if(this->orientation_vertical) {
        if(y+4>10) {
            return;
        }
    } else {
        if(x+4>10) {
            return;
        }
    }

    std::cout << "carrier placed position: " << x << "," << y << "\n";

    this->carrier.setPosition
    (
        this->grid.getPosition() + sf::Vector2f
        (
            (11.0f * (x-1) + 1.0f + 5.0f) * global_scale, (11.0f * (y-1) + 1.0f + 5.0f) * global_scale
        )
    );

    this->ships.push_back(this->carrier);
}

void Grid::place_battleship(int x, int y) {

    if(this->orientation_vertical) {
        if(y+3>10) {
            return;
        }
    } else {
        if(x+3>10) {
            return;
        }
    }

    std::cout << "battleship placed position: " << x << "," << y << "\n";

    this->battleship.setPosition
    (
        this->grid.getPosition() + sf::Vector2f
        (
            (11.0f * (x-1) + 1.0f + 5.0f) * global_scale, (11.0f * (y-1) + 1.0f + 5.0f) * global_scale
        )
    );

    this->ships.push_back(this->battleship);
}

void Grid::place_cruiser(int x, int y) {

    if(this->orientation_vertical) {
        if(y+2>10) {
            return;
        }
    } else {
        if(x+2>10) {
            return;
        }
    }

    std::cout << "cruiser placed position: " << x << "," << y << "\n";

    this->cruiser.setPosition
    (
        this->grid.getPosition() + sf::Vector2f
        (
            (11.0f * (x-1) + 1.0f + 5.0f) * global_scale, (11.0f * (y-1) + 1.0f + 5.0f) * global_scale
        )
    );

    this->ships.push_back(this->cruiser);
}

void Grid::place_submarine(int x, int y) {

    if(this->orientation_vertical) {
        if(y+2>10) {
            return;
        }
    } else {
        if(x+2>10) {
            return;
        }
    }

    std::cout << "submarine placed position: " << x << "," << y << "\n";

    this->submarine.setPosition
    (
        this->grid.getPosition() + sf::Vector2f
        (
            (11.0f * (x-1) + 1.0f + 5.0f) * global_scale, (11.0f * (y-1) + 1.0f + 5.0f) * global_scale
        )
    );

    this->ships.push_back(this->submarine);
}

void Grid::place_destroyer(int x, int y) {

    if(this->orientation_vertical) {
        if(y+1>10) {
            return;
        }
    } else {
        if(x+1>10) {
            return;
        }
    }

    std::cout << "destroyer placed position: " << x << "," << y << "\n";

    this->destroyer.setPosition
    (
        this->grid.getPosition() + sf::Vector2f
        (
            (11.0f * (x-1) + 1.0f + 5.0f) * global_scale, (11.0f * (y-1) + 1.0f + 5.0f) * global_scale
        )
    );

    this->ships.push_back(this->destroyer);
}

bool Grid::all_ships_placed() {
    return this->ships.size() >= 5;
}

// Drawing all pegs

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

// Update place holder

void Grid::update_place_holder(int x, int y) {
    int size;
    switch (this->ships.size())
    {
    case 0:
        size = 5;
        break;
    case 1:
        size = 4;
        break;
    case 2:
        size = 3;
        break;
    case 3:
        size = 3;
        break;
    case 4:
        size = 2;
        break;
    default:
        break;
    }

    this->place_holder.setSize(sf::Vector2f(sf::Vector2f((11.f * (size) + 1) * global_scale, 11.f * global_scale)));
    this->place_holder.setPosition
    (
        this->grid.getPosition() + sf::Vector2f
        (
            (11.0f * (x-1) + 1.0f + 5.0f) * global_scale, (11.0f * (y-1) + 1.0f + 5.0f) * global_scale
        )
    );

}

// Draw place holder

void Grid::draw_place_holder(sf::RenderWindow* window) {
    window->draw(this->place_holder);
}


// Drawing ships

void Grid::draw_ships(sf::RenderWindow* window) {
    for (auto &s : this->ships) {
        window->draw(s);
    }
}

// change orientation

void Grid::change_orientation() {

    if(this->orientation_vertical) {
        this->place_holder.rotate(-90);
        this->carrier.rotate(-90);
        this->battleship.rotate(-90);
        this->cruiser.rotate(-90);
        this->submarine.rotate(-90);
        this->destroyer.rotate(-90);
    } else {
        this->place_holder.rotate(90);
        this->carrier.rotate(90);
        this->battleship.rotate(90);
        this->cruiser.rotate(90);
        this->submarine.rotate(90);
        this->destroyer.rotate(90);
    }

    this->orientation_vertical = !this->orientation_vertical;
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
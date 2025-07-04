#include "Classes.hpp"
#include "assets/board_png.hpp"
#include "assets/white-peg_png.hpp"
#include "assets/red-peg_png.hpp"
#include "assets/carrier-5_png.hpp"
#include "assets/battleship-4_png.hpp"
#include "assets/cruiser-3_png.hpp"
#include "assets/submarine-3_png.hpp"
#include "assets/destroyer-2_png.hpp"

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
    if(!this->grid_texture.loadFromMemory(board_png,board_png_len)) {
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
   if(!this->white_peg_texture.loadFromMemory(white_peg_png, white_peg_png_len)) {
    std::cout << "Unable to load white peg texture\n";
   }

   this->white_peg.setTexture(this->white_peg_texture);
   this->white_peg.setScale(global_scale,global_scale);

   if(!this->red_peg_texture.loadFromMemory(red_peg_png, red_peg_png_len)) {
    std::cout << "Unable to load red peg texture\n";
   }

   this->red_peg.setTexture(this->red_peg_texture);
   this->red_peg.setScale(global_scale,global_scale);

   // Initializing peg checker grid
   this->peg_check.assign(10, std::vector<int>(10, 0));

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
    if(!this->carrier_texture.loadFromMemory(carrier_5_png,carrier_5_png_len)) {
        std::cout << "Unable to load carrier texture\n";
    }

    this->carrier.setTexture(this->carrier_texture);
    this->carrier.setScale(global_scale,global_scale);

    sf::FloatRect carrier_bounds = this->carrier.getGlobalBounds();
    this->carrier.setOrigin(
        carrier_bounds.left + 5,
        carrier_bounds.top + 5
    );

    // Battleship
    if(!this->battleship_texture.loadFromMemory(battleship_4_png,battleship_4_png_len)) {
        std::cout << "Unable to load battleship texture\n";
    }

    this->battleship.setTexture(this->battleship_texture);
    this->battleship.setScale(global_scale,global_scale);

    sf::FloatRect battleship_bounds = this->battleship.getGlobalBounds();
    this->battleship.setOrigin(
        battleship_bounds.left + 5,
        battleship_bounds.top + 5
    );

    // Cruiser
    if(!this->cruiser_texture.loadFromMemory(cruiser_3_png,cruiser_3_png_len)) {
        std::cout << "Unable to load cruiser texture\n";
    }

    this->cruiser.setTexture(this->cruiser_texture);
    this->cruiser.setScale(global_scale,global_scale);

    sf::FloatRect cruiser_bounds = this->cruiser.getGlobalBounds();
    this->cruiser.setOrigin(
        cruiser_bounds.left + 5,
        cruiser_bounds.top + 5
    );


    // Submarine
    if(!this->submarine_texture.loadFromMemory(submarine_3_png,submarine_3_png_len)) {
        std::cout << "Unable to load submarine texture\n";
    }

    this->submarine.setTexture(this->submarine_texture);
    this->submarine.setScale(global_scale,global_scale);

    sf::FloatRect submarine_bounds = this->submarine.getGlobalBounds();
    this->submarine.setOrigin(
        submarine_bounds.left + 5,
        submarine_bounds.top + 5
    );

    // Destroyer
    if(!this->destroyer_texture.loadFromMemory(destroyer_2_png,destroyer_2_png_len)) {
        std::cout << "Unable to load destroyer texture\n";
    }

    this->destroyer.setTexture(this->destroyer_texture);
    this->destroyer.setScale(global_scale,global_scale);

    sf::FloatRect destroyer_bounds = this->destroyer.getGlobalBounds();
    this->destroyer.setOrigin(
        destroyer_bounds.left + 5,
        destroyer_bounds.top + 5
    );

    // Initializing health
    this->carrier_life = 5;
    this->battleship_life = 4;
    this->cruiser_life = 3;
    this->submarine_life = 3;
    this->destroyer_life = 2;

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

bool Grid::shoot(sf::Vector2f mouse_position_view) {

    std::pair<int,int> rel_pos = this->get_rel_pos(mouse_position_view);
    int x = rel_pos.first;
    int y = rel_pos.second;

    if(x < 1 || x > 10 || y < 1 || y > 10 || this->peg_check[x-1][y-1] != 0) {
        return false;
    }

    int ship_tag = this->contains_ship(mouse_position_view);

    switch (ship_tag)
    {
    case -1:
        this->place_white_peg(x,y);
        peg_check[x-1][y-1] = 1;
        break;

    case 0:
        this->place_red_peg(x,y);
        this->carrier_life -= 1;
        peg_check[x-1][y-1] = 2;
        break;

    case 1:
        this->place_red_peg(x,y);
        this->battleship_life -= 1;
        peg_check[x-1][y-1] = 2;
        break;

    case 2:
        this->place_red_peg(x,y);
        this->cruiser_life -= 1;
        peg_check[x-1][y-1] = 2;
        break;

    case 3:
        this->place_red_peg(x,y);
        this->submarine_life -= 1;
        peg_check[x-1][y-1] = 2;
        break;

    case 4:
        this->place_red_peg(x,y);
        this->destroyer_life -= 1;
        peg_check[x-1][y-1] = 2;
        break;
    
    default:
        break;
    }

    // std::cout << this->status_text_gen(mouse_position_view) << "\n";

    return true;
}

std::pair<int,int> Grid::noob_opponent_shoot() {

    x = (rand() % 10) + 1;
    y = (rand() % 10) + 1;

    if(!this->shoot(this->get_abs_pos(x,y))) 
            
    {
        return this->noob_opponent_shoot();
    } else {
        std::pair<int,int> pos;
        pos.first = x;
        pos.second = y;
        return pos;
    }
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

void Grid::auto_place_ship() {

    while(this->ships.size() < 5) {
        if (rand() % 2 == 1) {
            this->change_orientation();
        }
        x = rand() % 11;
        y = rand() % 11;
        this->place_ship(x,y);
    }
}

void Grid::place_carrier(int x, int y) {

    if(x < 1 || y < 1) {
        return;
    }

    if(this->orientation_vertical) {
        if(y+4>10 || x > 10) {
            return;
        }
    } else {
        if(x+4>10 || y > 10) {
            return;
        }
    }

    this->carrier.setPosition
    (
        this->grid.getPosition() + sf::Vector2f
        (
            (11.0f * (x-1) + 1.0f + 5.0f) * global_scale, (11.0f * (y-1) + 1.0f + 5.0f) * global_scale
        )
    );

    if(this->intersets_ships(this->carrier) >= 0) {
        return;
    }

    // std::cout << "carrier placed position: " << x << "," << y << "\n";

    this->ships.push_back(this->carrier);
}

void Grid::place_battleship(int x, int y) {

    if(x < 1 || y < 1) {
        return;
    }

    if(this->orientation_vertical) {
        if(y+3>10 || x > 10) {
            return;
        }
    } else {
        if(x+3>10 || y > 10) {
            return;
        }
    }

    this->battleship.setPosition
    (
        this->grid.getPosition() + sf::Vector2f
        (
            (11.0f * (x-1) + 1.0f + 5.0f) * global_scale, (11.0f * (y-1) + 1.0f + 5.0f) * global_scale
        )
    );

    if(this->intersets_ships(this->battleship) >= 0) {
        return;
    }

    // std::cout << "battleship placed position: " << x << "," << y << "\n";

    this->ships.push_back(this->battleship);
}

void Grid::place_cruiser(int x, int y) {

    if(x < 1 || y < 1) {
        return;
    }

    if(this->orientation_vertical) {
        if(y+2>10 || x > 10) {
            return;
        }
    } else {
        if(x+2>10 || y > 10) {
            return;
        }
    }

    this->cruiser.setPosition
    (
        this->grid.getPosition() + sf::Vector2f
        (
            (11.0f * (x-1) + 1.0f + 5.0f) * global_scale, (11.0f * (y-1) + 1.0f + 5.0f) * global_scale
        )
    );

    if(this->intersets_ships(this->cruiser) >= 0) {
        return;
    }

    // std::cout << "cruiser placed position: " << x << "," << y << "\n";

    this->ships.push_back(this->cruiser);
}

void Grid::place_submarine(int x, int y) {

    if(x < 1 || y < 1) {
        return;
    }

    if(this->orientation_vertical) {
        if(y+2>10 || x > 10) {
            return;
        }
    } else {
        if(x+2>10 || y > 10) {
            return;
        }
    }

    this->submarine.setPosition
    (
        this->grid.getPosition() + sf::Vector2f
        (
            (11.0f * (x-1) + 1.0f + 5.0f) * global_scale, (11.0f * (y-1) + 1.0f + 5.0f) * global_scale
        )
    );

    if(this->intersets_ships(this->submarine) >= 0) {
        return;
    }

    // std::cout << "submarine placed position: " << x << "," << y << "\n";

    this->ships.push_back(this->submarine);
}

void Grid::place_destroyer(int x, int y) {

    if(x < 1 || y < 1) {
        return;
    }

    if(this->orientation_vertical) {
        if(y+1>10 || x > 10) {
            return;
        }
    } else {
        if(x+1>10 || y > 10) {
            return;
        }
    }

    this->destroyer.setPosition
    (
        this->grid.getPosition() + sf::Vector2f
        (
            (11.0f * (x-1) + 1.0f + 5.0f) * global_scale, (11.0f * (y-1) + 1.0f + 5.0f) * global_scale
        )
    );

    if(this->intersets_ships(this->destroyer) >= 0) {
        return;
    }

    // std::cout << "destroyer placed position: " << x << "," << y << "\n";

    this->ships.push_back(this->destroyer);
}

bool Grid::all_ships_placed() {
    return this->ships.size() >= 5;
}

int Grid::intersets_ships(sf::Sprite ship) {

    for(int i = 0; i < this->ships.size(); i++) {
        if(ships[i].getGlobalBounds().intersects(ship.getGlobalBounds())) {
            // std::cout << "Intersect " << i << "\n";
            return i;
        }
    }

    return -1;
    
}

int Grid::contains_ship(sf::Vector2f mouse_pos_view) {

    for(int i = 0; i < this->ships.size(); i++) {
        if(this->ships[i].getGlobalBounds().contains(mouse_pos_view)) {
            // std::cout << "Contains " << i << "\n";
            return i;
        }
    }

    return -1;
    
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

// Get absolute position

sf::Vector2f Grid::get_abs_pos(int x, int y) {
    return this->grid.getPosition() + sf::Vector2f(
            (11.0f * (x-1) + 1.0f + 5.0f) * global_scale, 
            (11.0f * (y-1) + 1.0f + 5.0f) * global_scale
        );
}

// ships size
int Grid::ships_size() {
    return this->ships.size();
}

// function to see if we lost

bool Grid::is_lost() {
    if(this->carrier_life + this->battleship_life 
        + this->cruiser_life + this->submarine_life
    + this->destroyer_life == 0) {
        return true;
    }

    return false;
}

// function to generate status text of shot

std::string Grid::status_text_gen(sf::Vector2f position) {
    std::pair<int,int> rel_pos = this->get_rel_pos(position);
    int ship_no = this->contains_ship(position);

    std::string ship;
    std::string other;
    switch (ship_no)
    {
    case 0:
        ship = " Car";
        if(this->carrier_life != 0)
            other = " Hit";
        else
            other = " Sank";
        break;

    case 1:
        ship = " Bat";
        if(this->battleship_life != 0)
            other = " Hit";
        else
            other = " Sank";
        break;

    case 2:
        ship = " Cru";
        if(this->cruiser_life != 0)
            other = " Hit";
        else
            other = " Sank";
        break;

    case 3:
        ship = " Sub";
        if(this->submarine_life != 0)
            other = " Hit";
        else
            other = " Sank";
        break;

    case 4:
        ship = " Des";
        if(this->destroyer_life != 0)
            other = " Hit";
        else
            other = " Sank";
        break;
    
    default:
        ship = "";
        other = " Miss";
        break;
    }

    char fst = 'A'+(rel_pos.second-1);

    std::string final_string = std::string() + fst + "-" + (std::to_string(rel_pos.first))
    + ship + other;

    return final_string;

}

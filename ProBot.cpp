#include "Classes.hpp"

// Vector functions

bool ProBot::contains_elements(std::vector<int> vec, int element) {
    /*
        To check if an element is contained within a int vector
    */

    return std::find(vec.begin(), vec.end(), element) != vec.end();
}

void ProBot::add_vectors(std::vector<std::vector<float>>& a, std::vector<std::vector<float>> b) {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            a[i][j] += b[i][j];
        }
    }
}

std::pair<int,int> ProBot::get_max_position(std::vector<std::vector<float>> prob) {
    float max_value = 0;
    std::pair<int,int> pos(0,0);

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if(prob[i][j] > max_value) {
                max_value = prob[i][j];
                pos = {i+1,j+1};
            }
        }
    }

    return pos;
}

// Bot functions

std::vector<std::vector<float>> ProBot::possible_locations_prob(std::vector<std::vector<int>> peg_check, int size) {

    /*
        function that returns grid of probabilities for peg positions and ship size
    */

    std::vector<std::vector<float>> final_matrix = std::vector<std::vector<float>>(10,std::vector<float>(10,0));
    std::vector<std::vector<float>> new_state;
    int if_there_is_hit;

    for(int row = 0; row < 10; row++) {
        for(int col = 0; col < 11 - size; col++) {
            std::vector<int> positions_with_hits = {};
            int empty_slot_counter = 0;

            for(int element = col; element < col+size; element++) {
                if(peg_check[row][element] != 1) {
                    if(peg_check[row][element] == 2) {
                        positions_with_hits.push_back(element);
                    }
                    empty_slot_counter += 1;
                }

            }

            if(empty_slot_counter == size) {
                new_state.assign(10,std::vector<float>(10,0));
                if_there_is_hit = (positions_with_hits.size()) ? 4*positions_with_hits.size() : 1;
                for(int element = col; element < col+size; element++) {
                    if(this->contains_elements(positions_with_hits, element)) {
                        new_state[row][element] = 0;
                    } else {
                        new_state[row][element] = float(size) * if_there_is_hit;
                    }
                }
                this->add_vectors(final_matrix, new_state);
            }
        }
    }

    for(int col = 0; col < 10; col++) {
        for(int row = 0; row < 11 - size; row++) {
            std::vector<int> positions_with_hits = {};
            int empty_slot_counter = 0;

            for(int element = row; element < row+size; element++) {
                if(peg_check[element][col] != 1) {
                    if(peg_check[element][col] == 2) {
                        positions_with_hits.push_back(element);
                    }
                    empty_slot_counter += 1;
                }

            }

            if(empty_slot_counter == size) {
                new_state.assign(10,std::vector<float>(10,0));
                if_there_is_hit = (positions_with_hits.size()) ? 4*positions_with_hits.size() : 1;
                for(int element = row; element < row+size; element++) {
                    if(this->contains_elements(positions_with_hits, element)) {
                        new_state[element][col] = 0;
                    } else {
                        new_state[element][col] = float(size) * if_there_is_hit;
                    }
                }
                this->add_vectors(final_matrix, new_state);
            }
        }
    }

    return final_matrix;

}

void ProBot::set_probabilities_for_all_ships(std::vector<std::vector<int>> peg_check) {
    /*
        setting the probability grid by computing probability for all ships
    */

    this->grid_prob.assign(10,std::vector<float>(10,0.0f));

    std::vector<int> ships = {5,4,3,2,1};

    for (auto& i : ships) {
        std::vector<std::vector<float>> probabilities = this->possible_locations_prob(peg_check, i);
        this->add_vectors(this->grid_prob, probabilities);
    }

}

std::pair<int,int> ProBot::get_next_move() {
    return this->get_max_position(grid_prob);
}

void ProBot::print_prob() {
    for(int i; i < 10; i++) {
        for(int j; j < 10; j++) {
            std::cout << this->grid_prob[i][j] << " ";
        }

        std::cout << "\n";
    }
}
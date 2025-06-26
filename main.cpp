#include "Classes.hpp"

/*
    To compile:
    g++ main.cpp Game.cpp Grid.cpp ProBot.cpp -o Game_ex -lsfml-graphics -lsfml-window -lsfml-system

    g++ main.cpp Game-font.cpp Grid-img.cpp ProBot.cpp -o battleship -lsfml-graphics -lsfml-window -lsfml-system

*/

int main() {

    // Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    // Game loop
    Game game;

    while(game.running()){

        game.poll_events();

        switch (game.state)
        {
        case GameState::Select:
            game.update_selection_screen();
            game.render_selection_screen();
            break;
            
        case GameState::Preparation:
        case GameState::Shooting:
        case GameState::Win:
        case GameState::Loose:
            game.render();
            game.update();
            game.render();
            break;
        
        default:
            break;
        }
    }
}
#include "Classes.hpp"

/*
    To compile:
    g++ main.cpp Game.cpp Grid.cpp -o Game_ex -lsfml-graphics -lsfml-window -lsfml-system

*/

int main() {

    // Game loop
    Game game;

    while(game.running()){

        game.poll_events();

        switch (game.state)
        {
        case GameState::Preparation:
        case GameState::Shooting:
            game.update();
            game.render();
            break;
        
        default:
            break;
        }
    }
}
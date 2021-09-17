#include "Game.hpp"

int main(int ac, char **av) {
    int nb_players = 2;
    int width = 21;
    int height = 21;

    try {
        if (ac >= 2) {
            nb_players = std::stoi(std::string(av[1]));
            if (nb_players < 2 || nb_players > 4) {
                nb_players = 2;
            }
        }
        if (ac == 4) {
            width = std::stoi(std::string(av[2]));
            if (width < 6 || width > 20) {
                width = 10;
            }
            height = std::stoi(std::string(av[2]));
            if (height < 6 || height > 20) {
                height = 10;
            }
        }
    } catch (std::invalid_argument &e) {
        std::cout << "Usage: ./Indie-Bomberman(.exe) <int nb_players> <int width> <int height>" << std::endl;
        return 84;
    }
    Game::getInstance()->start(nb_players, width, height);
    return 0;
}
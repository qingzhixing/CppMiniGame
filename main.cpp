#include <format>
#include <iostream>
#include <vector>

#include "GameFrame.h"
#include "GuessNumber.h"

std::vector<GameFrame *> game_frames{};

void RegisterGameFrame(GameFrame *game_frame) {
    if (game_frame == nullptr) {
        return;
    }
    game_frames.push_back(game_frame);
}

int main() {
    std::cout << "Cpp Mini Game [@qingzhixing]" << std::endl;

    RegisterGameFrame(new GuessNumber());

    std::cout << "Please select a game to play:" << std::endl;

    for (int index = 0; index < game_frames.size(); index++) {
        std::cout << std::format("{}: {}\n", index + 1, game_frames[index]->name);
    }
    std::cout << "0 to exit." << std::endl;

    GameFrame *selected_game = nullptr;
    int selected_number = 0;
    while (selected_game == nullptr) {
        std::cin >> selected_number;
        if (selected_number == 0) {
            break;
        }
        if (selected_number > game_frames.size()) {
            std::cout << "Invalid number, Try again." << std::endl;
        } else {
            selected_game = game_frames[selected_number - 1];
        }
    }
    if (selected_game != nullptr) {
        selected_game->run();
    }
    std::cout << "Thanks for playing!";
    return 0;
}

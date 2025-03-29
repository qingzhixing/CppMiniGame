#include <format>
#include <iostream>
#include <vector>
#include <windows.h>

#include "GameFrame.h"
#include "GuessNumber.h"
#include "Snakes/Snakes.h"

void EnableUTF8Console() {
    // 设置控制台输入输出编码为 UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // 解决 Windows 下中文输出乱码问题
    std::ios::sync_with_stdio(false);
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale(""));
    std::wcin.imbue(std::locale(""));
}

std::vector<GameFrame *> game_frames{};

void RegisterGameFrame(GameFrame *game_frame) {
    if (game_frame == nullptr) {
        return;
    }
    game_frames.push_back(game_frame);
}

int main() {

    std::cout << "Cpp Mini Game [@qingzhixing]" << std::endl;

    EnableUTF8Console();

    // 使用宽字符输出
    std::wcout << L"跨平台UTF-8测试: 你好世界! 🌍" << std::endl;

    RegisterGameFrame(new GuessNumber());
    RegisterGameFrame(new Snakes());

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
    std::cout << "Thanks for playing!" << std::endl;
    getchar();
    return 0;
}

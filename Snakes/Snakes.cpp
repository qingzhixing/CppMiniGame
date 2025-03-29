//
// Created by qingzhixing on 2025/3/29.
//

#include "Snakes.h"

#include <Windows.h>
#include <iostream>
#include <list>
#include <queue>
#include <cstring>

#include <random>
#include <thread>

Snakes::Snakes():
    GameFrame("Snakes") {
}

enum MapElements {
    EMPTY,
    WALL,
    SNAKE_HEAD,
    SNAKE_BODY,
    APPLE,
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

static Direction direction = UP;

static std::list<std::pair<int, int> > snake_body{};

static std::pair<int, int> map_size = {15, 15};

static MapElements **game_map;

static void init_map() {
    game_map = new MapElements *[map_size.first + 5];
    for (int i = 0; i < map_size.first; i++) {
        game_map[i] = new MapElements[map_size.second + 5];
    }

    for (int i = 0; i < map_size.first; i++) {
        for (int j = 0; j < map_size.second; j++) {
            if (i == 0 || i == map_size.first - 1 || j == 0 || j == map_size.second - 1) {
                game_map[i][j] = WALL;
            }
        }
    }
}

static void init_snake() {
    snake_body.emplace_back(10, 10);
    game_map[10][10] = SNAKE_HEAD;
    snake_body.emplace_back(10, 11);
    game_map[10][11] = SNAKE_BODY;
    snake_body.emplace_back(10, 12);
    game_map[10][12] = SNAKE_BODY;
}

static void generate_apple() {
    std::random_device random;
    std::pair<unsigned int, unsigned int> apple_pos = {
            random() % map_size.first,
            random() % map_size.second
    };
    while (game_map[apple_pos.first][apple_pos.second] != EMPTY) {
        apple_pos = {
                random() % map_size.first,
                random() % map_size.second
        };
    }
    game_map[apple_pos.first][apple_pos.second] = APPLE;
}

static void init_apple() {
    generate_apple();
}

static void draw_map() {
    for (int i = 0; i < map_size.first; i++) {
        for (int j = 0; j < map_size.second; j++) {
            if (game_map[i][j] == SNAKE_HEAD) {
                std::cout << "@";
            } else if (game_map[i][j] == SNAKE_BODY) {
                std::cout << "o";
            } else if (game_map[i][j] == APPLE) {
                std::cout << "*";
            } else if (game_map[i][j] == WALL) {
                std::cout << "X";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout.flush();
}

static void handle_input() {
}

static void update_snake() {
}

static bool is_game_over() {
    return false;
}

static void end_game() {
}

static void clear_screen() {
    system("cls");
}


void Snakes::run() {
    std::cout << "Snakes starting..." << std::endl;
    init_map();
    std::cout << "Map initialized." << std::endl;
    init_snake();
    std::cout << "Snake initialized." << std::endl;
    init_apple();
    std::cout << "Apple initialized." << std::endl;
    while (true) {
        clear_screen();
        handle_input();
        update_snake();
        draw_map();
        if (is_game_over()) {
            break;
        }
        _sleep(200);
    }
    end_game();
}

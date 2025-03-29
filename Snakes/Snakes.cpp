//
// Created by qingzhixing on 2025/3/29.
//

#include "Snakes.h"

#include <Windows.h>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <list>

#include <random>

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

enum Direction:short {
    UP = 1,
    DOWN = -1,
    LEFT = 2,
    RIGHT = -2,
};

static Direction old_direction = UP;
static Direction updating_direction = UP;

static std::list<std::pair<int, int> > snake_body{};

static std::pair<int, int> map_size = {15, 15};

static MapElements **game_map;

static bool quit = false;

static bool is_game_over = false;

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

static void end_game() {
}

static void handle_input() {
    Direction new_direction = updating_direction;
    if (GetAsyncKeyState('W') & 0x8000) {
        new_direction = UP;
    } else if (GetAsyncKeyState('S') & 0x8000) {
        new_direction = DOWN;
    } else if (GetAsyncKeyState('A') & 0x8000) {
        new_direction = LEFT;
    } else if (GetAsyncKeyState('D') & 0x8000) {
        new_direction = RIGHT;
    } else if (GetAsyncKeyState('Q') & 0x8000) {
        quit = true;
    }
    // 防止反向移动
    if (new_direction + old_direction != 0) {
        updating_direction = new_direction;
    }
}

static void update_snake() {
    auto head = snake_body.front();
    auto new_head = head;
    switch (updating_direction) {
        case UP:
            new_head.first--;
            break;
        case DOWN:
            new_head.first++;
            break;
        case LEFT:
            new_head.second--;
            break;
        case RIGHT:
            new_head.second++;
            break;
    }
    old_direction = updating_direction;
    if (game_map[new_head.first][new_head.second] == WALL ||
        game_map[new_head.first][new_head.second] == SNAKE_BODY) {
        is_game_over = true;
    }
    if (game_map[new_head.first][new_head.second] != APPLE) {
        const auto [fst, snd] = snake_body.back();
        snake_body.pop_back();
        game_map[fst][snd] = EMPTY;
    } else {
        generate_apple();
    }
    snake_body.emplace_front(new_head);
    game_map[new_head.first][new_head.second] = SNAKE_HEAD;
    game_map[head.first][head.second] = SNAKE_BODY;
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

    auto last_update = std::chrono::steady_clock::now();
    while (!quit) {
        handle_input();
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_update).count() > 500) {
            update_snake();
            clear_screen();
            draw_map();
            last_update = now;
        }
        if (is_game_over) {
            break;
        }
    }
    end_game();
}

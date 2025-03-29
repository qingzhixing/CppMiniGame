//
// Created by qingzhixing on 2025/3/26.
//

#ifndef GAME_FRAME_H
#define GAME_FRAME_H
#include <string>
#include <utility>
#include <vector>


class GameFrame {

public:
    explicit GameFrame(std::string _name);

    virtual ~GameFrame() = default;

    virtual void run();

public:
    std::string name;
};

#endif // GAME_FRAME_H

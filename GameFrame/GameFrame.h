//
// Created by qingzhixing on 2025/3/26.
//

#ifndef GAME_FRAME_H
#define GAME_FRAME_H


class GameFrame {
public:
    virtual ~GameFrame() = default;
    virtual void run() = 0;
};


#endif // GAME_FRAME_H

//
// Created by qingzhixing on 2025/3/26.
//

#ifndef GUESS_NUMBER_H
#define GUESS_NUMBER_H

#include "GameFrame.h"

class GuessNumber final : public GameFrame {
public:
    GuessNumber() = default;
    ~GuessNumber() override = default;

public:
    void run() override;

private:
    unsigned int number{};
    int guess_count{};
    unsigned int guess_limit_max{};
};


#endif // GUESS_NUMBER_H

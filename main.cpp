#include <iostream>

#include "GameFrame.h"
#include "GuessNumber.h"

int main() {
    std::cout << "Cpp Mini Game [@qingzhixing]" << std::endl;
    GameFrame *gameFrame = new GuessNumber();
    gameFrame->run();
    return 0;
}

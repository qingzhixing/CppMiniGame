//
// Created by qingzhixing on 2025/3/26.
//

#include "GuessNumber.h"
#include <format>
#include <iostream>
#include <random>
void GuessNumber::run() {
    std::random_device random_device;
    std::cout << "Choose guessing range:" << std::endl;
    std::cout << "a. Range [0, 10]" << std::endl;
    std::cout << "b. Range [0, 100]" << std::endl;
    std::cout << "c. Range [0, 1000]" << std::endl;
    std::cout << "d. Range [0, 10000]" << std::endl;
    std::cout << "q. Quit" << std::endl;
    char choice;
    bool input_valid = false;
    while (!input_valid) {
        input_valid = true;
        std::cin >> choice;
        switch (choice) {
            case 'a':
            case 'A':
                guess_limit_max = 10;
                break;
            case 'b':
            case 'B':
                guess_limit_max = 100;
                break;
            case 'c':
            case 'C':
                guess_limit_max = 1000;
                break;
            case 'd':
            case 'D':
                guess_limit_max = 10000;
                break;
            case 'q':
            case 'Q':
                return;
            default:
                std::cout << "Invalid choice, please try again." << std::endl;
                input_valid = false;
        }
    }
    number = random_device() % (guess_limit_max + 1);
    bool correct = false;
    unsigned guess_number{};
    std::pair<unsigned int, unsigned int> guessing_range = std::make_pair(0, guess_limit_max); // 猜数辅助

    while (!correct) {
        std::cout << std::format("Guess the number of [{}, {}] (guess count: {}): ", guessing_range.first,
                                 guessing_range.second, guess_count);
        std::cin >> guess_number;
        guess_count++;
        if (guess_number == number) {
            correct = true;
            std::cout << std::format("Correct! The number is {}.", guess_number);
        } else if (guess_number > number) {
            guessing_range.second = std::min(guessing_range.second, guess_number);
            std::cout << "The number is greater than the number of guesses." << std::endl;
        } else {
            guessing_range.first = std::max(guessing_range.first, guess_number);
            std::cout << "The number is less than the number of guesses." << std::endl;
        }
    }
}

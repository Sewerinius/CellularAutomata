//
// Created by sewerin on 07.06.2020.
//

#include <random>
#include <chrono>
#include <iostream>
#include "RectangularBoard.h"

RectangularBoard::RectangularBoard(unsigned int width, unsigned int height)
        : width(width), height(height),
          map(8 * height, std::vector<int>(8 * width, 0)) {
    for (auto & i : map) {
        std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
        std::discrete_distribution<int> distribution{1, 1};
        for (int & j : i) {
            j = distribution(generator);
        }
    }

//    map[3][4] = 1;
//    map[4][4] = 1;
//    map[5][4] = 1;
}

const std::vector<std::vector<int>> &RectangularBoard::getMap() const {
    return map;
}

RectangularBoard::RectangularBoard(unsigned int width, unsigned int height, const std::vector<std::vector<int>> &map)
        : width(width), height(height), map(map) {}

void RectangularBoard::setMap(const std::vector<std::vector<int>> &map) {
    RectangularBoard::map = map;
}

void RectangularBoard::print() {
    for (auto& row : map) {
        for (auto & x : row) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
}

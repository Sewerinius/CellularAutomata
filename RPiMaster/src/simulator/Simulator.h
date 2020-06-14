//
// Created by sewerin on 07.06.2020.
//

#ifndef CELLULARAUTOMATARPI_SIMULATOR_H
#define CELLULARAUTOMATARPI_SIMULATOR_H


#include "../board/RectangularBoard.h"
#include "../rules/Rule.h"

class Simulator {
private:
    RectangularBoard& board;
    Rule& rule;

public:
    Simulator(RectangularBoard& board, Rule &rule);

    void step();
};


#endif //CELLULARAUTOMATARPI_SIMULATOR_H

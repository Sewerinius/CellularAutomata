//
// Created by sewerin on 07.06.2020.
//

#ifndef CELLULARAUTOMATARPI_CONNECTION_H
#define CELLULARAUTOMATARPI_CONNECTION_H


#include <cstdint>
#include <vector>

#include "commands.h"

class Connection {
public:
    virtual int sendCommand(Command command, std::vector<uint8_t> data) = 0;

    void sendBoard(const std::vector<std::vector<int> >& board);
};


#endif //CELLULARAUTOMATARPI_CONNECTION_H

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
    virtual int sendCommand(Command command, std::vector<uint8_t> data) = 0; //TODO: change data to a reference type
    virtual int receiveCommand(Command command, std::vector<uint8_t>& dataBuffer, std::vector<uint8_t>::size_type count) = 0;

    void sendBoard(const std::vector<std::vector<int> >& board);
    void getInputs(std::vector<std::vector<int> >& inputs);
};


#endif //CELLULARAUTOMATARPI_CONNECTION_H

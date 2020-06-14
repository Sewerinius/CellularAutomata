//
// Created by sewerin on 07.06.2020.
//

#ifndef CELLULARAUTOMATARPI_I2CCONNECTION_H
#define CELLULARAUTOMATARPI_I2CCONNECTION_H


#include "Connection.h"

class I2CConnection : public Connection {
    const int i2cFD;
    const unsigned long address;
    int prepareTransmission();

public:
    I2CConnection(int i2CFd, unsigned long address);

    int sendCommand(Command command, std::vector<uint8_t> data) override;

    int
    receiveCommand(Command command, std::vector<uint8_t> &dataBuffer, std::vector<uint8_t>::size_type count) override;
};


#endif //CELLULARAUTOMATARPI_I2CCONNECTION_H

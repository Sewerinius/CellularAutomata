//
// Created by sewerin on 07.06.2020.
//

#include <linux/i2c-dev.h>
#include <iostream>
#include <unistd.h>

#include "I2CConnection.h"

static const int MAX_RETRIES = 10;

int I2CConnection::sendCommand(Command command, std::vector<uint8_t> data) {
    int retryCount = 0;
    int res;
    do {
        res = prepareTransmission();
    } while (res != 0 && retryCount++ < MAX_RETRIES);
    if(res != 0) {
        perror("Error while preparing transmission");
        return res;
    }

    do {
        res = write(i2cFD, &command, 1);
    } while (res < 0 && retryCount++ < MAX_RETRIES);
    if(res < 0) {
        perror("Error while sending command");
        return res;
    }

    for (int i = 0; i < data.size(); i += 32) {
        do {
            int count = i + 32 < data.size() ? 32 : data.size() - i;
            res = write(i2cFD, data.data() + i, count);
        } while (res < 0 && retryCount++ < MAX_RETRIES);
        if(res < 0){
            perror("Error while sending command data");
            return res;
        }
    }
    return 0;
}

I2CConnection::I2CConnection(const int i2CFd, const unsigned long address) : i2cFD(i2CFd), address(address) {}

int I2CConnection::prepareTransmission() {
    if (ioctl(i2cFD, I2C_SLAVE, address) < 0) {
        std::cout << "Unable to set the i2c address" << std::endl;
        return errno;
    }
    return 0;
}

int I2CConnection::receiveCommand(Command command, std::vector<uint8_t> &dataBuffer, std::vector<uint8_t>::size_type count) {
    int retryCount = 0;
    int res;
    do {
        res = prepareTransmission();
    } while (res != 0 && retryCount++ < MAX_RETRIES);
    if(res != 0) {
        perror("Error while preparing transmission");
        return res;
    }

    do {
        res = write(i2cFD, &command, 1);
    } while (res < 0 && retryCount++ < MAX_RETRIES);
    if(res < 0) {
        perror("Error while sending command");
        return res;
    }

    dataBuffer.resize(count);
    do {
        res = read(i2cFD, dataBuffer.data(), count);
    } while (res < 0 && retryCount++ < MAX_RETRIES);
    if(res < 0) {
        perror("Error while sending command");
        return res;
    }
    return 0;
}

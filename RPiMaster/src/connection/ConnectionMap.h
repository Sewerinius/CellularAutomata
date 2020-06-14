//
// Created by sewerin on 07.06.2020.
//

#ifndef CELLULARAUTOMATARPI_CONNECTIONMAP_H
#define CELLULARAUTOMATARPI_CONNECTIONMAP_H


#include <memory>
#include "Connection.h"
#include "../board/RectangularBoard.h"

class ConnectionMap {
    const int width;
    const int height;

    std::vector<std::vector<std::unique_ptr<Connection> > > map;
public:
    ConnectionMap(std::vector<std::vector<std::unique_ptr<Connection>>> map);
    ConnectionMap(const int width, const int height);

    void setConnection(int x, int y, std::unique_ptr<Connection> connection);

    void sendBoard(const RectangularBoard& board);

    void handleInputs(RectangularBoard& board); //TODO: this is not a responsibility of this class
};


#endif //CELLULARAUTOMATARPI_CONNECTIONMAP_H

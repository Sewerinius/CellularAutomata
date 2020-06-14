//
// Created by sewerin on 07.06.2020.
//

#ifndef CELLULARAUTOMATARPI_RECTANGULARBOARD_H
#define CELLULARAUTOMATARPI_RECTANGULARBOARD_H


#include <vector>

class RectangularBoard {
private:
    std::vector<std::vector<int> > map;

public:
    const unsigned int width;
    const unsigned int height;

    RectangularBoard(unsigned int width, unsigned int height);

    RectangularBoard(unsigned int width, unsigned int height, const std::vector<std::vector<int>> &map);

    const std::vector<std::vector<int>> &getMap() const;

    void setMap(const std::vector<std::vector<int>> &map);

    void set(int x, int y, int v);

    void print();
};


#endif //CELLULARAUTOMATARPI_RECTANGULARBOARD_H

//
// Created by sewerin on 07.06.2020.
//

#include <cassert>
#include "ConnectionMap.h"

ConnectionMap::ConnectionMap(const int width, const int height) : width(width), height(height) {
    map.reserve(height);
    for (int i = 0; i < height; i++) {
        map.emplace_back(width);
    }
}

ConnectionMap::ConnectionMap(std::vector<std::vector<std::unique_ptr<Connection>>> map) :
        height(map.size()),
        width(map[0].size()),
        map(std::move(map)) {}

void ConnectionMap::setConnection(int x, int y, std::unique_ptr<Connection> connection) {
    map[y][x] = std::move(connection);
}

void ConnectionMap::sendBoard(const RectangularBoard &board) {
    assert(width == board.width);
    assert(height == board.height);

    for (int w = 0; w < width; w++) {
        for (int h = 0; h < height; h++) {
            if (map[h][w]) {
                std::vector<std::vector<int>> boardSlice(8);
                for (int i = 0; i < 8; i++) {
                    boardSlice[i].insert(std::end(boardSlice[i]),
                                         std::begin(board.getMap()[h * 8 + i]) + w * 8,
                                         std::begin(board.getMap()[h * 8 + i]) + w * 8 + 8);
                }
                map[h][w]->sendBoard(boardSlice);
            }
        }
    }
}

void ConnectionMap::handleInputs(RectangularBoard &board) {
    for (int w = 0; w < width; w++) {
        for (int h = 0; h < height; h++) {
            if (map[h][w]) {
                std::vector<std::vector<int> > inputs(8, std::vector<int>(8));
                map[h][w]->getInputs(inputs);
                const auto& boardMap = board.getMap();
                for (int y = 0; y < 8; y++) {
                    for (int x = 0; x < 8; x++) {
                        if (inputs[y][x] != 0) {
                            int v = 1 - boardMap[h*8 + y][w*8+x]; //TODO: different ways to update v
                            board.set(w*8+x, h*8 + y, v);
                        }
                    }
                }
            }
        }
    }
}

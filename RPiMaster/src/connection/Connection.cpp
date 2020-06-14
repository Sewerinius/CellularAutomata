//
// Created by sewerin on 07.06.2020.
//

#include <cassert>
#include "Connection.h"

void Connection::sendBoard(const std::vector<std::vector<int> >& board) {
    std::vector<uint8_t> data;
    data.reserve(board.size() * board[0].size());
    for (auto& row : board) {
        data.insert(std::end(data), std::begin(row), std::end(row));
    }

    int res = sendCommand(SET_BOARD, data);
    assert(res == 0);
}

void Connection::getInputs(std::vector<std::vector<int> > &inputs) {
    std::vector<uint8_t> data;
    receiveCommand(GET_INPUTS, data, 8);
    for (int i = 0; i < 8; i++) {
        uint8_t row = data[i];
        for (int j = 7; j >= 0; j--) {
            inputs[i][j] = row & 1u;
            row >>= 1u;
        }
    }
}

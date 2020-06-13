//
// Created by sewerin on 07.06.2020.
//

#include "Simulator.h"

Simulator::Simulator(RectangularBoard& board, Rule &rule) : board(board), rule(rule) {}

void Simulator::step() {
    auto& map = board.getMap();
    auto copy = map;
    for (int h = 0; h < map.size(); h++) {
        for (int w = 0; w < map[0].size(); w++) {
            int tl = 0, tm = 0, tr = 0, ml = 0, mm = 0, mr = 0, bl = 0, bm = 0, br = 0;
            bool top = h > 0, bottom = h < map.size()-1;
            bool left = w > 0, right = w < map[0].size()-1;

            if (top && left)        tl = map[h-1][w-1];
            if (top)                tm = map[h-1][w];
            if (top && right)       tr = map[h-1][w+1];
            if (left)               ml = map[h][w-1];
                                    mm = map[h][w];
            if (right)              mr = map[h][w+1];
            if (bottom && left)     bl = map[h+1][w-1];
            if (bottom)             bm = map[h+1][w];
            if (bottom && right)    br = map[h+1][w+1];

            int res = rule.check(tl, tm, tr, ml, mm, mr, bl, bm, br);
            copy[h][w] = (res != -1 ? res : 0);
        }
    }
    board.setMap(copy);
}

//
// Created by sewerin on 07.06.2020.
//

#ifndef CELLULARAUTOMATARPI_RULE_H
#define CELLULARAUTOMATARPI_RULE_H


class Rule {
public:
    virtual int check(int tl, int tm, int tr, int ml, int mm, int mr, int bl, int bm, int br) = 0;
};


#endif //CELLULARAUTOMATARPI_RULE_H

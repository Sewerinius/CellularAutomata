//
// Created by sewerin on 07.06.2020.
//

#ifndef CELLULARAUTOMATARPI_COUNTRULE_H
#define CELLULARAUTOMATARPI_COUNTRULE_H


#include <utility>
#include <map>
#include "Rule.h"

class CountRule : public Rule {
private:
    int current;
    std::map<int, std::pair<int, int>> ranges;
    int next;
public:
    CountRule(int current, int next, const std::map<int, std::pair<int, int>> &ranges);

private:

    int check(int tl, int tm, int tr, int ml, int mm, int mr, int bl, int bm, int br) override;
};


#endif //CELLULARAUTOMATARPI_COUNTRULE_H

//
// Created by sewerin on 07.06.2020.
//

#ifndef CELLULARAUTOMATARPI_AGGREGATERULE_H
#define CELLULARAUTOMATARPI_AGGREGATERULE_H


#include <vector>
#include <memory>
#include "Rule.h"

class AggregateRule : public Rule {
private:
    std::vector<std::unique_ptr<Rule>> rules;

public:
    AggregateRule() {};
    AggregateRule(std::vector<std::unique_ptr<Rule>> rules);

    int check(int tl, int tm, int tr, int ml, int mm, int mr, int bl, int bm, int br) override;

    void append(std::unique_ptr<Rule> rule);
};


#endif //CELLULARAUTOMATARPI_AGGREGATERULE_H

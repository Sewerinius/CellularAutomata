//
// Created by sewerin on 07.06.2020.
//

#include "AggregateRule.h"

#include <utility>

AggregateRule::AggregateRule(std::vector<std::unique_ptr<Rule> > rules) : rules(std::move(rules)) {}

int AggregateRule::check(int tl, int tm, int tr, int ml, int mm, int mr, int bl, int bm, int br) {
    for (auto& rule : rules) {
        int res = rule->check(tl, tm, tr, ml, mm, mr, bl, bm, br);
        if (res != -1) {
            return res;
        }
    }
    return -1;
}

void AggregateRule::append(std::unique_ptr<Rule> rule) {
    rules.emplace_back(std::move(rule));
}

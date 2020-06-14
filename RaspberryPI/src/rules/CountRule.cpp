//
// Created by sewerin on 07.06.2020.
//

#include "CountRule.h"

int CountRule::check(int tl, int tm, int tr, int ml, int mm, int mr, int bl, int bm, int br) {
    if (mm != current) {
        return -1;
    }

    std::map<int, int> counts;
    counts[tl]++;
    counts[tm]++;
    counts[tr]++;

    counts[ml]++;
    counts[mr]++;

    counts[bl]++;
    counts[bm]++;
    counts[br]++;

    for(auto& range : ranges) {
        if (counts[range.first] < range.second.first || counts[range.first] > range.second.second) {
            return -1;
        }
    }

    return next;
}

CountRule::CountRule(int current, int next, const std::map<int, std::pair<int, int>> &ranges) : current(current),
                                                                                                ranges(ranges),
                                                                                                next(next) {}

//
// Created by timpo on 3/23/19.
//

#include "TrigramsHolder.h"
void TrigramsHolder::sort() {
    std::sort(trigrams.begin(), trigrams.end());
}

bool TrigramsHolder::contains(trigram tr) {
    return std::binary_search(trigrams.begin(), trigrams.end(), tr);
}

void TrigramsHolder::insert(trigram tr) {
    trigrams.push_back(tr);
}

QVector<trigram>::iterator TrigramsHolder::begin() {
    return trigrams.begin();
}

QVector<trigram>::iterator TrigramsHolder::end() {
    return trigrams.end();
}

//
// Created by timpo on 3/23/19.
//

#ifndef FINDER_TRIGRAMSHOLDER_H
#define FINDER_TRIGRAMSHOLDER_H

#include <QtCore/QVector>

using trigram = uint32_t;

class TrigramsHolder {
public:
    TrigramsHolder() : trigrams(QVector<trigram>{}) {};

    void insert(trigram);
    void sort();
    bool contains(trigram);

    QVector<trigram>::iterator begin();

    QVector<trigram>::iterator end();

    int size();
    void clear();

private:
    QVector<trigram> trigrams;
};


#endif //FINDER_TRIGRAMSHOLDER_H

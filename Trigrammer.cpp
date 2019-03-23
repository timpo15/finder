//
// Created by timpo on 3/23/19.
//

#include <QtCore/QFile>
#include <QtCore/QSet>
#include "Trigrammer.h"
#include "Index.h"

void Trigrammer::extractTrigrams() {
    QVector<QPair<QString, TrigramsHolder>> ans;
    try {
        for (auto &file : files) {
            TrigramsHolder trigramsHolder = getTrigrams(file);
            ans.push_back(QPair<QString, TrigramsHolder>(file, trigramsHolder));
        }
    } catch (std::exception &e) {
    }
    emit finished(ans);
}

TrigramsHolder Trigrammer::getTrigrams(QString fileName) {
    QFile file(fileName);
    TrigramsHolder trigrams;
    if (file.open(QIODevice::ReadOnly)) {
        QSet<trigram> tr;
        char buf[BUFFER_SIZE + TRIGRAM_SIZE - 1];
        qint64 read = file.read(buf, BUFFER_SIZE) - TRIGRAM_SIZE + 1;
        if (read >= 1)
            do {
                read += 2;
                for (size_t i = 0; i <= (read) - TRIGRAM_SIZE; ++i) {
                    trigram calc = 0;
                    for (int j = 0; j < TRIGRAM_SIZE; ++j) {
                        calc = (calc << 8);
                        calc += static_cast<unsigned char>(buf[i + j]);
                    }
                       tr.insert(calc);
                }
                if (tr.size() > 19990) {
                    return TrigramsHolder();
                }
                for (int i = 1; i < TRIGRAM_SIZE; ++i) {
                    buf[i - 1] = buf[BUFFER_SIZE - TRIGRAM_SIZE + i];
                }
            } while ((read = file.read(buf + TRIGRAM_SIZE - 1, BUFFER_SIZE)) >= 1);
        for (auto t : tr) {
            trigrams.insert(t);
        }
        trigrams.sort();
        file.close();
    } else {
    }
    return trigrams;
}

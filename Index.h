//
// Created by timpo on 3/23/19.
//

#ifndef DIRDEMO_INDEX_H
#define DIRDEMO_INDEX_H


#include <QtCore/QObject>
#include <QtCore/QHash>
#include "TrigramsHolder.h"
namespace {
    const int BUFFER_SIZE = 1 << 14;
    const int TRIGRAM_SIZE = 3;
}
class Index : public QObject {
Q_OBJECT

    friend class MainWindow;


public slots:

    void startIndexing(QString rootDir);
    void updateIndex(QVector<QPair<QString, TrigramsHolder>>);
    void findFilesStupid(QString line);
    void findedAns(QVector<QString>);
signals:
    void changeStatus(QString);
    void ready(QVector<QString>);
private:
    void extractTrigrams(QString root);
    QHash<QString, TrigramsHolder> trigrams_map;
    size_t finishedThreadsIndexing = 0;
    size_t finishedThreadsSearching = 0;
    QVector<QString> ans;

};


#endif //DIRDEMO_INDEX_H

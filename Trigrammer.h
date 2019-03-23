//
// Created by timpo on 3/23/19.
//

#ifndef FINDER_TRIGRAMMER_H
#define FINDER_TRIGRAMMER_H


#include <QtCore/QArgument>
#include "TrigramsHolder.h"

class Trigrammer : QObject {
    friend class Index;

Q_OBJECT
private:
    Trigrammer(QVector<QString> files,QObject *parent = nullptr) : QObject(parent), files(files) {};

signals:

    void finished(QVector<QPair<QString, TrigramsHolder>>);

private slots:

    void extractTrigrams();
private:
    TrigramsHolder getTrigrams(QString fileName);
    TrigramsHolder getTrigramHolder(QString line);
    QVector<QString> files;

};

#endif //FINDER_TRIGRAMMER_H

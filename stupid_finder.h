//
// Created by timpo on 3/23/19.
//

#ifndef FINDER_STUPID_FINDER_H
#define FINDER_STUPID_FINDER_H


#include <QtCore/QObject>
#include <QtCore/QVector>

class stupid_finder : QObject {
    friend class Index;

Q_OBJECT
private:
    stupid_finder(QVector<QString> files, QString str, QObject *parent = nullptr) : QObject(parent), files(files),
                                                                                    str(str) {};

    bool checkString(QString path, QString str);

signals:

    void finded(QVector<QString>);

private slots:

    void searchString();

private:
    QVector<QString> files;
    QString str;
};


#endif //FINDER_STUPID_FINDER_H

//
// Created by timpo on 3/23/19.
//

#include <QtCore/QFile>
#include "stupid_finder.h"
#include "pf.h"
void stupid_finder::searchString() {
    QVector<QString> ans;
    for (auto& file: files) {
        if (checkString(file, str))
        {
            ans.push_back(file);
        }
    }
    emit finded(ans);
}

bool stupid_finder::checkString(QString path, QString str) {
    pf prefix(str.toStdString());
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    char c;
    while (file.getChar(&c)) {
        if (prefix.check(c)) {
            return true;
        }
    }
    return false;

}
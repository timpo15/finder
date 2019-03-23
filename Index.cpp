//
// Created by timpo on 3/23/19.
//

#include <QtCore/QDirIterator>
#include <QtCore/QSet>
#include <iostream>
#include <thread>
#include <QtCore/QThread>
#include "Index.h"
#include "Trigrammer.h"
#include "stupid_finder.h"


void Index::startIndexing(QString rootDir) {
    trigrams_map.clear();
    QDirIterator it(rootDir, QDir::Hidden | QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    extractTrigrams(rootDir);
}

void Index::extractTrigrams(QString rootDirectory) {
    finishedThreadsIndexing = 0;
    QDirIterator it(rootDirectory, QDir::Hidden | QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QVector<QString> files;
    while (it.hasNext()) {
        auto file = it.next();
        if (!it.fileInfo().isSymLink()) files.push_back(file);
    }
    int threads_count = std::thread::hardware_concurrency();
    QVector<QVector<QString>> files_for_threads(threads_count);
    for (int i = 0; i < files.size(); i++) {
        files_for_threads[i % threads_count].push_back(files[i]);
    }
    for (int i = 0; i < threads_count; ++i) {
        auto *new_thread = new QThread();
        auto *trigrammer = new Trigrammer(files_for_threads[i]);
        trigrammer->moveToThread(new_thread);

        connect(new_thread, SIGNAL(started()), trigrammer, SLOT(extractTrigrams()));
        qRegisterMetaType<QVector<QPair<QString, TrigramsHolder>>>("QVector<QPair<QString, TrigramsHolder>>");
        connect(trigrammer, SIGNAL(finished(QVector<QPair<QString, TrigramsHolder>>)),
                new_thread, SLOT(quit()));
        connect(trigrammer, SIGNAL(finished(QVector<QPair<QString, TrigramsHolder>>)), this,
                SLOT(updateIndex(QVector<QPair<QString, TrigramsHolder>>)));
        connect(trigrammer, SIGNAL(finished(QVector<QPair<QString, TrigramsHolder>>)),
                trigrammer, SLOT(deleteLater()));
        connect(new_thread, SIGNAL(finished()), new_thread, SLOT(deleteLater()));

        new_thread->start();
    }
}

void Index::updateIndex(QVector<QPair<QString, TrigramsHolder>> holders) {
    for (auto it = holders.begin(); it != holders.end(); ++it) {
        trigrams_map.insert(it->first, it->second);
    }
    ++finishedThreadsIndexing;
    if (finishedThreadsIndexing == std::thread::hardware_concurrency()) {
        finishedThreadsIndexing = 0;
        emit changeStatus(QString("Indexed"));
    }
}


void Index::findFilesStupid(QString line) {
    ans.clear();
    if (line.isEmpty())
            emit ready(QVector<QString>{});
    TrigramsHolder trigramsHolder;
    QVector<QString> goodFiles;
    std::string str = line.toStdString();
    for (ptrdiff_t i = 0; i <= static_cast<ptrdiff_t>(str.size()) - TRIGRAM_SIZE; ++i) {
        trigram calc = 0;
        for (int j = 0; j < TRIGRAM_SIZE; ++j) {
            calc = (calc << 8);
            calc += static_cast<unsigned char>(str[i + j]);
        }
        trigramsHolder.insert(calc);
    }
    for (auto it = trigrams_map.begin(); it != trigrams_map.end(); it++) {
        bool contains = true;
        for (auto &tri : trigramsHolder) {
            if (!(it.value().contains(tri))) {
                contains = false;
                break;
            }
        }
        if (contains) {
            goodFiles.push_back(it.key());
        }
    }
    int threads_count = std::thread::hardware_concurrency();
    QVector<QVector<QString>> files_for_threads(threads_count);
    for (int i = 0; i < goodFiles.size(); i++) {
        files_for_threads[i % threads_count].push_back(goodFiles[i]);
    }
    for (int i = 0; i < threads_count; ++i) {
        auto *new_thread = new QThread();
        auto *searcher = new stupid_finder(files_for_threads[i], line);
        searcher->moveToThread(new_thread);
        connect(new_thread, SIGNAL(started()), searcher, SLOT(searchString()));
        connect(searcher, SIGNAL(finded(QVector<QString>)), new_thread, SLOT(quit()));
        connect(searcher, SIGNAL(finded(QVector<QString>)), searcher, SLOT(deleteLater()));
        connect(new_thread, SIGNAL(finished()), new_thread, SLOT(deleteLater()));
        connect(searcher, SIGNAL(finded(QVector<QString>)), this, SLOT(findedAns(QVector<QString>)));

        new_thread->start();
    }
}

void Index::findedAns(QVector<QString> files) {
    for (auto &file:files) {
        ans.push_back(file);
    }
    ++finishedThreadsSearching;
    if (finishedThreadsSearching == std::thread::hardware_concurrency()) {
        finishedThreadsSearching = 0;
        emit ready(ans);
    }
}
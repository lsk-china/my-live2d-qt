//
// Created by lsk on 2/10/23.
//

#ifndef QDESKTOPPET_2_CMAKE_RUNNINGCHECK_H
#define QDESKTOPPET_2_CMAKE_RUNNINGCHECK_H

#include <QCryptographicHash>
#include <QFile>
#include <QByteArray>
#include <QCoreApplication>
#include <QDirIterator>

static QByteArray calcHash(QString);
static bool isDigit(QString s);
bool check();

#endif //QDESKTOPPET_2_CMAKE_RUNNINGCHECK_H

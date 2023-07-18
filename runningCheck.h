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
#include <QMessageBox>
#include <QTextStream>

#define LOCK_FILE QDir::homePath() + "/.pet_running"
#define THIS_PID QCoreApplication::applicationPid()

bool check();
void deleteLock();
static QByteArray calcHash(QString);

#endif //QDESKTOPPET_2_CMAKE_RUNNINGCHECK_H

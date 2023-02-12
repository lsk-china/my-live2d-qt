//
// Created by lsk on 2/10/23.
//

#include <iostream>
#include "runningCheck.h"

static QByteArray calcHash(QString procDir) {
    QCryptographicHash hash(QCryptographicHash::Algorithm::Md5);
    QFile fileIn(procDir + "/exe");
    fileIn.open(QIODevice::ReadOnly);
    char buf[2048];
    while(fileIn.read(buf, 2048) > 0) {
        hash.addData(buf);
    }
    fileIn.close();
    return hash.result();
}

static bool isDigit(QString s) {
    for (auto i : s) {
        if (!isdigit(i.toLatin1())) {
            return false;
        }
    }
    return true;
}

bool check() {
    qint64 selfPid = QCoreApplication::applicationPid();
    std::cout << selfPid << std::endl;
    QString procDir = "/proc/";
    QString selfProcDir = procDir + QString::number(selfPid);
    QByteArray selfMD5 = calcHash(selfProcDir);
    QDirIterator iter("/proc", QDirIterator::Subdirectories);
    while (iter.hasNext()) {
        QString aProcDir = iter.next();
        if (isDigit(aProcDir.right(aProcDir.lastIndexOf('/')))) {
            int pid = aProcDir.right(aProcDir.lastIndexOf('/')).toInt();
            if (pid > 50 && pid < selfPid) {
                QByteArray procHash = calcHash(aProcDir);
                if (procHash == selfMD5) {
                    std::cout<< aProcDir.toStdString() << std::endl;
                    return true;
                }
            }
        }
    }
    return false;
}

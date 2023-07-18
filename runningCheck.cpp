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

bool check() {
    QFile lockFile = QFile(LOCK_FILE);
    if (! lockFile.exists()) {
        if (!lockFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::NewOnly)) {
            QMessageBox::critical(nullptr, "Error", "Cannot open lock file!");
            QCoreApplication::exit(1);
        }
        lockFile.write(QByteArray().fromStdString(std::to_string(THIS_PID)));
        lockFile.close();
        return false;
    } else {
        // if the lock file exists, there are 2 situations:
        //  1. another process is running
        //  2. another process didn't exit properly and didn't delete the lock file
        // So we need to check if the pid in the lock file is exists and represents a QDesktopPet instance.
        if (!lockFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {
            QMessageBox::critical(nullptr, "Error", "Cannot open lock file!");
            QCoreApplication::exit(1);
        }
        int pid = lockFile.readLine().toInt();
        QDir processDir = QDir(QString("/proc/$1").arg(pid));
        if (! processDir.exists()) {
            // situation 2 and the process doesn't exist. we just need to update the pid
            lockFile.write(QByteArray().fromStdString(std::to_string(THIS_PID)));
            lockFile.close();
            return false;
        } else {
            // check if the process is a QDesktopPet instance
            QDir thisProcess = QDir(QString("/proc/$1").arg(THIS_PID));
            if (calcHash(thisProcess.absolutePath()) == calcHash(processDir.absolutePath())) {
                // situation 1, process exists and process is a QDesktopPet instance
                lockFile.close();
                return true;
            } else {
                // situation 2 and the process is not a QDesktopPet instance
                // update the pid and continue
                lockFile.write(QByteArray().fromStdString(std::to_string(THIS_PID)));
                lockFile.close();
                return false;
            }
        }
    }
}

void deleteLock() {
    QFile lockFile = QFile(LOCK_FILE);
    lockFile.remove();
}

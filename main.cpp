#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QThread>

#include "webserverController.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto mainwindow = new QWidget();
    auto hbox = new QHBoxLayout(mainwindow);

    auto start = new QPushButton("start", mainwindow);
    auto stop =  new QPushButton("stop", mainwindow);

    hbox->addWidget(start);
    hbox->addWidget(stop);

    mainwindow->setLayout(hbox);
    mainwindow->show();

    auto serverController = new webserverController();

    QObject::connect(start,&QPushButton::clicked,serverController,&webserverController::ensureStarted);
    QObject::connect(stop,&QPushButton::clicked,serverController,&webserverController::requestStop);

    return QApplication::exec();
}

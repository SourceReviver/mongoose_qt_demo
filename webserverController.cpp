#include "webserverController.h"

webserverController::webserverController() {}

void webserverController::ensureStarted(){
    serverThread = new QThread();
    server = new webserver();
    server->moveToThread(serverThread);
    connect(serverThread,&QThread::started,server,&webserver::start);
    connect(server,&webserver::finished,serverThread,&QThread::quit);
    connect(server,&webserver::finished,server,&QObject::deleteLater);
    connect(server,&webserver::finished,serverThread, &QThread::deleteLater);
    serverThread->start();
}

void webserverController::requestStop() {
    server->stop();
}

webserverController::~webserverController() {
    delete server;
    serverThread->quit();
    serverThread->wait();
}

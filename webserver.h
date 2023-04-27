#pragma once
#include <QThread>
#include "mongoose/mongoose.h"

class webserver : public QObject {

Q_OBJECT

public:
    explicit webserver();
    ~webserver();

    static void process(struct mg_connection *c, int ev, void *ev_data, void *fn_data);
signals:
 void finished();
public slots:
    void start();
    void stop();
private:
    bool stop_requested;
    struct mg_mgr mgr{};

    static void invalidRequestHandler(struct mg_connection *c);
};

namespace {
  QString mg_str_to_QString(mg_str * mgstr);
}



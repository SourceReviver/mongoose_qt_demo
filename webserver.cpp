#include "webserver.h"
#include <QDebug>
#include "dictionary.h"
webserver::webserver() : stop_requested(false) {
}

void webserver::process(struct mg_connection *c, int ev, void *ev_data,
                        void *fn_data) {
  if (ev == MG_EV_HTTP_MSG) {
    auto *hm = (struct mg_http_message *) ev_data;

    struct mg_str caps[2];  //  expected matchs +1

    qDebug() << "Requested with uri" << mg_str_to_QString(&hm->uri);

    if (mg_match(hm->uri, mg_str("/query/*"), caps)) {
      QString word = mg_str_to_QString(&caps[0]);
      mg_http_reply(c, 200, "", "Result: %s \n",
                    getWordMeaning(word).toUtf8().constData());
    } else {  // For all other URIs,
      invalidRequestHandler(c);
    }
  }
}

void webserver::invalidRequestHandler(struct mg_connection *c) {
  mg_http_reply(c, 200, "", "Invalid request :(", mg_print_esc, 0, "status", 1);
}

void webserver::start() {
  qDebug() << "Server starts";
  mg_mgr_init(&mgr);  // Init manager
  mg_http_listen(&mgr, "http://0.0.0.0:8000", webserver::process,
                 &mgr);  // Setup listener

  for (;;) {
    if (stop_requested) {
      break;
    }
    mg_mgr_poll(&mgr, 1000);  // Infinite event loop
  }
  emit finished();
}

void webserver::stop() {
  qDebug() << "Stop requested";
  stop_requested = true;
}
webserver::~webserver() {
  mg_mgr_free(&mgr);
}

namespace {
QString mg_str_to_QString(mg_str *mgstr) {
  return QString::fromUtf8(mgstr->ptr, mgstr->len);
}
}  // namespace

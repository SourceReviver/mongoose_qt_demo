#include "webserver.h"
#include <QThread>

class webserverController : public QObject {
  Q_OBJECT
 public:
  explicit webserverController();
  ~webserverController();
public slots:
  void ensureStarted();
  void requestStop();
 private:
  QThread * serverThread;
  webserver * server;
};

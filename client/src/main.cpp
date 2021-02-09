#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "models/roomlistmodel.h"
#include "models/messagelistmodel.h"

// #include <QtWebSockets/QWebSocket>
// #include <QAbstractSocket>

// #include <QDebug>

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  /*
  QWebSocket web_socket("client", QWebSocketProtocol::VersionUnknown);
  QObject::connect(&web_socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
      [=](QAbstractSocket::SocketError error){
    std::cerr << error;
  });
  web_socket.open(QUrl(QStringLiteral("ws://localhost:9002")));

  QTime dieTime= QTime::currentTime().addSecs(10);
  while (QTime::currentTime() < dieTime)
      QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

  if (web_socket.isValid()) {
    std::cerr << "ok" << std::endl;
  } else {
    qDebug() << web_socket.errorString();
    std::cerr << "failed" << std::endl;
  }
  //*/

  QQmlApplicationEngine engine;
  RoomListModel room_list_model;
  MessageListModel message_list_model;
  engine.rootContext()->setContextProperty("roomListModel", &room_list_model);
  engine.rootContext()->setContextProperty(
        "messageListModel", &message_list_model);
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
      if (!obj && url == objUrl)
        QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}

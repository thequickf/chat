#ifndef MESSAGELISTMODEL_H
#define MESSAGELISTMODEL_H

#include <QAbstractListModel>

struct Message {
  QString message;
  bool own;
  Message(const QString& msg, bool own) : message(msg), own(own) {}
};

class MessageListModel : public QAbstractListModel {
  Q_OBJECT
public:
  enum MessageRoles {
    MessageRole = Qt::UserRole + 1,
    OwnRole
  };

  explicit MessageListModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(
      const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

public slots:
  void addMessage(const QString& message, bool own);

signals:
  void addMessageFinished();

private:
  QList<Message> messages_;
};

#endif // MESSAGELISTMODEL_H

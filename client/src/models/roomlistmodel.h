#ifndef ROOMLISTMODEL_H
#define ROOMLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QString>

class RoomListModel : public QAbstractListModel {
  Q_OBJECT
  Q_PROPERTY(int selected_room READ selectedRoom
             WRITE setSelectedRoom NOTIFY selectedRoomChanged)
  Q_PROPERTY(int size READ size NOTIFY sizeChanged)

public:
  enum RoomRoles {
    NameRole = Qt::UserRole + 1
  };

  explicit RoomListModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(
      const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

  int selectedRoom() const;
  int size() const;

public slots:
  void setSelectedRoom(int selected_room);

signals:
  void selectedRoomChanged(int selected_room);
  void sizeChanged(int count);

private:
  QList<QString> room_names_;
  int selected_room_ = 0;
};

#endif // ROOMLISTMODEL_H

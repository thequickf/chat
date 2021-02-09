#include "roomlistmodel.h"

RoomListModel::RoomListModel(QObject *parent)
  : QAbstractListModel(parent) {
  room_names_ = {"Global",
                 "Alice",
                 "Bob",
                 "Jane",
                 "Harry",
                 "Wendy",
                 "Michael",
                 "Tomas",
                 "John",
                 "Greg",
                 "Jesus",
                 "Albert",
                 "Forrest",
                 "Phillip"};
}

int RoomListModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return 0;

  return room_names_.size();
}

QVariant RoomListModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  if (role == NameRole) {
    return room_names_.at(index.row());
  }
  return QVariant();
}

int RoomListModel::selectedRoom() const {
  return selected_room_;
}

int RoomListModel::size() const {
  return room_names_.size();
}

void RoomListModel::setSelectedRoom(int selected_room) {
  if (selected_room_ == selected_room)
    return;

  selected_room_ = selected_room;
  emit selectedRoomChanged(selected_room_);
}

QHash<int, QByteArray> RoomListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}

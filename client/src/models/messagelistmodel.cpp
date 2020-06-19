#include "messagelistmodel.h"

#include <QDebug>

MessageListModel::MessageListModel(QObject *parent)
  : QAbstractListModel(parent) {
  messages_ = {
    { "Hey you, out there in the cold"
      "Getting lonely, getting old"
      "Can you feel me?"
      "Hey you, standing in the aisles"
      "With itchy feet and fading smiles"
      "Can you feel me?"
      "Hey you, don't help them to bury the light"
      "Don't give in without a fight",
      true },
    { "Hey you, out there in the cold\n"
      "Getting lonely, getting old\n"
      "Can you feel me?\n"
      "Hey you, standing in the aisles\n"
      "With itchy feet and fading smiles\n"
      "Can you feel me?\n"
      "Hey you, don't help them to bury the light\n"
      "Don't give in without a fight",
      true },
    { "Who was born in a house full of pain."
      "Who was trained not to spit in the fan."
      "Who was told what to do by the man."
      "Who was broken by trained personnel."
      "Who was fitted with collar and chain."
      "Who was given a pat on the back."
      "Who was breaking away from the pack."
      "Who was only a stranger at home."
      "Who was ground down in the end."
      "Who was found dead on the phone."
      "Who was dragged down by the stone."
      "Who was dragged down by the stone.",
      false },
    { "Who was told what to do by the man.", true },
    { "Waters\nRoger\nSyd\nBarret\nTest?", false },
    { "Harry\nPotter", true },
    { "First",  false},
    { "Second", true },
    { "Third", true }
  };
}

int MessageListModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return 0;

  return messages_.size();
}

QVariant MessageListModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  switch (role) {
  case MessageRole:
    return messages_[index.row()].message;
    break;
  case OwnRole:
    return messages_[index.row()].own;
    break;
  default:
    return QVariant();
  }
}

QHash<int, QByteArray> MessageListModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[MessageRole] = "message";
  roles[OwnRole] = "mine";
  return roles;
}

void MessageListModel::addMessage(const QString& message, bool own) {
  beginInsertRows(QModelIndex(),  messages_.size(), messages_.size());
  messages_.append(Message(message, own));
  endInsertRows();
  emit addMessageFinished();
}

#ifndef CONTACTMODEL_H
#define CONTACTMODEL_H

#include <QAbstractTableModel>
#include "contact.h"

class ContactModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit ContactModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void loadContacts();
    void searchContacts(const QString &query);
    Contact getContact(int row) const;

private:
    QList<Contact> contacts;
};

#endif // CONTACTMODEL_H

#include "contactmodel.h"
#include "database.h"

ContactModel::ContactModel(QObject *parent)
    : QAbstractTableModel(parent) {}

int ContactModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return contacts.count();
}

int ContactModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 5;
}

QVariant ContactModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    const Contact &contact = contacts[index.row()];

    switch (index.column()) {
        case 0: return contact.firstName;
        case 1: return contact.lastName;
        case 2: return contact.email;
        case 3: return contact.phone;
        case 4: return contact.address;
        default: return QVariant();
    }
}

QVariant ContactModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return tr("Prénom");
            case 1: return tr("Nom");
            case 2: return tr("Email");
            case 3: return tr("Téléphone");
            case 4: return tr("Adresse");
            default: return QVariant();
        }
    }
    return QVariant();
}

void ContactModel::loadContacts() {
    contacts = Database::loadContacts();
    emit layoutChanged();
}

void ContactModel::searchContacts(const QString &query) {
    contacts = Database::searchContacts(query);
    emit layoutChanged();
}

Contact ContactModel::getContact(int row) const {
    if (row < 0 || row >= contacts.size()) {
        return Contact();
    }
    return contacts.at(row);
}

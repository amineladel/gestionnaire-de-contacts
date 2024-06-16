#ifndef DATABASE_H
#define DATABASE_H

#include <QList>
#include "contact.h"

class Database {
public:
    static void initialize();
    static QList<Contact> loadContacts();
    static QList<Contact> searchContacts(const QString &query);
    static void addContact(const QString &firstName, const QString &lastName, const QString &email, const QString &phone, const QString &address);
    static void updateContact(int id, const QString &firstName, const QString &lastName, const QString &email, const QString &phone, const QString &address);
    static void deleteContact(int id);
};

#endif // DATABASE_H

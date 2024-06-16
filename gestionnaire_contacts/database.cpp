#include "database.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

void Database::initialize() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("contacts.db");

    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
    } else {
        qDebug() << "Database: connection ok";
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS contacts ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "first_name TEXT, "
               "last_name TEXT, "
               "email TEXT, "
               "phone TEXT, "
               "address TEXT)");
}

QList<Contact> Database::loadContacts() {
    QList<Contact> contacts;
    QSqlQuery query("SELECT id, first_name, last_name, email, phone, address FROM contacts");

    while (query.next()) {
        Contact contact(query.value(0).toInt(),
                        query.value(1).toString(),
                        query.value(2).toString(),
                        query.value(3).toString(),
                        query.value(4).toString(),
                        query.value(5).toString());
        contacts.append(contact);
    }
    return contacts;
}

QList<Contact> Database::searchContacts(const QString &queryStr) {
    QList<Contact> contacts;
    QSqlQuery query;
    query.prepare("SELECT id, first_name, last_name, email, phone, address FROM contacts WHERE "
                  "first_name LIKE ? OR last_name LIKE ? OR email LIKE ? OR phone LIKE ? OR address LIKE ?");
    QString likeQuery = "%" + queryStr + "%";
    query.addBindValue(likeQuery);
    query.addBindValue(likeQuery);
    query.addBindValue(likeQuery);
    query.addBindValue(likeQuery);
    query.addBindValue(likeQuery);
    query.exec();

    while (query.next()) {
        Contact contact(query.value(0).toInt(),
                        query.value(1).toString(),
                        query.value(2).toString(),
                        query.value(3).toString(),
                        query.value(4).toString(),
                        query.value(5).toString());
        contacts.append(contact);
    }
    return contacts;
}

void Database::addContact(const QString &firstName, const QString &lastName, const QString &email, const QString &phone, const QString &address) {
    QSqlQuery query;
    query.prepare("INSERT INTO contacts (first_name, last_name, email, phone, address) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(firstName);
    query.addBindValue(lastName);
    query.addBindValue(email);
    query.addBindValue(phone);
    query.addBindValue(address);
    query.exec();
}

void Database::updateContact(int id, const QString &firstName, const QString &lastName, const QString &email, const QString &phone, const QString &address) {
    QSqlQuery query;
    query.prepare("UPDATE contacts SET first_name = ?, last_name = ?, email = ?, phone = ?, address = ? WHERE id = ?");
    query.addBindValue(firstName);
    query.addBindValue(lastName);
    query.addBindValue(email);
    query.addBindValue(phone);
    query.addBindValue(address);
    query.addBindValue(id);
    query.exec();
}

void Database::deleteContact(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM contacts WHERE id = ?");
    query.addBindValue(id);
    query.exec();
}

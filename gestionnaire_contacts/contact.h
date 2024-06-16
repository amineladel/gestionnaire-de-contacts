#ifndef CONTACT_H
#define CONTACT_H

#include <QString>

class Contact {
public:
    int id;
    QString firstName;
    QString lastName;
    QString email;
    QString phone;
    QString address;

    Contact() : id(0), firstName(""), lastName(""), email(""), phone(""), address("") {}
    Contact(int id, const QString &firstName, const QString &lastName, const QString &email, const QString &phone, const QString &address);
};

#endif // CONTACT_H

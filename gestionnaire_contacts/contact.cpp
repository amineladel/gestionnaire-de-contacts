#include "contact.h"

Contact::Contact(int id, const QString &firstName, const QString &lastName, const QString &email, const QString &phone, const QString &address)
    : id(id), firstName(firstName), lastName(lastName), email(email), phone(phone), address(address) {}

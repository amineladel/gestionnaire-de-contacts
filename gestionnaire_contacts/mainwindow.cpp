#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , contactModel(new ContactModel(this))
{
    ui->setupUi(this);
    ui->contactsTableView->setModel(contactModel);

    // Taille des colonnes
    ui->contactsTableView->setColumnWidth(0, 100); // Prénom
    ui->contactsTableView->setColumnWidth(1, 100); // Nom
    ui->contactsTableView->setColumnWidth(2, 175); // Email
    ui->contactsTableView->setColumnWidth(3, 100); // Téléphone
    ui->contactsTableView->setColumnWidth(4, 250); // Adresse

    Database::initialize();
    contactModel->loadContacts();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_addContactButton_clicked() {
    bool ok;
    QString firstName = QInputDialog::getText(this, tr("Ajouter un contact"),
                                              tr("Prénom:"), QLineEdit::Normal,
                                              "", &ok);
    if (ok && !firstName.isEmpty()) {
        QString lastName = QInputDialog::getText(this, tr("Ajouter un contact"),
                                                 tr("Nom:"), QLineEdit::Normal,
                                                 "", &ok);
        QString email = QInputDialog::getText(this, tr("Ajouter un contact"),
                                              tr("Email:"), QLineEdit::Normal,
                                              "", &ok);
        QString phone = QInputDialog::getText(this, tr("Ajouter un contact"),
                                              tr("Téléphone:"), QLineEdit::Normal,
                                              "", &ok);
        QString address = QInputDialog::getText(this, tr("Ajouter un contact"),
                                                tr("Adresse:"), QLineEdit::Normal,
                                                "", &ok);
        Database::addContact(firstName, lastName, email, phone, address);
        contactModel->loadContacts();
    }
}

void MainWindow::on_editContactButton_clicked() {
    QModelIndex index = ui->contactsTableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Modifier le contact"), tr("Veuillez sélectionner un contact à modifier."));
        return;
    }
    Contact contact = contactModel->getContact(index.row());
    bool ok;
    QString firstName = QInputDialog::getText(this, tr("Modifier le contact"),
                                              tr("Prénom:"), QLineEdit::Normal,
                                              contact.firstName, &ok);
    if (ok && !firstName.isEmpty()) {
        QString lastName = QInputDialog::getText(this, tr("Modifier le contact"),
                                                 tr("Nom:"), QLineEdit::Normal,
                                                 contact.lastName, &ok);
        QString email = QInputDialog::getText(this, tr("Modifier le contact"),
                                              tr("Email:"), QLineEdit::Normal,
                                              contact.email, &ok);
        QString phone = QInputDialog::getText(this, tr("Modifier le contact"),
                                              tr("Téléphone:"), QLineEdit::Normal,
                                              contact.phone, &ok);
        QString address = QInputDialog::getText(this, tr("Modifier le contact"),
                                                tr("Adresse:"), QLineEdit::Normal,
                                                contact.address, &ok);
        Database::updateContact(contact.id, firstName, lastName, email, phone, address);
        contactModel->loadContacts();
    }
}

void MainWindow::on_deleteContactButton_clicked() {
    QModelIndex index = ui->contactsTableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Supprimer le contact"), tr("Veuillez sélectionner un contact à supprimer."));
        return;
    }
    Contact contact = contactModel->getContact(index.row());
    Database::deleteContact(contact.id);
    contactModel->loadContacts();
}

void MainWindow::on_searchLineEdit_textChanged(const QString &text) {
    contactModel->searchContacts(text);
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "contactmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addContactButton_clicked();
    void on_editContactButton_clicked();
    void on_deleteContactButton_clicked();
    void on_searchLineEdit_textChanged(const QString &text);

private:
    Ui::MainWindow *ui;
    ContactModel *contactModel;
};

#endif // MAINWINDOW_H

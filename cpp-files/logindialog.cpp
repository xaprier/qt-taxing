#include "../header-files/logindialog.h"

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>
#include <QVariantMap>

#include "../design-files/ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::loginDialog) {
    ui->setupUi(this);
    ui->usernameLine->setFocus();
}

loginDialog::~loginDialog() { delete ui; }

void loginDialog::on_lgnBtn_clicked() {
    // file operation
    QFile file("../data/logins.json");
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "Error, Cannot open the file.";
        return;
    }
    // data entered?
    if (ui->usernameLine->text().isEmpty() || ui->passwdLine->text().isEmpty()) {
        QMessageBox::warning(this, "Hata",
                             "Şifre ve kullanıcı adı girilmesi zorunlud"
                             "ur!");
        return;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
    if (jsonDoc.object()
            .value(ui->usernameLine->text())
            .toObject()
            .value("password")
            .toString() == ui->passwdLine->text()) {
        QMessageBox::information(this, "Login", "Giriş başarılı");
        this->hide();
        mDialog = new managementdialog(this);
        if (mDialog->exec() == QMessageBox::Rejected) {
            qDebug() << "Login Dialog closed";
            this->show();
        }
    } else {
        QMessageBox::warning(this, "Error", "Hatalı kullanıcı adı veya şifre.");
    }
}

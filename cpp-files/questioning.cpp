#include "../header-files/questioning.h"

#include <QCloseEvent>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QDate>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>

#include "../design-files/ui_questioning.h"

questioning::questioning(QWidget *parent)
    : QDialog(parent), ui(new Ui::questioning) {
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this,
            &questioning::inquiryClicked);
}

questioning::~questioning() { delete ui; }

void questioning::inquiryClicked() {
    QFile file("data/users.json");

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error, Cannot open the file.";
        return;
    }
    QJsonArray users = QJsonDocument::fromJson(file.readAll()).object()["users"].toArray();
    QJsonObject my_user;
    for (const auto &user : users) {
        if (user.toObject().keys()[0] == ui->lineEdit->text()) {
            my_user = user.toObject();
            break;
        }
    }

    qDebug() << my_user;

    if (my_user.isEmpty()) {
        QMessageBox::warning(this, "Hata", "Kullanıcı bulunamadı!");
        return;
    }

    // set the data
    ui->txtBoxEditName->setText(my_user[my_user.keys()[0]].toObject()["name"].toString());
    ui->txtBoxEditSurname->setText(my_user[my_user.keys()[0]].toObject()["surname"].toString());
    ui->txtBoxEditSalary->setText(my_user[my_user.keys()[0]].toObject()["salary"].toString());
    ui->txtBoxEditTaxRatio->setText(my_user[my_user.keys()[0]].toObject()["taxRatio"].toString());
    ui->txtBoxEditCustomerNo->setText(my_user.keys()[0]);
    // this month is paid or not
    ui->cbEdit_2->setChecked(my_user[my_user.keys()[0]].toObject()["pays"].toArray()[0].toObject()[QString::number(QDate::currentDate().year()) + "/" + QString::number(QDate::currentDate().month())].toString() == "Ödendi" ? true : false);
    // amount of tax
    ui->lEditTotalValue->setText(QString::number(my_user[my_user.keys()[0]].toObject()["salary"].toString().toDouble() * my_user[my_user.keys()[0]].toObject()["taxRatio"].toString().toDouble() / 100));
    file.close();
}

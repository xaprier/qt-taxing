#include "../header-files/questioning.h"

#include "../design-files/ui_questioning.h"
#include <QCloseEvent>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

questioning::questioning(QWidget *parent)
    : QDialog(parent), ui(new Ui::questioning) {
  ui->setupUi(this);
  connect(ui->pushButton, &QPushButton::clicked, this,
          &questioning::inquiryClicked);
}

questioning::~questioning() { delete ui; }

void questioning::inquiryClicked() {
  QFile file("../data/users.json");

  if (!file.open(QIODevice::ReadWrite)) {
    qDebug() << "Error, Cannot open the file.";
    return;
  }
  // QJsonDocument::fromJson(file.readAll()).object()["users"].toArray()
  for (QJsonValue const &user :
       QJsonDocument::fromJson(file.readAll()).object()["users"].toArray()) {
    if (user.toObject().keys()[0] == ui->lineEdit->text()) {
      ui->txtBoxEditName->setText(user.toObject()[user.toObject().keys()[0]]
                                      .toObject()["name"]
                                      .toString());
      ui->txtBoxEditSurname->setText(user.toObject()[user.toObject().keys()[0]]
                                         .toObject()["surname"]
                                         .toString());
      ui->txtBoxEditSalary->setText(user.toObject()[user.toObject().keys()[0]]
                                        .toObject()["salary"]
                                        .toString());
      ui->txtBoxEditTaxRatio->setText(user.toObject()[user.toObject().keys()[0]]
                                          .toObject()["taxRatio"]
                                          .toString());

      ui->txtBoxEditCustomerNo->setText(user.toObject().keys()[0]);

      ui->cbEdit_2->setChecked(
          (user.toObject()[user.toObject().keys()[0]]
               .toObject()["pays"]
               .toArray()
               .last()
               .toObject()
               .keys()[0] ==
           QString::number(QDate::currentDate().year()) + "/" +
               QString::number(QDate::currentDate().month())) &&
          user.toObject()[user.toObject().keys()[0]]
                  .toObject()["pays"]
                  .toArray()
                  .last()
                  .toObject()
                  .value(user.toObject()[user.toObject().keys()[0]]
                             .toObject()["pays"]
                             .toArray()
                             .last()
                             .toObject()
                             .keys()[0])
                  .toString() == "Ödendi");
      ui->lEditTotalValue->setText(
          QString::number((user.toObject()[user.toObject().keys()[0]]
                               .toObject()["taxRatio"]
                               .toString()
                               .toDouble() /
                           100) *
                          user.toObject()[user.toObject().keys()[0]]
                              .toObject()["salary"]
                              .toString()
                              .toDouble()));
    }
  }
  file.close();
}

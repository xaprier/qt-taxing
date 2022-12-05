#include "../header-files/managementdialog.h"

#include <QDate>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QtGlobal>

#include "../design-files/ui_managementdialog.h"
managementdialog::managementdialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::managementdialog) {
    ui->setupUi(this);
    ui->toolBox->setCurrentIndex(0);
    connect(ui->btnAdd, &QPushButton::clicked, this,
            &managementdialog::btnAdd_clicked);
    connect(ui->lWUsers, &QListWidget::currentRowChanged, this,
            &managementdialog::duzenlemeAyarla);
    connect(ui->cbEdit, &QCheckBox::stateChanged, this,
            &managementdialog::duzenlenebilirMi);
    connect(ui->applyChangesBtn, &QPushButton::clicked, this,
            &managementdialog::degisiklikleriUygula);
    kullanicilariEkle();
    duzenlenebilirMi();
}

managementdialog::~managementdialog() { delete ui; }

void managementdialog::btnAdd_clicked() {
    QFile file("../data/users.json");

    // file check
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Error, Cannot open the file.";
        return;
    }

    // the data's entered?
    if (!verilerGirildiMi()) {
        QMessageBox::warning(this, "Hata", "Lütfen bütün boşlukları doldurunuz");
        return;
    }

    // there won't be a same name and surname
    if (kullaniciZatenVar(ui->txtBoxName->text() + ui->txtBoxSurname->text())) {
        QMessageBox::warning(this, "Hata", "Kullanıcı zaten var!");
        return;
    }

    // tax ratio cannot be lower than 0 and upper then 100
    if (ui->txtBoxTaxRatio->text().toInt() < 0 &&
        ui->txtBoxTaxRatio->text().toInt() > 100) {
        QMessageBox::warning(this, "Hata",
                             "Vergi oranı 0'dan küçük veya 100'den büyük olamaz!");
        return;
    }

    // unique tax number
    quint32 number = rand();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());

    QJsonArray jsonArr = jsonDoc.object()["users"].toArray();

    // convert the values which read to the jsonobject
    QJsonObject jsonObj;
    jsonObj.insert(
        QString::number(number),
        QJsonObject{
            {"name", ui->txtBoxName->text()},
            {"surname", ui->txtBoxSurname->text()},
            {"salary", ui->txtBoxSalary->text()},
            {"taxRatio", ui->txtBoxTaxRatio->text()},
            {"pays", QJsonArray({QJsonObject{
                         {QString::number(QDate::currentDate().year()) + "/" +
                              QString::number(QDate::currentDate().month()),
                          ui->cbPaid->isChecked() ? "Ödendi" : "Ödenmedi"}}})}});
    // while loop until the tax number is unique
    for (QJsonValue const &a : jsonArr) {
        while (a.toObject().keys().contains(QString::number(number))) {
            number = rand();
        }
    }
    // append the object to the jsonArr and append it to the users in json file
    jsonArr.push_back(QJsonValue(jsonObj));
    QJsonObject final_object;
    final_object.insert("users", QJsonValue(jsonArr));
    // seek the file(start from 0 while writing)
    file.resize(0);
    file.write(QJsonDocument(final_object).toJson());
    file.close();
    // add the users to the list widget and print to the screen successfully
    kullanicilariEkle();
    QMessageBox::information(this, "Başarılı", "Kullanıcı başarı ile eklendi");
}

bool managementdialog::kullaniciZatenVar(QString a) {
    QFile file("../data/users.json");
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Error, Cannot open the file.";
        return -1;
    }

    QJsonArray jsonArr =
        QJsonDocument::fromJson(file.readAll()).object()["users"].toArray();

    bool find = 0;

    for (QJsonValue a : jsonArr) {
        if (a.toObject()[a.toObject().keys()[0]].toObject()["name"] ==
                ui->txtBoxName->text() &&
            a.toObject()[a.toObject().keys()[0]].toObject()["surname"] ==
                ui->txtBoxSurname->text()) {
            find = 1;
        }
    }
    file.close();
    return find;
}

bool managementdialog::verilerGirildiMi() {
    return !ui->txtBoxName->text().isEmpty() &&
           !ui->txtBoxSurname->text().isEmpty() &&
           !ui->txtBoxSalary->text().isEmpty() &&
           !ui->txtBoxTaxRatio->text().isEmpty();
}

void managementdialog::kullanicilariEkle() {
    // clear the list widget and read the file and add the all users to the widget
    ui->lWUsers->clear();
    QFile file("../data/users.json");
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Error, Cannot open the file.";
        return;
    }

    QJsonArray jsonArr =
        QJsonDocument::fromJson(file.readAll()).object()["users"].toArray();

    for (QJsonValue a : jsonArr) {
        ui->lWUsers->addItem(
            a.toObject().keys()[0] + "-" +
            a.toObject()[a.toObject().keys()[0]].toObject()["name"].toString() +
            " " +
            a.toObject()[a.toObject().keys()[0]].toObject()["surname"].toString());
    }

    file.close();
}

void managementdialog::duzenlemeAyarla() {
    if (ui->lWUsers->selectedItems().isEmpty())
        return;

    QFile file("../data/users.json");

    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Error, Cannot open the file.";
        return;
    }

    for (QJsonValue const &user :
         QJsonDocument::fromJson(file.readAll()).object()["users"].toArray()) {
        if (user.toObject().keys()[0] ==
            ui->lWUsers->currentItem()->text().first(
                ui->lWUsers->currentItem()->text().indexOf('-'))) {
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

void managementdialog::duzenlenebilirMi() {
    (!ui->cbEdit->isChecked()) ? ui->editInputs->setEnabled(false)
                               : ui->editInputs->setEnabled(true);
}

void managementdialog::degisiklikleriUygula() {
    QFile file("../data/users.json");

    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Error, Cannot open the file.";
        return;
    }

    // keep the values of json file's users array in jsonArr
    QJsonArray jsonArr =
        QJsonDocument::fromJson(file.readAll()).object()["users"].toArray();

    // the edited values object
    QJsonObject editedObj;

    // find the edited value in array and edit the json object with edited values
    for (const QJsonValue &user : jsonArr) {
        if (user.toObject().keys()[0] ==
            ui->lWUsers->currentItem()->text().first(
                ui->lWUsers->currentItem()->text().indexOf('-'))) {
            editedObj.insert(
                ui->txtBoxEditCustomerNo->text(),
                QJsonObject{
                    {"name", ui->txtBoxEditName->text()},
                    {"surname", ui->txtBoxEditSurname->text()},
                    {"salary", ui->txtBoxEditSalary->text()},
                    {"taxRatio", ui->txtBoxEditTaxRatio->text()},
                    {"pays",
                     QJsonArray({QJsonObject{
                         {QString::number(QDate::currentDate().year()) + "/" +
                              QString::number(QDate::currentDate().month()),
                          ui->cbEdit_2->isChecked() ? "Ödendi" : "Ödenmedi"}}})}});
        }
    }

    // clear the edited object on json array
    for (auto it = jsonArr.begin(); it != jsonArr.end(); ++it) {
        QJsonObject obj = (*it).toObject();
        if (obj.keys()[0] == ui->lWUsers->currentItem()->text().first(
                                 ui->lWUsers->currentItem()->text().indexOf('-'))) {
            jsonArr.erase(it);
            break;
        }
    }

    // add the edited json object to the array
    jsonArr.append(editedObj);
    QJsonObject final_object;
    final_object.insert("users", QJsonValue(jsonArr));

    // seek the file(start from 0 while writing)
    file.resize(0);
    qDebug() << final_object;
    file.write(QJsonDocument(final_object).toJson());
    file.close();

    // reread the file and add the items to the list widget and print the screen
    // successfully
    QMessageBox::information(this, "Başarılı", "Kullanıcı başarı ile düzenlendi");
    kullanicilariEkle();
}

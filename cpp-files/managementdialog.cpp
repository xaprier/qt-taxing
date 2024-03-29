#include "../header-files/managementdialog.h"

#include <QDate>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>
#include <QMessageBox>
#include <QtGlobal>
#include <QRandomGenerator>
#include <QShowEvent>
#include <QString>

#include "../design-files/ui_managementdialog.h"
managementdialog::managementdialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::managementdialog) {
    ui->setupUi(this);
    ui->toolBox->setCurrentIndex(0);
    connect(ui->btnAdd, &QPushButton::clicked, this,
            &managementdialog::btnAdd);
    connect(ui->lWUsers, &QListWidget::currentRowChanged, this,
            &managementdialog::setEditing);
    connect(ui->cbEdit, &QCheckBox::stateChanged, this,
            &managementdialog::isItEditable);
    connect(ui->applyChangesBtn, &QPushButton::clicked, this,
            &managementdialog::applyChanges);
    connect(ui->toolBox, &QToolBox::currentChanged, this, &managementdialog::toolBoxChanged);
}

managementdialog::~managementdialog() { delete ui; }

void managementdialog::toolBoxChanged() {
    if (ui->toolBox->currentWidget() != ui->userEdit) return;
    addUsers();
    ui->lWUsers->setCurrentRow(0);
    isItEditable();
}

void managementdialog::btnAdd() {
    QFile file("data/users.json");

    // file check
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Error, Cannot open the file.";
        return;
    }

    // the data's entered?
    if (!dataEntered()) {
        QMessageBox::warning(this, "Hata", "Lütfen bütün boşlukları doldurunuz");
        return;
    }

    // there won't be a same name and surname
    if (userExists()) {
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
    QRandomGenerator random;
    random = QRandomGenerator::securelySeeded();
    quint32 number = random.generate();

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
    for (const QJsonValueRef &a : jsonArr) {
        while (a.toObject().keys().contains(QString::number(number))) {
            number = random();
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
    //addUsers();
    QMessageBox::information(this, "Başarılı", "Kullanıcı başarı ile eklendi");
}

bool managementdialog::userExists() {
    QFile file("data/users.json");
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Error, Cannot open the file.";
        return -1;
    }

    QJsonArray jsonArr =
        QJsonDocument::fromJson(file.readAll()).object()["users"].toArray();

    bool find = false;

    for (QJsonValue a : jsonArr) {
        if (a.toObject()[a.toObject().keys()[0]].toObject()["name"] ==
                ui->txtBoxName->text() &&
            a.toObject()[a.toObject().keys()[0]].toObject()["surname"] ==
                ui->txtBoxSurname->text()) {
            find = true;
        }
    }
    file.close();
    return find;
}

bool managementdialog::dataEntered() {
    return !ui->txtBoxName->text().isEmpty() &&
           !ui->txtBoxSurname->text().isEmpty() &&
           !ui->txtBoxSalary->text().isEmpty() &&
           !ui->txtBoxTaxRatio->text().isEmpty();
}

void managementdialog::addUsers() {
    // clear the list widget and read the file and add the all users to the widget
    ui->lWUsers->clear();
    QFile file("data/users.json");
    if (!file.open(QIODevice::ReadOnly)) {
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

void managementdialog::setEditing() {
    if (ui->lWUsers->selectedItems().isEmpty())
        return;

    QFile file("data/users.json");

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error, Cannot open the file.";
        return;
    }

    QJsonObject muser = QJsonDocument::fromJson(file.readAll())
                                   .object()["users"]
                                   .toArray()[ui->lWUsers->currentRow()].toObject();

    // set the line edits to the selected user's data
    ui->txtBoxEditName->setText(muser[muser.keys()[0]].toObject()["name"].toString());
    ui->txtBoxEditSurname->setText(muser[muser.keys()[0]].toObject()["surname"].toString());
    ui->txtBoxEditSalary->setText(muser[muser.keys()[0]].toObject()["salary"].toString());
    ui->txtBoxEditTaxRatio->setText(muser[muser.keys()[0]].toObject()["taxRatio"].toString());
    ui->txtBoxEditCustomerNo->setText(muser.keys()[0]);
    // this month is paid or not
    ui->cbEdit_2->setChecked(muser[muser.keys()[0]].toObject()["pays"].toArray()[0].toObject()[QString::number(QDate::currentDate().year()) + "/" + QString::number(QDate::currentDate().month())].toString() == "Ödendi" ? true : false);
    // amount of tax
    ui->lEditTotalValue->setText(QString::number(muser[muser.keys()[0]].toObject()["salary"].toString().toDouble() * muser[muser.keys()[0]].toObject()["taxRatio"].toString().toDouble() / 100));

    file.close();
}

void managementdialog::isItEditable() {
    (!ui->cbEdit->isChecked()) ? ui->editInputs->setEnabled(false)
                               : ui->editInputs->setEnabled(true);
}

void managementdialog::applyChanges() {
    QFile file("data/users.json");

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
    for (const QJsonValueRef &user : jsonArr) {
        if (user.toObject().keys()[0] ==
			QString::fromStdString(
				ui->lWUsers->currentItem()->text().toStdString().substr(0, ui->lWUsers->currentItem()->text().indexOf('-')))
			) {
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
        if (obj.keys()[0] == QString::fromStdString(
			ui->lWUsers->currentItem()->text().toStdString().substr(0, ui->lWUsers->currentItem()->text().indexOf('-')))
			) {
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
	addUsers();
}

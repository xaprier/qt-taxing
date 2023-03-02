#include "../header-files/logindialog.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QMessageBox>

#include "../design-files/ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::loginDialog) {
    ui->setupUi(this);

	connect(ui->lgnBtn, &QPushButton::clicked, this, &loginDialog::onLogin);
    ui->usernameLine->setFocus();
	mDialog = new managementdialog();
}

loginDialog::~loginDialog() { delete ui; delete mDialog; }

void loginDialog::onLogin() {
    // file operation
    QFile file("../data/logins.json");
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "Error, Cannot open the file.";
        return;
    }
    // data entered?
    if (ui->usernameLine->text().isEmpty() || ui->passwdLine->text().isEmpty()) {
        QMessageBox::warning(this, "Login",
                             "Please enter your username and password.");
		file.close();
        return;
    }

	QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
	if (jsonDoc.object().find(ui->usernameLine->text())->toObject()["password"].toString() == ui->passwdLine->text()) {
		QMessageBox::information(this, "Login", "Login successful");
		this->hide();
		if (mDialog->exec() == QMessageBox::Rejected) {
			qDebug() << "Login Dialog closed";
			this->show();
		}
	} else {
		QMessageBox::warning(this, "Login", "Login failed");
	}
	file.close();
}

#include "../header-files/taxsystem.h"

#include <QMessageBox>
#include <QDebug>

#include "../design-files/ui_taxsystem.h"

taxSystem::taxSystem(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::taxSystem) {
    ui->setupUi(this);

    connect(ui->managementBtn, &QPushButton::clicked, this,
            &taxSystem::managementBtn);

    connect(ui->inquiryTaxBtn, &QPushButton::clicked, this,
            &taxSystem::inquiryBtn);

	questioningScreen = new questioning;
	loginScreen = new loginDialog;
}

taxSystem::~taxSystem() { delete ui; delete questioningScreen; delete loginScreen; }

void taxSystem::inquiryBtn() {
    this->hide();
    questioningScreen->setModal(true);
    if (questioningScreen->exec() == QMessageBox::Rejected) {
        qDebug() << "Questioning Dialog closed";
        this->show();
    }
}

void taxSystem::managementBtn() {
    this->hide();
	loginScreen->setModal(true);
    if (loginScreen->exec() == QMessageBox::Rejected) {
        qDebug() << "Login Dialog closed";
        this->show();
    }
}

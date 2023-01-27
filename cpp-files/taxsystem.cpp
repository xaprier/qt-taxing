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
}

taxSystem::~taxSystem() { delete ui; }

void taxSystem::inquiryBtn() {
    questioningScreen = new questioning;
    this->hide();
    questioningScreen->setModal(true);
    if (questioningScreen->exec() == QMessageBox::Rejected) {
        qDebug() << "Questioning Dialog closed";
        this->show();
    }
    delete questioningScreen;
}

void taxSystem::managementBtn() {
    loginScreen = new loginDialog;
    this->hide();
    loginScreen->setModal(true);
    if (loginScreen->exec() == QMessageBox::Rejected) {
        qDebug() << "Login Dialog closed";
        this->show();
    }
    delete loginScreen;
}

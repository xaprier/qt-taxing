#include <QApplication>

#include "../header-files/logindialog.h"
#include "../header-files/managementdialog.h"
#include "../header-files/taxsystem.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    taxSystem t;
    t.show();
    return a.exec();
}

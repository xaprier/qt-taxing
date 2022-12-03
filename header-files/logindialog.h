#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "../header-files/managementdialog.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class loginDialog;
}
QT_END_NAMESPACE

class loginDialog : public QDialog {
  Q_OBJECT

public:
  loginDialog(QWidget *parent = nullptr);
  ~loginDialog();
private slots:
  void on_lgnBtn_clicked();

private:
  Ui::loginDialog *ui;
  managementdialog *mDialog;
};
#endif // LOGINDIALOG_H

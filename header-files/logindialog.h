#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

#include "../header-files/managementdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class loginDialog;
}
QT_END_NAMESPACE

class loginDialog : public QDialog {
    Q_OBJECT

  public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog() override;
  private slots:
    void on_lgnBtn_clicked();

  private:
    Ui::loginDialog *ui;
    managementdialog *mDialog;
};
#endif  // LOGINDIALOG_H

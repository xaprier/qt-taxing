#ifndef managementdialog_H
#define managementdialog_H

#include <QDialog>

namespace Ui {
class managementdialog;
}

class managementdialog : public QDialog {
    Q_OBJECT

  public:
    explicit managementdialog(QWidget *parent = nullptr);
    ~managementdialog();

  private slots:
    void btnAdd_clicked();
    void duzenlemeAyarla();
    void duzenlenebilirMi();
    void degisiklikleriUygula();

  private:
    Ui::managementdialog *ui;
    bool kullaniciZatenVar(QString);
    bool verilerGirildiMi();
    void kullanicilariEkle();
};

#endif  // managementdialog_H

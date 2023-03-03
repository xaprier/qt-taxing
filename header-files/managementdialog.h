#ifndef managementdialog_H
#define managementdialog_H

#include <QDialog>
#include <QShowEvent>

namespace Ui {
class managementdialog;
}

class managementdialog : public QDialog {
    Q_OBJECT

  public:
    explicit managementdialog(QWidget *parent = nullptr);
    ~managementdialog() override;

  private slots:
    void btnAdd();
    void setEditing();
    void isItEditable();
    void applyChanges();

  private:
    Ui::managementdialog *ui;
    bool userExists();
    bool dataEntered();
    void addUsers();
    void toolBoxChanged();
};

#endif  // managementdialog_H

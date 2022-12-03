#ifndef TAXSYSTEM_H
#define TAXSYSTEM_H

#include <QMainWindow>

#include "logindialog.h"
#include "questioning.h"

namespace Ui {
class taxSystem;
}

class taxSystem : public QMainWindow {
  Q_OBJECT

public:
  explicit taxSystem(QWidget *parent = nullptr);
  ~taxSystem();

private slots:
  void managementBtn();
  void inquiryBtn();

private:
  Ui::taxSystem *ui;
  loginDialog *loginScreen;
  questioning *questioningScreen;
};

#endif // TAXSYSTEM_H

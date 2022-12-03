#ifndef QUESTIONING_H
#define QUESTIONING_H

#include <QDialog>

namespace Ui {
class questioning;
}

class questioning : public QDialog {
  Q_OBJECT

public:
  explicit questioning(QWidget *parent = nullptr);
  ~questioning();
private slots:
  void inquiryClicked();

private:
  Ui::questioning *ui;
};

#endif // QUESTIONING_H

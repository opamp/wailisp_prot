#ifndef CENTRALWIDGET_HPP
#define CENTRALWIDGET_HPP
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>

class CentralWidget : public QWidget {
Q_OBJECT
public:
  CentralWidget(QWidget* parent = 0);

private slots:
  void push_run();

private:
  QVBoxLayout *topbox;
  QHBoxLayout *texpline_box;
  QLineEdit *texpline;
  QPushButton *runbtn;
  QTextEdit *console;
};

#endif

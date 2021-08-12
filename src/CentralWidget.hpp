#ifndef CENTRALWIDGET_HPP
#define CENTRALWIDGET_HPP
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QThread>

#include "LispRunner.hpp"

class CentralWidget : public QWidget {
Q_OBJECT
public:
  CentralWidget(QWidget* parent = 0);
  ~CentralWidget();

signals:
  void run_lisp(QString exp);
  void init_lisp();

private slots:
  void push_run();
  //void show_returned(QString, QString);
  void update_console(QString);

private:
  QVBoxLayout *topbox;
  QHBoxLayout *texpline_box;
  QLineEdit *texpline;
  QPushButton *runbtn;
  QTextEdit *console;

  LispRunner *lisprunner;
  QThread *lispthread;
};

#endif

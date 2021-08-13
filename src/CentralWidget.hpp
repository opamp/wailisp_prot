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
#include "LispPort.hpp"

class CentralWidget : public QWidget {
Q_OBJECT
public:
  CentralWidget(QWidget* parent = 0);
  ~CentralWidget();

signals:
  void run_lisp();
  void init_lisp(LispPortData*, LispPortData*, LispPortData*);

private slots:
  void push_run();
  void update_std_console();
  void update_err_console();

private:
  QVBoxLayout *topbox;
  QHBoxLayout *texpline_box;
  QLineEdit *texpline;
  QPushButton *runbtn;
  QTextEdit *console;

  LispPortData *in;
  LispPortData *out;
  LispPortData *err;

  LispRunner *lisprunner;
  QThread *lispthread;
};

#endif

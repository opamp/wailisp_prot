#ifndef CENTRALWIDGET_HPP
#define CENTRALWIDGET_HPP
#include <QtWidgets>
#include <QThread>

#include "TextEditConsole.hpp"
#include "CodeEditors.hpp"
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
  void input_lisp(QString);
  void update_std_console();
  void update_err_console();

private:
  // Widgets
  TextEditConsole *console;
  CodeEditors *editors;

  // Layouts
  QVBoxLayout *topbox;

  // LispPorts
  LispPortData *in;
  LispPortData *out;
  LispPortData *err;

  // LispThread
  LispRunner *lisprunner;
  QThread *lispthread;
};

#endif

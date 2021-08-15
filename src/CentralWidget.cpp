#include "CentralWidget.hpp"
#include <string>


CentralWidget::CentralWidget(QWidget* parent)
  :QWidget(parent) {
  
  // Lisp
  in = new LispPortData();
  out = new LispPortData();
  err = new LispPortData();
  connect(out, SIGNAL(update_data()), this, SLOT(update_std_console()));
  connect(err, SIGNAL(update_data()), this, SLOT(update_err_console()));
  
  lispthread = new QThread(this);
  lisprunner = new LispRunner();
  lisprunner->moveToThread(lispthread);
  connect(lispthread,
          SIGNAL(finished()),
          lisprunner,
          SLOT(deleteLater()));
  connect(this,
          SIGNAL(run_lisp()),
          lisprunner,
          SLOT(run()));
  connect(this,
          SIGNAL(init_lisp(LispPortData*, LispPortData*, LispPortData*)),
          lisprunner,
          SLOT(init(LispPortData*, LispPortData*, LispPortData*)));
  lispthread->start();

  // UI
  console = new TextEditConsole(this);
  connect(console, SIGNAL(enter(QString)), this, SLOT(input_lisp(QString)));

  editors = new CodeEditors(this);
  connect(editors, SIGNAL(run_code(QString)), this, SLOT(input_lisp(QString)));

  topbox = new QVBoxLayout(this);
  topbox->addWidget(editors);
  topbox->addWidget(console);

  setLayout(topbox);

  emit init_lisp(in, out, err);
}

void CentralWidget::input_lisp(QString exp) {
  in->set_data(exp + "\n");
}

void CentralWidget::update_std_console() {
  TextEditConsoleData data;
  data.set_data(out->get_data());
  console->print(&data);
}

void CentralWidget::update_err_console() {
  TextEditConsoleData data;
  data.set_data(out->get_data());
  console->print(&data);
}

CentralWidget::~CentralWidget() {
  lispthread->exit();
  lispthread->wait();
}

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
  topbox = new QVBoxLayout(this);
  texpline_box = new QHBoxLayout(this);
  texpline = new QLineEdit(this);
  runbtn = new QPushButton(tr("Run(Eval)"), this);
  console = new TextEditConsole(this);

  connect(runbtn, SIGNAL(clicked()), this, SLOT(push_run()));
  connect(console, SIGNAL(enter(QString)), this, SLOT(input_lisp(QString)));

  texpline_box->addWidget(texpline);
  texpline_box->addWidget(runbtn);
  
  topbox->addLayout(texpline_box);
  topbox->addWidget(console);

  setLayout(topbox);

  emit init_lisp(in, out, err);
}


void CentralWidget::push_run() {
  this->input_lisp(texpline->text());
  //emit run_lisp();
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

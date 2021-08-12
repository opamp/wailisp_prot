#include "CentralWidget.hpp"
#include <string>

CentralWidget::CentralWidget(QWidget* parent)
  :QWidget(parent) {

  // Lisp
  lispthread = new QThread(this);
  lisprunner = new LispRunner();
  lisprunner->moveToThread(lispthread);
  connect(lispthread, SIGNAL(finished()), lisprunner, SLOT(deleteLater()));
  connect(this, SIGNAL(run_lisp(QString)), lisprunner, SLOT(run(QString)));
  connect(this, SIGNAL(init_lisp()), lisprunner, SLOT(init()));
  //connect(lisprunner, SIGNAL(returned(QString, QString)), this, SLOT(show_returned(QString, QString)));
  connect(lisprunner, SIGNAL(read_stdout(QString)), this, SLOT(update_console(QString)));
  connect(lisprunner, SIGNAL(read_stderr(QString)), this, SLOT(update_console(QString)));
  lispthread->start();

  // UI
  topbox = new QVBoxLayout(this);
  texpline_box = new QHBoxLayout(this);
  texpline = new QLineEdit(this);
  runbtn = new QPushButton(tr("Run(Eval)"), this);
  console = new QTextEdit(this);
  
  connect(runbtn, SIGNAL(clicked()), this, SLOT(push_run()));

  texpline_box->addWidget(texpline);
  texpline_box->addWidget(runbtn);
  
  topbox->addLayout(texpline_box);
  topbox->addWidget(console);

  setLayout(topbox);

  emit init_lisp();
}


void CentralWidget::push_run() {
  emit run_lisp(texpline->text());
}

void CentralWidget::update_console(QString str) {
  if(!str.isEmpty()){
    this->console->append(str);
  }
}

CentralWidget::~CentralWidget() {
  lispthread->exit();
  lispthread->wait();
}

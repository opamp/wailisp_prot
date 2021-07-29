#include <string>
#include "CentralWidget.hpp"

CentralWidget::CentralWidget(QWidget* parent)
  :QWidget(parent) {

  // Lisp
  lispthread = new QThread(this);
  lisprunner = new LispRunner();
  lisprunner->moveToThread(lispthread);
  connect(lispthread, SIGNAL(finished()), lisprunner, SLOT(deleteLater()));
  connect(this, SIGNAL(run_lisp(QString)), lisprunner, SLOT(run(QString)));
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
}


void CentralWidget::push_run() {
  emit run_lisp(texpline->text());
}

CentralWidget::~CentralWidget() {
  lispthread->exit();
  lispthread->wait();
}

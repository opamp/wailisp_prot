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
  connect(lisprunner, SIGNAL(returned(QString, QString)), this, SLOT(show_returned(QString, QString)));
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

void CentralWidget::show_returned(QString out, QString err) {
  if(!out.isEmpty()){
    this->console->append(out);
  }
  if(!err.isEmpty()){
    this->console->append(err);
  }
}

CentralWidget::~CentralWidget() {
  lispthread->exit();
  lispthread->wait();
}

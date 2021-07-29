#include <ecl/ecl.h>
#include <iostream>
#include <string>
#include "CentralWidget.hpp"

CentralWidget::CentralWidget(QWidget* parent)
  :QWidget(parent) {

  topbox = new QVBoxLayout();
  texpline_box = new QHBoxLayout();
  
  texpline = new QLineEdit();
  runbtn = new QPushButton(tr("Run(Eval)"));
  connect(runbtn, SIGNAL(clicked()), this, SLOT(push_run()));
  
  console = new QTextEdit();

  texpline_box->addWidget(texpline);
  texpline_box->addWidget(runbtn);
  
  topbox->addLayout(texpline_box);
  topbox->addWidget(console);

  setLayout(topbox);
}


void CentralWidget::push_run() {

}

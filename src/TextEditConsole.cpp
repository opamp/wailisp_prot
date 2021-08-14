#include "TextEditConsole.hpp"
#include <iostream>

TextEditConsoleData::TextEditConsoleData(QObject *parent):
  QObject(parent) {
}

void TextEditConsoleData::set_data(QString data) {
  this->data = data;
}

QString TextEditConsoleData::to_QString() {
  return data;
}


TextEditConsole::TextEditConsole(QWidget* parent) :
  QTextEdit(parent) {
  userinput = "";
}

void TextEditConsole::print(ConsoleData *data) {
  QString printstr = data->to_QString();
  if(!printstr.isEmpty()){
    this->moveCursor(QTextCursor::End);
    this->insertPlainText(printstr);
    this->moveCursor(QTextCursor::End);
  }
}

void TextEditConsole::keyPressEvent(QKeyEvent* e) {
  int code = e->key();
  QString input_char = e->text();
  
  /* sample
  std::cout<<"press key = "<<code<<", "<<txt.toStdString()<<std::endl;
  if(e->modifiers() == Qt::ControlModifier) {
    std::cout<<"Control"<<std::endl;
    if(code == Qt::Key_A) {
      std::cout<<"Ctrl-A"<<std::endl;
    }
  }
  this->moveCursor(QTextCursor::End);
  std::cout<<"END"<<std::endl;
  */

  // Text input or Enter
  if(code == Qt::Key_Enter || code == Qt::Key_Return) {
    emit enter(userinput);
    userinput.clear();
    this->insertPlainText(input_char);
  }else if(!input_char.isEmpty()) {
    this->insertPlainText(input_char);
    userinput += input_char;
  }

  // shortcuts
  if(e->modifiers() == Qt::ControlModifier) {
    // Ctrl-*

  }else if(e->modifiers() == Qt::MetaModifier) {
    // M-*

  }else if(e->modifiers() == Qt::ShiftModifier) {
    // S-*

  }else {
    
  }
}

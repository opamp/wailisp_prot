#include "TextEditConsole.hpp"


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
  this->prompt = QString("> ");
}

void TextEditConsole::set_prompt(QString prmptstr) {
  this->prompt = prmptstr;
}

void TextEditConsole::print(ConsoleData *data) {
  QString printstr = data->to_QString();
  if(!printstr.isEmpty()){
    this->moveCursor(QTextCursor::End);
    this->insertPlainText(printstr);
    this->moveCursor(QTextCursor::End);
  }
}

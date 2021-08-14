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
  userinput_pos = 0;
}

void TextEditConsole::print(ConsoleData *data) {
  QString printstr = data->to_QString();
  if(!printstr.isEmpty()){
    this->moveCursor(QTextCursor::End);
    this->insertPlainText(printstr);
    this->moveCursor(QTextCursor::End);
  }
}

bool TextEditConsole::deleteChar(bool bsmode) {
  if(!bsmode) {
    // Delete
    if( userinput.length() > userinput_pos) {
      this->textCursor().deleteChar();
      userinput = userinput.left(userinput_pos) + userinput.mid(userinput_pos + 1);
      return true;
    }else {
      return false;
    }
  }else {
    // BackSpace
    if(userinput_pos > 0) {
      this->textCursor().deletePreviousChar();
      userinput = userinput.left(userinput_pos - 1) + userinput.mid(userinput_pos);
      userinput_pos -= 1;
      return true;
    }else {
      return false;
    }
  }
}

bool TextEditConsole::moveLeft() {
  if(userinput_pos > 0){
    this->moveCursor(QTextCursor::Left);
    userinput_pos -= 1;
    return true;
  }else {
    return false;
  }
}

bool TextEditConsole::moveRight() {
  if(userinput_pos < userinput.length()) {
    this->moveCursor(QTextCursor::Right);
    userinput_pos += 1;
    return true;
  }else {
    return false;
  }
}

void TextEditConsole::insertStr(QString c) {
  this->insertPlainText(c);
  userinput += c;
  userinput_pos += c.length();
}

void TextEditConsole::keyPressEvent(QKeyEvent* e) {
  int code = e->key();
  QString input_char = e->text();

  // shortcuts
  if(e->modifiers() == Qt::ControlModifier) {
    // Ctrl-*
    switch(code) {
    case Qt::Key_D:
      deleteChar(false);
      break;
    case Qt::Key_F:
      moveRight();
      break;
    case Qt::Key_B:
      moveLeft();
      break;
    }
    return;
  }else if(e->modifiers() == Qt::MetaModifier) {
    // M-*
    return;
  }
    
  // Text input/delete or Enter
  if(code == Qt::Key_Enter || code == Qt::Key_Return) {
    // Press Enter/Retrun
    emit enter(userinput);
    userinput.clear();
    userinput_pos = 0;
    this->moveCursor(QTextCursor::End);
    this->insertPlainText(input_char);
    
  }else if(code == Qt::Key_Backspace) {
    // Press BS
    deleteChar(true);
    
  }else if(code == Qt::Key_Delete) {
    // Press Delete
    deleteChar(false);
    
  }else if(!input_char.isEmpty()) {
    // Input chars
    insertStr(input_char);
  }
}

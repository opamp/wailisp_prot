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

  // Text input/delete or Enter
  if(code == Qt::Key_Enter || code == Qt::Key_Return) {
    // Press Enter/Retrun
    emit enter(userinput);
    userinput.clear();
    userinput_pos = 0;
    this->insertPlainText(input_char);
    
  }else if(code == Qt::Key_Backspace) {
    // Press BS
    deleteChar(true);
    
  }else if(code == Qt::Key_Delete) {
    // Press Delete
    deleteChar(false);
    
  }else if(!input_char.isEmpty()) {
    // Input chars
    this->insertPlainText(input_char);
    userinput += input_char;
    userinput_pos += input_char.length();
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

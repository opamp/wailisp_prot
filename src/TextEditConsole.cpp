#include "TextEditConsole.hpp"

static bool isPrintableQString(QString str) {
  for(int i = 0;i < str.length(); i++) {
    QChar c = str.at(i);
    if(!c.isPrint()) {
      return false;
    }
  }
  return true;
}

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
  history_pos = 0;
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

void TextEditConsole::moveHead() {
  for(int i = 0; i < userinput_pos; i++) {
    this->moveCursor(QTextCursor::Left);
  }
  userinput_pos = 0;
}

void TextEditConsole::moveEnd() {
  for(int i = 0; i < userinput.length() - userinput_pos; i++) {
    this->moveCursor(QTextCursor::Right);
  }
  userinput_pos = userinput.length();
}

void TextEditConsole::insertStr(QString c) {
  this->insertPlainText(c);
  userinput = userinput.left(userinput_pos) + c + userinput.mid(userinput_pos);
  userinput_pos += c.length();
}

void TextEditConsole::movecursorinputpos() {
  this->moveCursor(QTextCursor::End);
  for(int i = 0; i < userinput.length() - userinput_pos; i++) {
    this->moveCursor(QTextCursor::Left);
  }
}

void TextEditConsole::enter_exp() {
  // Press Enter/Retrun
  emit enter(userinput);

  // Save history
  if(!userinput.isEmpty()) {
    history.push_back(userinput);
    history_pos = history.length();
  }
  
  userinput.clear();
  userinput_pos = 0;
  this->moveCursor(QTextCursor::End);
  this->insertPlainText("\n");
}

void TextEditConsole::clear_exp() {
  this->moveCursor(QTextCursor::End);
  for(int i = 0; i < userinput.length(); i++) {
    this->textCursor().deletePreviousChar();
  }
  userinput.clear();
  userinput_pos = 0;
}

void TextEditConsole::insert_history() {
  if(history_pos > 0 && history_pos <= history.length()) {
    QString histexp = history.at(history_pos - 1);
    clear_exp();
    insertStr(histexp);
  }
}

void TextEditConsole::keyPressEvent(QKeyEvent* e) {
  // move insert position
  movecursorinputpos();

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
    case Qt::Key_A:
      moveHead();
      break;
    case Qt::Key_E:
      moveEnd();
      break;
    case Qt::Key_P:
      insert_history();
      if(history_pos > 0){
        history_pos -= 1;
      }
      break;
    case Qt::Key_N:
      if(history_pos < history.length()) {
        history_pos += 1;
      }
      insert_history();
      break;
    }
    return;
  }else if(e->modifiers() == Qt::MetaModifier) {
    // M-*
    return;
  }
    
  // Text input/delete or Enter
  if(code == Qt::Key_Enter || code == Qt::Key_Return) {
    enter_exp();
    
  }else if(code == Qt::Key_Backspace) {
    // Press BS
    deleteChar(true);
    
  }else if(code == Qt::Key_Delete) {
    // Press Delete
    deleteChar(false);
    
  }else if(!input_char.isEmpty() && isPrintableQString(input_char)) {
    // Input chars
    insertStr(input_char);
  }

}

#ifndef GUIREPL
#define GUIREPL
#include <QTextEdit>
#include <QKeyEvent>
#include "Console.hpp"

class TextEditConsoleData : public QObject, public ConsoleData {
Q_OBJECT
public:
  TextEditConsoleData(QObject *parent = 0);
  void set_data(QString data);
  QString to_QString();

protected:
  QString data;
};


class TextEditConsole : public QTextEdit, public Console {
Q_OBJECT
public:
  TextEditConsole(QWidget* parent = 0);

  void print(ConsoleData*);

signals:
  void enter(QString);

protected:
  void keyPressEvent(QKeyEvent* e);

  void enter_exp();
  void insert_history();
  void clear_exp();
  bool deleteChar(bool bsmode = false);
  void insertStr(QString);
  bool moveLeft();
  bool moveRight();
  void moveHead();
  void moveEnd(); 
  void movecursorinputpos();

private:
  QVector<QString> history;
  int history_pos;
  QString userinput;
  int userinput_pos;
};
#endif

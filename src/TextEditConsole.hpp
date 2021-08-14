#ifndef GUIREPL
#define GUIREPL
#include <QTextEdit>
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

  void set_prompt(QString prmptstr);

  void print(ConsoleData*);

protected:
  QString prompt;
};
#endif

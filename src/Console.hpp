#ifndef CONSOLE
#define CONSOLE
#include <QString>

class ConsoleData {
public:
  virtual QString to_QString() = 0;
};

class Console {
public:
  virtual void print(ConsoleData*) = 0;
};

#endif

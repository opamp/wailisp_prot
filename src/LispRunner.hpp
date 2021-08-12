#ifndef LISPRUNNER_HPP
#define LISPRUNNER_HPP
#include <QObject>
#include "LispPort.hpp"

class LispRunner : public QObject {
Q_OBJECT
public:
  LispRunner(QObject *parent = 0);

public slots:
  void init();
  void run(QString exp);

private slots:
  void get_stdoutportstr();
  void get_stderrportstr();

signals:
  void returned();
  void read_stdout(QString);
  void read_stderr(QString);

private:
  LispPort* in;
  LispPort* out;
  LispPort* err;
};

#endif

#ifndef LISPRUNNER_HPP
#define LISPRUNNER_HPP
#include <QObject>
#include "LispPort.hpp"

class LispRunner : public QObject {
Q_OBJECT
public:
  LispRunner(QObject *parent = 0);

public slots:
  void run(QString exp);

signals:
  void returned(QString, QString);

private:
  LispPort* in;
  LispPort* out;
  LispPort* err;
};

#endif

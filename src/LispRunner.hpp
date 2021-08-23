#ifndef LISPRUNNER_HPP
#define LISPRUNNER_HPP
#include <QObject>
#include "LispPort.hpp"

class LispRunner : public QObject {
Q_OBJECT
public:
  LispRunner(QObject *parent = 0);
  void set_portsdata(LispPortData* in, LispPortData* out, LispPortData *err);

public slots:
  void init(LispPortData*, LispPortData*, LispPortData*);

signals:
  void returned();

private:
  LispPort* in;
  LispPort* out;
  LispPort* err;
};

#endif

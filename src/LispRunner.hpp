#ifndef LISPRUNNER_HPP
#define LISPRUNNER_HPP
#include <QObject>

class LispRunner : public QObject {
Q_OBJECT
public:
  LispRunner(QObject *parent = 0);

public slots:
  void run(QString exp);
};

#endif

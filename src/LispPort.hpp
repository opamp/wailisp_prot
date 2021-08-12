#ifndef LISPPORT_HPP
#define LISPPORT_HPP
#include <QObject>
#include <libguile.h>


class LispPort : public QObject {
Q_OBJECT
public:
  LispPort(QObject *parent = 0);
  SCM get_read_port();
  SCM get_write_port();

  size_t read(SCM dst, size_t start, size_t count);
  size_t write(SCM src, size_t start, size_t count);

  void set_data(QString data);
  QString get_data();
  
protected:
  scm_t_port_type* porttype;
  QString data;
};
#endif

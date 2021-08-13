#ifndef LISPPORT_HPP
#define LISPPORT_HPP
#include <QObject>
#include <libguile.h>


class LispPortData : public QObject {
Q_OBJECT
public:
  LispPortData(QObject *parent = 0);

  void set_data(QString data);
  QString get_data(bool notclear = false);
  void clear();

signals:
  void update_data();

private:
  QString data;
};

class LispPort : public QObject {
Q_OBJECT
public:
  LispPort(QObject *parent = 0);
  void set_portdata(LispPortData* portdata);
  SCM get_read_port();
  SCM get_write_port();

  size_t read(SCM dst, size_t start, size_t count);
  size_t write(SCM src, size_t start, size_t count);

signals:
  void read_port();
  void write_port();
  
protected:
  scm_t_port_type* porttype;
  LispPortData* portdata;
};
#endif

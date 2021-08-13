#include "LispPort.hpp"
#include <cstring>

static size_t read_stream(SCM port, SCM dst, size_t start, size_t count) {
  auto obj = (LispPort*)SCM_STREAM(port);
  return obj->read(dst, start ,count);
}

static size_t write_stream(SCM port, SCM src, size_t start, size_t count) {
  auto obj = (LispPort*)SCM_STREAM(port);
  return obj->write(src, start, count);
}

LispPort::LispPort(QObject *parent):
  QObject(parent) {
  char portname[] = "lispport";
  porttype = scm_make_port_type(portname, &read_stream, &write_stream);
}

void LispPort::set_portdata(LispPortData* portdata) {
  this->portdata = portdata;
}

SCM LispPort::get_read_port() {
  return scm_c_make_port(porttype, SCM_RDNG, (scm_t_bits)this);
}

SCM LispPort::get_write_port() {
  return scm_c_make_port(porttype, SCM_WRTNG | SCM_BUFLINE, (scm_t_bits)this);
}

size_t LispPort::read(SCM dst, size_t start, size_t count) {
  QString data = portdata->get_data(true);
  QString read_str;
  
  if(data.isEmpty()){
      return 0;
  }

  if(data.length() <= count) {
    read_str = data;
    data.clear();
  }else{
    read_str = data.left(count);
    data = data.right(count + 1);
  }
  portdata->set_data(data);

  QByteArray ba = read_str.toLocal8Bit();
  const char *cstr = ba.data();

  memcpy(SCM_BYTEVECTOR_CONTENTS(dst) + start, cstr, strlen(cstr));
  emit read_port();
  return strlen(cstr);
}

size_t LispPort::write(SCM src, size_t start, size_t count) {
  char* buf = new char[count + 1];
  memcpy(buf, SCM_BYTEVECTOR_CONTENTS(src) + start, count);
  buf[count] = '\0';
  QString qbuf = QString(reinterpret_cast<char*>(buf));
  
  QString data = portdata->get_data(true);
  data += qbuf;
  portdata->set_data(data);
  
  emit write_port();
  return count;
}


LispPortData::LispPortData(QObject *parent) :
  QObject(parent) {
}

void LispPortData::set_data(QString data) {
  this->data = data;
  emit update_data();
}

QString LispPortData::get_data(bool notclear) {
  QString rtn = this->data;
  if(!notclear){
    this->clear();
  }
  return rtn;
}

void LispPortData::clear() {
  this->data.clear();
}


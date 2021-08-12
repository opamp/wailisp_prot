#include "LispPort.hpp"
#include <cstring>

/*
sample: https://github.com/emacsmirror/lilypond/blob/2be19f11c11d89f03d0c54ceeb20b8a022261af7/lily/include/overlay-string-port.hh
*/

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


SCM LispPort::get_read_port() {
  return scm_c_make_port(porttype, SCM_RDNG, (scm_t_bits)this);
}

SCM LispPort::get_write_port() {
  return scm_c_make_port(porttype, SCM_WRTNG | SCM_BUFLINE, (scm_t_bits)this);
}

size_t LispPort::read(SCM dst, size_t start, size_t count) {
  if(this->data.isEmpty()){
      return 0;
  }

  QString read_str;
  if(data.length() <= count) {
    read_str = data;
    data.clear();
  }else{
    read_str = data.left(count);
    data = data.right(count + 1);
  }

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
  this->data += qbuf;
  emit write_port();
  return count;
}


void LispPort::set_data(QString data) {
  this->data = data;
}

QString LispPort::get_data(bool notclear) {
  QString rtn = this->data;
  if(!notclear){
    this->clear();
  }
  return rtn;
}

void LispPort::clear() {
  this->data.clear();
}

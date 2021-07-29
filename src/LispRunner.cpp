#include "LispRunner.hpp"
#include <libguile.h>
#include <iostream>

static void* testfunc(void *data) {
  const char *sexp_str = (char*)data;
  
  SCM sexp = scm_from_locale_string(sexp_str);
  scm_eval_string(sexp);

  return NULL;
}

LispRunner::LispRunner(QObject *parent) :
  QObject(parent) {
  
}

void LispRunner::run(QString exp) {
  // char*に変換
  QByteArray ba = exp.toLocal8Bit();
  const char *c_sexp = ba.data();
  std::cout<<"LispRunner run"<<std::endl;
  scm_with_guile(testfunc, (void*)c_sexp);
  std::cout<<"LispRunner finish"<<std::endl;
}

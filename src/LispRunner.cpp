#include "LispRunner.hpp"
#include <libguile.h>

struct std_ports {
  LispPort *in;
  LispPort *out;
  LispPort *err;
};

static void *eval_with_port(void *data) {
  // save default ports
  SCM def_input = scm_current_input_port();
  SCM def_outport = scm_current_output_port();
  SCM def_errport = scm_current_error_port();

  // get/set default ports
  struct std_ports *ports = (struct std_ports*)data;
  SCM lisp_input = ports->in->get_read_port();
  SCM lisp_outport = ports->out->get_write_port();
  SCM lisp_errport = ports->err->get_write_port();
  scm_set_current_input_port(lisp_input);
  scm_set_current_output_port(lisp_outport);
  scm_set_current_error_port(lisp_errport);

  //SCM re = scm_read(ports->in->get_port());
  //SCM out = scm_eval(re, scm_interaction_environment());
  //char* result = scm_to_locale_string(out);
  //std::cout<<">> "<<result<<std::endl;

  //scm_set_current_input_port(ports->in->get_port());
  //scm_set_current_output_port(ports->out->get_port());
  //scm_set_current_error_port(ports->err->get_port());
  scm_c_eval_string("(define ans (eval (read) (interaction-environment)))");
  scm_c_eval_string("(display ans)");
  //SCM re = scm_read(ports->in->get_port());
  //SCM out = scm_eval(re, scm_interaction_environment());

  // print eval result (string only) for test
  //char* result = scm_to_locale_string(out);
  //std::cout<<">> "<<result<<std::endl;

  // print stdout/err for test
  scm_force_output(lisp_outport);
  scm_force_output(lisp_errport);

  // revert ports
  scm_set_current_input_port(def_input);
  scm_set_current_output_port(def_outport);
  scm_set_current_error_port(def_errport);
  return NULL;
}

LispRunner::LispRunner(QObject *parent) :
  QObject(parent) {
}

void LispRunner::run(QString exp) {
  // char*に変換
  scm_init_guile();
  in = new LispPort(this);
  out = new LispPort(this);
  err = new LispPort(this);
  this->in->set_data(exp);
  struct std_ports ports;
  ports.in = in;
  ports.out = out;
  ports.err = err;

  eval_with_port(&ports);

  QString outstr = out->get_data();
  QString errstr = err->get_data();

  emit returned(outstr, errstr);
}

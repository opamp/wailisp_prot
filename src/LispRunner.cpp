#include "LispRunner.hpp"
#include <libguile.h>

LispRunner::LispRunner(QObject *parent) :
  QObject(parent) {
}

void LispRunner::init() {
  scm_init_guile();
  in = new LispPort(this);
  out = new LispPort(this);
  err = new LispPort(this);
  connect(out, SIGNAL(write_port()), this, SLOT(get_stdoutportstr()));
  connect(err, SIGNAL(write_port()), this, SLOT(get_stderrportstr()));

  scm_c_eval_string("(define stdin (current-input-port))");
  scm_c_eval_string("(define stdout (current-output-port))");
  scm_c_eval_string("(define stderr (current-error-port))");

  SCM lisp_input = in->get_read_port();
  SCM lisp_outport = out->get_write_port();
  SCM lisp_errport = err->get_write_port();
  
  scm_set_current_input_port(lisp_input);
  scm_set_current_output_port(lisp_outport);
  scm_set_current_error_port(lisp_errport);
}

void LispRunner::run(QString exp) {
  this->in->set_data(exp);

  // TODO: 例外をキャッチしないと落ちます
  scm_c_eval_string("(define ans (eval (read) (interaction-environment)))");
  scm_c_eval_string("(format #t \"ans = ~s\" ans)");
  
  scm_c_eval_string("(force-output (current-output-port))");
  scm_c_eval_string("(force-output (current-error-port))");

  emit returned();
}

void LispRunner::get_stdoutportstr() {
  QString stdout_str = out->get_data();
  emit read_stdout(stdout_str);
}

void LispRunner::get_stderrportstr() {
  QString stderr_str = err->get_data();
  emit read_stderr(stderr_str);
}

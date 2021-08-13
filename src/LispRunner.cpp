#include "LispRunner.hpp"
#include <libguile.h>

LispRunner::LispRunner(QObject *parent) :
  QObject(parent) {
}

void LispRunner::init(LispPortData* in_d, LispPortData* out_d, LispPortData* err_d) {
  scm_init_guile();
  
  in = new LispPort(this);
  out = new LispPort(this);
  err = new LispPort(this);

  in->set_portdata(in_d);
  out->set_portdata(out_d);
  err->set_portdata(err_d);
  
  scm_c_eval_string("(define stdin (current-input-port))");
  scm_c_eval_string("(define stdout (current-output-port))");
  scm_c_eval_string("(define stderr (current-error-port))");

  SCM lisp_input = in->get_read_port();
  SCM lisp_outport = out->get_write_port();
  SCM lisp_errport = err->get_write_port();
  
  scm_set_current_input_port(lisp_input);
  scm_set_current_output_port(lisp_outport);
  scm_set_current_error_port(lisp_errport);

  scm_c_eval_string("(use-modules (system repl repl))");
  scm_c_eval_string("(start-repl)");
}

void LispRunner::run() {
  // TODO: 例外をキャッチしないと落ちます
  scm_c_eval_string("(define ans (eval (read) (interaction-environment)))");
  scm_c_eval_string("(format #t \"ans = ~s\" ans)");
  
  scm_c_eval_string("(force-output (current-output-port))");
  scm_c_eval_string("(force-output (current-error-port))");

  emit returned();
}


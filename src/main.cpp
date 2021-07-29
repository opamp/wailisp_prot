#include <QApplication>
#include <libguile.h>
#include "MainWindow.hpp"

// static SCM my_hostname(){
//     return scm_from_locale_string ("My-host-name-dummy");
// }

// static void* imain(void *data){
//   scm_c_define_gsubr("my-hostname", 0, 0, 0, (scm_t_subr)my_hostname);
//   SCM st2 = scm_from_locale_string("(/ 1 0)");
//   scm_eval_string(st2);
//   SCM st = scm_from_locale_string("hello world\n");
//   SCM out = scm_current_output_port();
//   scm_display(st, out);
//   return NULL;
// }


int main(int argc, char** argv) {
  // scm_with_guile(imain, 0);
  // return 0;
  QApplication app(argc, argv);
  app.setApplicationName("GuiREPL");

  MainWindow* window = new MainWindow();
  window->show();

  return app.exec();
}

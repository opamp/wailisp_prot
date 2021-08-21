#ifndef CODEEDITORS_HPP
#define CODEEDITORS_HPP
#include <QtWidgets>
#include <QVector>
#include "FileEdit.hpp"

class CodeEditors : public QWidget {
Q_OBJECT
public:
  CodeEditors(QWidget* parent = 0);
  void selectLastTab();

signals:
  void run_code(QString);
                                  
public slots:
  void new_trig();
  void open_trig();
  void save_trig();
  void saveas_trig();
  void close_trig();
  void run_trig();

private:
  QToolBar *toolbar;
  QAction *neweditAction;
  QAction *openfileAction;
  QAction *savefileAction;
  QAction *saveasfileAction;
  QAction *closefileAction;
  QAction *runAction;
  
  QTabWidget *tab;
  FileEdit *scratch;
  QList<FileEdit*> editors;

  QVBoxLayout *topbox;

  int tabcount;
};
#endif

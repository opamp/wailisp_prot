#ifndef CODEEDITORS_HPP
#define CODEEDITORS_HPP
#include <QtWidgets>
#include <QVector>

class CodeEditors : public QWidget {
Q_OBJECT
public:
  CodeEditors(QWidget* parent = 0);

signals:
  void run_code(QString);
                                  
private slots:
  void run_trig();

private:
  QToolBar *toolbar;
  QAction *neweditAction;
  QAction *openfileAction;
  QAction *savefileAction;
  QAction *closefileAction;
  QAction *runAction;
  
  QTabWidget *tab;
  QPlainTextEdit *scratch;
  QVector<QPlainTextEdit> editors;

  QVBoxLayout *topbox;
};
#endif

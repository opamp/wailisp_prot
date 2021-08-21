#ifndef FILEEDIT_HPP
#define FILEEDIT_HPP
#include <QtWidgets>

class FileEdit : public QPlainTextEdit {
Q_OBJECT
public:
  FileEdit(QWidget* parent = 0);
  bool isAssociatedWithFile();
  void setFilePath(QString);
  QString getFilePath();
  QString getTitle(bool full = false);

signals:
  void titleChanged(QString);

public slots:
  void save();
  void load();
  
protected:
  QFile file;
  QString title[2];
};

#endif

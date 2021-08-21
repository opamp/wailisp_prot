#ifndef FILEEDIT_HPP
#define FILEEDIT_HPP
#include <QtWidgets>

class FileEdit : public QPlainTextEdit {
Q_OBJECT
public:
  FileEdit(QWidget* parent = 0);
  bool isAssociatedWithFile();
  bool isChanged();
  void setFilePath(QString);
  QString getFilePath();
  QString getTitle(bool full = false);

signals:
  void titleChanged(QString);

public slots:
  void save();
  void load();

private slots:
  void setChanged();
  
protected:
  QFile file;
  QString title[2];

  bool changed;
};

#endif

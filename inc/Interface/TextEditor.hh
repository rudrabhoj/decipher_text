#ifndef __INTERFACE_TEXTEDITOR_HH__
#define __INTERFACE_TEXTEDITOR_HH__

#include <Control/ControlData.hh>
#include <Document/Page.hh>

#include <QMainWindow>
#include <QTextEdit>
#include <QList>

class TextEditor : public QTextEdit{
public:
  TextEditor(QMainWindow *parent, ControlData *ctrlData);
  void syncText(QString inputText);
  void editorFontSetting();

private:
  ControlData *localControl;
  QList<Page> *pagesData;

  void enableFontFamily();
  void configureConnections();
  void cursorMoved();
  void unSetSave();
  void enableSave();

  //Foreign dependents
  QString getConfigFontFamily();
  double getConfigFontSize();
  void syncCurrentWord(int lineNo, int pos);
  void sendDrawEvent();
  bool getSaveStatus();
  void configureSave(bool staat);

};

#endif

#ifndef __INTERFACE_TEXTEDITOR_HH__
#define __INTERFACE_TEXTEDITOR_HH__

#include <Control/ControlData.hh>
#include <QMainWindow>
#include <QTextEdit>


class TextEditor : public QTextEdit{
public:
  TextEditor(QMainWindow *parent, ControlData *ctrlData);
  void editorFontSetting();

private:
  ControlData *localControl;
  void enableFontFamily();
  
  //Foreign dependents
  QString getConfigFontFamily();
  double getConfigFontSize();
    
};

#endif

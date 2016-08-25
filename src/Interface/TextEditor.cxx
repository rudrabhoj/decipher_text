#include <Interface/TextEditor.hh>
#include <Document/Page.hh>

#include <QTextCursor>
#include <iostream>

TextEditor::TextEditor(QMainWindow *parent, ControlData *ctrlData) : QTextEdit(parent){
  localControl = ctrlData;
  
  configureConnections();
  
  setParent(parent);
}

void TextEditor::editorFontSetting(){
  if (getConfigFontFamily() != "NaN"){
    this->setFontFamily(getConfigFontFamily());
  }

  this->setFontPointSize(getConfigFontSize());
}

void TextEditor::configureConnections(){
  connect(this, &QTextEdit::cursorPositionChanged, this, &TextEditor::cursorMoved);
}

void TextEditor::cursorMoved(){
  QTextCursor tmpCur;
  int position, lineNo;
  
  tmpCur = textCursor();
  position = tmpCur.columnNumber();
  lineNo = tmpCur.blockNumber();
  
  syncCurrentWord(lineNo, position);
}

//Foreign dependents
QString TextEditor::getConfigFontFamily(){
  return localControl->getSetting()->getFontFamily();
}

double TextEditor::getConfigFontSize(){
  return localControl->getSetting()->getFontSize();
}

void TextEditor::syncCurrentWord(int lineNo, int pos){
  int pgNo;
  QList<Page> *pageBank;
  Page *localPage;
  
  pgNo = localControl->getProjectManager()->getCurrentPage();
  
  if (pgNo > -1){
    pageBank = localControl->getProjectManager()->emitPages();
    localPage = &((*pageBank)[pgNo]);
    
    if(localPage->getOcrStatus()){
      localPage->interpretCurrentWord(lineNo, pos);
    }
  }
}


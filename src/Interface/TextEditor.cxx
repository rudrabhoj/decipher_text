#include <Interface/TextEditor.hh>

TextEditor::TextEditor(QMainWindow *parent, ControlData *ctrlData) : QTextEdit(parent){
  localControl = ctrlData;
  
  setParent(parent);
}

void TextEditor::editorFontSetting(){
  if (getConfigFontFamily() != "NaN"){
    this->setFontFamily(getConfigFontFamily());
  }

  this->setFontPointSize(getConfigFontSize());
}

//Foreign dependents
QString TextEditor::getConfigFontFamily(){
  return localControl->getSetting()->getFontFamily();
}

double TextEditor::getConfigFontSize(){
  return localControl->getSetting()->getFontSize();
}


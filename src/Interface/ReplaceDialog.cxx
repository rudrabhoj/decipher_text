#include <Interface/ReplaceDialog.hh>
#include "ui_ReplaceDialog.h"

#include <iostream>

ReplaceDialog::ReplaceDialog(QWidget *parent, ControlData *ctrData) :
  QDialog(parent), ui(new Ui::ReplaceDialog){
  ui->setupUi(this);
  localControl = ctrData;
  currentItem = -1;

  connectButtons();
}

void ReplaceDialog::displayDialog(int inCurrentItem){
  currentItem = inCurrentItem;
  show();
}

void ReplaceDialog::connectButtons(){
  connect(ui->currentButton, &QPushButton::clicked, this, &ReplaceDialog::replaceCurrent);
  connect(ui->allButton, &QPushButton::clicked, this, &ReplaceDialog::replaceAll);
  connect(ui->closeButton, &QPushButton::clicked, this, &ReplaceDialog::hide);
}

void ReplaceDialog::replaceCurrent(){
  QString originalText = ui->searchEdit->text();
  QString newText = ui->replaceEdit->text();

  replaceAt(currentItem, originalText, newText);
}

int ReplaceDialog::getTotalPages(){
  return getPages()->length();
}

void ReplaceDialog::replaceAll(){
  QString originalText = ui->searchEdit->text();
  QString newText = ui->replaceEdit->text();

  int i, lim;
  lim = getTotalPages();

  for(i = 0; i < lim; i++){
    replaceAt(i, originalText, newText);
  }
}

ReplaceDialog::~ReplaceDialog(){
  delete ui;
}



//Foreign Dependents
QList<Page>* ReplaceDialog::getPages(){
  return localControl->getProjectManager()->emitPages();
}

void ReplaceDialog::replaceAt(int pos, QString original, QString replacement){
  QList<Page> *localPages;
  QString originalContent;

  localPages = getPages();

  if((*localPages)[pos].getOcrStatus()){
    originalContent = (*localPages)[pos].getText();

    originalContent.replace(original, replacement);
    (*localPages)[pos].resetDataX(originalContent);

    publishCurrentReplaced();
  }
}

void ReplaceDialog::publishCurrentReplaced(){
  localControl->getPubSub()->publish("currentReplaced");
}

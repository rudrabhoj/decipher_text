#include <Interface/ReplaceDialog.hh>
#include "ui_ReplaceDialog.h"

ReplaceDialog::ReplaceDialog(QWidget *parent, ControlData *ctrData) :
  QDialog(parent), ui(new Ui::ReplaceDialog){
  ui->setupUi(this);
  localControl = ctrData;
}

ReplaceDialog::~ReplaceDialog(){
  delete ui;
}

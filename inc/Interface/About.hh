#ifndef __INTERFACE_ABOUT_HH__
#define __INTERFACE_ABOUT_HH__
#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QString>
#include <Control/Setting.hh>
#include <Control/ControlData.hh>

class About : public QDialog {
public:
  About(QWidget *parent, ControlData *ctrlData);
  void displayDialog();
private:
  Setting *localSetting;
  ControlData *localControl;
  QVBoxLayout *rowLayout;
  QTextEdit *textBox;
  QPushButton *doneOkay;

  void configureDialog();
  void allocateResources();
  void configureTextbox();
  void configureButtons();
  void configureGui();
  void configureLayout();
  void configureConnections();
  void hideDialog();
  void loadAboutText();
  QString solveVariables(QString rawInput);
  QString getAboutData();

  //Foreign dependents:
  QString getAboutUrl();
  QString getVersion();
};

#endif

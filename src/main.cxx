//Main file
#include <iostream>
#include <QApplication>
#include <Control/Setting.hh>
#include <Interface/MainWindow.hh>
#include <Control/ControlData.hh>
#include <Control/Language.hh>

int main(int argc, char *argv[]){
  int rc;

  QApplication decipherApp(argc, argv);
  ControlData *globalControl = new ControlData(argc, argv);

  std::cout << "Decipher Text 0.1-alpha" << std::endl;
  //Setting *hello = new Setting();

  MainWindow *decipherWindow = new MainWindow(0, globalControl);

  rc = decipherApp.exec();

  delete globalControl;

  return rc;
}

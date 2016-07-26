//Main file
#include <iostream>
#include <QApplication>
#include <Control/Setting.hh>
#include <Interface/MainWindow.hh>

int main(int argc, char *argv[]){
  QApplication decipherApp(argc, argv);

  std::cout << "Decipher Text 0.1-alpha" << std::endl;
  //Setting *hello = new Setting();

  MainWindow *decipherWindow = new MainWindow(0);

  return decipherApp.exec();
}

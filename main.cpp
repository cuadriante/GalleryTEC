#include <iostream>
//#include <QApplication>
//#include "Interface/MainWindow.h"
#include "StorageManager/raidManager.h"

using namespace std;

int main(int argc, char** argv) {

    raidManager manager;

//    manager.read("2");
    manager.addNewImage("111001101000", "3");

    //QApplication app(argc, argv);
    //MainWindow mainWindow;
    //mainWindow.show();

    //return app.exec();
    return 0;
}

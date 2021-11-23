#include <iostream>
//#include <QApplication>
//#include "Interface/MainWindow.h"
#include "StorageManager/raidManager.h"

using namespace std;

int main(int argc, char** argv) {

    raidManager manager;

    manager.read("3");

//    string prueba = "Actualmente-curso-seis-temas-distintos-en-el-TEC";
//    cout << prueba.length() << endl;

//    manager.write("Actualmente-curso-seis-temas-distintos-en-el-TEC", "3");

    //QApplication app(argc, argv);
    //MainWindow mainWindow;
    //mainWindow.show();

    //return app.exec();
    return 0;
}

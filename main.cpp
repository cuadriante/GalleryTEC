#include <iostream>
//#include <QApplication>
//#include "Interface/MainWindow.h"
#include "StorageManager/raidManager.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;

int main(int argc, char** argv) {

//    namespace pt = boost::property_tree;
//
//    pt::ptree root, prueba;
//
//    pt::read_json("RAIDStorage/Disk1/data.json", root);
//
//    prueba.put_child("1", root.get_child("3"));
//
//    cout << prueba.get<string>("1.dictionary") << endl;

    raidManager manager;

//    manager.checkForRecover("3");
    manager.getCode("1");
//    manager.addNewImage("111001101000", "3");

    //QApplication app(argc, argv);
    //MainWindow mainWindow;
    //mainWindow.show();

    //return app.exec();
    return 0;
}

#include <iostream>
#include <QApplication>
#include "Interface/Interface.h"
#include "DataBase/DataBaseHandler.h"
#include "StorageManager/RaidManager.h"

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/client_session.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
namespace pt = boost::property_tree;

int main(int argc, char** argv) {

    DataBaseHandler dataBaseHandler;
    RaidManager raidManager;
    QApplication app(argc, argv);
    Interface interface;
    interface.setDbHandler(&dataBaseHandler);
    interface.setRaidManager(&raidManager, 1);
    interface.show();

//    pt::ptree dictionary;

//    dictionary.put("", "This is the dictionary");

//    raidManager.addNewImage("010001000101010111", "1", dictionary);
//    raidManager.addNewImage("0111101", "2", dictionary);
//    raidManager.addNewImage("110010101000", "3", dictionary);

//    cout << raidManager.getCode("2") << endl;

    return app.exec();

}

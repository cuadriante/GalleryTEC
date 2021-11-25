#include <iostream>
#include <QApplication>
#include "Interface/Interface.h"
#include "DataBase/DataBaseHandler.h"
#include "StorageManager/raidManager.h"

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

int main(int argc, char** argv) {

//    raidManager manager;

    DataBaseHandler dataBaseHandler;

//    dataBaseHandler.addUserToDb("adri", "xx");
//    dataBaseHandler.setCurrentUser("adri");
//    dataBaseHandler.addGalleryToUserDb("maxi");
//    dataBaseHandler.addGalleryToUserDb("temi");
//    dataBaseHandler.addGalleryToUserDb("foca");
//    dataBaseHandler.addImageToUserGalleryDb("maxito", "maxi");
//    dataBaseHandler.retrieveAllUserGalleries();

    QApplication app(argc, argv);
    Interface interface;
    interface.setDbHandler(&dataBaseHandler);
    interface.show();

    return app.exec();
    return 1;
}

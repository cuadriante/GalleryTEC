#include <iostream>
#include <QApplication>
#include "Interface/Interface.h"
#include "DataBase/DataBaseHandler.h"

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/client_session.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

int main(int argc, char** argv) {

    DataBaseHandler dataBaseHandler;
    dataBaseHandler.addUserToDb("adri", "xx");
    dataBaseHandler.setCurrentUser("adri");
    dataBaseHandler.addGalleryToUserDb("maxi");
    dataBaseHandler.addImageToUserGalleryDb("maxito", "maxi");
//    QApplication app(argc, argv);
//    Interface interface;
//    interface.setDbHandler(&dataBaseHandler);
//    interface.show();
//
//    return app.exec();
    return 1;
}

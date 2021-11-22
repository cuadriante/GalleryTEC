#include <iostream>
#include <QApplication>
#include "Interface/MainWindow.h"
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
    dataBaseHandler.addUserToDb("adrr", "222");
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}

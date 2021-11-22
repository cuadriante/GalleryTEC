//
// Created by cuadriante on 21/11/21.
//

#ifndef GALLERYTEC_DATABASEHANDLER_H
#define GALLERYTEC_DATABASEHANDLER_H



#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/client_session.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

using namespace std;
using namespace mongocxx;

class DataBaseHandler {
private:
    database db;
    client conn;
public:

    DataBaseHandler();
    bool addUserToDb(const std::string &username, const std::string &password);
    bool checkForUserInDb(const std::string &username, const std::string &password);
    bool addGalleryToUserDb(const std::string &galleryName);
    bool removeGalleryFromUser(const std::string &galleryName);
    bool addImageToUserGalleryDb(const std::string &imageName);
    bool editGalleryFromUserDb(const std::string &galleryName);

};




#endif //GALLERYTEC_DATABASEHANDLER_H

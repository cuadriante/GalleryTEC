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
using namespace bsoncxx::builder::basic;
using namespace bsoncxx::builder::stream;


class DataBaseHandler {
private:
    database db;
    client conn;
    string currentUser;
    vector<string> galleriesVector;
public:

    DataBaseHandler();
    bool addUserToDb(const std::string &username, const std::string &password);
    bool checkForUserInDb(const std::string &username, const std::string &password);
    bool addGalleryToUserDb(const std::string &galleryName);
    bool deleteGalleryFromUserDb(const std::string &galleryName);
    bool addImageToUserGalleryDb(const string &imageName, const string &galleryName);
    bool deleteImageFromUserGalleryDb(const string &imageName, const string &galleryName);
    bool editGalleryFromUserDb(const std::string &galleryName);

    void setCurrentUser(const string &currentUser);

    vector<string> retrieveAllUserGalleries();

    vector<string> retrieveAllImagesFromUserGallery(string gallery);

    bool checkForImageInUserGallery(const string &imageName, const string &galleryName);

    bool
    editImageMetadata(const string &imageName, const string &galleryName, const string &parameter,
                      const string &newValue);

    vector<string> retrieveImageMetadata(const string &imageName, const string &galleryName);
};




#endif //GALLERYTEC_DATABASEHANDLER_H

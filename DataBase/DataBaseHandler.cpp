//
// Created by cuadriante on 21/11/21.
//

#include "DataBaseHandler.h"

DataBaseHandler::DataBaseHandler() {
    instance inst{};
    uri myURI("mongodb://localhost:27017");
    try {
        client conn(myURI);
        db = conn["GalleryTEC"];
        collection coll = db["users"];
        cursor cor = coll.find({});
        cout << "successful connection to GalleryTEC database." << endl;


    } catch (const exception& xcp){
        cout << "connection failed: " << xcp.what() << endl;
    }
}

bool DataBaseHandler::addUserToDb(const string &username, const string &password) {
    uri myURI("mongodb://localhost:27017");
    client conn(myURI);
    db = conn["GalleryTEC"];
    collection coll = db["users"];
    coll.insert_one(bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("username", username),
            bsoncxx::builder::basic::kvp("password", password),
            bsoncxx::builder::basic::kvp("galleries", bsoncxx::builder::basic::make_array(""))
            ));
    return false;
}

bool DataBaseHandler::checkForUserInDb(const string &username, const string &password) {
    uri myURI("mongodb://localhost:27017");
    client conn(myURI);
    db = conn["GalleryTEC"];
    collection coll = db["users"];
    auto cursor = coll.find({});
    for(auto&& doc : cursor){
        bsoncxx::document::element dbUsername = doc["username"];
        cout << "username: " << dbUsername.get_utf8().value << endl;
        string dbUsernameString = (string) dbUsername.get_utf8().value;
        if (dbUsernameString == username){
            cout << "found username <" << username << "> in database" << endl;
            dbUsername = doc["password"];
            dbUsernameString = (string) dbUsername.get_utf8().value;
            if (dbUsernameString == password){
                cout << "found password match for <" << username << "> : " << password << endl;
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

bool DataBaseHandler::addGalleryToUserDb(const string &galleryName) {
    uri myURI("mongodb://localhost:27017");
    client conn(myURI);
    db = conn["GalleryTEC"];
    collection coll = db["users"];
//    auto builder = bsoncxx::builder::stream::document{};
//    bsoncxx::document::value update_statement = builder
//            << "$push" << bsoncxx::builder::stream::open_document
//            << "galleries" << bsoncxx::builder::stream::open_document
//            << "$each" << bsoncxx::builder::stream::open_array
//            << galleryName
//            << bsoncxx::builder::stream::close_array
//            <<bsoncxx::builder::stream::close_document
//            <<bsoncxx::builder::stream::close_document
//            << bsoncxx::builder::stream::finalize;
//
//    coll.update_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("username", currentUser)), update_statement.view());

    return false;
}

void DataBaseHandler::setCurrentUser(const string &currentUser) {
    DataBaseHandler::currentUser = currentUser;
}

bool DataBaseHandler::editGalleryFromUserDb(const string &galleryName) {
//    uri myURI("mongodb://localhost:27017");
//    client conn(myURI);
//    db = conn["GalleryTEC"];
//    collection coll = db["users"];
//    auto builder = bsoncxx::builder::stream::document{};
//    coll.update_one(
//            builder << "username" << currentUser
//                    << bsoncxx::builder::stream::finalize,
//
//            builder <<
//    )
    return false;
}

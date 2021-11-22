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
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_to_add = builder
            << "username" << username
            << "password" << password
            << bsoncxx::builder::stream::finalize;
    coll.insert_one(doc_to_add.view());
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

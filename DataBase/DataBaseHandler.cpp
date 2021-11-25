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

// USER MANAGEMENT

bool DataBaseHandler::addUserToDb(const string &username, const string &password) {
    uri myURI("mongodb://localhost:27017");
    client conn(myURI);
    db = conn["GalleryTEC"];
    collection coll = db["users"];
    auto cursor = coll.find({});
    for(auto&& doc : cursor) {
        bsoncxx::document::element dbUsername = doc["username"];
        cout << "username: " << dbUsername.get_utf8().value << endl;
        string dbUsernameString = (string) dbUsername.get_utf8().value;
        if (dbUsernameString == username) {
            cout << "found username <" << username << "> in database" << endl;
            return false;
        }
    }
    coll.insert_one(make_document(
            kvp("username", username),
            kvp("password", password),
            kvp("galleries", make_array())
            ));

    return true;
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

void DataBaseHandler::setCurrentUser(const string &currentUser) {
    DataBaseHandler::currentUser = currentUser;
}

// GALLERY MANAGEMENT

bool DataBaseHandler::addGalleryToUserDb(const string &galleryName) {
    retrieveAllUserGalleries();
    if(galleriesVector.size() > 5) {
        return false;
    }
    uri myURI("mongodb://localhost:27017");
    client conn(myURI);
    db = conn["GalleryTEC"];
    collection coll = db["users"];
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value update_statement = builder
            << "$push" << bsoncxx::builder::stream::open_document
            << "galleries" << bsoncxx::builder::stream::open_document
                    << "$each" << bsoncxx::builder::stream::open_array
                    << galleryName
                << bsoncxx::builder::stream::close_array
            << bsoncxx::builder::stream::close_document
            << bsoncxx::builder::stream::close_document
            << bsoncxx::builder::stream::finalize;
    coll.update_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("username", currentUser)), update_statement.view());

    return true;

}

bool DataBaseHandler::editGalleryFromUserDb(const string &galleryName, const string &newGalleryName) {
    if(find(galleriesVector.begin(), galleriesVector.end(), galleryName) != galleriesVector.end()){
        uri myURI("mongodb://localhost:27017");
        client conn(myURI);
        db = conn["GalleryTEC"];
        collection coll = db["users"];
        deleteGalleryFromUserDb(galleryName, false);

        vector<string> currentImages = retrieveAllImagesFromUserGallery(galleryName);
        for(const string& imageName : currentImages){
            editImageMetadata(imageName, galleryName, "gallery", newGalleryName);
        }

        addGalleryToUserDb(newGalleryName);
        return true;
    }
    return false;
}

bool DataBaseHandler::deleteGalleryFromUserDb(const string &galleryName, bool deleteImages) {\
    //vector<string> currentGalleries = retrieveAllUserGalleries();
    if(find(galleriesVector.begin(), galleriesVector.end(), galleryName) != galleriesVector.end()){
            uri myURI("mongodb://localhost:27017");
            client conn(myURI);
            db = conn["GalleryTEC"];
            collection coll = db["users"];
            coll.update_one(make_document(kvp("username", currentUser)), make_document(kvp("$unset", make_document(kvp("galleries",
            make_array())))));

            if (galleriesVector.size() != 1){
                remove(galleriesVector.begin(), galleriesVector.end(), galleryName);
                for(const string& gallery : galleriesVector){
                    if (!gallery.empty()){
                        addGalleryToUserDb(gallery);
                    }
                }
            }

            if(deleteImages){
                deleteAllImagesFromUserGalleryDb(galleryName);
            }
        return true;
    } else {
        return false;
    }
}

vector<string> DataBaseHandler::retrieveAllUserGalleries() {
    galleriesVector.clear();
    uri myURI("mongodb://localhost:27017");
    client conn(myURI);
    db = conn["GalleryTEC"];
    collection coll = db["users"];
    auto cursor = coll.find({});
    for(auto&& doc : cursor){
        bsoncxx::document::element userGalleries = doc["username"];
        cout << "username: " << userGalleries.get_utf8().value << endl;
        string dbUsernameString = (string) userGalleries.get_utf8().value;
        if (dbUsernameString == currentUser){
            userGalleries = doc["galleries"];
            if(userGalleries && userGalleries.type() == bsoncxx::type::k_array){
                bsoncxx::array::view galleries{userGalleries.get_array().value};
                for (bsoncxx::array::element subdocument : galleries){
                    cout << subdocument.get_utf8().value << endl;
                    string galleryName = (string) subdocument.get_utf8().value;
                    galleriesVector.push_back(galleryName);
                }
            }
        }
    }
    return galleriesVector;
}

// IMAGE MANAGEMENT

bool DataBaseHandler::addImageToUserGalleryDb(const string &imageName, const string &galleryName) {
    if(find(galleriesVector.begin(), galleriesVector.end(), galleryName) != galleriesVector.end()){
        uri myURI("mongodb://localhost:27017");
        client conn(myURI);
        db = conn["GalleryTEC"];
        collection coll = db["images"];
        auto builder = bsoncxx::builder::stream::document{};
        bsoncxx::document::value update_statement = builder
                << "username" << currentUser
                << "gallery" << galleryName
                << "imageName" << imageName
                << "imageAuthor" << "unknown"
                << "imageYear" << "unknown"
                << "imageSize" << "unknown"
                << "imageDesc" << "unknown"
                << finalize;
        coll.insert_one(update_statement.view());
        return true;
    } else {
        return false;
    }


}

bool DataBaseHandler::deleteAllImagesFromUserGalleryDb(const string &galleryName) {
        uri myURI("mongodb://localhost:27017");
        client conn(myURI);
        db = conn["GalleryTEC"];
        collection coll = db["images"];
        coll.delete_one(make_document(kvp("username", currentUser), kvp("gallery", galleryName)));
        return true;

}

bool DataBaseHandler::deleteImageFromUserGalleryDb(const string &imageName, const string &galleryName) {
    if (checkForImageInUserGallery(imageName, galleryName)){
        uri myURI("mongodb://localhost:27017");
        client conn(myURI);
        db = conn["GalleryTEC"];
        collection coll = db["images"];
        coll.delete_one(make_document(kvp("username", currentUser), kvp("gallery", galleryName), kvp("imageName", imageName)));
        return true;
    } else {
        return false;
    }
}

bool DataBaseHandler::checkForImageInUserGallery(const string &imageName, const string &galleryName) {
    vector<string> galleryImagesVector;
    uri myURI("mongodb://localhost:27017");
    client conn(myURI);
    db = conn["GalleryTEC"];
    collection coll = db["images"];
    auto cursor = coll.find({});
    for (auto &&doc: cursor) {
        bsoncxx::document::element userGalleries = doc["username"];
        cout << "username: " << userGalleries.get_utf8().value << endl;
        string dbUsernameString = (string) userGalleries.get_utf8().value;
        if (dbUsernameString == currentUser) {
            userGalleries = doc["gallery"];
            string dbGalleryString = (string) userGalleries.get_utf8().value;
            if (dbGalleryString == galleryName) {
                userGalleries = doc["imageName"];
                string dbImageString = (string) userGalleries.get_utf8().value;
                if (dbImageString == imageName){
                    return true;
                }
            }
        }
    }
    return false;
}

vector<string> DataBaseHandler::retrieveAllImagesFromUserGallery(string gallery) {
    vector<string> galleryImagesVector;
    uri myURI("mongodb://localhost:27017");
    client conn(myURI);
    db = conn["GalleryTEC"];
    collection coll = db["images"];
    auto cursor = coll.find({});
    for (auto &&doc: cursor) {
        bsoncxx::document::element userGalleries = doc["username"];
        cout << "username: " << userGalleries.get_utf8().value << endl;
        string dbUsernameString = (string) userGalleries.get_utf8().value;
        if (dbUsernameString == currentUser) {
            userGalleries = doc["gallery"];
            string dbGalleryString = (string) userGalleries.get_utf8().value;
            if (dbGalleryString == gallery) {
                userGalleries = doc["imageName"];
                string imageName = (string) userGalleries.get_utf8().value;
                galleryImagesVector.push_back(imageName);

            }
        }
    }
    return  galleryImagesVector;
}

// METADATA MANAGEMENTmake_document(kvp(parameter, newValue)))

vector<string> DataBaseHandler::retrieveImageMetadata(const string &imageName, const string &galleryName){
    vector<string> imageMetadataVector;
    uri myURI("mongodb://localhost:27017");
    client conn(myURI);
    db = conn["GalleryTEC"];
    collection coll = db["images"];
    auto cursor = coll.find({});
    for (auto &&doc: cursor) {
        bsoncxx::document::element userGalleries = doc["username"];
        cout << "username: " << userGalleries.get_utf8().value << endl;
        string dbUsernameString = (string) userGalleries.get_utf8().value;
        if (dbUsernameString == currentUser) {
            userGalleries = doc["gallery"];
            string dbGalleryString = (string) userGalleries.get_utf8().value;
            if (dbGalleryString == galleryName) {
                userGalleries = doc["imageName"];
                string dbImageString = (string) userGalleries.get_utf8().value;
                if (dbImageString == imageName){
                    imageMetadataVector.push_back(dbImageString);
                    imageMetadataVector.push_back((string) doc["imageAuthor"].get_utf8().value);
                    imageMetadataVector.push_back((string) doc["imageYear"].get_utf8().value);
                    imageMetadataVector.push_back((string) doc["imageSize"].get_utf8().value);
                    imageMetadataVector.push_back((string) doc["imageDesc"].get_utf8().value);
                }
            }
        }
    }
    return imageMetadataVector;
}

bool DataBaseHandler::editImageMetadata(const string &imageName, const string &galleryName, const string &parameter, const string &newValue){
    if (checkForImageInUserGallery(imageName, galleryName)){
        uri myURI("mongodb://localhost:27017");
        client conn(myURI);
        db = conn["GalleryTEC"];
        collection coll = db["images"];

        auto builder = bsoncxx::builder::stream::document{};
        bsoncxx::document::value update_statement = builder
                << "$set" << open_document
                << parameter << newValue
                << close_document
                << finalize;

        coll.update_one(make_document(kvp("username", currentUser),
                                      kvp("imageName", imageName),
                                      kvp("gallery", galleryName)), update_statement.view());
        return true;
    } else {
        return false;
    }
}



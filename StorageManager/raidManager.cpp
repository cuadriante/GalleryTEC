#include "raidManager.h"

raidManager::raidManager() {
    setFileLocation();
}

void raidManager::write(string data) {
    setDisk();
    setFileLocation();

    ofstream file;
    file.open(fileLocation, ios::app);

    if (file.fail()) {
        cout << "File " + fileLocation + " not found" << endl;
    } else {
        file << data + "\n";
        cout << "Data stored on Disk " + to_string(disk) << endl;
        file.close();
    }
}

void raidManager::read(string imgID) {
//    ifstream file;
//    string data;
//
//    int counter = 1;
//
//    file.open(fileLocation, ios::in);
//
//    if (file.fail()) {
//        cout << "File " + fileLocation + " not found" << endl;
//    } else {
//        while (counter < 4) {
//            getline(file, data);
//            counter++;
//
//        }
//        cout << data << endl;
//        cout << data[0] << endl;
//        cout << "Data found" << endl;
//
//        file.close();
//    }

    setImageId(imgID);
    int counter = 1;


    while (counter < 5) {
        setDisk();
        setFileLocation();
        pt::read_json(fileLocation, root);
        try {
            if (root.get<bool>(imageID + ".parity") == 0) {
                tempCode = root.get<string>(imageID + ".code");
                if (root.get<bool>(imageID + ".extrabit") == 1) {
                    deleteExtraBit(tempCode);
                }
                completeCode += tempCode;
                counter ++;
            }
        } catch (boost::property_tree::ptree_bad_path err) {
            cout << "Data not found" << endl;
        }
    }

    cout << completeCode << endl;



}

void raidManager::deleteExtraBit(string code) {
    string newCode = "";
    for (int i = 0; i < code.length() - 1; ++i) {
        newCode += code[i];
    }

    tempCode = newCode;
}

void raidManager::setFileLocation() {
    raidManager::fileLocation = "RAIDStorage/Disk" + to_string(disk) + "/data.json";
}

void raidManager::setDisk() {
    raidManager::disk += 1;
    if (raidManager::disk > 5) {
        raidManager::disk = 1;
    }
}

void raidManager::setImageId(const string &imageId) {
    imageID = imageId;
}

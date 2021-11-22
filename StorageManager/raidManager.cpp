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

string raidManager::read() {
    ifstream file;
    string data;

    int counter = 1;

    file.open(fileLocation, ios::in);

    if (file.fail()) {
        cout << "File " + fileLocation + " not found" << endl;
    } else {
        while (counter < 4) {
            getline(file, data);
            counter++;

        }
        cout << data << endl;
        cout << data[0] << endl;
        cout << "Data found" << endl;

        file.close();
    }

    return data;
}

void raidManager::setFileLocation() {
    raidManager::fileLocation = "RAIDStorage/Disk" + to_string(disk) + "/data.txt";
}

void raidManager::setDisk() {
    raidManager::disk += 1;
    if (raidManager::disk > 4) {
        raidManager::disk = 1;
    }
}

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

void raidManager::setFileLocation() {
    raidManager::fileLocation = "RAIDStorage/Disk" + to_string(disk) + "/data.txt";
}

void raidManager::setDisk() {
    raidManager::disk += 1;
    if (raidManager::disk > 4) {
        raidManager::disk = 1;
    }
}

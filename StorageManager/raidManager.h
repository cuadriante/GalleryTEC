#ifndef GALLERYTEC_RAIDMANAGER_H
#define GALLERYTEC_RAIDMANAGER_H

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

class raidManager {
public:
    raidManager();

    void write(string data);
    string read();

private:
    string fileLocation;
    bool isParity;
    int disk = 5;

    void setFileLocation();
    void setDisk();

};


#endif

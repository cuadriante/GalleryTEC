#ifndef GALLERYTEC_RAIDMANAGER_H
#define GALLERYTEC_RAIDMANAGER_H

#include <iostream>
//#include <stdlib.h>
//#include <string.h>
//#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
namespace pt = boost::property_tree;

class raidManager {
public:
    raidManager();

    void write(string data);
    void read(string imgID);

    void setImageId(const string &imageId);

private:
    string fileLocation, completeCode, tempCode, imageID;
    bool isParity;
    int disk = 6;
    int codeIndex = 1;
    pt::ptree root, dictionary;

    void setFileLocation();
    void setDisk();
    void deleteExtraBit(string code);

};


#endif

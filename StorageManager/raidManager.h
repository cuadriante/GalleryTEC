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

    void write(string data, string newImgID);
    void read(string imgID);

private:
    string fileLocation, completeCode, tempCode, imageID;
    string code1 = "";
    string code2 = "";
    string code3 = "";
    string code4 = "";
    string code5 = "";
    bool isParity;
    int disk = 6;
    int codeIndex = 1;
    int parityBlock = 1;
    pt::ptree root, dictionary, newImage, code_1, code_2, code_3, code_4, code_5, parity;
    pt::ptree length1, length2, length3, length4, length5, lengthTree;

    void setFileLocation();
    void setDisk();
    void deleteExtraBit(string code);
    void setImageId(const string &imageId);
    void setIsParity(bool isParity);
    void codeSplitter();
    void setCompleteCode(const string &completeCode);
    void setLenght();
    void changeParity();
};


#endif

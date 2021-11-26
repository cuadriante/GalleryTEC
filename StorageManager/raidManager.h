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
    void addNewImage(string data, string newImgID);
    void getDictionary(pt::ptree &dictionary, string imgID);
    string getCode(string imgID);
    int setNextID();
//    void checkForRecover(string imgID);

private:
    string fileLocation, completeCode, tempCode, imageID;
    string code1 = "";
    string code2 = "";
    string code3 = "";
    string code4 = "";
    string code5 = "";
    int disk = 6;
    int parityBlock = 1;
    bool isParity = false;
    pt::ptree root, dictionary, newImage, code_1, code_2, code_3, code_4, code_5, parity;
    pt::ptree length1, length2, length3, length4, length5, lengthTree;

    void write(string data, string newImgID);
    void applyXOR();
    string xorAlgorithm(string firstCode, string secondCode);
    void checkForRecover(string imgID);
    void recoverDisk(int diskToCheck);
    void recoverySave(int diskToCheck);
    void deleteExtraBit(string code);
    void codeSplitter();
    void setFileLocation();
    void setDisk();
    void setImageId(const string &imageId);
    void setCompleteCode(const string &completeCode);
    void setLength();
};


#endif

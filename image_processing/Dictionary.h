//
// Created by eduardo on 24/11/21.
//

#ifndef GALLERYTEC_DICTIONARY_H
#define GALLERYTEC_DICTIONARY_H

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "opencv2/opencv.hpp"
#include "../data_structures/TreeNode.h"

using namespace cv;
using namespace std;
using namespace boost::property_tree;

class Dictionary {
private:
    ptree root;
    vector<pair<Vec3b, string>> elements;
    static int id1;
    int id;
public:
    void addElement(Vec3b pixel, string code);
    void generateJSON(string filename, vector<pair<Vec3b, string>> list);
    vector<TreeNode> readJSON(string filename, string image);
};


#endif //GALLERYTEC_DICTIONARY_H

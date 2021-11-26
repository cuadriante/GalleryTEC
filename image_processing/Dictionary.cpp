//
// Created by eduardo on 24/11/21.
//

#include "Dictionary.h"

ptree Dictionary::getRoot() {
    return this->root;
}
vector<pair<Vec3b, string>> Dictionary::getElements() {
    return this->elements;
}


void Dictionary::addElement(Vec3b pixel, string code) {
    this->elements.push_back(make_pair(pixel, code));
}

ptree Dictionary::generateJSON() {
    ptree pixels_node;
    ptree color_node;
    ptree code_node;
    for (pair<Vec3b, string> p : this->elements) {
        ptree pixel_node;
        color_node.put_value(p.first);
        code_node.put_value(p.second);
        pixel_node.push_back(make_pair("color", color_node));
        pixel_node.add_child("code", code_node);
        pixels_node.push_back(make_pair("pixel", pixel_node));
    }
    this->root.add_child("pixels", pixels_node);
    return this->root;
}

vector<TreeNode> Dictionary::readJSON(string coding, ptree dictionary) {
    int begin = 0;
    int end = 0;
    vector<TreeNode> pixels;
    while (end <= coding.size()) {
        for (ptree::value_type pixel : dictionary.get_child("pixels")) {
            string substring = coding.substr(begin,end);
            if (pixel.second.get_child("code").data() == substring) {
                string color = pixel.second.get_child("color").data();
                TreeNode node;
                pixels.push_back(node);
                begin = end;
                end = 0;
            }
        }
        end++;
    }
    return pixels;
}
//
// Created by eduardo on 24/11/21.
//

#include "Dictionary.h"

vector<pair<Vec3b, string>> Dictionary::getElements() {
    return this->elements;
}


void Dictionary::addElement(Vec3b pixel, string code) {
    this->elements.push_back(make_pair(pixel, code));
}

void Dictionary::generateJSON(string filename) {
    ptree pixels_node;
    ptree color_node;
    ptree code_node;
    for (pair<Vec3b, string> p : this->elements) {
        ptree pixel_node;
        color_node.put_value(p.first);
        code_node.put_value(p.second);
        pixel_node.add_child("color", color_node);
        pixel_node.add_child("code", code_node);
        pixels_node.push_back(make_pair("pixel", pixel_node));
    }
    this->root.add_child("pixels", pixels_node);
    json_parser::write_json(filename, this->root);
}

vector<TreeNode> Dictionary::readJSON(string filename, string image) {
    /*int begin = 0;
    int end = 0;
    vector<TreeNode> pixels;
    for (ptree::value_type pixel : this->root.get_child("pixels")) {
        while (end < image.size()) {
            string substring = image.substr(begin,end);
            if (pixel.second.get_child("code").data() == substring) {
                Vec3b color = pixel.second.get_child("color").get<Vec3b>();
                TreeNode node;
                node.setData(color);
                pixels.push_back(node);
                begin = end;
            }
            end++;
        }
    }
    return pixels;*/
}
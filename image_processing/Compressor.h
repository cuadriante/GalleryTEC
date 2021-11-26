//
// Created by eduardo on 15/11/21.
//

#ifndef GALLERYTEC_COMPRESSOR_H
#define GALLERYTEC_COMPRESSOR_H

#include "../data_structures/HuffmanBinaryTree.h"
#include "Dictionary.h"

using namespace std;

class Compressor {
private:
    vector<TreeNode> nodes;
    string imageCode;
    HuffmanBinaryTree* tree;
    Dictionary* dictionary;
    int size;
    void buildTree();
    void createDictionary();
public:
    Compressor(vector<TreeNode> pixels);
    pair<string,ptree> compress();
    vector<TreeNode> decompress(string coding);
    static vector<TreeNode> bubble_sort(vector<TreeNode> pixels);
};


#endif //GALLERYTEC_COMPRESSOR_H

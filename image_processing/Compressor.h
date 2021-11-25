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
    HuffmanBinaryTree* tree;
    int size;
    void buildTree();
    Dictionary createDictionary();
public:
    Compressor(vector<TreeNode> pixels);
    ~Compressor();
    void compress();
    void decompress();
    static vector<TreeNode> bubble_sort(vector<TreeNode> pixels);
};


#endif //GALLERYTEC_COMPRESSOR_H

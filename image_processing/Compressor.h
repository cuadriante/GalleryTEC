//
// Created by eduardo on 15/11/21.
//

#ifndef GALLERYTEC_COMPRESSOR_H
#define GALLERYTEC_COMPRESSOR_H

#include "../data_structures/HuffmanBinaryTree.h"

using namespace std;

class Compressor {
private:
    vector<Vec3b> orderedList;
    HuffmanBinaryTree tree;
    bool compressed;
public:
    Compressor();
    void compress();
    void decompress();
    void bubble_sort();
    bool isCompressed();
};


#endif //GALLERYTEC_COMPRESSOR_H

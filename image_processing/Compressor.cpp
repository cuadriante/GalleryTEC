//
// Created by eduardo on 15/11/21.
//

#include "Compressor.h"

Compressor::Compressor(vector<TreeNode> pixels) {
    this->orderedList = this->bubble_sort(pixels);
    this->compressed = false;
    this->tree = new HuffmanBinaryTree(this->orderedList);
}

Compressor::~Compressor() {
    delete this->tree;
}

void Compressor::compress() {

}

void Compressor::decompress() {

}

vector<TreeNode> Compressor::bubble_sort(vector<TreeNode> list) {
    int count = int (list.size());
    while (count > 0) {
        for (int i = 0; i < count; i++) {
            if (list[i].getFrequency() > list[i+1].getFrequency()) {
                TreeNode temp = list[i];
                list[i] = list[i+1];
                list[i+1] = temp;
            }
        }
        count--;
    }
    return list;
}

bool Compressor::isCompressed() const {
    return this->compressed;
}
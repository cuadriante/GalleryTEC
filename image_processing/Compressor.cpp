//
// Created by eduardo on 15/11/21.
//

#include "Compressor.h"

Compressor::Compressor(vector<TreeNode> pixels) {
    this->nodes = pixels;
    this->tree = new HuffmanBinaryTree(this->nodes);
}

Compressor::~Compressor() {
    delete this->tree;
}

void Compressor::compress() {
    TreeNode parent;
    int c = 10;
    while (c > 1 || this->tree->getSize() > 0) {
        this->tree->setRoots(Compressor::bubble_sort(this->tree->getRoot()));
        for (TreeNode n : this->tree->getRoot()) {
            cout << n.getFrequency();
            cout << ", ";
        }
        cout << endl;
        for (TreeNode n : this->tree->getRoot()) {
            cout << "Parent: ";
            cout << n.getFrequency() << endl;
            if (n.getLeftChild() != nullptr) {
                cout << "Left: ";
                cout << n.getLeftChild()->getFrequency();
                cout << ", ";
            }
            if (n.getRightChild() != nullptr) {
                cout << "Right: ";
                cout << n.getRightChild()->getFrequency();
            }
            else {
                cout << "No children";
            }
            cout << endl;
        }
        parent.setFrequency(this->tree->getRoot()[0].getFrequency() + this->tree->getRoot()[1].getFrequency());
        parent.setLeftChild(&this->tree->getRoot()[0]);
        parent.setRightChild(&this->tree->getRoot()[1]);
        this->tree->updateTreeRoots(parent);
        c--;
    }
}

void Compressor::decompress() {

}

vector<TreeNode> Compressor::bubble_sort(vector<TreeNode> list) {
    int count = int (list.size());
    while (count > 0) {
        for (int i = 0; i < count - 1; i++) {
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
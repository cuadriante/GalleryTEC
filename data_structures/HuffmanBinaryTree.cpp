//
// Created by eduardo on 15/11/21.
//

#include "HuffmanBinaryTree.h"

HuffmanBinaryTree::HuffmanBinaryTree(vector<TreeNode> nodes) {
    this->roots = nodes;
    this->size = int (this->roots.size());
}

void HuffmanBinaryTree::setRoots(vector<TreeNode> nodes) {
    this->roots = nodes;
}

vector<TreeNode> HuffmanBinaryTree::getRoot() {
    return this->roots;
}

void HuffmanBinaryTree::updateTreeRoots(TreeNode parent) {
    this->roots.push_back(parent);
    this->roots.erase(this->roots.begin(), this->roots.begin() + 2);
    this->size = this->size - 2;
}

int HuffmanBinaryTree::getSize() {
    return this->size;
}
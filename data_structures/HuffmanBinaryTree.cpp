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

TreeNode HuffmanBinaryTree::getRoot() {
    if (this->size == 1) {
        return this->roots[0];
    }
}

vector<TreeNode> HuffmanBinaryTree::getRoots() {
    return this->roots;
}

void HuffmanBinaryTree::updateTreeRoots(TreeNode parent) {
    this->roots.push_back(parent);
    this->roots.erase(this->roots.begin(), this->roots.begin() + 2);
    this->size--;
}

int HuffmanBinaryTree::getSize() {
    return this->size;
}
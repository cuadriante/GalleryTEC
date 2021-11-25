//
// Created by eduardo on 15/11/21.
//

#include "TreeNode.h"

TreeNode::TreeNode() {
    this->data = Vec3b(0,0,0);
    this->frequency = 0;
    this->rightChild = nullptr;
    this->leftChild = nullptr;
}

TreeNode::TreeNode(Vec3b data1, int freq) {
    this->data = data1;
    this->frequency = freq;
    this->rightChild = nullptr;
    this->leftChild = nullptr;
}

Vec3b TreeNode::getData() {
    return this->data;
}

void TreeNode::setFrequency(int freq) {
    this->frequency = freq;
}

int TreeNode::getFrequency() {
    return this->frequency;
}

void TreeNode::setRightChild(TreeNode* right) {
    this->rightChild = right;
}

void TreeNode::setLeftChild(TreeNode* left) {
    this->leftChild = left;
}

TreeNode* TreeNode::getLeftChild() {
    return leftChild;
}

TreeNode* TreeNode::getRightChild() {
    return rightChild;
}
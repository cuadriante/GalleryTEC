//
// Created by eduardo on 15/11/21.
//

#include "TreeNode.h"

TreeNode::TreeNode() {
    this->data = Vec3b(0,0,0);
    this->frequency = 0;
    this->rightChild = nullptr;
    this->leftChild = nullptr;
    this->visited = false;
}

TreeNode::TreeNode(Vec3b data1, int freq) {
    this->data = data1;
    this->frequency = freq;
    this->parent = nullptr,
    this->rightChild = nullptr;
    this->leftChild = nullptr;
    this->visited = false;
}

void TreeNode::setData(Vec3b color) {
    this->data = color;
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

void TreeNode::visit() {
    this->visited = true;
}

bool TreeNode::isVisited() {
    return this->visited;
}
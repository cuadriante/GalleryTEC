//
// Created by eduardo on 15/11/21.
//

#include "TreeNode.h"

int TreeNode::currentId = 0;

TreeNode::TreeNode(Vec3b data1) {
    this->data = data1;
    this->id = TreeNode::currentId++;
}

Vec3b TreeNode::getData() {
    return this->data;
}

int TreeNode::getID() {
    return this->id;
}

TreeNode *TreeNode::getLeftChild() {
    return this->leftChild;
}

TreeNode *TreeNode::getRightChild() {
    return this->rightChild;
}
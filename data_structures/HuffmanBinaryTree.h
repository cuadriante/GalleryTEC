//
// Created by eduardo on 15/11/21.
//

#ifndef GALLERYTEC_HUFFMANBINARYTREE_H
#define GALLERYTEC_HUFFMANBINARYTREE_H

#include "TreeNode.h"

using namespace std;

class HuffmanBinaryTree {
private:
    vector<TreeNode> roots;
    int size;
public:
    HuffmanBinaryTree(vector<TreeNode> nodes);
    void setRoots(vector<TreeNode> nodes);
    vector<TreeNode> getRoot();
    void updateTreeRoots(TreeNode parent);
    int getSize();
};


#endif //GALLERYTEC_HUFFMANBINARYTREE_H

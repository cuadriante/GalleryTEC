//
// Created by eduardo on 15/11/21.
//

#ifndef GALLERYTEC_HUFFMANBINARYTREE_H
#define GALLERYTEC_HUFFMANBINARYTREE_H

#include "TreeNode.h"

class HuffmanBinaryTree {
private:
    std::vector<TreeNode> root;
    int size;
public:
    HuffmanBinaryTree(std::vector<TreeNode> list);
    void insert(Vec3b pix);
    void erase(int id);
    Vec3b get(int id);
};


#endif //GALLERYTEC_HUFFMANBINARYTREE_H

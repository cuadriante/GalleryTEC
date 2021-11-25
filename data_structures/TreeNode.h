//
// Created by eduardo on 15/11/21.
//

#ifndef GALLERYTEC_TREENODE_H
#define GALLERYTEC_TREENODE_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

class TreeNode {
private:
    Vec3b data;
    TreeNode *rightChild, *leftChild;
    int frequency;
public:
    TreeNode();
    TreeNode(Vec3b data1, int freq);
    void setData(Vec3b data1);
    Vec3b getData();
    void setFrequency(int freq);
    int getFrequency();
    void setRightChild(TreeNode* right);
    void setLeftChild(TreeNode* left);
    TreeNode* getRightChild();
    TreeNode* getLeftChild();
};


#endif //GALLERYTEC_TREENODE_H

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
    static int currentId;
    int id;
    TreeNode* rightChild;
    TreeNode* leftChild;
    int frequency;
public:
    TreeNode(Vec3b data1, int freq);
    Vec3b getData();
    int getID();
    int getFrequency();
    TreeNode* getRightChild();
    TreeNode* getLeftChild();
};


#endif //GALLERYTEC_TREENODE_H

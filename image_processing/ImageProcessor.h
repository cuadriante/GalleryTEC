//
// Created by eduardo on 15/11/21.
//

#ifndef GALLERYTEC_IMAGEPROCESSOR_H
#define GALLERYTEC_IMAGEPROCESSOR_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "../data_structures/TreeNode.h"

using namespace cv;
using namespace std;

class ImageProcessor {
private:
    Mat* image;
    int height, width;
    vector<Vec3b> allColors;
    vector<Vec3b> unrepeatedColors;
    vector<TreeNode> pixels;
    vector<TreeNode> frequencyCounter();
public:
    ImageProcessor(const string& imgUrl);
    ~ImageProcessor();
    vector<TreeNode> pixelReader();
    void constructImg(vector<TreeNode> vec);
};


#endif //GALLERYTEC_IMAGEPROCESSOR_H

//
// Created by eduardo on 15/11/21.
//

#ifndef GALLERYTEC_IMAGEPROCESSOR_H
#define GALLERYTEC_IMAGEPROCESSOR_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "Pixel.h"

using namespace cv;
using namespace std;

class ImageProcessor {
private:
    Mat* image;
    vector<Vec3b> pixels;
    vector<Pixel> unrepeatedPixels;
public:
    ImageProcessor(const string& imgUrl);
    ~ImageProcessor();
    void pixelReader();
    void unrepeatedReader();
};


#endif //GALLERYTEC_IMAGEPROCESSOR_H

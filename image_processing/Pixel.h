//
// Created by eduardo on 20/11/21.
//

#ifndef GALLERYTEC_PIXEL_H
#define GALLERYTEC_PIXEL_H

#include "opencv2/opencv.hpp"

using namespace cv;

class Pixel {
private:
    int probability;
    Vec3b color;
public:
    Pixel(Vec3b color, int prob);
    int getProbability() const;
    void setProbability(int prob);
    Vec3b getColor();
    void setColor(Vec3b color1);
};


#endif //GALLERYTEC_PIXEL_H

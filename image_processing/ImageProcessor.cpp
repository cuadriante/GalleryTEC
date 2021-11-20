//
// Created by eduardo on 15/11/21.
//

#include "ImageProcessor.h"

ImageProcessor::ImageProcessor(const string& imgUrl) {
    this->image = new Mat();
    *image = imread(imgUrl);
    imshow("Try", *image);
}

ImageProcessor::~ImageProcessor() {
    delete this->image;
}

void ImageProcessor::pixelReader() {
    int i = 0;
    Pixel pix;
    Vec3b color;
    cout << "All pixels:" << endl;
    for (int r = 0; r < this->image->rows; r++) {
        for (int c = 0; c < this->image->cols; c++) {
            color = this->image->at<Vec3b>(Point(c,r));
            if (find(this->pixels.begin(), this->pixels.end(), color) == this->pixels.end()) {
                this->pixels.push_back(color);
            }
        }
        cout << pixels[i] << endl;
        i++;
    }
}
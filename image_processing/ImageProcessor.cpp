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
    //int i = 0;
    Vec3b color;
    //cout << "All pixels:" << endl;
    for (int r = 0; r < this->image->rows; r++) {
        for (int c = 0; c < this->image->cols; c++) {
            color = this->image->at<Vec3b>(Point(c,r));
            this->allColors.push_back(color);
            if (find(this->pixels.begin(), this->pixels.end(), color) == this->pixels.end()) {
                this->pixels.push_back(color);
            }
        }
        //cout << pixels[i] << endl;
        //i++;
    }
}

void ImageProcessor::frequencyCounter() {
    int counter = 0;
    if (!this->pixels.empty() && !this->allColors.empty()) {
        for (Vec3b color : pixels) {
            for (Vec3b repeated : allColors) {
                if (repeated[0] == color[0] && repeated[1] == color[1] && repeated[2] == color[2]) {
                    counter++;
                }
            }
            Pixel pixel(color, counter);
            this->unrepeatedPixels.push_back(pixel);
            cout << "Color: ";
            cout << pixel.getColor();
            cout << " Se repite: " + to_string(counter) << endl;
            counter = 0;
        }
    }
    else {
        cout << "There are no pixels read yet" << endl;
    }
}
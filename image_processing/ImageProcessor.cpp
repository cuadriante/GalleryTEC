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

vector<TreeNode> ImageProcessor::pixelReader() {
    //int i = 0;
    Vec3b color;
    //cout << "All pixels:" << endl;
    for (int r = 0; r < this->image->rows; r++) {
        for (int c = 0; c < this->image->cols; c++) {
            color = this->image->at<Vec3b>(Point(c,r));
            this->allColors.push_back(color);
            if (find(this->unrepeatedColors.begin(), this->unrepeatedColors.end(), color) == this->unrepeatedColors.end()) {
                this->unrepeatedColors.push_back(color);
            }
        }
        //cout << pixels[i] << endl;
        //i++;
    }
    return this->frequencyCounter();
}

vector<TreeNode> ImageProcessor::frequencyCounter() {
    int counter = 0;
    if (!this->unrepeatedColors.empty() && !this->allColors.empty()) {
        for (Vec3b color : unrepeatedColors) {
            for (Vec3b repeated : allColors) {
                if (repeated[0] == color[0] && repeated[1] == color[1] && repeated[2] == color[2]) {
                    counter++;
                }
            }
            TreeNode pixel(color, counter);
            this->pixels.push_back(pixel);
            //cout << "Color: ";
            //cout << pixel.getData();
            //cout << " Se repite: " + to_string(counter) << endl;
            counter = 0;
        }
        return this->pixels;
    }
    else {
        cout << "There are no pixels read yet" << endl;
    }
}
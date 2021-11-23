#include <iostream>
#include "image_processing/ImageProcessor.h"
#include "opencv2/opencv.hpp"
#include "image_processing/Compressor.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    /*Mat image = imread("/home/eduardo/Documentos/GitHub/GalleryTEC/cupcake.png");
    Vec3b color;
    for (int r = 0; r < image.rows; r++) {
        for (int c = 0; c < image.cols; c++) {
            color = image.at<Vec3b>(Point(c,r));
            if (color[0] == 202 && color[1] == 166 && color[2] == 241) {
                image.at<Vec3b>(Point(c,r))[0] = 0;
                image.at<Vec3b>(Point(c,r))[1] = 0;
                image.at<Vec3b>(Point(c,r))[2] = 0;
            }
        }
    }
    imshow("Hello", image);
    waitKey();*/
    ImageProcessor img("/home/eduardo/Documentos/GitHub/GalleryTEC/Captura de pantalla de 2021-11-11 21-49-33.png");

    vector<TreeNode> pixels = img.pixelReader();

    vector<TreeNode> ordered = Compressor::bubble_sort(pixels);
    cout << "In order:" << endl;
    for (TreeNode pix : ordered) {
        cout << "Color: ";
        cout << pix.getData();
        cout << ", Frequency: " + to_string(pix.getFrequency()) << endl;
    }
    return 0;
}

#include <iostream>
#include "image_processing/ImageProcessor.h"
#include "opencv2/opencv.hpp"
#include "image_processing/Compressor.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    vector<pair<Vec3b, string>> v;
    v.push_back(make_pair(Vec3b(0,0,0), "10001"));
    v.push_back(make_pair(Vec3b(0,5,6), "10000"));
    v.push_back(make_pair(Vec3b(12,234,165), "101"));
    v.push_back(make_pair(Vec3b(6,5,2), "1011"));
    v.push_back(make_pair(Vec3b(5,6,7), "10111"));

    Dictionary dict;
    dict.generateJSON("/home/eduardo/Documentos/GitHub/GalleryTEC/cupcake.json", v);
    return 0;
}

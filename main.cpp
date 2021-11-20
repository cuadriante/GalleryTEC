#include <iostream>
#include "image_processing/ImageProcessor.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    ImageProcessor* pros = new ImageProcessor("/home/eduardo/Documentos/GitHub/GalleryTEC/cupcake.png");
    pros->pixelReader();
    delete pros;
    return 0;
}

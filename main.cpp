#include <iostream>
#include "image_processing/ImageProcessor.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    ImageProcessor p("/home/eduardo/Documentos/GitHub/GalleryTEC/cupcake.png");
    p.pixelReader();
    p.frequencyCounter();
    return 0;
}

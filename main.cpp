#include <iostream>
#include "image_processing/ImageProcessor.h"
#include "opencv2/opencv.hpp"
#include "image_processing/Compressor.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    /*TreeNode t1(Vec3b(1,4,3), 23);
    TreeNode t2(Vec3b(22,5,43), 10);
    TreeNode t3(Vec3b(25,197,165), 65);
    TreeNode t4(Vec3b(12,76,54), 2);
    TreeNode t5(Vec3b(10,23,34), 34);

    vector<TreeNode> v;
    v.push_back(t1);
    v.push_back(t2);
    v.push_back(t3);
    v.push_back(t4);
    v.push_back(t5);*/

    Dictionary my_dick;
    my_dick.addElement(Vec3b(0,0,0), "10001");
    my_dick.addElement(Vec3b(9,4,3), "00101");
    my_dick.generateJSON("/home/eduardo/Documentos/GitHub/GalleryTEC/cupcake.json");
    return 0;
}

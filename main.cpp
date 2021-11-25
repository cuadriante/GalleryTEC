#include <iostream>
#include "image_processing/ImageProcessor.h"
#include "opencv2/opencv.hpp"
#include "image_processing/Compressor.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    TreeNode t1(Vec3b(1,2,2), 14);
    TreeNode t2(Vec3b(21,2,1), 46);
    TreeNode t3(Vec3b(21,2,1), 34);
    TreeNode t4(Vec3b(21,2,1), 4);
    TreeNode t5(Vec3b(21,2,1), 65);
    TreeNode t6(Vec3b(21,2,1), 62);
    TreeNode t7(Vec3b(21,2,1), 92);

    vector<TreeNode> p;

    p.push_back(t1);
    p.push_back(t2);
    p.push_back(t3);
    p.push_back(t4);
    p.push_back(t5);
    p.push_back(t6);
    p.push_back(t7);

    Compressor compressor(p);
    compressor.compress();
    return 0;
}

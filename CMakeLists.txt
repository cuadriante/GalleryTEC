cmake_minimum_required(VERSION 3.20)
project(GalleryTEC)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(GalleryTEC main.cpp image_processing/ImageProcessor.cpp image_processing/ImageProcessor.h data_structures/HuffmanBinaryTree.cpp data_structures/HuffmanBinaryTree.h image_processing/Compressor.cpp image_processing/Compressor.h data_structures/TreeNode.cpp data_structures/TreeNode.h)
target_link_libraries(GalleryTEC
        ${OpenCV_LIBS})
cmake_minimum_required(VERSION 3.20)
project(GalleryTEC)

set(CMAKE_CXX_STANDARD 14)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)


find_package(OpenCV REQUIRED)
find_package(Boost 1.45.0 COMPONENTS ptree json_parser)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(progname file1.cxx file2.cxx)
    target_link_libraries(progname ${Boost_LIBRARIES})
endif()

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(GalleryTEC main.cpp image_processing/ImageProcessor.cpp image_processing/ImageProcessor.h data_structures/HuffmanBinaryTree.cpp data_structures/HuffmanBinaryTree.h image_processing/Compressor.cpp image_processing/Compressor.h data_structures/TreeNode.cpp data_structures/TreeNode.h image_processing/Dictionary.cpp image_processing/Dictionary.h)
target_link_libraries(GalleryTEC
        ${OpenCV_LIBS})
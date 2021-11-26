cmake_minimum_required(VERSION 3.20)
project(GalleryTEC)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/qt5")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Boost 1.45.0 COMPONENTS ptree json_parser)

find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/lib")

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(progname file1.cxx file2.cxx)
    target_link_libraries(progname ${Boost_LIBRARIES})
endif()

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(GalleryTEC main.cpp image_processing/ImageProcessor.cpp image_processing/ImageProcessor.h data_structures/HuffmanBinaryTree.cpp data_structures/HuffmanBinaryTree.h image_processing/Compressor.cpp image_processing/Compressor.h data_structures/TreeNode.cpp data_structures/TreeNode.h image_processing/Dictionary.cpp image_processing/Dictionary.h DataBase/DataBaseHandler.cpp DataBase/DataBaseHandler.h Interface/Interface.cpp Interface/Interface.h StorageManager/raidManager.cpp StorageManager/raidManager.h)
target_link_libraries(GalleryTEC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        ${LIBMONGOCXX_LIBRARIES}
        ${LIBBSONCXX_LIBRARIES}
        ${OpenCV_LIBS})
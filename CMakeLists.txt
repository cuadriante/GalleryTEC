cmake_minimum_required(VERSION 3.20)
project(GalleryTEC)

find_package(Qt5Widgets REQUIRED)
set(Qt5_DIR "~/Qt/5.12.2/clang_64/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/lib")
include_directories($OpenCV_INCLUDE_DIRS)

add_executable(GalleryTEC main.cpp Interface/Interface.cpp Interface/Interface.h DataBase/DataBaseHandler.cpp DataBase/DataBaseHandler.h DataBase/DataBaseHandler.cpp DataBase/DataBaseHandler.h)
target_link_libraries(GalleryTEC Qt5::Core Qt5::Widgets)
target_link_libraries(GalleryTEC ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(GalleryTEC ${LIBBSONCXX_LIBRARIES})
target_link_libraries(GalleryTEC ${OpenCV_LIBS})





cmake_minimum_required(VERSION 3.20)
project(GalleryTEC)

find_package(Qt5Widgets REQUIRED)
# Tell cmake where Qt is located
set(Qt5_DIR "~/Qt/5.12.2/clang_64/lib/cmake/Qt5")
# Tell cmake to find the modules Qt5Core and Qt5widgets
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

include_directories(${MONGO_INCLUDE_DIRS})
include_directories(${MONGO_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.c)

add_executable(GalleryTEC main.cpp Interface/MainWindow.cpp Interface/MainWindow.h DataBase/Users.cpp DataBase/Users.h)
# Link the library to the executable
target_link_libraries(GalleryTEC ${MONGO_LIBRARIES} )
target_link_libraries(GalleryTEC Qt5::Core Qt5::Widgets)
#target_link_libraries(GalleryTEC ${MONGODB_LIBRARY} ${BSON_LIBRARY})


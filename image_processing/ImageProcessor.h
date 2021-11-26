/**
 * @file ImageProcessor.h
 * @version 1.0
 * @date 25 de noviembre de 2021
 * @author Eduardo Bolívar
 * @title Procesador de imágenes
 * @brief Procesa una imagen dada
 */

#ifndef GALLERYTEC_IMAGEPROCESSOR_H
#define GALLERYTEC_IMAGEPROCESSOR_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "../data_structures/TreeNode.h"
#include <QLabel>

using namespace cv;
using namespace std;

class ImageProcessor {
private:
    Mat* image;
    int height, width;
    vector<Vec3b> allColors;
    vector<Vec3b> unrepeatedColors;
    vector<TreeNode> pixels;
    vector<TreeNode> frequencyCounter();
public:

    /**
     * @brief Constructor
     * @param imgUrl Dirección de la imagen en la base de datos
     */
    ImageProcessor(const string& imgUrl);

    /**
     * @brief Contructor
     */
    ~ImageProcessor();

    /**
     * @brief Lector de pixeles
     * @return Un vector asociado al pixel
     */
    vector<TreeNode> pixelReader();

    /**
     * @brief Contructor de la imagen
     * @param pixels Pixeles de la imagen
     * @return La imagen
     */
    QLabel* constructImg(vector<TreeNode> pixels);
};


#endif //GALLERYTEC_IMAGEPROCESSOR_H

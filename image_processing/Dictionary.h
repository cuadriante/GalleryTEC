/**
 * @file Dictionary.h
 * @version 1.0
 * @date 25 de noviembre de 2021
 * @author Eduardo Bolívar
 * @title Diccionario
 * @brief Crea el diccionario asociado a la imagen
 */

#ifndef GALLERYTEC_DICTIONARY_H
#define GALLERYTEC_DICTIONARY_H

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "opencv2/opencv.hpp"
#include "../data_structures/TreeNode.h"

using namespace cv;
using namespace std;
using namespace boost::property_tree;

class Dictionary {
private:
    ptree root;
    vector<pair<Vec3b, string>> elements;
public:

    /**
     * @brief Getter
     * @return Obtiene la raíz de un árbol
     */
    ptree getRoot();

    /**
     * @brief Getter
     * @return Un vector de elementos
     */
    vector<pair<Vec3b,string>> getElements();

    /**
     * @brief Agrega elementos al vector
     * @param pixel Pixel de la imagen
     * @param code Código de compresión
     */
    void addElement(Vec3b pixel, string code);

    /**
     * @brief Generador de Json
     * @return Un nodo Ptree que contiene el diccionario
     */
    ptree generateJSON();

    /**
     * @brief Lector de Json
     * @param coding Código de compresión de la imagen
     * @param dictionary Diccionario asociado a la imagen
     * @return Vector
     */
    vector<TreeNode> readJSON(string coding, ptree dictionary);
};


#endif //GALLERYTEC_DICTIONARY_H

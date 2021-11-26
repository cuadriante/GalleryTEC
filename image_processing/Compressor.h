/**
 * @file Compressor.h
 * @version 1.0
 * @date 25 de noviembre de 2021
 * @author Eduardo Bolívar
 * @title Compresor
 * @brief Comprime imágenes
 */

#ifndef GALLERYTEC_COMPRESSOR_H
#define GALLERYTEC_COMPRESSOR_H

#include "../data_structures/HuffmanBinaryTree.h"
#include "Dictionary.h"

using namespace std;

class Compressor {
private:
    vector<TreeNode> nodes;
    string imageCode;
    HuffmanBinaryTree* tree;
    Dictionary* dictionary;
    int size;
    void buildTree();
    void createDictionary();
public:

    /**
     * @brief Constructor
     * @param pixels Pixeles de la imagen
     */
    Compressor(vector<TreeNode> pixels);

    /**
     * @brief Método de compresión
     * @return Un vector resultante de la compresión
     */
    pair<string,ptree> compress();

    /**
     * @brief Método de descompresión
     * @param coding Cadena binaria de compresión
     * @return Un vector para el árbol
     */
    vector<TreeNode> decompress(string coding);

    /**
     * @brief Algoritmo BubbleSort
     * @param pixels Pixeles de la imagen
     * @return El parámetro pero ordenado
     */
    static vector<TreeNode> bubble_sort(vector<TreeNode> pixels);
};


#endif //GALLERYTEC_COMPRESSOR_H

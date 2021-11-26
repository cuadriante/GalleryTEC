/**
 * @file TreeNode.h
 * @version 1.0
 * @date 25 de noviembre de 2021
 * @author Eduardo Bolívar
 * @title Nodo de árbol
 * @brief Define un nodo de un árbol
 */

#ifndef GALLERYTEC_TREENODE_H
#define GALLERYTEC_TREENODE_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

class TreeNode {
private:
    Vec3b data;
    TreeNode *rightChild, *leftChild;
    int frequency;
    bool visited;
public:

    /**
     * @brief Constructor
     */
    TreeNode();

    /**
     * @brief Constructor
     * @param data1 Vector de información
     * @param freq Frecuencia
     */
    TreeNode(Vec3b data1, int freq);

    /**
     * @brief Setter
     * @param color Color del pixel
     */
    void setData(Vec3b color);

    /**
     * @brief Getter
     * @return Vector de información
     */
    Vec3b getData();

    /**
     * @brief Setter
     * @param freq Frecuencia de aparición de un color
     */
    void setFrequency(int freq);

    /**
     * @brief Getter
     * @return Frecuencia con que aparece un color
     */
    int getFrequency();

    /**
     * @brief Setter
     * @param right Hijo derecho de un nodo
     */
    void setRightChild(TreeNode* right);

    /**
     * @brief Setter
     * @param left Hijo izquierdo de un nodo
     */
    void setLeftChild(TreeNode* left);

    /**
     * @brief Getter
     * @return Hijo derecho del nodo
     */
    TreeNode* getRightChild();

    /**
     * @brief Getter
     * @return Hijo izquierdo del nodo
     */
    TreeNode* getLeftChild();

    /**
     * @brief Determina si un nodo ha sido visitado
     */
    void visit();

    /**
     * @brief Indica si el nodo ha sido visitado
     * @return Respuesta binaria a la consulta
     */
    bool isVisited();
};


#endif //GALLERYTEC_TREENODE_H

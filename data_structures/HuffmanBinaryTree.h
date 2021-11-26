/**
 * @file HuffmanBinaryTree.h
 * @version 1.0
 * @date 25 de noviembre de 2021
 * @author Eduardo Bolívar
 * @title Árbol binario de Huffman
 * @brief Crea un árbol con el objeto compreso
 */

#ifndef GALLERYTEC_HUFFMANBINARYTREE_H
#define GALLERYTEC_HUFFMANBINARYTREE_H

#include "TreeNode.h"

using namespace std;

class HuffmanBinaryTree {
private:
    vector<TreeNode> roots;
    int size;
public:

    /**
     * @brief Constructor
     * @param nodes Nodos del árbol
     */
    HuffmanBinaryTree(vector<TreeNode> nodes);

    /**
     * @brief Setter
     * @param nodes Nodos del árbol
     */
    void setRoots(vector<TreeNode> nodes);

    /**
     * @brief Getter
     * @return Nodo padre del árbol
     */
    TreeNode getRoot();

    /**
     * @brief Getter
     * @return Nodos padre de un segmento del árbol
     */
    vector<TreeNode> getRoots();

    /**
     * @brief Actualiza los nodos padre del árbol
     * @param parent Nodo padre
     */
    void updateTreeRoots(TreeNode parent);

    /**
     * @brief Getter
     * @return Tamaño del árbol
     */
    int getSize();
};


#endif //GALLERYTEC_HUFFMANBINARYTREE_H

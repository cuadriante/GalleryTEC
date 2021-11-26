/**
 * @file raidManager.h
 * @version 1.0
 * @date 25 de noviembre de 2021
 * @author Gregory Alpízar
 * @title Administrador de sistema RAID 5
 * @brief Sistema de manejo de almacenamiento y recuperación de datos en RAID 5
 */

#ifndef GALLERYTEC_RAIDMANAGER_H
#define GALLERYTEC_RAIDMANAGER_H

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
namespace pt = boost::property_tree;

class raidManager {
public:

    /**
     * @brief Constructor
     */
    raidManager();

    /**
     * @brief Agregar una nueva imagen (no existente) al sistema de almacenamiento
     * @param data Código binario de la imagen
     * @param newImgID Identificador único de la imagen
     */
    void addNewImage(string data, string newImgID);

    /**
     * @brief Accede al diccionario correspondiente a la imagen
     * @param dictionary Puntero del diccionario donde se va a almacenar la información en formato Json
     * @param imgID Identificador de la imagen que se desea descomprimir
     */
    void getDictionary(pt::ptree &dictionary, string imgID);

    /**
     * @brief Accede a la cadena binaria de compresión de la imagen
     * @param imgID Identificar de la imagen que se desea descomprimir
     * @return Cadena completa de bits para la imagen especificada
     */
    string getCode(string imgID);

    /**
     * @brief Establece el identificador que debe asociarse a la siguiente imagen para el almacenamiento de datos
     * @return El identificar de la siguiente imagen que se guarde en el sistema
     */
    int setNextID();
//    void checkForRecover(string imgID);

private:
    string fileLocation, completeCode, tempCode, imageID;
    string code1 = "";
    string code2 = "";
    string code3 = "";
    string code4 = "";
    string code5 = "";
    int disk = 6;
    int parityBlock = 1;
    bool isParity = false;
    pt::ptree root, dictionary, newImage, code_1, code_2, code_3, code_4, code_5, parity;
    pt::ptree length1, length2, length3, length4, length5, lengthTree;

    void write(string data, string newImgID);
    void applyXOR();
    string xorAlgorithm(string firstCode, string secondCode);
    void checkForRecover(string imgID);
    void recoverDisk(int diskToCheck);
    void recoverySave(int diskToCheck);
    void deleteExtraBit(string code);
    void codeSplitter();
    void setFileLocation();
    void setDisk();
    void setImageId(const string &imageId);
    void setCompleteCode(const string &completeCode);
    void setLength();
};


#endif

/**
 * @file DataBaseHandler.h
 * @version 1.0
 * @date 25 de noviembre de 2021
 * @author Adriana Calderón
 * @title Manipulador de la base de datos
 * @brief Manejo de usuarios, galerías, imágenes y METADATA de imágenes
 */

#ifndef GALLERYTEC_DATABASEHANDLER_H
#define GALLERYTEC_DATABASEHANDLER_H



#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/client_session.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

using namespace std;
using namespace mongocxx;
using namespace bsoncxx::builder::basic;
using namespace bsoncxx::builder::stream;


class DataBaseHandler {
private:
    database db;
    client conn;
    string currentUser;
    vector<string> galleriesVector;
public:

    /**
     * @brief Constructor
     */
    DataBaseHandler();

    /**
     * @brief Agrega el nuevo usuario a la base de datos
     * @param username Nombre del usuario
     * @param password Contraseña asociada al nombre de usuario
     * @return Respuesta binaria de éxito en el almacenamiento de los datos del usuario
     */
    bool addUserToDb(const std::string &username, const std::string &password);

    /**
     * @brief Busca si el usuario consultado se encuentra registrado en el sistema
     * @param username Nombre de usuario
     * @param password COntraseña asociada al nombre de usuario
     * @return Respuesta binaria sobre el resultado de la búsqueda
     */
    bool checkForUserInDb(const std::string &username, const std::string &password);

    /**
     * @brief Agrega una nueva galería para un usuario existente
     * @param galleryName Nombre de la galería
     * @return Respuesta binaria sobre el éxito en el almacenamiento de la galería
     */
    bool addGalleryToUserDb(const std::string &galleryName);

    /**
     * @brief Elimina una galería existente
     * @param galleryName Nombre de la galería a eliminar
     * @param deleteImages Indica si se desean eliminar las imágenes dentro de la galería
     * @return Respuesta binaria sobre el éxito en la eliminación
     */
    bool deleteGalleryFromUserDb(const string &galleryName, bool deleteImages);

    /**
     * @brief Agrega una nueva imagen a la galería existente
     * @param imageName Nombre de la nueva imagen
     * @param galleryName Nombre de la galería en la que se desea almacenar la imagen
     * @return Respuesta binaria sobre el éxito en el almacenamiento de la imagen
     */
    bool addImageToUserGalleryDb(const string &imageName, const string &galleryName);

    /**
     * @brief Elimina una imagen de una galería específica
     * @param imageName Nombre de la imagen a eliminar
     * @param galleryName Galería en la que se encuentra la imagen
     * @return Respuesta binaria sobre el éxito en la eliminación de la imagen
     */
    bool deleteImageFromUserGalleryDb(const string &imageName, const string &galleryName);

    /**
     * @brief Elimina todas las imágenes de una galería
     * @param galleryName Nombre de la galería que almacena las imágenes
     * @return Respuesta binaria sobre el éxito en la eliminación de las imágenes
     */
    bool deleteAllImagesFromUserGalleryDb(const string &galleryName);

    /**
     * @brief Edita las características de una galería
     * @param galleryName Nombre de la galería a editar
     * @param newGalleryName Nuevo nombre que se le desea asignar a la galería
     * @return Respuesta binaria sobre el éxito en la modificación del nombre
     */
    bool editGalleryFromUserDb(const string &galleryName, const string &newGalleryName);

    /**
     * @brief Asigna el valor del parámetro a la variable currentUser
     * @param currentUser Nuevo valor de la variable
     */
    void setCurrentUser(const string &currentUser);

    /**
     * @brief Recopila los nombres de todas las galerías correspondientes a un usuario
     * @return Un vector con los nombres de todas galerías del usuario
     */
    vector<string> retrieveAllUserGalleries();

    /**
     * @brief Recopila todas las imágenes correspondientes a una galería
     * @param gallery Nombre de la galería a analizar
     * @return Un vector con los nombres de todas las imágenes existentes en la galería
     */
    vector<string> retrieveAllImagesFromUserGallery(string gallery);

    /**
     * @brief Verifica si la imagen existe en la galería
     * @param imageName Nombre de la imagen a buscar
     * @param galleryName Nombre de la galería en análisis
     * @return Respuesta binaria sobre la existencia de la imagen
     */
    bool checkForImageInUserGallery(const string &imageName, const string &galleryName);

    /**
     * @brief Modifica la METADATA de una imagen
     * @param imageName Nombre de la imagen a modificar
     * @param galleryName Galería en la que se encuentra la imagen
     * @param parameter Atributo a modificar en la metadata
     * @param newValue Nuevo valor del atributo a modificar
     * @return Respuesta binaria sobre el éxito en la edición de la información
     */
    bool
    editImageMetadata(const string &imageName, const string &galleryName, const string &parameter,
                      const string &newValue);

    /**
     * @brief Recopila la METADATA de una imagen
     * @param imageName Nombre de la imagen a analizar
     * @param galleryName Nombre de la galería donde se encuentra la imagen
     * @return Un vector con todos los atributos de la imagen
     */
    vector<string> retrieveImageMetadata(const string &imageName, const string &galleryName);


};




#endif //GALLERYTEC_DATABASEHANDLER_H

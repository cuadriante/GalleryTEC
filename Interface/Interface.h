/**
 * @file Interface.h
 * @version 1.0
 * @date 25 de noviembre de 2021
 * @author Adriana Calderón
 * @title Interfaz
 * @brief Interfaz de la aplicación
 */

//#ifndef GALLERYTEC_INTERFACE_H
//#define GALLERYTEC_INTERFACE_H

//#include <QGraphicsView>
//#include <QGraphicsScene>
//#include <QtWidgets>
//#include <QGraphicsItem>
//#include <QGraphicsRectItem>
//#include <QTimer>
//#include <QBrush>
//#include <QDebug>
//#include <QKeyEvent>
//#include <QApplication>
#include <unistd.h>
#include <iostream>
#include "../DataBase/DataBaseHandler.h"
#include "../StorageManager/RaidManager.h"
#include "../image_processing/Compressor.h"
#include "../image_processing/ImageProcessor.h"

using namespace std;

class Interface: public QGraphicsView {
Q_OBJECT

private:

    DataBaseHandler * dbHandler;
    RaidManager * raidManager;
    int imageId;
    ImageProcessor * imgProcessor;
    Compressor * compressor;

    const QString BG_GALLERY_TEC = "../Resources/galleryTEC.png";
    const QString BG_GALLERIES = "../Resources/galleries.png";
    const QString BG_BACKGROUND = "../Resources/background.png";
    const QString BG_IMAGE = "../Resources/image.png";
    const QString BG_METADATA = "../Resources/metadata.png";

    const int MENU = 0;
    const int LOGIN = 1;
    const int SIGNUP = 1;
    const int GALLERY_MENU = 1;
    const int GALLERY_MANAGEMENT = 3;
    const int IMAGE_MENU = 3;
    const int IMAGE_METADATA = 4;
    int currentWindow = MENU;
    int currentImageIndex = 0;

    QImage * bgImage;
    QGraphicsPixmapItem * pixmap;

    QPushButton * logInButton;
    QPushButton * signUpButton;
    QPushButton * backButton;
    QPushButton * verifyUserButton;
    QPushButton * createUserButton;
    QPushButton * addGalleryButton;
    QPushButton * editGalleryButton;
    QPushButton * editGalleryNameButton;
    QPushButton * addImageButton;
    QPushButton * deleteImageButton;
    QPushButton * deleteGalleryButton;
    QPushButton * previousImageButton;
    QPushButton * imageMetaDataButton;
    QPushButton * nextImageButton;
    QPushButton * imageNameButton;
    QPushButton * imageAuthorButton;
    QPushButton * imageSizeButton;
    QPushButton * imageYearButton;
    QPushButton * imageDescriptionButton;
    QPushButton * confirmAddGalleryButton;
    QPushButton * selectPicButton;

    bool createdLogInWindow = false;
    bool askedForUsernameAndPassword = false;
    bool userCreated = true;
    bool successfulVerification = true;
    bool successfulCreation = true;
    bool displayedGalleries = false;
    bool displayedImage = false;
    bool displayedMetadata = false;
    bool hasAddedGallery = false;
    bool successfulGalleryManagement = false;
    bool hasEdited = false;
    bool createdImageVector = false;

    QLineEdit * usernameTextInput;
    QLineEdit * passwordTextInput;
    QLineEdit * imageNameInput;
    QLineEdit * imageAuthorInput;
    QLineEdit * imageSizeInput;
    QLineEdit * imageYearInput;
    QLineEdit * imageDescriptionInput;
    QLineEdit * newGalleryInput;

    QLabel * noticeLabel;
    QLabel * currentGalleryLabel;
    QLabel * currentImageLabel;
    QLabel * imageNameLabel;
    QLabel * imageAuthorLabel;
    QLabel * imageSizeLabel;
    QLabel * imageYearLabel;
    QLabel * imageDescriptionLabel;
    QLabel * imagePictureLabel;

    QString currentGallery = "New Gallery";
    QString currentImageName = "Unknown";
    QString imageAuthor = "Unknown";
    QString imageSize = "Unknown";
    QString imageYear = "Unknown";
    QString imageDescription = "Unknown";
    QString imagePath = "";


    vector<QWidget*> currentWidgets;
    vector<string> currentImages;
    string currentGalleryString;

    void startWindow();
    void askForUsernameAndPassword();
    void galleriesWindow();
    void widgetInitialization();
    void addExistingGalleriesToGalleryWindow();
    void clearWindow(bool addBackButton);
    void addToWindow(QWidget *widget);
    void createButton(QPushButton *button, QString text, int ax, int ay, int aw, int ah);
    void imageWindow();
    void addExistingImagesFromGallery();
    void metadataWindow();
    void createLabel(QLabel *label, QString text, int ax, int ay, int aw, int ah);
    void createInput(QLineEdit *input, QString text, int ax, int ay, int aw, int ah);
    void editGalleryWindow();

public:

    QGraphicsScene *scene;

    /**
     * @brief Constructor
     * @param parent Nodo padre de la interfaz (nulo en este caso)
     */
    Interface(QWidget* parent=NULL);

    /**
     * @brief Setter
     * @param dbHandler
     */
    void setDbHandler(DataBaseHandler *dbHandler);
    void setRaidManager(RaidManager *raidManager, int imageId);

private slots:
    void clickedLogIn();
    void clickedSignUp();
    void clickedBack();
    void clickedVerify();
    void clickedCreate();
    void clickedManageGallery();
    void clickedPreviousImage();
    void clickedImageMetaData();
    void clickedNextImage();
    void clickedGallery();
    void clickedEditImageMetaData();
    void clickedAcceptEditImageMetadata();
    void clickedAcceptManageGallery();
    void clickedSelectPicButton();



    void retrieveImageMetadataFromDb();

    void displayImage();
};
#endif //GALLERYTEC_INTERFACE_H

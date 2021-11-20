//
// Created by cuadriante on 16/11/21.
//

#ifndef GALLERYTEC_MAINWINDOW_H
#define GALLERYTEC_MAINWINDOW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtWidgets>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QBrush>
#include <QDebug>
#include <QKeyEvent>
#include <QApplication>
#include <unistd.h>
#include <iostream>

using namespace std;

class MainWindow: public QGraphicsView {
Q_OBJECT
private:
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

    QImage * bgImage;
    QGraphicsPixmapItem * pixmap;

    QPushButton * logInButton;
    QPushButton * signUpButton;
    QPushButton * backButton;
    QPushButton * verifyUserButton;
    QPushButton * createUserButton;
    QPushButton * addGalleryButton;
    QPushButton * editGalleryButton;
    QPushButton * deleteGalleryButton;
    QPushButton * previousImageButton;
    QPushButton * imageMetaDataButton;
    QPushButton * nextImageButton;
    QPushButton * imageNameButton;
    QPushButton * imageAuthorButton;
    QPushButton * imageSizeButton;
    QPushButton * imageYearButton;
    QPushButton * imageDescriptionButton;

    bool createdLogInWindow = false;
    bool askedForUsernameAndPassword = false;
    bool userCreated = true;
    bool successfulVerification = true;
    bool successfulCreation = true;
    bool displayedGalleries = false;
    bool displayedImage = false;
    bool displayedMetadata = false;

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

    QString currentGallery = "New Gallery";
    QString currentImageName = "Unknown";
    QString imageAuthor = "Unknown";
    QString imageSize = "Unknown";
    QString imageYear = "Unknown";
    QString imageDescription = "Unknown";

    vector<QWidget*> currentWidgets;


public:
    QGraphicsScene *scene;
    MainWindow(QWidget* parent=NULL);
    void logInWindow();
    void askForUsernameAndPassword();
    void galleriesWindow();
    void widgetInitialization();
    void addExistingGalleriesToGalleryWindow();
    void clearWindow(bool addBackButton);
    void imageWindow();
    void displayCurrentImage();
    void metadataWindow();
private slots:
    void clickedLogIn();
    void clickedSignUp();
    void clickedBack();
    void clickedVerify();
    void clickedCreate();
    void clickedAddGallery();
    void clickedEditGallery();
    void clickedDeleteGallery();
    void clickedPreviousImage();
    void clickedImageMetaData();
    void clickedNextImage();
    void clickedGallery();
    void clickedEditImageMetaData();
    void clickedAcceptEditImageMetadata();


};
#endif //GALLERYTEC_MAINWINDOW_H

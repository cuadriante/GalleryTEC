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

    const int MENU = 0;
    const int LOGIN = 1;
    const int SIGNUP = 1;
    const int GALLERY_MENU = 1;
    const int GALLERY_MANAGEMENT = 3;
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

    bool createdLogInWindow = false;
    bool askedForUsernameAndPassword = false;
    bool userCreated = true;
    bool successfulVerification = true;
    bool successfulCreation = true;
    bool displayedGalleries = false;

    QLineEdit * usernameTextInput;
    QLineEdit * passwordTextInput;
    QLabel * noticeLabel;
    QLabel * currentGalleryLabel;
    QString currentGallery;
    vector<QWidget*> currentWidgets;


public:
    QGraphicsScene *scene;
    MainWindow(QWidget* parent=NULL);
    void logInWindow();
    void askForUsernameAndPassword();
    void galleriesWindow();

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


    void widgetInitialization();

    void addExistingGalleriesToGalleryWindow();

    void clearWindow(bool addBackButton);
};
#endif //GALLERYTEC_MAINWINDOW_H

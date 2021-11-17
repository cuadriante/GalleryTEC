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
    const int MENU = 0;
    const int LOGIN = 1;
    const int SIGNUP = 1;
    const int GALLERY_MENU = 2;
    const int GALLERY_MANAGEMENT = 3;
    int currentWindow = MENU;
    QPushButton * logInButton;
    QPushButton * signUpButton;
    bool createdLogInWindow = false;
    QPushButton * backButton;
    QLineEdit * usernameTextInput;
    QLineEdit * passwordTextInput;
    bool askedForUsernameAndPassword = false;
    QPushButton * verifyUserButton;
    QPushButton * createUserButton;
    bool userCreated = true;
    bool succesfulVerification = true;
    bool succesfulCreation = true;
    QLabel * noticeLabel;
    QPushButton * addGalleryButton;
    QPushButton * editGalleryButton;
    QPushButton * deleteGalleryButton;
    bool displayedGalleries = false;
    QPushButton * previousImageButton;
    QPushButton * imageMetaDataButton;
    QPushButton * nextImageButton;
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


    void widgetInitialization();
};
#endif //GALLERYTEC_MAINWINDOW_H

//
// Created by cuadriante on 16/11/21.
//


#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene(0,0,850,700);
    setScene(scene);
    this->setWindowTitle("GalleryTEC");
    bgImage = new QImage();
    bgImage->load(BG_GALLERY_TEC);
    pixmap = new QGraphicsPixmapItem(QPixmap::fromImage(*bgImage));
    scene->addItem(pixmap);
    pixmap->setPos(0,0);
    pixmap->show();
    //setStyleSheet("background-color:pink;");
    widgetInitialization();

}

void MainWindow::widgetInitialization() {
    backButton = new QPushButton(this);
    backButton->setGeometry(35, 35, 180, 70);
    backButton->setText("Back");
    backButton->setVisible(false);
    backButton->setStyleSheet("color: black;");
    connect(backButton, SIGNAL(clicked()), this, SLOT(clickedBack()));

    noticeLabel = new QLabel(this);
    noticeLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    noticeLabel->setStyleSheet("color: red;");
    QFont noticeFont = noticeLabel->font();
    noticeFont.setPointSize(15);
    noticeFont.setBold(true);
    noticeLabel->setFont(noticeFont);

    QFont font("Century SchoolBook L");
    font.setPointSize(30);
    font.bold();
    font.setStyleHint(QFont::Monospace);
    QApplication::setFont(font);

    logInWindow();
}

void MainWindow::logInWindow() {
    currentWindow = GALLERY_MENU;
    bgImage->load(BG_GALLERY_TEC);
    if (!createdLogInWindow){
        logInButton = new QPushButton(this);
        logInButton->setGeometry(335, 425, 180, 70);
        logInButton->setText("Log In");
        logInButton->setVisible(true);
        logInButton->setStyleSheet("color: black;");
        connect(logInButton, SIGNAL(clicked()), this, SLOT(clickedLogIn()));
        signUpButton = new QPushButton(this);
        signUpButton->setGeometry(335, 525, 180, 70);
        signUpButton->setText("Sign Up");
        signUpButton->setVisible(true);
        signUpButton->setStyleSheet("color: black;");
        connect(signUpButton, SIGNAL(clicked()), this, SLOT(clickedSignUp()));
        createdLogInWindow = true;
    } else {
        backButton->setVisible(false);
        logInButton->setVisible(true);
        signUpButton->setVisible(true);
    }
}

void MainWindow::galleriesWindow() {
    currentWindow = GALLERY_MENU;
    bgImage->load(BG_GALLERIES);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));
    if(!displayedGalleries){
        addGalleryButton = new QPushButton(this);
        QFont galleryButtonFont = addGalleryButton->font();
        galleryButtonFont.setPointSize(20);
        addGalleryButton->setFont(galleryButtonFont);
        addGalleryButton->setGeometry(25, 600, 220, 70);
        addGalleryButton->setText("Add Gallery");
        addGalleryButton->setStyleSheet("color: black;");
        addGalleryButton->setVisible(true);
        connect(addGalleryButton, SIGNAL(clicked()), this, SLOT(clickedAddGallery()));

        editGalleryButton = new QPushButton(this);
        editGalleryButton->setFont(galleryButtonFont);
        editGalleryButton->setGeometry(315, 600, 220, 70);
        editGalleryButton->setText("Edit Gallery");
        editGalleryButton->setStyleSheet("color: black;");
        editGalleryButton->setVisible(true);
        connect(editGalleryButton, SIGNAL(clicked()), this, SLOT(clickedEditGallery()));

        deleteGalleryButton = new QPushButton(this);
        deleteGalleryButton->setGeometry(605, 600, 220, 70);
        deleteGalleryButton->setFont(galleryButtonFont);
        deleteGalleryButton->setText("Delete Gallery");
        deleteGalleryButton->setStyleSheet("color: black;");
        deleteGalleryButton->setVisible(true);
        connect(deleteGalleryButton, SIGNAL(clicked()), this, SLOT(clickedDeleteGallery()));
    } else {
        addGalleryButton->setVisible(true);
        editGalleryButton->setVisible(true);
        deleteGalleryButton->setVisible(true);
    }
}


void MainWindow::clickedLogIn() {
    currentWindow = LOGIN;
    cout << "current window" << currentWindow << endl;
    cout << "clicked log in" << endl;
    signUpButton->setVisible(false);
    logInButton->setVisible(false);
    backButton->setVisible(true);
    userCreated = true;
    askForUsernameAndPassword();
}



void MainWindow::clickedSignUp() {
    currentWindow = SIGNUP;
    cout << "clicked sign up" << endl;
    signUpButton->setVisible(false);
    logInButton->setVisible(false);
    backButton->setVisible(true);
    userCreated = false;
    askForUsernameAndPassword();
}

void MainWindow::clickedBack() {
    cout << "current window: " << currentWindow << endl;
    noticeLabel->setVisible(false);
    int previousWindow = currentWindow - 1;
    switch(previousWindow){
        case  0: {
            passwordTextInput->setVisible(false);
            usernameTextInput->setVisible(false);
            if (!userCreated){
                createUserButton->setVisible(false);
            } else {
                verifyUserButton->setVisible(false);
            }
            currentWindow = MENU;
            logInWindow();
            break;
        }
        case 1: {
            addGalleryButton->setVisible(false);
            editGalleryButton->setVisible(false);
            deleteGalleryButton->setVisible(false);
            currentWindow = MENU;
            logInWindow();
            break;
        }
        case 2: {
            addGalleryButton->setVisible(false);
            editGalleryButton->setVisible(false);
            deleteGalleryButton->setVisible(false);
            logInButton->setVisible(false);
            signUpButton->setVisible(false);
            currentWindow = GALLERY_MENU;
            galleriesWindow();
            break;
        }
        case 3: {
        }
    }
}

void MainWindow::clickedCreate() {
    if (succesfulCreation){
        noticeLabel->setText("User created succesfully! \nReturn to main window.");
        noticeLabel->setGeometry(120, 200, 600, 200);
        noticeLabel->setVisible(true);
        passwordTextInput->setVisible(false);
        usernameTextInput->setVisible(false);
        createUserButton->setVisible(false);
        backButton->setVisible(true);

    } else {
        noticeLabel->setText("ERROR: Could not create user.");
        noticeLabel->setGeometry(470, 420, 100, 100);
        noticeLabel->setVisible(true);
    }
}

void MainWindow::clickedVerify() {
    if (succesfulVerification){
        currentWindow = GALLERY_MENU;
        passwordTextInput->setVisible(false);
        usernameTextInput->setVisible(false);
        verifyUserButton->setVisible(false);
        backButton->setVisible(true);
        galleriesWindow();
    } else {
        noticeLabel->setText("ERROR: Username or password incorrect.");
        noticeLabel->setGeometry(470, 420, 100, 100);
        noticeLabel->setVisible(true);

    }
}




void MainWindow::askForUsernameAndPassword() {
    if(!askedForUsernameAndPassword){
        usernameTextInput = new QLineEdit(this);
        usernameTextInput->setAlignment(Qt::AlignCenter);
        usernameTextInput->setPlaceholderText("Username");
        usernameTextInput->setStyleSheet("color : white;");
        usernameTextInput->setMaxLength(20);
        usernameTextInput->setGeometry(240, 250, 400, 70);
        usernameTextInput->setVisible(true);

        passwordTextInput = new QLineEdit(this);
        passwordTextInput->setAlignment(Qt::AlignCenter);
        passwordTextInput->setPlaceholderText("Password");
        passwordTextInput->setStyleSheet("color : white;");
        passwordTextInput->setMaxLength(20);
        passwordTextInput->setGeometry(240, 350, 400, 70);
        passwordTextInput->setVisible(true);
        askedForUsernameAndPassword = true;

        createUserButton = new QPushButton(this);
        createUserButton->setGeometry(335, 550, 180, 70);
        createUserButton->setText("Create");
        createUserButton->setStyleSheet("color: black;");
        connect(createUserButton, SIGNAL(clicked()), this, SLOT(clickedCreate()));

        verifyUserButton = new QPushButton(this);
        verifyUserButton->setGeometry(335, 550, 180, 70);
        verifyUserButton->setText("Verify");
        verifyUserButton->setStyleSheet("color: black;");
        connect(verifyUserButton, SIGNAL(clicked()), this, SLOT(clickedVerify()));

        if (!userCreated){
            createUserButton->setVisible(true);
        } else{
            verifyUserButton->setVisible(true);
        }
    } else {
        usernameTextInput->setVisible(true);
        passwordTextInput->setVisible(true);
        if (!userCreated){
           createUserButton->setVisible(true);
        } else {
           verifyUserButton->setVisible(true);
        }
    }

}

void MainWindow::clickedAddGallery() {
    currentWindow = GALLERY_MANAGEMENT;
    addGalleryButton->setVisible(false);
    editGalleryButton->setVisible(false);
    deleteGalleryButton->setVisible(false);
    backButton->setVisible(true);
}

void MainWindow::clickedEditGallery() {
    currentWindow = GALLERY_MANAGEMENT;
    addGalleryButton->setVisible(false);
    editGalleryButton->setVisible(false);
    deleteGalleryButton->setVisible(false);
    backButton->setVisible(true);
}

void MainWindow::clickedDeleteGallery() {
    currentWindow = GALLERY_MANAGEMENT;
    addGalleryButton->setVisible(false);
    editGalleryButton->setVisible(false);
    deleteGalleryButton->setVisible(false);
    backButton->setVisible(true);
}

void MainWindow::clickedPreviousImage() {

}

void MainWindow::clickedImageMetaData() {

}

void MainWindow::clickedNextImage() {

}





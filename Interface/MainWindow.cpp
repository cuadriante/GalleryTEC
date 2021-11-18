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
    noticeLabel = new QLabel(this);
    noticeLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    noticeLabel->setStyleSheet("color: white;");
    QFont noticeFont = noticeLabel->font();
    noticeFont.setPointSize(15);
    noticeFont.setBold(true);
    noticeLabel->setFont(noticeFont);

    QFont font("Century SchoolBook L");
    font.setPointSize(30);
    font.bold();
    font.setStyleHint(QFont::Monospace);
    QApplication::setFont(font);

    backButton = new QPushButton(this);
    backButton->setGeometry(25, 25, 140, 50);
    font.setPointSize(20);
    backButton->setFont(font);
    backButton->setText("Back");
    backButton->setVisible(false);
    backButton->setStyleSheet("color: black; background-color:pink;");
    connect(backButton, SIGNAL(clicked()), this, SLOT(clickedBack()));

    logInWindow();
}

void MainWindow::logInWindow() {
    currentWindow = GALLERY_MENU;
    bgImage->load(BG_GALLERY_TEC);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));
    if (!createdLogInWindow){
        logInButton = new QPushButton(this);
        logInButton->setGeometry(335, 425, 180, 70);
        logInButton->setText("Log In");
        logInButton->setVisible(true);
        logInButton->setStyleSheet("color: black; background-color:pink;");
        currentWidgets.push_back(logInButton);
        connect(logInButton, SIGNAL(clicked()), this, SLOT(clickedLogIn()));
        signUpButton = new QPushButton(this);
        signUpButton->setGeometry(335, 525, 180, 70);
        signUpButton->setText("Sign Up");
        signUpButton->setVisible(true);
        signUpButton->setStyleSheet("color: black; background-color:pink;");
        currentWidgets.push_back(signUpButton);
        connect(signUpButton, SIGNAL(clicked()), this, SLOT(clickedSignUp()));
        createdLogInWindow = true;
    } else {
        backButton->setVisible(false);
        logInButton->setVisible(true);
        currentWidgets.push_back(logInButton);
        signUpButton->setVisible(true);
        currentWidgets.push_back(signUpButton);
    }
}

void MainWindow::galleriesWindow() {
    currentWindow = GALLERY_MENU;
    bgImage->load(BG_GALLERIES);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));
    backButton->setVisible(true);
    if(!displayedGalleries){
        addGalleryButton = new QPushButton(this);
        QFont galleryButtonFont = addGalleryButton->font();
        galleryButtonFont.setPointSize(20);
        addGalleryButton->setFont(galleryButtonFont);
        addGalleryButton->setGeometry(25, 600, 220, 70);
        addGalleryButton->setText("Add Gallery");
        addGalleryButton->setStyleSheet("color: black; background-color:pink;");
        addGalleryButton->setVisible(true);
        currentWidgets.push_back(addGalleryButton);
        connect(addGalleryButton, SIGNAL(clicked()), this, SLOT(clickedAddGallery()));

        editGalleryButton = new QPushButton(this);
        editGalleryButton->setFont(galleryButtonFont);
        editGalleryButton->setGeometry(315, 600, 220, 70);
        editGalleryButton->setText("Edit Gallery");
        editGalleryButton->setStyleSheet("color: black; background-color:pink;");
        editGalleryButton->setVisible(true);
        currentWidgets.push_back(editGalleryButton);
        connect(editGalleryButton, SIGNAL(clicked()), this, SLOT(clickedEditGallery()));

        deleteGalleryButton = new QPushButton(this);
        deleteGalleryButton->setGeometry(605, 600, 220, 70);
        deleteGalleryButton->setFont(galleryButtonFont);
        deleteGalleryButton->setText("Delete Gallery");
        deleteGalleryButton->setStyleSheet("color: black; background-color:pink;");
        deleteGalleryButton->setVisible(true);
        currentWidgets.push_back(deleteGalleryButton);
        connect(deleteGalleryButton, SIGNAL(clicked()), this, SLOT(clickedDeleteGallery()));

        addExistingGalleriesToGalleryWindow();
    } else {
        addGalleryButton->setVisible(true);
        currentWidgets.push_back(addGalleryButton);
        editGalleryButton->setVisible(true);
        currentWidgets.push_back(addGalleryButton);
        deleteGalleryButton->setVisible(true);
        currentWidgets.push_back(deleteGalleryButton);
    }
}

void MainWindow::clickedLogIn() {
    bgImage->load(BG_BACKGROUND);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));
    currentWindow = LOGIN;
    cout << "current window" << currentWindow << endl;
    cout << "clicked log in" << endl;
    clearWindow(true);
    userCreated = true;
    askForUsernameAndPassword();
}

void MainWindow::clickedSignUp() {
    bgImage->load(BG_BACKGROUND);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));
    currentWindow = SIGNUP;
    cout << "clicked sign up" << endl;
    clearWindow(true);
    userCreated = false;
    askForUsernameAndPassword();
}

void MainWindow::clickedCreate() {
    if (successfulCreation){
        noticeLabel->setText("User created succesfully! \nReturn to main window.");
        noticeLabel->setGeometry(120, 200, 600, 200);
        clearWindow(true);
        noticeLabel->setVisible(true);

    } else {
        noticeLabel->setText("ERROR: Could not create user.");
        noticeLabel->setGeometry(470, 420, 100, 100);
        noticeLabel->setVisible(true);
    }
}

void MainWindow::clickedVerify() {
    if (successfulVerification){
        currentWindow = GALLERY_MENU;
        clearWindow(true);
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
        usernameTextInput->setStyleSheet("color : black;");
        usernameTextInput->setMaxLength(20);
        usernameTextInput->setGeometry(240, 250, 400, 70);
        usernameTextInput->setVisible(true);
        currentWidgets.push_back(usernameTextInput);

        passwordTextInput = new QLineEdit(this);
        passwordTextInput->setAlignment(Qt::AlignCenter);
        passwordTextInput->setPlaceholderText("Password");
        passwordTextInput->setStyleSheet("color : black;");
        passwordTextInput->setMaxLength(20);
        passwordTextInput->setGeometry(240, 350, 400, 70);
        passwordTextInput->setVisible(true);
        currentWidgets.push_back(passwordTextInput);

        askedForUsernameAndPassword = true;

        createUserButton = new QPushButton(this);
        createUserButton->setGeometry(335, 550, 180, 70);
        createUserButton->setText("Create");
        createUserButton->setStyleSheet("color: black; background-color:pink;");
        currentWidgets.push_back(createUserButton);
        connect(createUserButton, SIGNAL(clicked()), this, SLOT(clickedCreate()));

        verifyUserButton = new QPushButton(this);
        verifyUserButton->setGeometry(335, 550, 180, 70);
        verifyUserButton->setText("Verify");
        verifyUserButton->setStyleSheet("color: black; background-color:pink;");
        currentWidgets.push_back(verifyUserButton);
        connect(verifyUserButton, SIGNAL(clicked()), this, SLOT(clickedVerify()));

        if (!userCreated){
            createUserButton->setVisible(true);
            currentWidgets.push_back(createUserButton);
        } else{
            verifyUserButton->setVisible(true);
            currentWidgets.push_back(verifyUserButton);
        }
    } else {
        usernameTextInput->setVisible(true);
        currentWidgets.push_back(usernameTextInput);
        passwordTextInput->setVisible(true);
        currentWidgets.push_back(passwordTextInput);
        if (!userCreated){
           createUserButton->setVisible(true);
            currentWidgets.push_back(createUserButton);
        } else {
           verifyUserButton->setVisible(true);
           currentWidgets.push_back(verifyUserButton);
        }
    }

}

void MainWindow::clickedAddGallery() {
    bgImage->load(BG_BACKGROUND);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));
    currentWindow = GALLERY_MANAGEMENT;
    clearWindow(true);
}

void MainWindow::clickedEditGallery() {
    bgImage->load(BG_BACKGROUND);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));
    currentWindow = GALLERY_MANAGEMENT;
    clearWindow(true);
}

void MainWindow::clickedDeleteGallery() {
    bgImage->load(BG_BACKGROUND);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));
    currentWindow = GALLERY_MANAGEMENT;
    clearWindow(true);
}

void MainWindow::clickedPreviousImage() {

}

void MainWindow::clickedImageMetaData() {

}

void MainWindow::clickedNextImage() {

}

void MainWindow::addExistingGalleriesToGalleryWindow() {

    QPushButton * galleryButton = new QPushButton(this);
    galleryButton->setGeometry(30, 170, 790, 50);
    galleryButton->setText("Gallery Example");
    galleryButton->setVisible(true);
    galleryButton->setStyleSheet("color: black; background-color:pink;");
    currentWidgets.push_back(galleryButton);
    connect(galleryButton, SIGNAL(clicked()), this, SLOT(clickedGallery()));
}

void MainWindow::clickedGallery() {
    clearWindow(true);
    currentWindow = GALLERY_MANAGEMENT;
    bgImage->load(BG_IMAGE);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    currentGallery = buttonSender->text();
    qDebug() << currentGallery;
    currentGalleryLabel = new QLabel(this);
    currentGalleryLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    currentGalleryLabel->setStyleSheet("color: white;");
    QFont galleryNameFont = currentGalleryLabel->font();
    galleryNameFont.setPointSize(35);
    galleryNameFont.setBold(true);
    currentGalleryLabel->setFont(galleryNameFont);
    currentGalleryLabel->setText(currentGallery);
    currentGalleryLabel->setGeometry(130, 45, 600, 80);
    currentGalleryLabel->setVisible(true);
    currentWidgets.push_back(currentGalleryLabel);

}

void MainWindow::clickedBack() {
    cout << "current window: " << currentWindow << endl;
    clearWindow(false);
    noticeLabel->setVisible(false);
    int previousWindow = currentWindow - 1;
    switch(previousWindow){
        case  0: {
            currentWindow = MENU;
            logInWindow();
            break;
        }
        case 2: {
            currentWindow = GALLERY_MENU;
            galleriesWindow();
            break;
        }
        case 3: {
        }
    }
}

void MainWindow::clearWindow(bool addBackButton) {
    for(QWidget * widget : currentWidgets){
        widget->setVisible(false);
    }
    backButton->setVisible(addBackButton);
    currentWidgets.clear();
}

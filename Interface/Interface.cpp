//
// Created by cuadriante on 16/11/21.
//


#include "Interface.h"

Interface::Interface(QWidget *parent) : QGraphicsView(parent) {
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

void Interface::widgetInitialization() {
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

    startWindow();
}

void Interface::startWindow() {
    currentWindow = GALLERY_MENU;
    bgImage->load(BG_GALLERY_TEC);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));
    if (!createdLogInWindow){
        logInButton = new QPushButton(this);
        createButton(logInButton, "Log In", 335, 425, 180, 70);
        connect(logInButton, SIGNAL(clicked()), this, SLOT(clickedLogIn()));
        signUpButton = new QPushButton(this);
        createButton(signUpButton, "Sign Up", 335, 525, 180, 70);
        connect(signUpButton, SIGNAL(clicked()), this, SLOT(clickedSignUp()));
        createdLogInWindow = true;
    }
    backButton->setVisible(false);
    addToWindow(logInButton);
    addToWindow(signUpButton);
}

void Interface::galleriesWindow() {
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
        addToWindow(addGalleryButton);
        addToWindow(editGalleryButton);
        addToWindow(deleteGalleryButton);
    }
}

void Interface::imageWindow() {
    currentWindow = IMAGE_MENU;
    currentGalleryLabel->setVisible(true);
    currentWidgets.push_back(currentGalleryLabel);
    bgImage->load(BG_IMAGE);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));
    backButton->setVisible(true);
    if(!displayedImage){
        previousImageButton = new QPushButton(this);
        QFont galleryButtonFont = addGalleryButton->font();
        galleryButtonFont.setPointSize(20);
        previousImageButton->setFont(galleryButtonFont);
        previousImageButton->setGeometry(25, 600, 220, 70);
        previousImageButton->setText("Previous");
        previousImageButton->setStyleSheet("color: black; background-color:pink;");
        connect(previousImageButton, SIGNAL(clicked()), this, SLOT(clickedPreviousImage()));

        imageMetaDataButton = new QPushButton(this);
        imageMetaDataButton->setFont(galleryButtonFont);
        imageMetaDataButton->setGeometry(315, 600, 220, 70);
        imageMetaDataButton->setText("Metadata");
        imageMetaDataButton->setStyleSheet("color: black; background-color:pink;");
        connect(imageMetaDataButton, SIGNAL(clicked()), this, SLOT(clickedImageMetaData()));

        nextImageButton = new QPushButton(this);
        nextImageButton->setGeometry(605, 600, 220, 70);
        nextImageButton->setFont(galleryButtonFont);
        nextImageButton->setText("Next");
        nextImageButton->setStyleSheet("color: black; background-color:pink;");
        connect(nextImageButton, SIGNAL(clicked()), this, SLOT(clickedNextImage()));

        currentImageLabel = new QLabel(this);
        currentImageLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        currentImageLabel->setStyleSheet("color: white;");
        QFont galleryNameFont = currentImageLabel->font();
        galleryNameFont.setPointSize(35);
        galleryNameFont.setBold(true);
        currentImageLabel->setFont(galleryNameFont);
        displayedImage = true;
    }
    previousImageButton->setVisible(true);
    currentWidgets.push_back(previousImageButton);
    imageMetaDataButton->setVisible(true);
    currentWidgets.push_back(imageMetaDataButton);
    nextImageButton->setVisible(true);
    currentWidgets.push_back(nextImageButton);
    currentImageLabel->setVisible(true);
    currentWidgets.push_back(currentImageLabel);
    displayCurrentImage();
}

void Interface::metadataWindow() {
    clearWindow(true);
    currentWindow = IMAGE_METADATA;
    bgImage->load(BG_METADATA);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));
    if (!displayedMetadata){
        imageNameLabel = new QLabel(this);
        imageNameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        imageNameLabel->setStyleSheet("color: black;");
        QFont galleryNameFont = currentGalleryLabel->font();
        galleryNameFont.setPointSize(25);
        galleryNameFont.setBold(true);
        imageNameLabel->setFont(galleryNameFont);
        imageNameLabel->setText("Name: " + currentImageName);
        imageNameLabel->setGeometry(200, 170, 460, 80);

        //createButton(imageNameButton, "Edit", 670, 180, 80, 50);
        imageNameButton = new QPushButton(this);
        imageNameButton->setFont(galleryNameFont);
        imageNameButton->setGeometry(670, 180, 80, 50);
        imageNameButton->setText("Edit");
        imageNameButton->setStyleSheet("color: black; background-color:pink;");
        imageNameButton->setAccessibleDescription("0");
        connect(imageNameButton, SIGNAL(clicked()), this, SLOT(clickedEditImageMetaData()));

        imageNameInput = new QLineEdit(this);
        imageNameInput->setAlignment(Qt::AlignCenter);
        imageNameInput->setPlaceholderText("New Name");
        imageNameInput->setStyleSheet("color : black;");
        imageNameInput->setFont(galleryNameFont);
        imageNameInput->setMaxLength(20);
        imageNameInput->setGeometry(315, 180, 340, 50);

        imageAuthorLabel = new QLabel(this);
        imageAuthorLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        imageAuthorLabel->setStyleSheet("color: black;");
        imageAuthorLabel->setFont(galleryNameFont);
        imageAuthorLabel->setText("Author: " + imageAuthor);
        imageAuthorLabel->setGeometry(200, 235, 460, 80);

        imageAuthorButton = new QPushButton(this);
        imageAuthorButton->setFont(galleryNameFont);
        imageAuthorButton->setGeometry(670, 245, 80, 50);
        imageAuthorButton->setText("Edit");
        imageAuthorButton->setStyleSheet("color: black; background-color:pink;");
        imageAuthorButton->setAccessibleDescription("1");
        connect(imageAuthorButton, SIGNAL(clicked()), this, SLOT(clickedEditImageMetaData()));

        imageAuthorInput = new QLineEdit(this);
        imageAuthorInput->setAlignment(Qt::AlignCenter);
        imageAuthorInput->setPlaceholderText("New Author");
        imageAuthorInput->setStyleSheet("color : black;");
        imageAuthorInput->setFont(galleryNameFont);
        imageAuthorInput->setMaxLength(20);
        imageAuthorInput->setGeometry(338, 245, 317, 50);

        imageYearLabel = new QLabel(this);
        imageYearLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        imageYearLabel->setStyleSheet("color: black;");
        imageYearLabel->setFont(galleryNameFont);
        imageYearLabel->setText("Year: " + imageYear);
        imageYearLabel->setGeometry(200, 300, 460, 80);

        imageYearButton = new QPushButton(this);
        imageYearButton->setFont(galleryNameFont);
        imageYearButton->setGeometry(670, 310, 80, 50);
        imageYearButton->setText("Edit");
        imageYearButton->setStyleSheet("color: black; background-color:pink;");
        imageYearButton->setAccessibleDescription("2");
        connect(imageYearButton, SIGNAL(clicked()), this, SLOT(clickedEditImageMetaData()));

        imageYearInput = new QLineEdit(this);
        imageYearInput->setAlignment(Qt::AlignCenter);
        imageYearInput->setPlaceholderText("New Year");
        imageYearInput->setStyleSheet("color : black;");
        imageYearInput->setFont(galleryNameFont);
        imageYearInput->setMaxLength(20);
        imageYearInput->setGeometry(295, 310, 360, 50);

        imageSizeLabel = new QLabel(this);
        imageSizeLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        imageSizeLabel->setStyleSheet("color: black;");
        imageSizeLabel->setFont(galleryNameFont);
        imageSizeLabel->setText("Size: " + imageSize);
        imageSizeLabel->setGeometry(200, 365, 460, 80);

        imageSizeButton = new QPushButton(this);
        imageSizeButton->setFont(galleryNameFont);
        imageSizeButton->setGeometry(670, 375, 80, 50);
        imageSizeButton->setText("Edit");
        imageSizeButton->setStyleSheet("color: black; background-color:pink;");
        imageSizeButton->setAccessibleDescription("3");
        connect(imageSizeButton, SIGNAL(clicked()), this, SLOT(clickedEditImageMetaData()));

        imageSizeInput = new QLineEdit(this);
        imageSizeInput->setAlignment(Qt::AlignCenter);
        imageSizeInput->setPlaceholderText("New Size");
        imageSizeInput->setStyleSheet("color : black;");
        imageSizeInput->setFont(galleryNameFont);
        imageSizeInput->setMaxLength(20);
        imageSizeInput->setGeometry(285, 375, 370, 50);

        imageDescriptionLabel = new QLabel(this);
        imageDescriptionLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        imageDescriptionLabel->setStyleSheet("color: black;");
        imageDescriptionLabel->setFont(galleryNameFont);
        imageDescriptionLabel->setText("Desc: " + imageDescription);
        imageDescriptionLabel->setGeometry(200, 430, 460, 80);

        imageDescriptionButton = new QPushButton(this);
        imageDescriptionButton->setFont(galleryNameFont);
        imageDescriptionButton->setGeometry(670, 440, 80, 50);
        imageDescriptionButton->setText("Edit");
        imageDescriptionButton->setAccessibleDescription("4");
        imageDescriptionButton->setStyleSheet("color: black; background-color:pink;");
        connect(imageDescriptionButton, SIGNAL(clicked()), this, SLOT(clickedEditImageMetaData()));

        imageDescriptionInput = new QLineEdit(this);
        imageDescriptionInput->setAlignment(Qt::AlignCenter);
        imageDescriptionInput->setPlaceholderText("New Description");
        imageDescriptionInput->setStyleSheet("color : black;");
        imageDescriptionInput->setFont(galleryNameFont);
        imageDescriptionInput->setMaxLength(20);
        imageDescriptionInput->setGeometry(295, 440, 360, 50);
    }
    addToWindow(imageNameLabel);
    addToWindow(imageNameButton);
    addToWindow(imageAuthorLabel);
    addToWindow(imageAuthorButton);
    addToWindow(imageYearLabel);
    addToWindow(imageYearButton);
    addToWindow(imageSizeLabel);
    addToWindow(imageSizeButton);
    addToWindow(imageDescriptionLabel);
    addToWindow(imageDescriptionButton);
}

void Interface::displayCurrentImage() {
    //aqui se displayea la imagen cargada del db
    currentImageName = "Image Example";
    currentImageLabel->setText(currentImageName);
    currentImageLabel->setGeometry(130, 500, 600, 80);
    currentImageLabel->setVisible(true);
}

void Interface::clickedLogIn() {

    currentWindow = LOGIN;
    userCreated = true;
    askForUsernameAndPassword();
}

void Interface::clickedSignUp() {
    currentWindow = SIGNUP;
    userCreated = false;
    askForUsernameAndPassword();
}

void Interface::clickedCreate() {
    //get username and password and verify
    //string username  = usernameTextInput->text().toStdString();
    //string password = passwordTextInput->text().toStdString();
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

void Interface::clickedVerify() {
    //get username and password and verify
    string username  = usernameTextInput->text().toStdString();
    string password = passwordTextInput->text().toStdString();
    cout << "username: " << username << " password: " << password << endl;
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

void Interface::askForUsernameAndPassword() {
    bgImage->load(BG_BACKGROUND);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));
    clearWindow(true);
    if(!askedForUsernameAndPassword){
        usernameTextInput = new QLineEdit(this);
        passwordTextInput = new QLineEdit(this);
        createUserButton = new QPushButton(this);
        verifyUserButton = new QPushButton(this);
        createInput(usernameTextInput, "Username", 240, 250, 400, 70);
        createInput(passwordTextInput, "Password", 240, 350, 400, 70);
        createButton(createUserButton, "Create", 335, 550, 180, 70);
        connect(createUserButton, SIGNAL(clicked()), this, SLOT(clickedCreate()));
        createButton(verifyUserButton, "Verify", 335, 550, 180, 70);
        connect(verifyUserButton, SIGNAL(clicked()), this, SLOT(clickedVerify()));
        askedForUsernameAndPassword = true;
    }
    addToWindow(usernameTextInput);
    addToWindow(passwordTextInput);
    if (!userCreated){
        addToWindow(createUserButton);
    } else {
        addToWindow(verifyUserButton);
    }
}

void Interface::clickedAddGallery() {
    bgImage->load(BG_BACKGROUND);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));
    currentWindow = GALLERY_MANAGEMENT;
    clearWindow(true);
    if(!hasAddedGallery){
        newGalleryInput = new QLineEdit(this);
        createInput(newGalleryInput, "New Gallery Name",  220, 250, 400, 70);
        confirmAddGalleryButton = new QPushButton(this);
        createButton(confirmAddGalleryButton, "Add", 335, 350, 180, 70);
        connect(confirmAddGalleryButton, SIGNAL(clicked()), this, SLOT(clickedCreate()));
        hasAddedGallery = true;
    }
    newGalleryInput->setPlaceholderText("New Gallery Name");
    confirmAddGalleryButton->setText("Add");
    addToWindow(newGalleryInput);
    addToWindow(confirmAddGalleryButton);
}

void Interface::clickedEditGallery() {
    bgImage->load(BG_BACKGROUND);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));
    currentWindow = GALLERY_MANAGEMENT;
    clearWindow(true);
}

void Interface::clickedDeleteGallery() {
    bgImage->load(BG_BACKGROUND);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));
    currentWindow = GALLERY_MANAGEMENT;
    clearWindow(true);
    if(!hasAddedGallery){
        newGalleryInput = new QLineEdit(this);
        createInput(newGalleryInput, "Gallery Name",  220, 250, 400, 70);
        confirmAddGalleryButton = new QPushButton(this);
        createButton(confirmAddGalleryButton, "Delete", 335, 350, 180, 70);
        connect(confirmAddGalleryButton, SIGNAL(clicked()), this, SLOT(clickedCreate()));
        hasAddedGallery = true;
    }
    newGalleryInput->setPlaceholderText("Gallery Name");
    confirmAddGalleryButton->setText("Delete");
    addToWindow(newGalleryInput);
    addToWindow(confirmAddGalleryButton);
}

void Interface::clickedPreviousImage() {
}

void Interface::clickedImageMetaData() {
    metadataWindow();
}

void Interface::clickedEditImageMetaData() {
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    QString buttonDescription = buttonSender->accessibleDescription();
    int buttonDescriptionInt = stoi(buttonDescription.toStdString());
    buttonSender->setText("OK");
    connect(buttonSender, SIGNAL(clicked()), this, SLOT(clickedAcceptEditImageMetadata()));
    qDebug() << buttonDescriptionInt;
    switch(buttonDescriptionInt){
        case 0: {
            imageNameInput->setVisible(true);
            currentWidgets.push_back(imageNameInput);
            break;
        }
        case 1: {
            imageAuthorInput->setVisible(true);
            currentWidgets.push_back(imageAuthorInput);
            break;
        }
        case 2: {
            imageYearInput->setVisible(true);
            currentWidgets.push_back(imageYearInput);
            break;
        }
        case 3: {
            imageSizeInput->setVisible(true);
            currentWidgets.push_back(imageSizeInput);
            break;
        }
        case 4: {
            imageDescriptionInput->setVisible(true);
            currentWidgets.push_back(imageDescriptionInput);
            break;
        }
    }
}

void Interface::clickedAcceptEditImageMetadata() {
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    QString buttonDescription = buttonSender->accessibleDescription();
    int buttonDescriptionInt = stoi(buttonDescription.toStdString());
    buttonSender->setText("Edit");
    connect(buttonSender, SIGNAL(clicked()), this, SLOT(clickedEditImageMetaData()));
    qDebug() << buttonDescriptionInt;
    switch(buttonDescriptionInt){
        case 0: {
            imageNameInput->setVisible(false);
            remove(currentWidgets.begin(), currentWidgets.end(), imageNameInput);
            break;
        }
        case 1: {
            imageAuthorInput->setVisible(false);
            remove(currentWidgets.begin(), currentWidgets.end(), imageAuthorInput);
            break;
        }
        case 2: {
            imageYearInput->setVisible(false);
            remove(currentWidgets.begin(), currentWidgets.end(), imageYearInput);
            break;
        }
        case 3: {
            imageSizeInput->setVisible(false);
            remove(currentWidgets.begin(), currentWidgets.end(), imageSizeInput);
            break;
        }
        case 4: {
            imageDescriptionInput->setVisible(false);
            remove(currentWidgets.begin(), currentWidgets.end(), imageDescriptionInput);
            break;
        }
    }
}

void Interface::clickedNextImage() {

}

void Interface::addExistingGalleriesToGalleryWindow() {
    QPushButton * galleryButton = new QPushButton(this);
    createButton(galleryButton, "Gallery Example", 30, 170, 790, 50);
    addToWindow(galleryButton);
    connect(galleryButton, SIGNAL(clicked()), this, SLOT(clickedGallery()));
}

void Interface::clickedGallery() {
    clearWindow(true);
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    currentGallery = buttonSender->text();
    qDebug() << currentGallery;

    currentGalleryLabel = new QLabel(this);
    createLabel(currentGalleryLabel, currentGallery, 130, 45, 600, 80);
    currentGalleryLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QFont galleryNameFont = currentGalleryLabel->font();
    galleryNameFont.setPointSize(35);
    galleryNameFont.setBold(true);
    currentGalleryLabel->setFont(galleryNameFont);

    addToWindow(currentGalleryLabel);
    imageWindow();

}

void Interface::clickedBack() {
    cout << "current window: " << currentWindow << endl;
    clearWindow(false);
    noticeLabel->setVisible(false);
    int previousWindow = currentWindow - 1;
    switch(previousWindow){
        case  0: {
            currentWindow = MENU;
            startWindow();
            break;
        }
        case 2: {
            currentWindow = GALLERY_MENU;
            galleriesWindow();
            break;
        }
        case 3: {
            currentWindow = IMAGE_MENU;
            imageWindow();
            break;
        }
    }
}

void Interface::clearWindow(bool addBackButton) {
    for(QWidget * widget : currentWidgets){
        widget->setVisible(false);
    }
    backButton->setVisible(addBackButton);
    currentWidgets.clear();
}

void Interface::addToWindow(QWidget *widget) {
    widget->setVisible(true);
    currentWidgets.push_back(widget);
}

void Interface::createButton(QPushButton *button, QString text, int ax, int ay, int aw, int ah) {
    button->setGeometry(ax, ay, aw, ah);
    button->setText(text);
    button->setStyleSheet("color: black; background-color:pink;");
}

void Interface::createLabel(QLabel *label, QString text, int ax, int ay, int aw, int ah){
    label->setGeometry(ax, ay, aw, ah);
    label->setText(text);
    label->setStyleSheet("color: white;");
}

void Interface::createInput(QLineEdit *input, QString text, int ax, int ay, int aw, int ah){
    input->setAlignment(Qt::AlignCenter);
    input->setPlaceholderText(text);
    input->setStyleSheet("color : black;");
    input->setMaxLength(20);
    input->setGeometry(ax, ay, aw, ah);
}

void Interface::setDbHandler(DataBaseHandler *dbHandler) {
    Interface::dbHandler = dbHandler;
}






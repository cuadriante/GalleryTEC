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
    createButton(backButton, "Back", 25, 25, 140, 50);
    font.setPointSize(20);
    backButton->setFont(font);
    connect(backButton, SIGNAL(clicked()), this, SLOT(clickedBack()));

    startWindow();
}

// WINDOWS

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
        addGalleryButton->setAccessibleDescription("0");
        createButton(addGalleryButton, "Add Gallery", 25, 600, 220, 70);
        connect(addGalleryButton, SIGNAL(clicked()), this, SLOT(clickedManageGallery()));

        editGalleryButton = new QPushButton(this);
        editGalleryButton->setFont(galleryButtonFont);
        editGalleryButton->setAccessibleDescription("1");
        createButton(editGalleryButton, "Edit Gallery", 315, 600, 220, 70);
        connect(editGalleryButton, SIGNAL(clicked()), this, SLOT(clickedManageGallery()));

        deleteGalleryButton = new QPushButton(this);
        deleteGalleryButton->setFont(galleryButtonFont);
        deleteGalleryButton->setAccessibleDescription("2");
        createButton(deleteGalleryButton, "Delete Gallery", 605, 600, 220, 70);
        connect(deleteGalleryButton, SIGNAL(clicked()), this, SLOT(clickedManageGallery()));
        addExistingGalleriesToGalleryWindow();
    }
    addToWindow(addGalleryButton);
    addToWindow(editGalleryButton);
    addToWindow(deleteGalleryButton);
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
        createButton(previousImageButton, "Previous", 25, 600, 220, 70);
        connect(previousImageButton, SIGNAL(clicked()), this, SLOT(clickedPreviousImage()));

        imageMetaDataButton = new QPushButton(this);
        createButton(imageMetaDataButton, "Metadata", 315, 600, 220, 70);
        imageMetaDataButton->setFont(galleryButtonFont);
        connect(imageMetaDataButton, SIGNAL(clicked()), this, SLOT(clickedImageMetaData()));

        nextImageButton = new QPushButton(this);
        createButton(nextImageButton, "Next", 605, 600, 220, 70);
        nextImageButton->setFont(galleryButtonFont);

        connect(nextImageButton, SIGNAL(clicked()), this, SLOT(clickedNextImage()));

        currentImageLabel = new QLabel(this);
        currentImageLabel->setAlignment(Qt::AlignCenter);
        createLabel(currentImageLabel, " ", 130, 500, 600, 80);
        QFont galleryNameFont = currentImageLabel->font();
        galleryNameFont.setPointSize(35);
        galleryNameFont.setBold(true);
        currentImageLabel->setFont(galleryNameFont);
        displayedImage = true;
    }
    if (!createdImageVector){
        addExistingImagesFromGallery();
        createdImageVector = true;
    }
    previousImageButton->setVisible(true);
    currentWidgets.push_back(previousImageButton);
    imageMetaDataButton->setVisible(true);
    currentWidgets.push_back(imageMetaDataButton);
    nextImageButton->setVisible(true);
    currentWidgets.push_back(nextImageButton);
    currentImageLabel->setVisible(true);
    currentWidgets.push_back(currentImageLabel);
    currentImageName = QString::fromStdString(currentImages.at(currentImageIndex));
    currentImageLabel->setText(currentImageName);
    displayImage();
}

void Interface::metadataWindow() {
    clearWindow(true);
    currentWindow = IMAGE_METADATA;
    bgImage->load(BG_METADATA);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));
    if (!displayedMetadata){
        imageNameLabel = new QLabel(this);
        imageNameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        createLabel(imageNameLabel, "Name: " + currentImageName, 200, 170, 460, 80);
        imageNameLabel->setStyleSheet("color: black;");
        QFont galleryNameFont = currentGalleryLabel->font();
        galleryNameFont.setPointSize(25);
        galleryNameFont.setBold(true);
        imageNameLabel->setFont(galleryNameFont);

        imageNameButton = new QPushButton(this);
        createButton(imageNameButton, "Edit", 670, 180, 80, 50);
        imageNameButton->setFont(galleryNameFont);
        imageNameButton->setAccessibleDescription("0");
        connect(imageNameButton, SIGNAL(clicked()), this, SLOT(clickedEditImageMetaData()));

        imageNameInput = new QLineEdit(this);
        createInput(imageNameInput, "New Name", 315, 180, 340, 50);
        imageNameInput->setFont(galleryNameFont);

        imageAuthorLabel = new QLabel(this);
        imageAuthorLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        createLabel(imageAuthorLabel, "Author: " + imageAuthor,200, 235, 460, 80);
        imageAuthorLabel->setStyleSheet("color: black;");
        imageAuthorLabel->setFont(galleryNameFont);

        imageAuthorButton = new QPushButton(this);
        imageAuthorButton->setFont(galleryNameFont);
        createButton(imageAuthorButton, "Edit", 670, 245, 80, 50);
        imageAuthorButton->setAccessibleDescription("1");
        connect(imageAuthorButton, SIGNAL(clicked()), this, SLOT(clickedEditImageMetaData()));

        imageAuthorInput = new QLineEdit(this);
        createInput(imageAuthorInput, "New Author",338, 245, 317, 50);
        imageAuthorInput->setFont(galleryNameFont);

        imageYearLabel = new QLabel(this);
        imageYearLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        createLabel(imageYearLabel, "Year: " + imageYear, 200, 300, 460, 80);
        imageYearLabel->setStyleSheet("color: black;");
        imageYearLabel->setFont(galleryNameFont);

        imageYearButton = new QPushButton(this);
        imageYearButton->setFont(galleryNameFont);
        createButton(imageYearButton, "Edit", 670, 310, 80, 50);
        imageYearButton->setAccessibleDescription("2");
        connect(imageYearButton, SIGNAL(clicked()), this, SLOT(clickedEditImageMetaData()));

        imageYearInput = new QLineEdit(this);
        createInput(imageYearInput, "New Year", 295, 310, 360, 50);
        imageYearInput->setFont(galleryNameFont);

        imageSizeLabel = new QLabel(this);
        imageSizeLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        createLabel(imageSizeLabel, "Size: " + imageSize, 200, 365, 460, 80);
        imageSizeLabel->setStyleSheet("color: black;");
        imageSizeLabel->setFont(galleryNameFont);

        imageSizeButton = new QPushButton(this);
        imageSizeButton->setFont(galleryNameFont);
        createButton(imageSizeButton, "Edit", 670, 375, 80, 50);
        imageSizeButton->setAccessibleDescription("3");
        connect(imageSizeButton, SIGNAL(clicked()), this, SLOT(clickedEditImageMetaData()));

        imageSizeInput = new QLineEdit(this);
        createInput(imageSizeInput, "New Size",285, 375, 370, 50);
        imageSizeInput->setFont(galleryNameFont);

        imageDescriptionLabel = new QLabel(this);
        imageDescriptionLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        createLabel(imageDescriptionLabel, "Desc: " + imageDescription, 200, 430, 460, 80);
        imageDescriptionLabel->setStyleSheet("color: black;");
        imageDescriptionLabel->setFont(galleryNameFont);

        imageDescriptionButton = new QPushButton(this);
        imageDescriptionButton->setFont(galleryNameFont);
        createButton(imageDescriptionButton, "Edit", 670, 440, 80, 50);
        imageDescriptionButton->setAccessibleDescription("4");
        connect(imageDescriptionButton, SIGNAL(clicked()), this, SLOT(clickedEditImageMetaData()));

        imageDescriptionInput = new QLineEdit(this);
        createInput(imageDescriptionInput, "New Description",  295, 440, 360, 50);
        imageDescriptionInput->setFont(galleryNameFont);

        selectPicButton = new QPushButton(this);
       //selectPicButton->setFont(galleryNameFont);
        createButton(selectPicButton, "Select pic", 200, 595, 450, 50);
        connect(selectPicButton, SIGNAL(clicked()), this, SLOT(clickedSelectPicButton()));
    }
    retrieveImageMetadataFromDb();
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
    addToWindow(selectPicButton);
}

void Interface::retrieveImageMetadataFromDb() {

    string currentImageNameString = currentImageName.toStdString();
    vector<string> imageMetadata = dbHandler->retrieveImageMetadata(currentImages.at(currentImageIndex), currentGalleryString);
    imageAuthorLabel->setText("Author: " + QString::fromStdString(imageMetadata.at(1)));
    imageYearLabel->setText("Year: " + QString::fromStdString(imageMetadata.at(2)));
    imageSizeLabel->setText("Size: " + QString::fromStdString(imageMetadata.at(3)));
    imageDescriptionLabel->setText("Desc: " + QString::fromStdString(imageMetadata.at(4)));
}

// MANAGE USERS

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
    //add user and password to db
    string username  = usernameTextInput->text().toStdString();
    string password = passwordTextInput->text().toStdString();
    successfulCreation = dbHandler->addUserToDb(username, password);
    //Display
    if (successfulCreation){
        cout << "username: " << username << " password: " << password << endl;
        noticeLabel->setText("User created succesfully! \nReturn to main window.");
        noticeLabel->setGeometry(120, 200, 600, 200);
        clearWindow(true);
        noticeLabel->setVisible(true);
    } else {
        noticeLabel->setText("ERROR: Could not create user.");
        noticeLabel->setGeometry(200, 420, 500, 100);
        noticeLabel->setVisible(true);
    }
}

void Interface::clickedVerify() {
    //Verify user and password
    string username  = usernameTextInput->text().toStdString();
    string password = passwordTextInput->text().toStdString();
    successfulVerification = dbHandler->checkForUserInDb(username, password);
    dbHandler->setCurrentUser(username);
    //Display
    if (successfulVerification){
        cout << "username: " << username << " password: " << password << endl;
        currentWindow = GALLERY_MENU;
        clearWindow(true);
        galleriesWindow();
    } else {
        noticeLabel->setText("ERROR: Username and/or password not found.");
        noticeLabel->setGeometry(170, 420, 500, 100);
        addToWindow(noticeLabel);
    }
}

void Interface::askForUsernameAndPassword() {
    bgImage->load(BG_BACKGROUND);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));
    clearWindow(true);
    if(!askedForUsernameAndPassword){
        usernameTextInput = new QLineEdit(this);
        passwordTextInput = new QLineEdit(this);
        passwordTextInput->setEchoMode(QLineEdit::Password);
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

// MANAGE GALLERY

void Interface::clickedManageGallery() {
    bgImage->load(BG_BACKGROUND);
    pixmap->setPixmap(QPixmap::fromImage(*bgImage));
    currentWindow = GALLERY_MANAGEMENT;
    clearWindow(true);
    auto * buttonSender = qobject_cast<QPushButton*>(sender());
    QString buttonDescription = buttonSender->accessibleDescription();
    int buttonDescriptionInt = stoi(buttonDescription.toStdString());
    if(!hasAddedGallery){
        newGalleryInput = new QLineEdit(this);
        createInput(newGalleryInput, "New Gallery Name",  220, 250, 400, 70);
        confirmAddGalleryButton = new QPushButton(this);
        createButton(confirmAddGalleryButton, "Add", 335, 350, 180, 70);
        connect(confirmAddGalleryButton, SIGNAL(clicked()), this, SLOT(clickedAcceptManageGallery()));
        hasAddedGallery = true;
    }
    switch(buttonDescriptionInt){
        case 0: {
            newGalleryInput->setPlaceholderText("New Gallery Name");
            confirmAddGalleryButton->setText("Add");
            confirmAddGalleryButton->setAccessibleDescription("0");
            break;
        }
        case 1: {
            newGalleryInput->setPlaceholderText("Gallery Name");
            confirmAddGalleryButton->setText("Edit");
            confirmAddGalleryButton->setAccessibleDescription("1");
            break;
        }
        case 2: {
            newGalleryInput->setPlaceholderText("Gallery Name");
            confirmAddGalleryButton->setText("Delete");
            confirmAddGalleryButton->setAccessibleDescription("2");
            break;
        }
        case 3: {
            currentGalleryString  = newGalleryInput->text().toStdString();
            newGalleryInput->setPlaceholderText("New Gallery Name");
            confirmAddGalleryButton->setText("Change");
            confirmAddGalleryButton->setAccessibleDescription("3");
            break;
        }
        case 4: {
            currentGalleryString  = newGalleryInput->text().toStdString();
            newGalleryInput->setPlaceholderText("New Image Name");
            confirmAddGalleryButton->setText("Add");
            confirmAddGalleryButton->setAccessibleDescription("4");
            break;
        }
        case 5: {
            currentGalleryString  = newGalleryInput->text().toStdString();
            newGalleryInput->setPlaceholderText("Image Name");
            confirmAddGalleryButton->setText("Delete");
            confirmAddGalleryButton->setAccessibleDescription("5");
            break;
        }
    }
    addToWindow(newGalleryInput);
    addToWindow(confirmAddGalleryButton);
}

void Interface::clickedAcceptManageGallery() {
    string objectName  = newGalleryInput->text().toStdString();
    auto * buttonSender = qobject_cast<QPushButton*>(sender());
    QString buttonDescription = buttonSender->accessibleDescription();
    int buttonDescriptionInt = stoi(buttonDescription.toStdString());
    switch(buttonDescriptionInt) {
        case 0: {
            // ADD GALLERY
            successfulGalleryManagement = dbHandler->addGalleryToUserDb(objectName);
            if (successfulGalleryManagement) {
                cout << "new Gallery: " << objectName << endl;
                noticeLabel->setText("Gallery created successfully! \nReturn to gallery window.");
                noticeLabel->setGeometry(120, 200, 600, 200);
                clearWindow(true);
                noticeLabel->setVisible(true);
            } else {
                noticeLabel->setText("ERROR: Could not create gallery.");
                noticeLabel->setGeometry(170, 420, 500, 100);
                noticeLabel->setVisible(true);
            }
            break;
        }
        case 1: {
            // EDIT GALLERY
            editGalleryWindow();
            break;
        }
        case 2: {
            // DELETE GALLERY
            successfulGalleryManagement = dbHandler->deleteGalleryFromUserDb(objectName, true);
            if (successfulGalleryManagement) {
                cout << "Gallery deleted: " << objectName << endl;
                noticeLabel->setText("Gallery deleted successfully! \nReturn to gallery window.");
                noticeLabel->setGeometry(120, 200, 600, 200);
                clearWindow(true);
                noticeLabel->setVisible(true);
            } else {
                noticeLabel->setText("ERROR: Could not delete objectName.");
                noticeLabel->setGeometry(170, 420, 500, 100);
                noticeLabel->setVisible(true);
            }
            break;
        }
        case 3: {
            // CHANGE GALLERY NAME
            successfulGalleryManagement = dbHandler->editGalleryFromUserDb(currentGalleryString, objectName);
            if (successfulGalleryManagement) {
                cout << "new Gallery name: " << objectName << endl;
                noticeLabel->setText("Gallery name changed successfully! \nReturn to gallery window.");
                noticeLabel->setGeometry(120, 200, 600, 200);
                clearWindow(true);
                noticeLabel->setVisible(true);
            } else {
                noticeLabel->setText("ERROR: Could not change name.");
                noticeLabel->setGeometry(170, 420, 500, 100);
                noticeLabel->setVisible(true);
            }
            break;
        }
        case 4: {
            // ADD IMAGE TO USER GALLERY
            successfulGalleryManagement = dbHandler->addImageToUserGalleryDb(objectName, currentGalleryString);
            if (successfulGalleryManagement) {
                cout << "new Image: " << objectName << endl;
                noticeLabel->setText("Image created successfully! \n Return to gallery window.");
                noticeLabel->setGeometry(120, 200, 600, 200);
                clearWindow(true);
                noticeLabel->setVisible(true);
            } else {
                noticeLabel->setText("ERROR: Could not create image.");
                noticeLabel->setGeometry(170, 420, 500, 100);
                noticeLabel->setVisible(true);
            }
            break;
        }
        case 5: {
            // DELETE IMAGE FROM USER GALLERY
            successfulGalleryManagement = dbHandler->deleteImageFromUserGalleryDb(objectName, currentGalleryString);
            if (successfulGalleryManagement) {
                cout << "deleted Image: " << objectName << endl;
                noticeLabel->setText("Image deleted successfully! \nReturn to gallery window.");
                noticeLabel->setGeometry(120, 200, 600, 200);
                clearWindow(true);
                noticeLabel->setVisible(true);

            } else {
                noticeLabel->setText("ERROR: Could not delete image.");
                noticeLabel->setGeometry(170, 420, 500, 100);
                noticeLabel->setVisible(true);
            }
            break;
        }
    }
}

void Interface::editGalleryWindow() {
    clearWindow(true);
    if (!hasEdited){
        editGalleryNameButton = new QPushButton(this);
        editGalleryNameButton->setAccessibleDescription("3");
        createButton(editGalleryNameButton, "Edit Name", 230, 150, 400, 70);
        connect(editGalleryNameButton, SIGNAL(clicked()), this, SLOT(clickedManageGallery()));

        addImageButton = new QPushButton(this);
        addImageButton->setAccessibleDescription("4");
        createButton(addImageButton, "Add Image", 230, 300, 400, 70);
        connect(addImageButton, SIGNAL(clicked()), this, SLOT(clickedManageGallery()));

        deleteImageButton = new QPushButton(this);
        deleteImageButton->setAccessibleDescription("5");
        createButton(deleteImageButton, "Delete Image", 230, 450, 400, 70);
        connect(deleteImageButton, SIGNAL(clicked()), this, SLOT(clickedManageGallery()));
        hasEdited = true;
    }
    addToWindow(editGalleryNameButton);
    addToWindow(addImageButton);
    addToWindow(deleteImageButton);

}

void Interface::addExistingGalleriesToGalleryWindow() {
    vector<string> currentGalleryNames = dbHandler->retrieveAllUserGalleries();
    int height = 170;
    for(const string& galleryName : currentGalleryNames){
        QString qGalleryName = QString::fromStdString(galleryName);
        auto * galleryButton = new QPushButton(this);
        createButton(galleryButton, qGalleryName, 30, height, 790, 50);
        addToWindow(galleryButton);
        connect(galleryButton, SIGNAL(clicked()), this, SLOT(clickedGallery()));
        height = height + 70;
    }

}

void Interface::clickedGallery() {


    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    currentGallery = buttonSender->text();
    currentGalleryString = currentGallery.toStdString();
    qDebug() << currentGallery;
    if (!dbHandler->retrieveAllImagesFromUserGallery(currentGalleryString).empty()){
        clearWindow(true);
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
}

// MANAGE IMAGES

void Interface::clickedPreviousImage() {
    clearWindow(true);
    currentImageIndex--;
    if (currentImageIndex < 0){
        currentImageIndex = currentImages.size() - 1;
    }
    currentImageName = QString::fromStdString(currentImages.at(currentImageIndex));
    vector<string> imageMetadata = dbHandler->retrieveImageMetadata(currentImages.at(currentImageIndex), currentGalleryString);
    imagePath = QString::fromStdString(imageMetadata.at(5));
    imageWindow();
}

void Interface::clickedNextImage() {
    clearWindow(true);
    currentImageIndex++;
    if (currentImageIndex >= currentImages.size()){
        currentImageIndex = 0;
    }
    if (currentImageIndex < 0){
        currentImageIndex = currentImages.size() - 1;
    }
    currentImageName = QString::fromStdString(currentImages.at(currentImageIndex));
    vector<string> imageMetadata = dbHandler->retrieveImageMetadata(currentImages.at(currentImageIndex), currentGalleryString);
    imagePath = QString::fromStdString(imageMetadata.at(5));
    imageWindow();

}

void Interface::addExistingImagesFromGallery() {
    //aqui se displayea la imagen cargada del db

    auto *buttonSender = qobject_cast<QPushButton *>(sender());
    QString buttonText = buttonSender->text();
    string gallery = buttonText.toStdString();
    currentImageIndex == 0;
    currentImages.clear();
    currentImages = dbHandler->retrieveAllImagesFromUserGallery(gallery);
    vector<string> imageMetadata = dbHandler->retrieveImageMetadata(currentImages.at(currentImageIndex), currentGalleryString);
    imagePath = QString::fromStdString(imageMetadata.at(5));
}

void Interface::clickedSelectPicButton() {
    imagePath = "";
    imagePath = QFileDialog::getOpenFileName(this, "Select image", "");

    // AQUI COMPRIMIR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if (QString::compare(imagePath, QString()) != 0){
        QImage imageToDisplay;
        bool successfulLoad = imageToDisplay.load(imagePath);
        if (successfulLoad){
            cout << "image: " << imagePath.toStdString() << endl;
            dbHandler->editImageMetadata(currentImages.at(currentImageIndex), currentGalleryString, "imagePath", imagePath.toStdString());

        } else {
            cout << "Could not upload image." << endl;
        }
    } else {
        cout << "Could not upload image." << endl;
    }

} // COMPRIMIR !!!!!!!!!!!!!!!!!!!!

void Interface::displayImage() {
    // AQUI !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!, quitar el de abajo
    imagePictureLabel = new QLabel(this);
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if (QString::compare(imagePath, QString()) != 0){
        QPixmap img(imagePath);

        imagePictureLabel->setPixmap(img.scaled(300, 300, Qt::KeepAspectRatio));
        addToWindow(imagePictureLabel);
        imagePictureLabel->setGeometry(280, 190, 300, 300);

        dbHandler->retrieveAllImagesFromUserGallery(currentGalleryString);

    } else {
        cout << "No image to load." << endl;
        imagePictureLabel->setVisible(false);
    }
} // DESCOMPRMIR !!!!!!!!!!!!!!!!!!!!!!


// MANAGE METADATA

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
            string toEdit  = imageNameInput->text().toStdString();
            currentImageName = imageNameInput->text();
            bool edited = dbHandler->editImageMetadata(currentImages.at(currentImageIndex), currentGalleryString, "imageName", toEdit);
            if (edited) {
                imageNameLabel->setText("Name: " + currentImageName);
            }
            remove(currentWidgets.begin(), currentWidgets.end(), imageNameInput);
            break;
        }
        case 1: {
            imageAuthorInput->setVisible(false);
            string toEdit  = imageAuthorInput->text().toStdString();
            imageAuthor = imageAuthorInput->text();
            bool edited = dbHandler->editImageMetadata(currentImages.at(currentImageIndex), currentGalleryString, "imageAuthor", toEdit);
            if (edited) {
                imageAuthorLabel->setText("Author: " + imageAuthor);
            }
            remove(currentWidgets.begin(), currentWidgets.end(), imageAuthorInput);
            break;
        }
        case 2: {
            imageYearInput->setVisible(false);
            string toEdit  = imageYearInput->text().toStdString();
            imageYear = imageYearInput->text();
            bool edited = dbHandler->editImageMetadata(currentImages.at(currentImageIndex), currentGalleryString, "imageYear", toEdit);
            if (edited) {
                imageYearLabel->setText("Year: " + imageYear);
            }
            remove(currentWidgets.begin(), currentWidgets.end(), imageYearInput);
            break;
        }
        case 3: {
            imageSizeInput->setVisible(false);
            string toEdit  = imageSizeInput->text().toStdString();
            imageSize = imageSizeInput->text();
            bool edited = dbHandler->editImageMetadata(currentImages.at(currentImageIndex), currentGalleryString, "imageSize", toEdit);
            if (edited) {
                imageSizeLabel->setText("Size: " + imageSize);
            }
            remove(currentWidgets.begin(), currentWidgets.end(), imageSizeInput);
            break;
        }
        case 4: {
            imageDescriptionInput->setVisible(false);
            string toEdit  = imageDescriptionInput->text().toStdString();
            imageDescription = imageDescriptionInput->text();
            bool edited = dbHandler->editImageMetadata(currentImages.at(currentImageIndex), currentGalleryString, "imageDesc", toEdit);
            if (edited) {
                imageDescriptionLabel->setText("Desc: " + imageDescription);
            }
            remove(currentWidgets.begin(), currentWidgets.end(), imageDescriptionInput);
            break;
        }
    }
}


// MANAGE WIDGETS

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
            currentImages.clear();
            createdImageVector = false;
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











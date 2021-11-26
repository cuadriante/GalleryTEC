#include "RaidManager.h"

raidManager::raidManager() {
    setFileLocation();
    parityBlock = 5;
}

void raidManager::addNewImage(string data, string newImgID, pt::ptree dict) {
    setImageId(newImgID);
    disk = 1;

    setFileLocation();
    pt::read_json(fileLocation, root);

    try {
        string test = root.get<string>(imageID + ".code");
        cout << "Image is already saved" << endl;
    } catch (boost::property_tree::ptree_bad_path err) {
        write(data, newImgID, dict);
    }
}

void raidManager::getDictionary(pt::ptree &dictionary, string imgID) {
    setImageId(imgID);
    disk = 1;
    setFileLocation();

    pt::read_json(fileLocation, root);
    dictionary.put_child("1", root.get_child(imageID + ".dictionary"));
}

string raidManager::getCode(string imgID) {
    bool recovering = false;
    setImageId(imgID);
    int counter = 1;
    disk = 1;
    int prueba = 0;


    while (counter < 5) {
        setFileLocation();
        prueba = disk;
        pt::read_json(fileLocation, root);
        cout << disk << endl;
        try {
            if (root.get<bool>(imageID + ".parity") == 0) {
                tempCode = root.get<string>(imageID + ".code");

                if (root.get<int>(imageID + ".length" + to_string(disk)) != tempCode.length()) {
                    deleteExtraBit(tempCode);
                }
                completeCode += tempCode;
                counter ++;
            }
        } catch (boost::property_tree::ptree_bad_path err) {
            cout << "Some data is missing" << endl;
            cout << "System is trying to recover the lost data" << endl;
            checkForRecover(imageID);
            recovering = true;
            break;
        }

        disk++;
        if (disk > 5) {
            disk = 1;
        }
    }

    if (recovering) {
        return completeCode;
    } else {
        cout << "A restart is necessary to work properly" << endl;
        return 0;
    }
}

int raidManager::setNextID() {
    int counter = 1;
    checkForRecover(to_string(counter));
    disk = 1;
    setFileLocation();
    string prueba = "";
    bool flag = true;

    root.clear();

    pt::read_json(fileLocation, root);

    while (flag) {
        try {
            prueba = root.get<string>(to_string(counter) + ".code");
            counter++;
        } catch (boost::property_tree::ptree_bad_path err) {
            return counter;
            flag = false;
        }

    }
}

void raidManager::write(string data, string newImgID, pt::ptree dict) {
    setCompleteCode(data);
    codeSplitter();
    applyXOR();

    setLength();

//    dictionary.put("", dict);

    disk = 1;

    while(disk < 6) {
        setFileLocation();
        pt::read_json(fileLocation, root);

        code_1.put("", code1);
        code_2.put("", code2);
        code_3.put("", code3);
        code_4.put("", code4);
        code_5.put("", code5);

        if (disk == 1) {
            newImage.push_back(make_pair("code", code_1));
        } else if (disk == 2) {
            newImage.push_back(make_pair("code", code_2));
        } else if (disk == 3) {
            newImage.push_back(make_pair("code", code_3));
        } else if (disk == 4) {
            newImage.push_back(make_pair("code", code_4));
        } else if (disk == 5) {
            newImage.push_back(make_pair("code", code_5));

        }

        if (parityBlock == disk) {
            parity.put("", true);
        } else {
            parity.put("", false);
        }


        newImage.push_back(make_pair("dictionary", dict));
        newImage.push_back(make_pair("parity", parity));
        newImage.push_back(make_pair("length1", length1));
        newImage.push_back(make_pair("length2", length2));
        newImage.push_back(make_pair("length3", length3));
        newImage.push_back(make_pair("length4", length4));
        newImage.push_back(make_pair("length5", length5));

        root.add_child(newImgID, newImage);

        newImage.clear();

        disk++;
        boost::property_tree::json_parser::write_json(fileLocation, root);

        root.clear();

    }

    parityBlock++;
    if (parityBlock > 5) {
        parityBlock = 1;
    }

    cout << "Image saved successfully" << endl;


}

void raidManager::applyXOR() {
    string newCode = "";
    string tempCode = "";
    int lastBlock = 0;

    if (parityBlock != 1 && parityBlock != 2) {
        newCode = xorAlgorithm(code1, code2);
        lastBlock = 2;
    } else if (parityBlock != 2 && parityBlock != 3) {
        newCode = xorAlgorithm(code2, code3);
        lastBlock = 3;
    } else if (parityBlock != 1 && parityBlock != 3) {
        newCode = xorAlgorithm(code1, code3);
        lastBlock = 3;
    }

    tempCode = newCode;

    if (parityBlock != 3 && lastBlock == 2) {
        newCode = xorAlgorithm(code3, tempCode);
        tempCode = newCode;
    }
    if (parityBlock != 4) {
        newCode = xorAlgorithm(code4, tempCode);
        tempCode = newCode;
    }
    if (parityBlock != 5) {
        newCode = xorAlgorithm(code5, tempCode);
    }

    if (parityBlock == 1) {
        code1 = newCode;
    } if (parityBlock == 2) {
        code2 = newCode;
    } if (parityBlock == 3) {
        code3 = newCode;
    } if (parityBlock == 4) {
        code4 = newCode;
    } if (parityBlock == 5) {
        code5 = newCode;
    }
}

string raidManager::xorAlgorithm(string firstCode, string secondCode) {
    string finalCode = "";

    for (int i = 0; i < firstCode.length(); ++i) {
        if (firstCode[i] == secondCode[i]) {
            finalCode += "0";
        } else {
            finalCode += "1";
        }
    }

    return finalCode;
}

void raidManager::checkForRecover(string imgID) {
    int failingDisks = 0;
    int diskToCheck = 0;
    setImageId(imgID);
    disk = 1;

    while (disk < 6) {
        setFileLocation();
        pt::read_json(fileLocation, root);

        try {
            string test = root.get<string>(imageID + ".code");
        } catch (boost::property_tree::ptree_bad_path err) {
            failingDisks++;
            diskToCheck = disk;
        }

        disk++;
    }

    if (failingDisks == 0) {
        cout << "All disks working ok" << endl;
    } else if (failingDisks == 1) {
        recoverDisk(diskToCheck);
    } else if (failingDisks > 1) {
        cout << "Disks damaged, the recovery system is uncapable to solved it";
    }

}

void raidManager::recoverDisk(int diskToCheck) {
    int checker = 1;
    bool flag = true;
    isParity = false;
    int realParity = diskToCheck;
    parityBlock = diskToCheck;
    int curr_disk = 1;
    string a, b, c, d, e;

    while (flag) {
        disk = 1;

        try {
            while (disk < 6) {
                newImage.clear();
                setFileLocation();

                pt::read_json(fileLocation, root);
                setImageId(to_string(checker));
                if (disk == 1 && disk != diskToCheck) {
                    code1 = root.get<string>(imageID + ".code");
                    a = code1;
                } else if (disk == 2 && disk != diskToCheck) {
                    code2 = root.get<string>(imageID + ".code");
                    b = code2;
                } else if (disk == 3 && disk != diskToCheck) {
                    code3 = root.get<string>(imageID + ".code");
                    c = code3;
                } else if (disk == 4 && disk != diskToCheck) {
                    code4 = root.get<string>(imageID + ".code");
                    d = code4;
                } else if (disk == 5 && disk != diskToCheck) {
                    code5 = root.get<string>(imageID + ".code");
                    e = code5;
                }

                if (disk != diskToCheck) {
                    isParity = root.get<bool>(imageID + ".parity") == 1;
                    if (isParity) {
                        realParity = disk;
                    }


                }
                disk++;
            }

            applyXOR();
            parityBlock = realParity;
            curr_disk = disk;
            recoverySave(diskToCheck);
            disk = curr_disk;
            checker++;
            parityBlock = diskToCheck;
            realParity = diskToCheck;
//            cout << imageID << endl;

        } catch (boost::property_tree::ptree_bad_path err) {
            parityBlock = realParity;
            cout << "Recovery finished" << endl;
            flag = false;
            break;
        }
    }
}


void raidManager::recoverySave(int diskToCheck) {
    disk = diskToCheck;
    int baseDisk = diskToCheck - 1;
    pt::ptree base, subBase;

    if (diskToCheck == 1) {
        baseDisk = 5;
    }

    setFileLocation();

    pt::read_json(fileLocation, root);
    pt::read_json("RAIDStorage/Disk" + to_string(baseDisk) + "/data.json", base);
    subBase.put_child("1", base.get_child(imageID));
//    cout << subBase.get<string>("1.code") << endl;

    if (disk == 1) {
        code_1.put("", code1);
        newImage.push_back(make_pair("code", code_1));
    } else if (disk == 2) {
        code_2.put("", code2);
        newImage.push_back(make_pair("code", code_2));
    } else if (disk == 3) {
        code_3.put("", code3);
        newImage.push_back(make_pair("code", code_3));
    } else if (disk == 4) {
        code_4.put("", code4);
        newImage.push_back(make_pair("code", code_4));
    } else if (disk == 5) {
        code_5.put("", code5);
        newImage.push_back(make_pair("code", code_5));
    }

    if (parityBlock == disk) {
        parity.put("", true);
    } else {
        parity.put("", false);
    }

    newImage.push_back(make_pair("dictionary", subBase.get_child("1.dictionary")));
    newImage.push_back(make_pair("parity", parity));
    newImage.push_back(make_pair("length1", subBase.get_child("1.length1")));
    newImage.push_back(make_pair("length2", subBase.get_child("1.length2")));
    newImage.push_back(make_pair("length3", subBase.get_child("1.length3")));
    newImage.push_back(make_pair("length4", subBase.get_child("1.length4")));
    newImage.push_back(make_pair("length5", subBase.get_child("1.length5")));

    root.add_child(imageID, newImage);

    boost::property_tree::json_parser::write_json(fileLocation, root);

    root.clear();
}

void raidManager::deleteExtraBit(string code) {
    string newCode = "";
    for (int i = 0; i < code.length() - 1; ++i) {
        newCode += code[i];
    }

    tempCode = newCode;
}

void raidManager::codeSplitter() {
    int lack = completeCode.length() % 4;
    int division = (completeCode.length() - lack) / 4;
    int i = 0;
    disk = 1;
    bool extraBit = false;
    string tempCode = "";

    if (lack > 0) {
        division++;
        extraBit = true;
    } else if (lack < 1) {
        lack--;
    }

    while (disk < 6) {
        if (lack == 0) {
            division--;
            lack--;
        }

        if (i < completeCode.length()) {
            for (int j = 0; j < division; ++j) {
                if (parityBlock != disk) {
                    tempCode += completeCode[i];
                    i++;
                }
            }

            if (lack < 1 && extraBit) {
                tempCode += "0";
            }

            if (disk == 1 && parityBlock != 1) {
                code1 = tempCode;
            } else if (disk == 2 && parityBlock != 2) {
                code2 = tempCode;
            } else if (disk == 3 && parityBlock != 3) {
                code3 = tempCode;
            } else if (disk == 4 && parityBlock != 4) {
                code4 = tempCode;
            } else if (disk == 5 && parityBlock != 5) {
                code5 = tempCode;
            }


            if (parityBlock != disk) {
                lack--;
            }

            tempCode = "";


        }

        disk++;


    }
}


void raidManager::setFileLocation() {
    raidManager::fileLocation = "RAIDStorage/Disk" + to_string(disk) + "/data.json";
}

void raidManager::setDisk() {
    raidManager::disk += 1;
    if (raidManager::disk > 5) {
        raidManager::disk = 1;
    }
}

void raidManager::setImageId(const string &imageId) {
    imageID = imageId;
}


void raidManager::setCompleteCode(const string &completeCode) {
    raidManager::completeCode = completeCode;
}

void raidManager::setLength() {
    int lack = completeCode.length() % 4;
    bool extraBit = false;

    if (lack > 0) {
        extraBit = true;
    }

    length1.put("", code1.length());

    if (parityBlock != 1) {
        lack--;
    }

    if (lack < 1 && extraBit) {
        length2.put("", code2.length() - 1);
    } else {
        length2.put("", code2.length());
    }

    if (parityBlock != 2) {
        lack--;
    }

    if (lack < 1 && extraBit) {
        length3.put("", code3.length() - 1);
    } else {
        length3.put("", code3.length());
    }

    if (parityBlock != 3) {
        lack--;
    }
    if (lack < 1 && extraBit) {
        length4.put("", code4.length() - 1);
    } else {
        length4.put("", code4.length());
    }

    if (parityBlock != 4) {
        lack--;
    }

    if (lack < 1 && extraBit) {
        length5.put("", code5.length() - 1);
    } else {
        length5.put("", code5.length());
    }

    lengthTree.push_back(make_pair("length1", length1));
    lengthTree.push_back(make_pair("length2", length2));
    lengthTree.push_back(make_pair("length3", length3));
    lengthTree.push_back(make_pair("length4", length4));
    lengthTree.push_back(make_pair("length5", length5));
}

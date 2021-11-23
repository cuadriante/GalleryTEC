#include "raidManager.h"

raidManager::raidManager() {
    setFileLocation();
}

void raidManager::write(string data, string newImgID) {
    setCompleteCode(data);
    codeSplitter();
    setLenght();

    dictionary.put("", "Hello");

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
//            code.put("", code1);
//            parity.put("", isParity);
            parity.put("", false);
        } else if (disk == 2) {
            newImage.push_back(make_pair("code", code_2));
//            code.put("", code2);
            parity.put("", false);
        } else if (disk == 3) {
            newImage.push_back(make_pair("code", code_3));
//            code.put("", code3);
            parity.put("", false);
        } else if (disk == 4) {
            newImage.push_back(make_pair("code", code_4));
//            code.put("", code4);
            parity.put("", false);
        } else if (disk == 5) {
            newImage.push_back(make_pair("code", code_5));
//            code.put("", "564687956");
            parity.put("", true);
        }

//        newImage.push_back(make_pair("code", code));
        newImage.push_back(make_pair("dictionary", dictionary));
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


}

void raidManager::read(string imgID) {
    setImageId(imgID);
    int counter = 1;
    disk = 1;


    while (counter < 5) {
        setFileLocation();
        pt::read_json(fileLocation, root);
        try {
            if (root.get<bool>(imageID + ".parity") == 0) {
                tempCode = root.get<string>(imageID + ".code");
                cout << tempCode.length() << endl;
//                cout << imageID + "length" + to_string(disk) << endl;
                if (root.get<int>(imageID + ".length" + to_string(disk)) != tempCode.length()) {
                    deleteExtraBit(tempCode);
                }
                completeCode += tempCode;
                counter ++;
            }
        } catch (boost::property_tree::ptree_bad_path err) {
            cout << "Data not found" << endl;
        }

        setDisk();
    }

    cout << completeCode << endl;
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
    cout << lack << endl;
    int i = 0;
    disk = 1;

    if (lack > 0) {
        division ++;
    } else if (lack == 0) {
        lack --;
    }

    while (disk < 6) {
        if (lack == 0) {
            division --;
            lack --;
        }
        if (i < completeCode.length() - 1) {
            for (int j = 0; j < division; ++j) {
                if (disk == 1) {
                    code1 += completeCode[i];
//                    cout << disk << endl;
                } else if (disk == 2) {
                    code2 += completeCode[i];
//                    cout << disk << endl;
                } else if (disk == 3) {
                    code3 += completeCode[i];
//                    cout << disk << endl;
                } else if (disk == 4) {
                    code4 += completeCode[i];
//                    cout << disk << endl;
                } else if (disk == 5) {
                    code5 += completeCode[i];
//                    cout << disk << endl;
                }


                i++;
            }

            lack --;


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

void raidManager::setIsParity(bool isParity) {
    raidManager::isParity = isParity;
}

void raidManager::setCompleteCode(const string &completeCode) {
    raidManager::completeCode = completeCode;
}

void raidManager::setLenght() {
    length1.put("", code1.length());
    length2.put("", code2.length());
    length3.put("", code3.length());
    length4.put("", code4.length());
    length5.put("", code5.length());

    lengthTree.push_back(make_pair("length1", length1));
    lengthTree.push_back(make_pair("length2", length2));
    lengthTree.push_back(make_pair("length3", length3));
    lengthTree.push_back(make_pair("length4", length4));
    lengthTree.push_back(make_pair("length5", length5));
}

#include "dataSetter.h"

dataSetter::dataSetter() {

}

void dataSetter::codeSplitter(string data, string &code1, string &code2, string &code3, string &code4, string &code5, int parityBlock) {
    int lack = data.length() % 4;
    int division = (data.length() - lack) / 4;
    int i = 0;
    int curr_disk = 1;
    bool extraBit = false;
    string tempCode = "";

    if (lack > 0) {
        division ++;
        extraBit = true;
    } else if (lack < 1) {
        lack --;
    }

    while (curr_disk < 6) {
        if (lack == 0) {
            division --;
            lack --;
        }

        if(i < data.length()) {
            for (int j = 0; j < division; ++j) {
                if (parityBlock != curr_disk) {
                    tempCode += data[i];
                    i++;
                }
            }

            if (lack < 1 && extraBit) {
                tempCode += oddParity(tempCode);
            }

            if (curr_disk == 1 && parityBlock != 1) {
                code1 = tempCode;
            } else if (curr_disk == 2 && parityBlock != 2) {
                code2 = tempCode;
            } else if (curr_disk == 3 && parityBlock != 3) {
                code2 = tempCode;
            } else if (curr_disk == 4 && parityBlock != 4) {
                code2 = tempCode;
            } else if (curr_disk == 5 && parityBlock != 5) {
                code2 = tempCode;
            }

            lack--;
        }

        curr_disk++;
    }
}
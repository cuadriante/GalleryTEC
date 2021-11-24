#ifndef GALLERYTEC_DATASETTER_H
#define GALLERYTEC_DATASETTER_H

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
namespace pt = boost::property_tree;

class dataSetter {
public:
    dataSetter();
    void codeSplitter(string data, string &code1, string &code2, string &code3,
                      string &code4, string &code5, int parityBlock);

private:
    string oddParity(string code);


};


#endif

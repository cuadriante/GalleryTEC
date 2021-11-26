//
// Created by eduardo on 15/11/21.
//

#include "Compressor.h"

Compressor::Compressor(vector<TreeNode> pixels) {
    this->nodes = pixels;
    this->tree = new HuffmanBinaryTree(this->nodes);
    this->dictionary = nullptr;
    this->imageCode = "";
}

void Compressor::buildTree() {
    TreeNode parent;
    while (this->tree->getSize() > 1) {
        this->tree->setRoots(Compressor::bubble_sort(this->tree->getRoots()));
        parent.setFrequency(this->tree->getRoots()[0].getFrequency() + this->tree->getRoots()[1].getFrequency());
        parent.setLeftChild(&this->tree->getRoots()[0]);
        parent.setRightChild(&this->tree->getRoots()[1]);
        this->tree->updateTreeRoots(parent);
    }
}

void Compressor::createDictionary() {
    this->dictionary = new Dictionary();
    string code = "";
    TreeNode current = this->tree->getRoot();
    int iterations = this->nodes.size();
    TreeNode previous;
    while (iterations > 0) {
        if (current.getLeftChild() != nullptr && !current.getLeftChild()->isVisited()) {
            code.push_back('0');
            current = *current.getLeftChild();
        }
        else if (current.getRightChild() != nullptr && !current.getRightChild()->isVisited()) {
            code.push_back('1');
            current = *current.getRightChild();
        }
        else if (current.getLeftChild() == nullptr && current.getRightChild() == nullptr) {
            this->dictionary->addElement(current.getData(), code);
            current.visit();
            current = previous;
        }
        iterations--;
    }
}

pair<string,ptree> Compressor::compress() {
    this->buildTree();
    this->createDictionary();
    for (TreeNode node : this->nodes) {
        for (pair<Vec3b, string> pair : this->dictionary->getElements()) {
            if (node.getData() == pair.first) {
                this->imageCode.append(pair.second);
                continue;
            }
            cout << imageCode << endl;
        }
    }
    ptree head = this->dictionary->generateJSON();
    return make_pair(imageCode, head);
}

vector<TreeNode> Compressor::decompress(string coding) {
    vector<TreeNode> imagePixels = this->dictionary->readJSON(coding, this->dictionary);
    delete this->tree;
    delete this->dictionary;
    return imagePixels;
}

vector<TreeNode> Compressor::bubble_sort(vector<TreeNode> list) {
    int count = int (list.size());
    while (count > 0) {
        for (int i = 0; i < count - 1; i++) {
            if (list[i].getFrequency() > list[i+1].getFrequency()) {
                TreeNode temp = list[i];
                list[i] = list[i+1];
                list[i+1] = temp;
            }
        }
        count--;
    }
    return list;
}
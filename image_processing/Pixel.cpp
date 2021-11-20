//
// Created by eduardo on 20/11/21.
//

#include "Pixel.h"


int Pixel::getProbability() const {
    return this->probability;
}

void Pixel::setProbability(int prob) {
    this->probability = prob;
}

Vec3b Pixel::getColor() {
    return this->color;
}

void Pixel::setColor(Vec3b color1) {
    this->color = color1;
}
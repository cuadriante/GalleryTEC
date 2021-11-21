//
// Created by eduardo on 20/11/21.
//

#include "Pixel.h"

Pixel::Pixel(Vec3b color, int prob) {
    this->color = color;
    this->probability = prob;
}

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
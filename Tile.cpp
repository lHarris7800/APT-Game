
#include "Tile.h"

Tile::Tile (Colour colour, Shape shape){
    this->colour = colour;
    this->shape = shape;
}

Tile::Tile(Tile& original){
    colour = original.colour;
    shape = original.shape;
}

Colour Tile::getColour() const {
    return colour;
}

Shape Tile::getShape() const {
    return shape;
}

std::string Tile::getTileName() {
    return std::string(colour + std::to_string(shape));
}
 
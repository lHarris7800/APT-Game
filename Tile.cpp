#include "Tile.h"

Tile::Tile (Colour colour, Shape shape){
    this->colour = colour;
    this->shape = shape;
}

Tile::Tile(Tile& original){
    colour = original.colour;
    shape = original.shape;
}

Tile::Tile(std::string tileName){
    colour = tileName[0];
    shape = tileName[1]-'0';
}

std::string Tile::getTileName() {
    return std::string(colour + std::to_string(shape));
}
 
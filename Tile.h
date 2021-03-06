
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
   Tile(Colour,Shape);

   Tile(Tile& original);

   Tile(std::string name);
   
   std::string getTileName();

   Colour colour;
   Shape  shape;
};

#endif // ASSIGN2_TILE_H

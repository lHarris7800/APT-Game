#include "Action.h"
#include "Tile.h"

class PlaceTileAction : public Action{
public:

    PlaceTileAction(Tile* playedTile, std::string boardLocation);

    ~PlaceTileAction();

    void doAction(Bag* bag, Board* board,Player* player);
    void undoAction(Bag* bag, Board* board,Player* player);

private:
    Tile* playedTile;
    Tile* newTile;
    std::string boardLocation;
};


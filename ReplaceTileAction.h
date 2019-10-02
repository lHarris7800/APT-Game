#include "Action.h"
#include "Tile.h"

class ReplaceTileAction : public Action{
public:

    ReplaceTileAction(Tile* replacedTile);

    ~ReplaceTileAction();

    void doAction(Bag* bag, Board* board,Player* player);
    void undoAction(Bag* bag, Board* board,Player* player);

private:
    Tile* replacedTile;
    Tile* newTile;
};
/***************************************
 * Created 10/13/2026                  *
 * Last Edited 10/20/2026              *
 * Implementation for tiling functions *
 ***************************************/

#include "tile.h"

#include <cmath>


void BasicTiling(std::vector<Tile> & tiles, float scalar, int32_t screen_width, int32_t screen_height)
{
    // empty the tile list just in case :)
    tiles = {};

    // initialize a tile that will be copied to complete the tiling 
    Tile BaseTile = SquareTile();
    BaseTile.Translate({0.5,0.5});
    // tile now has side lengths `scalar` * `scalar`, 
    // since the `SquareTile` function returns a tile with side lenghts of 1
    BaseTile.Scale(scalar);

    // get number of tiles to be placed in each direction 
    const int32_t NUM_TILES_X = ceil((float)screen_width / scalar);
    const int32_t NUM_TILES_Y = ceil((float)screen_height / scalar);

    // insert tiles into list of tiles 
    for (int32_t i = 0; i < NUM_TILES_X; ++i)
    {
        for (int32_t j = 0; j < NUM_TILES_Y; ++j)
        {
            Tile temp(BaseTile); 
            temp.Translate({i * scalar, j * scalar});

            tiles.push_back(temp);
        }
    }
}
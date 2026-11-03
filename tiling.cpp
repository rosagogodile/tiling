/***************************************
 * Created 10/13/2026                  *
 * Last Edited 11/3/2026               *
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


void DiamondTiling(std::vector<Tile> & tiles, float scalar, int32_t screen_width, int32_t screen_height)
{
    // empty the tile list just in case :3 
    tiles = {};

    // initialize the tile 
    Tile BaseTile = SquareTile();
    // BaseTile.Scale(scalar);
    // Note: We want to scale the diagonal
    const float DIAGONAL_SCALAR = scalar / sqrt(2);
    BaseTile.Scale(DIAGONAL_SCALAR);
    BaseTile.Rotate(0.7853982); // 45 degree rotation 

    // const float DIAGONAL = sqrt(2) * scalar;
    const float DIAGONAL = scalar;

    const int32_t NUM_TILES_X = ceil((float)screen_width / DIAGONAL);
    const int32_t NUM_TILES_Y = ceil((float)screen_height / DIAGONAL);

    // slap tiles into list of tiles 
    for (int32_t i = 0; i <= NUM_TILES_X; ++i)
    {
        for (int32_t j = 0; j <= NUM_TILES_Y * 2; ++j)
        {
            Tile temp(BaseTile);

            // odd tiles are placed on an offset 
            // even tiles don't have this offset 
            temp.Translate({(i * DIAGONAL) + (DIAGONAL / 2 * (j % 2 == 1)), j * DIAGONAL / 2});

            tiles.push_back(temp);
        }
    }
}
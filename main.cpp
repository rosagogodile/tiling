/***************************************
 * Created 10/12/2026                  *
 * Last Edited 11/3/2026               *
 * Code that renders the tiling        *
 ***************************************/

#include <iostream>
#include "tile.h"
#include "colorlut.h"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500 

using namespace std;

int main(int argc, char ** argv)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "tiling experiment");
    cout << "q                          Save Tiling To File.\n";
    SetTargetFPS(60);

    // initialize vector that stores each tile 
    vector<Tile> tiles; 

    // function call that generates the tiling
    DiamondTiling(tiles, 60, SCREEN_WIDTH, SCREEN_HEIGHT);

    ColorLut lut;
    lut.append({160,217,153,255});
    lut.append({25,165,85,255});
    lut.append({50,155,125,255});
    lut.append({35,120,160,255});
    lut.append({25,35,185,255});

    Image tiling = GenImageColor(SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    DrawTiling(&tiling, tiles, lut, SCREEN_WIDTH, SCREEN_HEIGHT);

    Texture2D tilingtexture = LoadTextureFromImage(tiling);

    while (!WindowShouldClose())
    {
        // save original image to file 
        if (IsKeyPressed(KEY_Q))
        {
            ExportImage(tiling, "original_tiling.png");
        }


        BeginDrawing();
            ClearBackground(WHITE);

            DrawTexture(tilingtexture, 0, 0, WHITE);

        EndDrawing();
    }

    CloseWindow();

    UnloadImage(tiling);
    UnloadTexture(tilingtexture);

    return 0;
}
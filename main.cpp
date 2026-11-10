/***************************************
 * Created 10/12/2026                  *
 * Last Edited 11/10/2026              *
 * Code that renders the tiling        *
 ***************************************/

#include <iostream>
#include "tile.h"
#include "colorlut.h"
#include "stereographic_projection.h"

#define IMG_WIDTH 3840
#define IMG_HEIGHT 3840

#define SCALE 8

#define SCREEN_WIDTH IMG_WIDTH / SCALE
#define SCREEN_HEIGHT IMG_HEIGHT / SCALE

using namespace std;

void PrintKeyboardCommands();

int main(int argc, char ** argv)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "tiling experiment");
    SetTargetFPS(60);

    // initialize vector that stores each tile 
    vector<Tile> tiles; 

    // function call that generates the tiling
    DiamondTiling(tiles, 60 * SCALE, IMG_WIDTH, IMG_HEIGHT);

    ColorLut lut;
    // lut.append({160,217,153,255});
    // lut.append({25,165,85,255});
    // lut.append({50,155,125,255});
    // lut.append({35,120,160,255});
    // lut.append({25,35,185,255});
    // lut.append({35,120,160,255});
    // lut.append({50,155,125,255});
    // lut.append({25,165,85,255});
    // lut.append({160,217,153,255});
    lut.append({250, 150, 150, 255});
    lut.append({25, 0, 6, 255});
    lut.append({250, 150, 150, 255});

    Image tiling = GenImageColor(IMG_WIDTH, IMG_HEIGHT, WHITE);
    DrawTiling(&tiling, tiles, lut);

    Texture2D tilingtexture = LoadTextureFromImage(tiling);

    PrintKeyboardCommands();

    while (!WindowShouldClose())
    {
        // save original image to file 
        if (IsKeyPressed(KEY_Q))
        {
            ExportImage(tiling, "original_tiling.png");
        }

        // stereographic transform
        if (IsKeyPressed(KEY_ONE))
        {
            Image out = GenImageColor(IMG_WIDTH, IMG_HEIGHT, {0,67,0,255});
            StereographicTransform(tiling, &out, IMG_WIDTH, IMG_HEIGHT, IMG_WIDTH, IMG_HEIGHT);
            UnloadImage(tiling);
            tiling = ImageCopy(out);
            UnloadImage(out);
            UnloadTexture(tilingtexture);
            tilingtexture = LoadTextureFromImage(tiling);
        }


        BeginDrawing();
            ClearBackground(WHITE);

            DrawTextureEx(tilingtexture, {0, 0}, 0.0, 1.0 / SCALE, WHITE);

        EndDrawing();
    }

    CloseWindow();

    UnloadImage(tiling);
    UnloadTexture(tilingtexture);

    return 0;
}


void PrintKeyboardCommands()
{
    cout << "\n\n\n";
    cout << "---------------------------------------------------\n";
    cout << "| q                          Save Tiling To File. |\n";
    cout << "| 1                     Stereographic Projection. |\n";
    cout << "---------------------------------------------------\n";
}
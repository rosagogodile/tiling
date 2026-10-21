/***************************************
 * Created 10/12/2026                  *
 * Last Edited 10/13/2026              *
 * Code that renders the tiling        *
 ***************************************/

#include <iostream>
#include "tile.h"

#define SCREEN_WIDTH 750
#define SCREEN_HEIGHT 500 

using namespace std;

int main(int argc, char ** argv)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "tiling experiment");
    SetTargetFPS(60);

    // initialize vector that stores each tile 
    vector<Tile> tiles; 

    // function call that generates the tiling
    BasicTiling(tiles, 50.0, SCREEN_WIDTH, SCREEN_HEIGHT);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(WHITE);

            // draw each tile
            for (const auto & t : tiles)
            {
                vector<Edge> edges = t.GetEdges();
                for (const auto & e : edges)
                    DrawLineEx(e.p1, e.p2, 1, BLACK);
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
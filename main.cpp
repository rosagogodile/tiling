/***************************************
 * Created 10/12/2026                  *
 * Last Edited 10/27/2026              *
 * Code that renders the tiling        *
 ***************************************/

#include <iostream>
#include "tile.h"
#include "colorlut.h"

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

    ColorLut lut;
    lut.append({0,255,0,255});
    lut.append({0,175,155,255});
    lut.append({0,0,255,255});

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(WHITE);

            int32_t count = 0;

            // draw each tile
            for (const auto & t : tiles)
            {
                // vector<Edge> edges = t.GetEdges();
                // for (const auto & e : edges)
                //     DrawLineEx(e.p1, e.p2, 1, BLACK);

                vector<Triangle> triangles = t.GetTriangulation();

                // get interpolated color
                const double interpolation_value = ((double)count / lut.GetSize()) * triangles.size();
                Color c = lut(interpolation_value);
                // Color c = lut[count];

                // draw triangles
                for (const auto & tr : triangles)
                {
                    DrawTriangle(tr.p1, tr.p2, tr.p3, c);
                }

                count++;
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
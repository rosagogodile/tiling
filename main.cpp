/***************************************
 * Created 10/12/2026                  *
 * Last Edited 10/27/2026              *
 * Code that renders the tiling        *
 ***************************************/

#include <iostream>
#include "tile.h"
#include "colorlut.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600 

using namespace std;

int main(int argc, char ** argv)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "tiling experiment");
    SetTargetFPS(60);

    // initialize vector that stores each tile 
    vector<Tile> tiles; 

    // function call that generates the tiling
    BasicTiling(tiles, 30, SCREEN_WIDTH, SCREEN_HEIGHT);

    ColorLut lut;
    lut.append({10,185,25,255});
    lut.append({25,165,85,255});
    lut.append({50,155,125,255});
    lut.append({35,120,160,255});
    lut.append({25,35,185,255});

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(WHITE);

            double count = 0.0;

            const double INTERPOLATE_MAX = (double)lut.GetSize() - 1;
            const double ITERATION_VALUE = INTERPOLATE_MAX / (double)tiles.size();

            // draw each tile
            for (const auto & t : tiles)
            {
                // vector<Edge> edges = t.GetEdges();
                // for (const auto & e : edges)
                //     DrawLineEx(e.p1, e.p2, 1, BLACK);

                vector<Triangle> triangles = t.GetTriangulation();

                // get interpolated color
                // const double interpolation_value = ((double)count / lut.GetSize()) * triangles.size();
                // const double interpolation_value = (double)count * (double)lut.GetSize() / (double)tiles.size();
                const double interpolation_value = count;
                Color c = lut(interpolation_value);

                // draw triangles
                for (const auto & tr : triangles)
                {
                    DrawTriangle(tr.p1, tr.p2, tr.p3, c);
                }

                count += ITERATION_VALUE;
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
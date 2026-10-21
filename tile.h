/***************************************
 * Created 10/12/2026                  *
 * Last Edited 10/20/2026              *
 * Classes that define a tile          *
 ***************************************/

#include <vector>
#include "raylib.h"
#include "raymath.h"
#include <cstdint>
#include <iostream>


// TODO:
// Add a function that draws the tile directly 
// will need to consider this: https://en.wikipedia.org/wiki/Polygon_triangulation
// consider this additionally, for if i wish to texture the tiles:
// https://www.raylib.com/examples/textures/loader.html?name=textures_polygon_drawing


struct Edge 
{
    Vector2 p1;
    Vector2 p2;
};

class Tile 
{
    public:
        Tile(std::vector<Edge> e, Vector2 c);
        // copy constructor 
        Tile(const Tile & rhs);

        void Translate(Vector2 vt);
        void Rotate(float a);
        void Scale(float s);

        void SetColor(Color c)
            { tilecolor = c; }

        std::vector<Edge> GetEdges() const
            { return edgelist; }

        // returns a copy of the center 
        Vector2 GetCenter() const 
            { return {center.x, center.y}; }

        Color GetColor(Color c) const 
            { return tilecolor; }

        // function used for testing, prints the nth edge of the tile 
        void PrintEdge(int32_t n) const;

    private:
        std::vector<Edge> edgelist;
        Vector2 center = {0.0,0.0}; 
        Color tilecolor = WHITE;
};

// returns a unit square centered at (0,0)
Tile SquareTile();

// FUNCTIONS THAT GENERATE TILINGS 

// generates a tiling using a square
// note: `scalar` ideally should divide `screen_width` and `screen_height`
void BasicTiling(std::vector<Tile> & tiles, float scalar, int32_t screen_width, int32_t screen_height);
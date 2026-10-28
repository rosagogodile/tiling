/***************************************
 * Created 10/12/2026                  *
 * Last Edited 10/27/2026              *
 * Classes that define a tile          *
 ***************************************/

#ifndef TILE_H
#define TILE_H

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


struct Triangle 
{
    Vector2 p1;
    Vector2 p2;
    Vector2 p3;
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

        std::vector<Edge> GetEdges() const
            { return edgelist; }

        // returns a copy of the center 
        Vector2 GetCenter() const 
            { return {center.x, center.y}; }

        // function used for testing, prints the nth edge of the tile 
        void PrintEdge(int32_t n) const;

        // triangulation functions 

        void SetTriangulation(const std::vector<Triangle> & tr);
        // generate triangulation, only gaurunteed to work for convex tiles 
        void ConvexTriangulation();
        std::vector<Triangle> GetTriangulation() const 
            { return triangulation; }

    private:
        std::vector<Edge> edgelist;
        Vector2 center = {0.0,0.0}; 

        // used to render the tile as a block of color 
        std::vector<Triangle> triangulation; 
};

// returns a unit square centered at (0,0)
Tile SquareTile();

// FUNCTIONS THAT GENERATE TILINGS 

// generates a tiling using a square
// note: `scalar` ideally should divide `screen_width` and `screen_height`
void BasicTiling(std::vector<Tile> & tiles, float scalar, int32_t screen_width, int32_t screen_height);
// generates a tiling using a square rotated 45 degrees 
void DiamondTiling(std::vector<Tile> & tiles, float scalar, int32_t screen_width, int32_t screen_height);

#endif
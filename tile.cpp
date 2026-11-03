/***************************************
 * Created 10/13/2026                  *
 * Last Edited 11/3/2026               *
 * Implementation for tile class       *
 ***************************************/

#include "tile.h"

Tile::Tile(std::vector<Edge> e, Vector2 c):
    edgelist(e),
    center(c)
{}

// copy constructor 
Tile::Tile(const Tile & rhs)
{
    using namespace std; 

    vector<Edge> temp_edgelist = rhs.GetEdges();
    Vector2 temp_center = rhs.GetCenter();
    vector<Triangle> temp_triangulation = rhs.GetTriangulation();

    edgelist = temp_edgelist;
    center = temp_center;
    triangulation = temp_triangulation;
}

void Tile::Translate(Vector2 vt)
{
    center = Vector2Add(center, vt);

    for (size_t i = 0; i < edgelist.size(); ++i)
    {
        edgelist[i].p1 = Vector2Add(edgelist[i].p1, vt);
        edgelist[i].p2 = Vector2Add(edgelist[i].p2, vt);
    }

    for (size_t i = 0; i < triangulation.size(); ++i)
    {
        triangulation[i].p1 = Vector2Add(triangulation[i].p1, vt);
        triangulation[i].p2 = Vector2Add(triangulation[i].p2, vt);
        triangulation[i].p3 = Vector2Add(triangulation[i].p3, vt);
    }
}

void Tile::Rotate(float a)
{
    // move center of tile to center of plane, 
    // then rotate by the angle `a`, 
    // then move back to the original center 
    Vector2 offset = {0.0, 0.0};
    offset.x = center.x; 
    offset.y = center.y; 

    // move to (0,0) 
    for (size_t i = 0; i < edgelist.size(); ++i)
    {
        edgelist[i].p1 = Vector2Subtract(edgelist[i].p1, offset);
        edgelist[i].p2 = Vector2Subtract(edgelist[i].p2, offset);
    }

    for (size_t i = 0; i < triangulation.size(); ++i)
    {
        triangulation[i].p1 = Vector2Subtract(triangulation[i].p1, offset);
        triangulation[i].p2 = Vector2Subtract(triangulation[i].p2, offset);
        triangulation[i].p3 = Vector2Subtract(triangulation[i].p3, offset);        
    }

    // rotate points 
    for (size_t i = 0; i < edgelist.size(); ++i)
    {
        edgelist[i].p1 = Vector2Rotate(edgelist[i].p1, a);
        edgelist[i].p2 = Vector2Rotate(edgelist[i].p2, a);
    }

    for (size_t i = 0; i < triangulation.size(); ++i)
    {
        triangulation[i].p1 = Vector2Rotate(triangulation[i].p1, a);
        triangulation[i].p2 = Vector2Rotate(triangulation[i].p2, a);
        triangulation[i].p3 = Vector2Rotate(triangulation[i].p3, a);
    }

    // move back to original center 
    for (size_t i = 0; i < edgelist.size(); ++i)
    {
        edgelist[i].p1 = Vector2Add(edgelist[i].p1, offset);
        edgelist[i].p2 = Vector2Add(edgelist[i].p2, offset);
    }

    for (size_t i = 0; i < edgelist.size(); ++i)
    {
        triangulation[i].p1 = Vector2Add(triangulation[i].p1, offset);
        triangulation[i].p2 = Vector2Add(triangulation[i].p2, offset);
        triangulation[i].p3 = Vector2Add(triangulation[i].p3, offset);                
    }
}

void Tile::Scale(float s)
{
    center = Vector2Scale(center, s);

    for (size_t i = 0; i < edgelist.size(); ++i)
    {
        edgelist[i].p1 = Vector2Scale(edgelist[i].p1, s);
        edgelist[i].p2 = Vector2Scale(edgelist[i].p2, s);
    }

    for (size_t i = 0; i < triangulation.size(); ++i)
    {
        triangulation[i].p1 = Vector2Scale(triangulation[i].p1, s);
        triangulation[i].p2 = Vector2Scale(triangulation[i].p2, s);
        triangulation[i].p3 = Vector2Scale(triangulation[i].p3, s);
    }
}

void Tile::PrintEdge(int32_t n) const
{
    using namespace std; 

    cout << "<" << edgelist[n].p1.x << ", " << edgelist[n].p1.y << ">  ~  <" << edgelist[n].p2.x << ", " << edgelist[n].p2.y << ">\n"; 
}

Tile SquareTile()
{
    Vector2 center = {0.0,0.0};

    std::vector<Edge> edgelist;
    edgelist.reserve(4);

    // tile has side lengths of 1
    edgelist.push_back({ {-0.5,-0.5}, {-0.5,0.5} });
    edgelist.push_back({ {-0.5,0.5},  {0.5,0.5} });
    edgelist.push_back({ {0.5,0.5},   {0.5,-0.5} });
    edgelist.push_back({ {0.5,-0.5},  {-0.5,-0.5} });

    Tile temp(edgelist, center);
    // generate triangulation
    temp.ConvexTriangulation();

    return temp;
}


void Tile::SetTriangulation(const std::vector<Triangle> & tr)
{
    for (const auto & t : tr)
    {
        triangulation.push_back(t);
    }
}


void Tile::ConvexTriangulation()
{
    // for each edge, add a triangle between the edge and the center 
    // of the tile 

    // since our tile is convex, these triangles are contained entirely within
    // the tile. 

    // additionally, these triangles span the entire tile 

    for (const auto & e : edgelist)
    {
        triangulation.push_back({e.p1, e.p2, center});
    }
}


void DrawTiling(Image * img, const std::vector<Tile> & tiles, ColorLut & lut)
{
    using namespace std; 

    // values used for interpolating between colors of the tiles 
    double count = 0.0;
    const double INTERPOLATE_MAX = (double)lut.GetSize() - 1;
    const double ITERATION_VALUE = INTERPOLATE_MAX / (double)tiles.size();

    vector<Triangle> triangles;

    // draw each tile 
    for (const auto & t : tiles)
    {
        triangles = t.GetTriangulation();

        // get interpolated color 
        Color c = lut(count);

        // draw triangles in image 
        for (const auto & tr : triangles)
        {
            ImageDrawTriangle(img, tr.p1, tr.p2, tr.p3, c);
        }

        count += ITERATION_VALUE;
    }
}
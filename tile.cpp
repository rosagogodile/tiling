/***************************************
 * Created 10/13/2026                  *
 * Last Edited 10/20/2026              *
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

    edgelist = temp_edgelist;
    center = temp_center;
}

void Tile::Translate(Vector2 vt)
{
    center = Vector2Add(center, vt);

    for (size_t i = 0; i < edgelist.size(); ++i)
    {
        edgelist[i].p1 = Vector2Add(edgelist[i].p1, vt);
        edgelist[i].p2 = Vector2Add(edgelist[i].p2, vt);
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

    // rotate points 
    for (size_t i = 0; i < edgelist.size(); ++i)
    {
        edgelist[i].p1 = Vector2Rotate(edgelist[i].p1, a);
        edgelist[i].p2 = Vector2Rotate(edgelist[i].p2, a);
    }

    // move back to original center 
    for (size_t i = 0; i < edgelist.size(); ++i)
    {
        edgelist[i].p1 = Vector2Add(edgelist[i].p1, offset);
        edgelist[i].p2 = Vector2Add(edgelist[i].p2, offset);
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

    return Tile(edgelist, center);
}
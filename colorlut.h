/***************************************
 * Created 10/27/2026                  *
 * Last Edited 10/27/2026              *
 * Class that defines a color lookup   *
 * table                               *
 ***************************************/

#ifndef COLORLUT_H
#define COLORLUT_H

#include <vector> 
#include "raylib.h"
#include "raymath.h"
#include <cstdint>


class ColorLut
{
    public: 
        ColorLut();
        ColorLut(const std::vector<Color> & cl);

        void append(Color c);

        size_t GetSize() const 
            { return size; }

        // operator overloading for array accessing 
        // use modular arithmetic to prevent out of bounds errors
        // https://www.geeksforgeeks.org/cpp/overloading-subscript-or-array-index-operator-in-c/
        // directly access color 
        Color & operator[] (size_t i);
        // interpolate between two colors
        Color operator() (double f);

    private:
        std::vector<Color> colorlist;
        size_t size;
};


#endif
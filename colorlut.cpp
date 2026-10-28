/***************************************
 * Created 10/27/2026                  *
 * Last Edited 10/27/2026              *
 * Implementation for color lookup     *
 * table                               *
 ***************************************/

#include "colorlut.h"
#include <cmath>


ColorLut::ColorLut()
{
    size = 0; 
    colorlist = {};
}


ColorLut::ColorLut(const std::vector<Color> & cl)
{
    size = 0;

    for (const auto & c : cl)
    {
        colorlist.push_back(c);
        size++;
    }
}


void ColorLut::append(Color c)
{
    colorlist.push_back(c);
    size++;
}


Color & ColorLut::operator[] (size_t i)
{
    if (size > 0)
        // modulus makes list wrap around itself
        return colorlist[i % size];
}

Color ColorLut::operator() (double f)
{
    using namespace std;

    // get two colors that we will interpolate 
    Color & c1 = colorlist[(size_t)floor(f) % size];
    Color & c2 = colorlist[(size_t)ceil(f) % size];

    // fractional values will be used to interpolate between the colors 
    const double fractional = f - (double)floor(f);
    const double fractional_complement = 1.0 - fractional;

    Color c3; 

    // PLEASE DON'T JUDGE ME FOR WRITING THIS ABOMBINATION 
    // i will be shocked if this compiles without throwing a warning
    c3.r = (uint8_t)((int32_t)((fractional * (double)c1.r) + (fractional_complement * (double)c2.r)) % 256);
    c3.g = (uint8_t)((int32_t)((fractional * (double)c1.g) + (fractional_complement * (double)c2.g)) % 256);
    c3.b = (uint8_t)((int32_t)((fractional * (double)c1.b) + (fractional_complement * (double)c2.b)) % 256);
    c3.a = (uint8_t)((int32_t)((fractional * (double)c1.a) + (fractional_complement * (double)c2.a)) % 256);

    return c3;
}
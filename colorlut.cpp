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

    const double f_prime = fmod(f,(double)size);

    // get two colors that we will interpolate 
    Color & c1 = colorlist[(size_t)floor(f_prime) % size];
    Color & c2 = colorlist[(size_t)ceil(f_prime) % size];

    // fractional values will be used to interpolate between the colors 
    const double fractional = f_prime - (double)floor(f_prime);
    const double fractional_complement = 1.0 - fractional;

    Color c3; 

    // PLEASE DON'T JUDGE ME FOR WRITING THIS ABOMBINATION 
    // i will be shocked if this compiles without throwing a warning
    // somehow, no warning
    c3.r = (uint8_t)(floor((fractional_complement * (double)c1.r) + (fractional * (double)c2.r)));
    c3.g = (uint8_t)(floor((fractional_complement * (double)c1.g) + (fractional * (double)c2.g)));
    c3.b = (uint8_t)(floor((fractional_complement * (double)c1.b) + (fractional * (double)c2.b)));
    c3.a = (uint8_t)(floor((fractional_complement * (double)c1.a) + (fractional * (double)c2.a)));

    return c3;
}
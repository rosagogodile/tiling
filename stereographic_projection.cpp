/***************************************
 * Created 11/4/2026                   *
 * Last Edited 11/4/2026               *
 * Function that transforms an image   *
 * according to the stereographic      *
 * projection                          *
 ***************************************/

#include "stereographic_projection.h"


// https://mathworld.wolfram.com/HemisphericalFunction.html
inline Vector3 HemisphericalCoords(Vector2 plane_coords, float radius)
{
    return {plane_coords.x, plane_coords.y,
            sqrt(pow(radius, 2.0) - pow(plane_coords.x, 2.0) - pow(plane_coords.y, 2.0)) };
} 


void StereographicTransform(Image in, Image * out, int32_t w, int32_t h)
{
    // pick minimum dimension to be the radius of our hemisphere
    const float RADIUS = ((h < w) ? h : w) / 2.0;
}
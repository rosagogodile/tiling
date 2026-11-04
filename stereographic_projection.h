/***************************************
 * Created 11/3/2026                   *
 * Last Edited 11/4/2026               *
 * Functions that define the           *
 * stereographic projection between    *
 * S^2 and R^2                         *
 ***************************************/

// definitions found here: 
// https://en.wikipedia.org/wiki/Stereographic_projection

// can be used as a homeomorphism between a hemisphere with an 
// open boundary and the real plane with a hole at <0,0>

#ifndef STEREOGRAPHIC_PROJECTION_H
#define STEREOGRAPHIC_PROJECTION_H

#include "raylib.h"
#include "raymath.h"

#include <cmath>
#include <cstdint>


inline Vector2 StereographicProjection(Vector3 sphere_coords)
{
    return {sphere_coords.x / (1 - sphere_coords.z), sphere_coords.y / (1 - sphere_coords.z)};
}

inline Vector3 InverseStereographicProjection(Vector2 plane_coords)
{
    return {2 * plane_coords.x / (1 + pow(plane_coords.x, 2.0) + pow(plane_coords.y, 2.0)),
            2 * plane_coords.y / (1 + pow(plane_coords.x, 2.0) + pow(plane_coords.y, 2.0)),
            (-1 + pow(plane_coords.x, 2.0) + pow(plane_coords.y, 2.0)) / (1 + pow(plane_coords.x, 2.0) + pow(plane_coords.y, 2.0))};
}

void StereographicTransform(Image in, Image * out, int32_t w, int32_t h);

#endif
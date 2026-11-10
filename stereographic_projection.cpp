/***************************************
 * Created 11/4/2026                   *
 * Last Edited 11/10/2026              *
 * Function that transforms an image   *
 * according to the stereographic      *
 * projection                          *
 ***************************************/

#include "stereographic_projection.h"


// https://mathworld.wolfram.com/HemisphericalFunction.html
inline Vector3 HemisphericalCoords(Vector2 plane_coords, float radius)
{
    // move plane coordinate to make sense for the formula!!!!
    // this vector considers the plane coordinates in regards to the center of the hemisphere, 
    // rather than the origin of the plane at 0,0
    Vector2 plane_coords_prime = {plane_coords.x - radius, plane_coords.y - radius};


    if (sqrt(pow(plane_coords_prime.x, 2.0) + pow(plane_coords_prime.y,2.0)) <= radius)
        return {plane_coords.x, plane_coords.y,
               sqrt(pow(radius, 2.0) - pow(plane_coords_prime.x, 2.0) - pow(plane_coords_prime.y, 2.0)) };
    else 
        return {plane_coords.x, plane_coords.y, 0};
} 


void StereographicTransform(Image in, Image * out, int32_t w_i, int32_t h_i, int32_t w_o, int32_t h_o)
{
    // pick minimum dimension to be the radius of our hemisphere
    const float RADIUS = ((h_i < w_i) ? h_i : w_i) / 2.0;

    // compute coordinates of the center of the image 
    // const int32_t CENTER_X = w_i / 2;
    // const int32_t CENTER_Y = h_i / 2;


    // assign hemisphere coordinates for each pixel in the image
    // Vector3 hemicoords[w_i][h_i];
    // allocate on the heap to prevent stack overflow lol
    Vector3 * hemicoords = new Vector3[w_i * h_i];

    if (hemicoords == nullptr)
        return;

    for (int32_t i = 0; i < w_i; ++i)
    {
        for (int32_t j = 0; j < h_i; ++j)
        {
            hemicoords[(i * h_i) + j] = HemisphericalCoords({(float)i, (float)j}, RADIUS);
        }
    }

    // apply transform to each pixel in output image

    
    Vector3 tempcoords[4];

    for (int32_t i = 0; i < w_o; ++i)
    {
        for (int32_t j = 0; j < h_o; ++j)
        {
            Vector2 plane_coords = 
            {
                (i - w_o / 2.0) / RADIUS,
                (j - h_o / 2.0) / RADIUS
            };

            // Vector3 normhemicoords = InverseStereographicProjection({(float)i, (float)j});
            Vector3 normhemicoords = InverseStereographicProjection(plane_coords);
            Vector3 unnormhemicoords = Vector3Scale(normhemicoords, RADIUS);


            //  Possible coordinate types: 
            //  ceil ceil
            //  ceil floor 
            //  floor ceil
            //  floor floor

            for (int32_t k = 0; k < 4; ++k)
            {
                // grabs a different coordinate for each iteration 
                // i will let the reader ruminate over how this works
                int32_t x_coord = (k < 2) ? ceil(unnormhemicoords.x) : floor(unnormhemicoords.x);
                int32_t y_coord = (k % 2 == 0) ? ceil(unnormhemicoords.y) : floor(unnormhemicoords.y);

                if (x_coord >= w_i)
                    x_coord--;
                if (y_coord >= h_i)
                    y_coord --;

                tempcoords[k] = hemicoords[(x_coord * h_i) + y_coord];
            }

            
            // color channels 
            int32_t r0 = 0;
            int32_t g0 = 0;
            int32_t b0 = 0;
            const int32_t a0 = 255; // alpha channel should always be 255

            // grab colors for each pixel
            for (int32_t k = 0; k < 4; ++k)
            {
                Vector3 coord = tempcoords[k];

                Color c_prime = GetImageColor(in, (int32_t)coord.x, (int32_t)coord.y);

                r0 += c_prime.r;
                g0 += c_prime.g;
                b0 += c_prime.b;
            }

            // divide each channel by 4
            // averages the color between the 4 pixels
            r0 /= 4;
            g0 /= 4;
            b0 /= 4;

            // ensure channel has a max value of 255
            r0 = (r0 < 255) ? r0 : 255;
            g0 = (g0 < 255) ? g0 : 255;
            b0 = (b0 < 255) ? b0 : 255;

            // place pixel in image
            Color c_final = {r0, g0, b0, a0};
            ImageDrawPixel(out, i, j, c_final);
            
        }
    }
    
    delete hemicoords;

}
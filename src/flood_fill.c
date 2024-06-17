#include "flood_fill.h"

#include <stdbool.h>
#include <stdlib.h>

#include "util.h"

int checkPixels(pixel_t* pixel1,pixel_t* pixel2)
{   
    // compare the given pixels with each other:

    if (pixel1->r == pixel2->r && pixel1->g == pixel2->g && pixel1->b == pixel2->b )
    {
        return 1;
    }
    return 0;
}

void flood(image_t *img, int x, int y, pixel_t *target_color) {
    // Check if the image pointer is NULL int the target color or if the target color pointer is NULL
    if (img == NULL || target_color == NULL) {
        return;
    }

    // Check if the starting positions of x and y are in the bounds of the image:
    if (x < 0 || y < 0 || x >= img->w || y >= img->h) {
        return;
    } 


    if(target_color->r < 0  || target_color->g < 0 || target_color->g > 255 || target_color->b > 255 || target_color->r > 255 || target_color->b < 0  )
    {
        return;
    }

    // Get the color of the pixel at the coords of x and y:
    pixel_t current_color = img->img[y * img->w + x];
    
    // Check if the current pixel has the same color as the target color
    if (checkPixels(&current_color, target_color)) {
        // The current pixel already has the target color, no need to fill
        return;
    }

    // Changing colors of the pixel that is currently at to the new color:
    img->img[y * img->w + x] = *target_color;

    // Using recursion to flood fill the pixels that are nearby:
   
    // Down direction:
    if (y < img->h - 1 && checkPixels(&current_color, &(img->img[(y + 1) * img->w + x]))) {
        flood(img, x, y + 1, target_color);
    }


     // up direction:
    if (y > 0 && checkPixels(&current_color, &(img->img[(y - 1) * img->w + x]))) {
        flood(img, x, y - 1, target_color);
    }

    // left direction:
    if (x > 0 && checkPixels(&current_color, &(img->img[y * img->w + x - 1]))) {
        flood(img, x - 1, y, target_color);
    }

     // Right direction:
    if (x < img->w - 1 && checkPixels(&current_color, &(img->img[y * img->w + x + 1]))) {
        flood(img, x + 1, y, target_color);
    }


}
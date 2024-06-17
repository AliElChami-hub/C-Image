#include "image_edit.h"

#include <stdlib.h>

#include "util.h"

void rotate_counterclockwise(image_t *img) {
    
     pixel_t *rotated_image = malloc(img->h * img->w * sizeof(pixel_t));
     
     if (!rotated_image) {
        // handle allocation failure
        return;
    }
     // rotate the image counter clockwise:
      for (int i = 0; i < img->h; i++) {
        for (int j = 0; j < img->w; j++) {
            int index = (img->w - j - 1) * img->h + i;
            rotated_image[index].r = img->img[i * img->w + j].r;
            rotated_image[index].g = img->img[i * img->w + j].g;
            rotated_image[index].b = img->img[i * img->w + j].b;
        }
 }
    free(img->img);
    img->img= rotated_image; 
    int temp = img->w;
    img->w = img->h;
    img->h = temp;




}

void rotate_clockwise(image_t *img) {
  
  
   pixel_t *rotated_image = malloc(img->h * img->w * sizeof(pixel_t));
 
    if (!rotated_image) {
        // handle allocation failure
        return;
    }
 
    // rotate the image clockwise:

 for (int i = 0; i < img->h; i++) {
  for (int j = 0; j < img->w; j++) {
    int index = (j * img->h) + (img->h - i - 1);
    rotated_image[index].r = img->img[i * img->w + j].r;
    rotated_image[index].g = img->img[i * img->w + j].g;
    rotated_image[index].b = img->img[i * img->w + j].b;
  }
 }
    free(img->img);
    img->img= rotated_image;
    int temp = img->w;
    img->w = img->h;
    img->h = temp;
    


 }


void mirror_horizontal(image_t *img) {
   int w = img->w;
    int h = img->h;
    pixel_t *temp = malloc(sizeof(pixel_t));
     if (!temp) {
        // handle allocation failure
        return;
    }

    int start = 0; 
    int end = w -1;
    // mirror the image horizontally: 
    while (start < end)
    {
        int i = start; 
        int j = end; 
        int counter = 0; 
        while(counter < h)
        {
            *temp = img->img[j];
            img->img[j] = img->img[i];
            img->img[i] = *temp; 
            i = i + w; 
            j = j + w; 
            counter++; 

        } 
        start = start +1; 
        end = end -1;

    }

      free(temp);
    


}

void mirror_vertical(image_t *img) {
 int w = img->w;
    int h = img->h;
    pixel_t *temp = malloc(sizeof(pixel_t));
     if (!temp) {
        // handle allocation failure
        return;
    }

    int up = 0; 
    int down = w * (h - 1);
    //mirror the image vertically: 
    while (up < down)
    {
        int i = up; 
        int j = down; 
        int counter = 0; 
        while(counter < w)
        {
            *temp = img->img[j];
            img->img[j] = img->img[i];
            img->img[i] = *temp; 
            i = i + 1; 
            j = j + 1; 
            counter++; 

        } 
        up = up + w; 
        down = down - w;

    }

      free(temp);

}


void resize(image_t *img, int new_width, int new_height) {
 
  //================================================================

    int w = img->w;
    int h = img->h;

    // Case 0: Same width and height
 if (new_width == w && new_height == h) {
    // No resizing needed, return without modifying the image
    return;
 }
    
    
    // Case 1: Resize to a larger image
    if (new_width >= w && new_height >= h) {
        pixel_t *new_img = calloc(new_width * new_height, sizeof(pixel_t));
        if (!new_img) {
            // handle allocation failure
          
           free(new_img);
            return;
        }

        // Copy original image pixels
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                new_img[i * new_width + j] = img->img[i * w + j];
            }
        }

        free(img->img);
        img->img = new_img;
        img->w = new_width;
        img->h = new_height;
        return;
    }

    // Case 2: Resize to a smaller image
    if (new_width < w && new_height < h) {
         pixel_t *new_img = calloc(new_width * new_height, sizeof(pixel_t));
        if (!new_img) {
            // handle allocation failure
           free(new_img);
            return;
        }

        // Crop original image to the specified coordinates
        for (int i = 0; i < new_height; i++) {
            for (int j = 0; j < new_width; j++) {
                new_img[i * new_width + j] = img->img[i * w + j];
            }
        }

        free(img->img);
        img->img = new_img;
        img->w = new_width;
        img->h = new_height;
        return;
    }

      // Case 3: Resize to a larger width and smaller height
    if (new_width >= w && new_height < h) {
        pixel_t *new_img = calloc(new_width * new_height, sizeof(pixel_t));
        if (!new_img) {
            // handle allocation failure
          free(new_img); 
            return;
        }


      // Copy original image pixels to the specified coordinates
        for (int i = 0; i < new_height; i++) {
            for (int j = 0; j < w; j++) {
                new_img[i * new_width + j] = img->img[i * w + j];
            }
        } 

        free(img->img);
        img->img = new_img;
        img->w = new_width;
        img->h = new_height;
        return;
    } 


  //Case 4: Resize to a smaller width and larger height
 if (new_width < w && new_height >= h) {
    pixel_t *new_img = calloc(new_width * new_height, sizeof(pixel_t));
    if (!new_img) {
        // handle allocation failure
   
       free(new_img);
        return;
    }

   // Crop original image to the specified coordinates
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < new_width; j++) {
            new_img[i * new_width + j] = img->img[i * w + j];
        }
    }
  

    free(img->img);
    img->img = new_img;
    img->w = new_width;
    img->h = new_height;
    return;
  } 
  

}





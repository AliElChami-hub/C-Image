#include "file_io.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "util.h"

int image_read(image_t *img, FILE *fin) {
  char format[3];
    int width, height, max_value;  
    width = 0; // inisialise the width and height
    height= 0;
   
    
    if (fin == NULL) {
       // fprintf(stderr, "Error: failed to open file\n");
        return -1;
    } 
    fscanf(fin, "%2s ", format); // read the magic number
   
    
    if (strcmp(format, "P3") != 0) {
       
       // fprintf(stderr,"The string is not equal to P3\n"); 
        return -1;
    } 
    fscanf(fin, "%d %d ", &width, &height); // read the width and height
    
    if(width < 0 || height < 0 ){

        return -1; // checking if the height and width are less than zero

    }



    fscanf(fin, "%d ", &max_value); // read the maximum pixel value
     
     if(max_value != 255) //checking if the max value is not equal to 255
    {
        return -1;
    }  
    
    pixel_t* pixels= malloc(width* height * sizeof(pixel_t));

    if (pixels == NULL) {
      
       free(pixels); // checking if the allocation is perfect
        return -1;
    }

   
    for (int i = 0;i < width * height;i++)
    {
        // scanning the r g and b values of the file:
        fscanf(fin, "%d %d %d ", &pixels[i].r,&pixels[i].g,&pixels[i].b);
        if(pixels[i].r < 0 || pixels[i].r>255|| pixels[i].g < 0 || pixels[i].g>255 || pixels[i].b < 0 || pixels[i].b>255){
            // checking the condition of the pixels
            return -1;
        }
         
    } 
   
    img->img = pixels;
    img->w = width;
    img->h = height; 
    
    
   
  

    return 0;
}

void image_write(const image_t *img, FILE *fout) {
   int max = 255;

    fprintf(fout, "P3 %d %d %d ", img->w, img->h,max); 
    int temp = 0; 
    //printing the values of the file:
    for (int i = 0; i < img->w * img->h; i++) {
        fprintf(fout, " %d %d %d ", img->img[i].r, img->img[i].g, img->img[i].b); 
        if (temp == img->w ) 
        {
            fprintf(fout," ");
            temp=0;
        }
        temp++;




}
}

void image_free(image_t *img){
    if (img->img != NULL) {
        free(img->img);
    }
    img->w = 0;
    img->h = 0;
    img->img = NULL;
}

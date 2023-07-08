#include "Image.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Allocate dynamic memory for the image structure and its R/G/B values */
/* Return the pointer to the image, or NULL in case of error */
Image *CreateImage(unsigned int Width, unsigned int Height){
    Image * image = malloc(sizeof(Image));
    if(!image) return NULL;
        image -> W = Width;
        image -> H = Height;

    const int size = Width * Height * sizeof(unsigned char);

    image -> R = malloc(size);
    image -> G = malloc(size);
    image -> B = malloc(size);

        if(!image ->R){
            free(image->R);/*free chanel*/
            free(image);/*free image*/
        }
        if(!image ->G){
            free(image ->G);
            free(image);
        }
        if(!image ->B){
            free(image->B);
            free(image);
        }
    return image;
}
/* Get the R intensity of pixel (x, y) in image */
unsigned char GetPixelR(const Image *image, unsigned int x,  unsigned int y){
    assert(image);
    assert(image -> R);
    assert(x < ImageWidth(image));
    return image->R[x + y * ImageWidth(image)];
}

/* Get the G intensity of pixel (x, y) in image */
unsigned char GetPixelG(const Image *image, unsigned int x,  unsigned int y){
    assert(image);
    assert(image -> G);
    assert(x < ImageWidth(image));
    return image->G[x + y * ImageWidth(image)];
}

/* Get the B intensity of pixel (x, y) in image */
unsigned char GetPixelB(const Image *image, unsigned int x,  unsigned int y){
    assert(image);
    assert(image -> B);
    assert(x < ImageWidth(image));
    return image->B[x + y * ImageWidth(image)];
}

/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(Image *image, unsigned int x,  unsigned int y, unsigned char r){
    assert(image);
    assert(image -> R);
    assert(x < ImageWidth(image));
    image->R[x + y * ImageWidth(image)] =r;
}

/* Set the G intensity of pixel (x, y) in image to g */
void SetPixelG(Image *image, unsigned int x,  unsigned int y, unsigned char g){
    assert(image);
    assert(image -> G);
    assert(x < ImageWidth(image));
    image->G[x + y * ImageWidth(image)] = g;
}

/* Set the B intensity of pixel (x, y) in image to b */
void SetPixelB(Image *image, unsigned int x,  unsigned int y, unsigned char b){
    assert(image);
    assert(image -> B);
    assert(x < ImageWidth(image));
    image->B[x + y * ImageWidth(image)]= b;
}

/* Free the memory for the R/G/B values and Image structure */
void DeleteImage(Image *image){
    assert(image != NULL);/*generante the image existed*/
    assert(image->R);
    assert(image->G);
    assert(image->B);

    free(image->R);
    free(image->G);
    free(image->B);
    free(image);
}

/* Return the image's width in pixels */
unsigned int ImageWidth(const Image *image){
    assert(image);
    return image->W;
}

/* Return the image's height in pixels */
unsigned int ImageHeight(const Image *image){
    assert(image);
    return image->H;
}
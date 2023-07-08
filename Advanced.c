#include "Advanced.h"
#include "Image.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

Image *Normalize(Image *image, int newMinR, int newMaxR, int newMinG, int newMaxG, int newMinB, int newMaxB)
{	
	assert(image);
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);
	int MaxR = MIN_PIXEL, MaxG = MIN_PIXEL, MaxB = MIN_PIXEL;
	int MinR = MAX_PIXEL, MinG = MAX_PIXEL, MinB = MAX_PIXEL;

	for (int i = 0; i < WIDTH; i++ ) {
		for(int j = 0; j < HEIGHT; j++){
			if(GetPixelR(image, i, j) > MaxR)
        		MaxR = GetPixelR(image, i, j);
			if(GetPixelG(image, i, j) > MaxG)
       			MaxG = GetPixelG(image, i, j);
      		if(GetPixelB(image, i, j) > MaxB)
        		MaxB = GetPixelB(image, i, j);
			if(GetPixelR(image, i, j) < MinR)
        		MinR = GetPixelR(image, i, j);
      		if(GetPixelG(image, i, j) < MinG)
       			MinG = GetPixelG(image, i, j);
			if(GetPixelB(image, i, j) < MinB)
        		MinB = GetPixelB(image, i, j);
		}
	}
	
	
	for (int i = 0; i < WIDTH; i++ ) {
		for(int j = 0; j < HEIGHT; j++){
			SetPixelR(image, i, j, (GetPixelR(image, i, j) - MinR) * (newMaxR - newMinR) / (MaxR - MinR) + newMinR);
			SetPixelG(image, i, j, (GetPixelG(image, i, j) - MinG) * (newMaxG - newMinG) / (MaxG - MinG) + newMinG);
			SetPixelB(image, i, j, (GetPixelB(image, i, j) - MinB) * (newMaxB - newMinB) / (MaxB - MinB) + newMinB);
		}
	}
	return image; 
}

/* make the image posterized */
Image *Posterize(Image *image, int rbits, int gbits, int bbits)
{
	assert(image);
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);
	int x,y;	
	for(x=0; x<WIDTH; x++) {
		for(y=0; y<HEIGHT; y++) {
			unsigned char one = 1;
			int i;
			for(i=0; i<rbits-1; i++) {
				SetPixelR(image,x,y,GetPixelR(image,x,y) |one);
				one <<= 1;
			}
			one = ~one;
			SetPixelR(image,x,y,GetPixelR(image,x,y) & one);

			one = 1;
			for(i=0; i<gbits-1; i++) {
				SetPixelG(image,x,y,GetPixelG(image,x,y)| one);
				one <<= 1;
			}
			one = ~one;
			SetPixelG(image,x,y,GetPixelG(image,x,y) & one);

			one = 1;
			for(i=0; i<bbits-1; i++) {
				SetPixelB(image,x,y,GetPixelB(image,x,y) | one);
				one <<= 1;
			}
			one = ~one;
			SetPixelB(image,x,y,GetPixelB(image,x,y) & one);
		}
	}
	return image;
}

/* rotate and zoom the image */
Image *Rotate(Image *image, double Angle, double ScaleFactor,  int CenterX, int CenterY){
	assert(image);
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);
   	unsigned char RotatedR[WIDTH][HEIGHT];
    unsigned char RotatedG[WIDTH][HEIGHT];
    unsigned char RotatedB[WIDTH][HEIGHT];
    int x, y;
    int x2, y2;
    const double pi = 3.14159265358979323846;
    double Radian;
    double ScaleX, ScaleY;
    double M[2][2];

    Radian = -Angle/360.0 * 2*pi;
    ScaleX = ScaleFactor;
    ScaleY = ScaleFactor;
    M[0][0] = cos(Radian)/ScaleX;
    M[0][1] = -sin(Radian)/ScaleX;
    M[1][0] = sin(Radian)/ScaleY;
    M[1][1] = cos(Radian)/ScaleY;
    for(y=0; y<HEIGHT; y++)
    {   for(x=0; x<WIDTH; x++)
        {
            x2 = (x-CenterX)*M[0][0] + (y-CenterY)*M[0][1] + CenterX;
            y2 = (x-CenterX)*M[1][0] + (y-CenterY)*M[1][1] + CenterY;
            if (  (x2<0) || (x2>WIDTH-1)
                ||(y2<0) || (y2>HEIGHT-1))
            {
                RotatedR[x][y] = 0;
                RotatedG[x][y] = 0;
                RotatedB[x][y] = 0;
            }
            else
            {
                RotatedR[x][y] = GetPixelR(image, x2, y2);
                RotatedG[x][y] = GetPixelG(image, x2, y2);
                RotatedB[x][y] = GetPixelB(image, x2, y2);
            }
        }
    }
    for(y=0; y<HEIGHT; y++)
    {   for(x=0; x<WIDTH; x++)
        {
            SetPixelR(image, x, y, RotatedR[x][y]);
			SetPixelG(image, x, y, RotatedG[x][y]);
			SetPixelB(image, x, y, RotatedB[x][y]);
		}
    }
	return image;
} /* end of Rotate */

/* add motion blur to the image */
Image *MotionBlur(Image *image, unsigned char BlurAmount)
{
	assert(image);
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);
	int x, y;
	int n;
	double tempR, tempG, tempB;
	for(x = 0; x < WIDTH; x++){
		for(y = 0; y < HEIGHT; y++){
			tempR = GetPixelR(image, x, y)/2;
			tempG = GetPixelG(image, x, y)/2;
			tempB = GetPixelB(image, x, y)/2;
			for(int i = 1; i < BlurAmount; i++){
				if(x + i < WIDTH){
					if(BlurAmount < WIDTH - x -1){
						n = BlurAmount;
					}
					else{
						n = WIDTH - x - 1;
					}
					
					tempR += GetPixelR(image, x + i, y) * 0.5 /n;
					tempG += GetPixelG(image, x + i, y) * 0.5 /n;
					tempB += GetPixelB(image, x + i, y) * 0.5 /n;
				}
			}
			SetPixelR(image, x, y, tempR);
			SetPixelG(image, x, y, tempG);
			SetPixelB(image, x, y, tempB);
		}
	}
	return image;
}
Image *Crop(Image *image, int x, int y, int W, int H){
	assert(image);
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);
	int i, j;
	int crop_w = W;
	int crop_h = H;

	if(x + crop_w > WIDTH){
		crop_w = WIDTH - x;
	}
	if(y + crop_h > HEIGHT){
		crop_h = HEIGHT - y;
	}
	Image *cropImage = NULL;
	cropImage = CreateImage(crop_w, crop_h);

	for(i = 0; i < crop_w; i++){
		for(j = 0; j < crop_h; j++){
			SetPixelR(cropImage, i, j, GetPixelR(image, x+i, y+j));
			SetPixelG(cropImage, i, j, GetPixelG(image, x+i, y+j));
			SetPixelB(cropImage, i, j, GetPixelB(image, x+i, y+j));
		}
	}
	DeleteImage(image);
	image = NULL;
	return cropImage;
}

/* Resize */
Image *Resize(Image *image, int newWidth, int newHeight){
	assert(image);
	int Width = ImageWidth(image);
	int Height = ImageHeight(image);
	double ScaleX =(double) newWidth /(double)Width;
	double ScaleY =(double) newHeight/(double)Height;
	int x,y,x2,y2;
	Image *resize = NULL;
	resize = CreateImage(newWidth, newHeight);
	
	for(y = 0; y<newHeight; y++)
	{
		for(x=0; x<newWidth; x++)
		{
			x2 = (int)(x/ScaleX);
			y2 = (int)(y/ScaleY);
			SetPixelR(resize, x, y, GetPixelR(image,x2,y2));
			SetPixelG(resize, x, y, GetPixelG(image,x2,y2));
			SetPixelB(resize, x, y, GetPixelB(image,x2,y2));
		}
	} 
	DeleteImage(image);
	image = NULL;
	return resize;
}

/* Watermark */
Image *Watermark(Image *image, const Image *watermark_image){
	assert(image);
	assert(watermark_image);
	int wm_width = ImageWidth(watermark_image);
	int wm_height = ImageHeight(watermark_image);
	int x, y;
	int r, g, b;
	for(x = 0; x < ImageWidth(image); x++){
		for(y = 0; y < ImageHeight(image); y++){
			//if the watermark image is larger than image
			int wm_x = x % wm_width;
			int wm_y = y % wm_height;
			int wm_r = GetPixelR(watermark_image, wm_x, wm_y);
			int wm_g = GetPixelG(watermark_image, wm_x, wm_y);
			int wm_b = GetPixelB(watermark_image, wm_x, wm_y);
			if (wm_r == 0 && wm_g == 0 && wm_b == 0){
				r = GetPixelR(image, x, y) * 1.45;
				g = GetPixelG(image, x, y) * 1.45;
				b = GetPixelB(image, x, y) * 1.45;
				//check if there is overflow
				if(r > 255){
					r = 255;
				}
				if(g > 255){
					g = 255;
				}
				if(b > 255){
					b = 255;
				}
				SetPixelR(image, x, y, r);
				SetPixelG(image, x, y, g);
				SetPixelB(image, x, y, b);
			}
		}
	}
	return image;
}

/* Brightness & Contrast */
Image *BrightnessAndContrast(Image *image, int brightness, int contrast){
	assert(image);
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);
	int x, y;
	int factor; 
	factor = (double)(259 * (contrast + 255)) / (double)(255 * (259 - contrast));
	int new_pixelvalueR, new_pixelvalueG, new_pixelvalueB;
	for(x = 0; x < WIDTH; x++){
		for(y = 0; y < HEIGHT; y++){

			new_pixelvalueR = (int)(factor * (GetPixelR(image, x, y) - 128) + 128) + brightness;
			new_pixelvalueG = (int)(factor * (GetPixelG(image, x, y) - 128) + 128) + brightness;
			new_pixelvalueB = (int)(factor * (GetPixelB(image, x, y) - 128) + 128) + brightness;

			if(new_pixelvalueR < 0){
				new_pixelvalueR = 0;
			}else if (new_pixelvalueR > 255){
				new_pixelvalueR = 255;
			}
			if(new_pixelvalueG < 0){
				new_pixelvalueG = 0;
			}else if (new_pixelvalueG > 255){
				new_pixelvalueG = 255;
			}
			if(new_pixelvalueB < 0){
				new_pixelvalueB = 0;
			}else if (new_pixelvalueB > 255){
				new_pixelvalueB = 255;
			}
			SetPixelR(image, x, y, new_pixelvalueR);
			SetPixelG(image, x, y, new_pixelvalueG);
			SetPixelB(image, x, y, new_pixelvalueB);
		}
	}

	return image;
}
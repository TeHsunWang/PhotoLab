
#include <stdio.h>

#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Test.h"

void PrintMenu();

int main()
{
	int result = 0;
#ifdef DEBUG
	result = AutoTest();
#else
	Image *image = NULL;
	Image *watermark_image = NULL;
	char fname[SLEN];
	int choice;
	PrintMenu();
	printf("please make your choice: ");
	scanf("%d", &choice);
	int target_r, target_g, target_b, threshold, replace_r, replace_g, replace_b;
	char color[SLEN]; int border_width;	    /* AddBorder parameters */
	unsigned char rbits, gbits, bbits;      /* posterize parameters */
	unsigned char BlurAmount;		    /* Amount of blur */
	int newWidth, newHeight;                      /* resize parameter */
	int x, y, W, H;                         /* crop parameters */
	int brightness, contrast;		    /* brightness and contrast parameters */
	int newMinR, newMaxR, newMinG, newMaxG, newMinB, newMaxB;/* Normalize() parameter */
	double Angle, ScaleFactor;  /* Rotate() parameter */
	int CenterX, CenterY; /* Rotate() parameter */

	while (choice != EXIT) {
		if (choice == 1) {
			printf("Please input the file name to load: ");
			scanf("%s", fname);
			if (image) DeleteImage(image);
			image = LoadImage(fname);
			if (! image) {
				printf("ERROR: Failed reading image \"%s\"!\n", fname);
			}
		}
		else if (choice >=2 && choice <= EXIT - 2) { /* neither autotest nor exit */
			if (! image) {
				printf("No image to process!\n");
			} else {
				switch (choice) {
					case 2:
						printf("Please input the file name to save: ");
						scanf("%s", fname);
						SaveImage(fname, image);
						break;
					case 3:
						image = BlackNWhite(image);
						printf( "\"Black and White\" operation is done!\n" );
						break;
					case 4:
						image = Negative(image);
						printf( "\"Negative\" operation is done!\n" );
						break;
					case 5:
						printf("Enter Red component for the target color: ") ;
						scanf("%d", &target_r) ;
						printf("Enter Green component for the target color: ") ;
						scanf("%d", &target_g) ;
						printf("Enter Blue component for the target color: ") ;
						scanf("%d", &target_b) ;
						printf("Enter threshold for the color difference: ") ;
						scanf("%d", &threshold) ;
						printf("Enter value for Red component in the target color: ") ;
						scanf("%d", &replace_r) ;
						printf("Enter value for Green component in the target color: ") ;
						scanf("%d", &replace_g) ;
						printf("Enter value for Blue  component in the target color: ") ;
						scanf("%d", &replace_b) ;

						image = ColorFilter(image, target_r, target_g, target_b, threshold, replace_r, replace_g, replace_b);
						printf("\"Color Filter\" operation is done!\n");
						break;
					case 6:
						image = Edge(image);
						printf("\"Edge\" operation is done!\n");
						break;
					case 7:
						image = Shuffle(image);
						printf("\"Shuffle\" operation is done!\n");
						break;
					case 8:
						image = HFlip(image);
						printf( "\"Horizontally Flip\" operation is done!\n" );
						break;
					case 9:
						image = HMirror(image);
						printf("\"Vertically Mirror\" operation is done!\n");
						break;
					case 10:
						printf("Enter border width:");
						scanf("%d", &border_width);
						printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
						printf("Select border color from the options: ");
						scanf("%s", color);
						image = AddBorder(image, color, border_width);
						printf("\"Border\" operation is done!\n");
					case 11:
						printf("Enter a new minimum value for the range of R channel:");
						scanf("%d", &newMinR);
						printf("Enter a new maximum value for the range of R channel:");
						scanf("%d", &newMaxR);
						printf("Enter a new minimum value for the range of G channel:");
						scanf("%d", &newMinG);
						printf("Enter a new maximum value for the range of G channel:");
						scanf("%d", &newMaxG);
						printf("Enter a new minimum value for the range of B channel:");
						scanf("%d", &newMinB);
						printf("Enter a new maximum value for the range of B channel:");
						scanf("%d", &newMaxB);
						image = Normalize(image, newMinR, newMaxR, newMinG, newMaxG, newMinB, newMaxB);
						printf("\"Normalize\" operation is done!\n");
						break;
					case 12:
						printf("Enter the number of posterization bits for R chennel (1 to 8): ");
						scanf("%hhu", &rbits);
						printf("Enter the number of posterization bits for G chennel (1 to 8): ");
						scanf("%hhu", &gbits);
						printf("Enter the number of posterization bits for B chennel (1 to 8): ");
						scanf("%hhu", &bbits);
						image = Posterize(image, rbits, gbits, bbits);
						printf("\"Posterize\" operation is done!\n");
						break;
					case 13:
						printf("Enter the angle of rotation:");
						scanf("%lf", &Angle);
						printf("Enter the scale of zooming:");
						scanf("%lf", &ScaleFactor);
						printf("Enter the X-axis coordinate of the center of rotation:");
						scanf("%d", &CenterX);
						printf("Enter the Y-axis coordinate of the center of rotation:");
						scanf("%d", &CenterY);
						image = Rotate(image, Angle, ScaleFactor, CenterX, CenterY);
						printf("\"Rotate\" operation is done!\n");
						break;
					case 14:
						printf("Please input motion blur amount: ");
						scanf("%hhu", &BlurAmount);
						image = MotionBlur(image, BlurAmount);
						printf("\"Motion Blur\" operation is done!\n");
						break;
					case 15:
						printf("Please input the X offset value: ");
						scanf("%u", &x);
						printf("Please input the Y offset value: ");
						scanf("%u", &y);
						printf("Please input the crop width: ");
						scanf("%u", &W);
						printf("Please input the crop height: ");
						scanf("%u", &H);
						image = Crop(image, x, y, W, H);
						printf("\"Crop\" operation is done!\n");
						break;
					case 16:
						printf("Please input the new image width: ");
						scanf("%u", &newWidth);
						printf("Please input the new image height: ");
						scanf("%u", &newHeight);
						image = Resize(image, newWidth, newHeight);
						printf("\"Resize\" operation is done!\n");
						break;
					case 17:
						printf("Please input the brightness level (integer between -255~255)");
						scanf("%d", &brightness);
						printf("Please input the contrast level (integer between -255~255)");
						scanf("%d", &contrast);
						image = BrightnessAndContrast(image, brightness, contrast);
						printf("\"Brightness and Contrast Adjustment\" operation is done!\n");
						break;
					case 18:
						printf("Please input the file name for the second image: ");
						scanf("%s", fname);
						watermark_image = LoadImage(fname);
						if (! watermark_image) {
							printf("ERROR: Loading watermark image \"%s\" failed!\n", fname);
						}
						else {
							image = Watermark(image, watermark_image);
							DeleteImage(watermark_image);
							watermark_image = NULL;
							printf("\"Watermark\" operation is done!\n");
						}
						break;
				}
			}
		}
		else if (choice == EXIT - 1) {
			result = AutoTest();
			if (result) {
				printf("AutoTest failed, error code %d!\n", result);
			}
			else {
				printf("AutoTest finished.\n");
			}
		}
		else {
			printf("Invalid selection!\n");
		}
		PrintMenu();
		printf("please make your choice: ");
		scanf("%d", &choice);
	}
	printf("You exit the program.\n");
	if (image) {
		DeleteImage(image);
		image = NULL;
	}
#endif
	return result;
}

void PrintMenu()
{
	printf("\n--------------------------------\n");
	printf(" 1:  Load a PPM image\n");
	printf(" 2:  Save an image in PPM and JPEG format\n");
	printf(" 3:  Change a color image to Black and White\n");
	printf(" 4:  Make a negative of an image\n");
	printf(" 5:  Color filter an image\n");
	printf(" 6:  Sketch the edge of an image\n");
	printf(" 7:  Shuffle an image\n");
	printf(" 8:  Flip an image vertically\n");
	printf(" 9:  Mirror an image vertically\n");
	printf("10:  Add border to an image\n");
	printf("11:  Normalize to an image\n");
	printf("12:  Posterize image\n");
	printf("13:  Rotate and zoom an image\n");
	printf("14:  Blur an image\n");
	printf("15:  Crop an image\n");
	printf("16:  Resize an image\n");
	printf("17:  Adjust the Brightness and Contrast of an image\n");
	printf("18:  Add Watermark to an image\n");
	printf("19:  Test all functions\n");
	printf("20:  Exit\n");
}

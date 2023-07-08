#Makefile PhotoLab
IMAGES = bw.ppm \
         negative.ppm \
         colorfilter.ppm \
         edge.ppm \
         hflip.ppm \
         shuffle.ppm \
         hmirror.ppm \
         border.ppm \
         normalize.ppm \
         rotate.ppm \
         posterize.ppm \
         blur.ppm\
         bigresize.ppm\
         smallresize.ppm\
         brightnessandcontrast.ppm\
         watermark.ppm
all: PhotoLab
PhotoLabTest: PhotoLab.c FileIO.c Advanced.c DIPs.c Image.c Test.c
	gcc -Wall -std=c11 -Ddebug -lm PhotoLab.c FileIO.c Advanced.c DIPs.c Image.c Test.c -o PhotoLabTest

PhotoLab: PhotoLab.o FileIO.o Advanced.o DIPs.o Image.o Test.o
	gcc -Wall -lm -std=c11 PhotoLab.o FileIO.o Advanced.o DIPs.o Image.o Test.o -o PhotoLab

Photo.o: PhotoLab.c
	gcc -Wall -std=c11 -c PhotoLab.c -o PhotoLab.o

FileIO.o: FileIO.c 
	gcc -Wall -std=c11 -c FileIO.c -o FileIO.o

Advanced.o: Advanced.c
	gcc -Wall -lm -std=c11 -c Advanced.c -o Advanced.o

DIPs.o: DIPs.c 
	gcc -Wall -std=c11 -c DIPs.c -o DIPs.o

Image.o: Image.c
	gcc -Wall -std=c11 -c Image.c -o Image.o

Test.o: Test.c
	gcc -Wall -std=c11 -c Test.c -o Test.o

clean:
	rm -f PhotoLab.o FileIO.o Advanced.o DIPs.o PhotoLab PhotoLabTest
	rm -f *.jpg PhotoLab $(IMAGES)
#EOF

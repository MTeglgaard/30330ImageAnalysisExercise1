#include <stdint.h>
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include  <conio.h>

int main(int argc, char* argv[])
{
	const char* wName = "Hello world!"; // window name 
	const char* wName2 = "Histogram Plot";
	cvNamedWindow(wName, 0); // create simple window    
	cvNamedWindow(wName2, 0); // create simple window 

	CvCapture* capture = 0;

	double capProp = 0;

	IplImage *frame, *img, *frame_copy = 0; // pointers to images 

	capture = cvCaptureFromCAM(0); // initialize capture device 

	img = cvLoadImage("ariane5_1b.jpg", 1);
	printf("img width: %d Hight: %d nSize: %d \n", img->height, img->width, img->nSize);

	cvResizeWindow(wName, img->width, img->height);
	cvMoveWindow(wName, 0, 0);


	uchar * data = (uchar *)img->imageData;
	int h = img->height;
	int w = img->width;
	int step = img->widthStep / sizeof(uchar);
	int color = 1; // red = 0, Green = 1,  Blue = 2 
	int c = 0 + color;
	int r = 0;
/*
	for (size_t i = 0; i < img->imageSize; i=i+3)
	{
		data[i + color]=255 - data[i + color];
		data[i + color+1] = 255- data[i + color + 1];
		data[i + color + 2] = 255 - data[i + color + 2];
	}
	img->imageData = (char *)data;
	//data[c + step * r]
*/

	unsigned char *channel; // pre-allocated array holding image data for the color channel or the grayscale image. 
	unsigned char value=0; // index value for the histogram (not really needed) 
	int histogram[256]; // histogram array - remember to set to zero initially 
	int width; // say, 320 
	int height; // say, 240 
	channel = (uchar *)img->imageData;
	width = w;
	height = h;
	int k = 256; 
	while (k-- > 0)
	{
		histogram[k] = 0; // reset histogram entry 
	}
	for (int i = 0; i < width*height; i++) 
	{ 
		value = channel[i];     
		histogram[value] += 1; 
		//printf("%d ", histogram[value]);
	}

	CvSize histImSiz = cvSize(256, 100000); //cvSize(width, height); 

	IplImage *histPlot = cvCreateImage(histImSiz, IPL_DEPTH_8U, img->nChannels);
	
	for (int i = 0; i < 256; i++)
	{
		int mag = histogram[i];
		cvLine(histPlot, cvPoint(i, 0), cvPoint(i, mag), cvScalar(255, 0, 0), 1);
	}
	
	//cvLine(histPlot, cvPoint(100, 0), cvPoint(100, 100), cvScalar(255, 0, 0), 1, 8, CV_AA);
	/*cvLine(		histPlot, cvPoint(400, 0), cvPoint(400, 200), cvScalar(255, 0, 0), 1);
	cvRectangle(histPlot, cvPoint(10, 10), cvPoint(20, 20), cvScalar(255, 0, 0), 1);*/
	cvResizeWindow(wName2, img->width, h);
	cvMoveWindow(wName2, 50, 50);





	while (1)
	{
		if (!img)
		{
			printf("no img");
			break;
		}

		cvShowImage(wName, img);
		cvShowImage(wName2, histPlot);
		if (cvWaitKey(0))
			break;
	}

	cvReleaseImage(&frame_copy);    
	cvDestroyWindow("Hello World");
	cvReleaseImage(&histPlot);
	cvDestroyWindow(wName2);

	return 0;
}

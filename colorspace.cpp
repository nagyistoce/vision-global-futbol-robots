//========================================================================
//  This software is free: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License Version 3,
//  as published by the Free Software Foundation.
//
//  This software is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  Version 3 in the file COPYING that came with this distribution.
//  If not, see <http://www.gnu.org/licenses/>.
//========================================================================
/*!
  \file    colorspace.cpp
  \brief   C++ Implementation: ColorSpace
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "colorspace.h"

ColorSpace::ColorSpace() {
	// TODO Auto-generated constructor stub

}

ColorSpace::~ColorSpace() {
	// TODO Auto-generated destructor stub
}

// convertion from a pixel in BGR to a pixel in HSV
// IN: pixel in BGR color space.
// OUT: pixel in HSV color space.
bool ColorSpace::bgr2hsv(const sRGB rgb, sHSV *hsv) {
	return true;
}

// convertion from an image at a pixel in BGR to a pixel in HSV
// IN: image in BGR color space and its pixel.
// OUT: pixel in HSV color space.
bool ColorSpace::bgr2hsv(const IplImage *imageBGR, const Pixel pixel, sHSV *hsv) {
	//sBGR bgr;
	//bgr = imageBGR->imageData at pixel
	//if (bgr2hsv(bgr, hsv))
		//return true;
	//else return false;

	// do it!
	imageHSV = cvCreateImage(cvGetSize(imageBGR), 8, 3);
	cvCvtColor(imageBGR, imageHSV, CV_BGR2HSV);

	int rowSizeIn = imageHSV->widthStep;		// Size of row in bytes, including extra padding
	char *imOfsIn = imageHSV->imageData;	// Pointer to the start of the input image HSV pixels.

	// Get the HSV pixel components
	hsv->hue = *(uchar*)(imOfsIn + pixel.y*rowSizeIn + pixel.x*3 + 0);	// Hue
	hsv->saturation = *(uchar*)(imOfsIn + pixel.y*rowSizeIn + pixel.x*3 + 1);	// Saturation
	hsv->value = *(uchar*)(imOfsIn + pixel.y*rowSizeIn + pixel.x*3 + 2);	// Value (Brightness)

	cvReleaseImage(&imageHSV);

	return true;
}

bool ColorSpace::bgr2hsv(IplImage *imageBGR, IplImage *imageHSV){
	cvCvtColor(imageBGR, imageHSV, CV_BGR2HSV); // notar que OpenCV almacena las imágenes RGB en orden B, G, R.
	return true;
}

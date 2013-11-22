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
  \file    segmentation.cpp
  \brief   C++ Implementation: Segmentation
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "segmentation.h"
#include <stdio.h>

inline int top_bit(unsigned n)
{
  int i = 1;
  if(!n) return(0);
  while(n>>i) i++;
  return(i-1);
}

Segmentation::Segmentation() {
	const unsigned k = 0;

	for (int i=0; i < COLOR_LEVEL_HUE_OPENCV; ++i) {
			h_class.push_back(* (new unsigned()) );
			h_class[i] = k;
			//std::cout << h_class[i] << std::endl;
	}

	for (int i=0; i <= COLOR_LEVELS; ++i ) {
			s_class.push_back(* (new unsigned()) );
			s_class[i] = k;
			v_class.push_back(* (new unsigned()) );
			v_class[i] = k;
	}

	// ToDO: find a better way to store this hash table.
	for (int i=0; i < HASH_INDEX_MAX; ++i) {
		hash.push_back(* (new int()));
		hash[i]=0;
	}

	hash[1] = cBLACK;
	hash[2]	= cWHITE;
	hash[4] = cGREY;
	hash[8]	= cRED;
	hash[16] = cBROWN;
	hash[32] = cORANGE;
	hash[64] = cYELLOW;
	hash[128] = cGREEN;
	hash[256] = cAQUA;
	hash[512] = cBLUE;
	hash[1024] = cPURPLE;
	hash[2048] = cPINK;

}

Segmentation::~Segmentation() {
	// TODO Auto-generated destructor stub
}

bool Segmentation::resetThreshold(){
	const unsigned k = 0;

	for (int i=0; i < COLOR_LEVEL_HUE_OPENCV; ++i)
			h_class[i] = k;

	for (int i=0; i <= COLOR_LEVELS; ++i ) {
			s_class[i] = k;
			v_class[i] = k;
	}
	return (true);
}

bool Segmentation::buildThreshold(std::vector<sColor*>&color) {
	resetThreshold();
	for (int i=0; i < NUM_COLOR_TYPES; ++i) {
		//if (color[i]->habilitar)
			setThreshold(color, i,
					color[i]->hsv_min.hue, color[i]->hsv_max.hue,
					color[i]->hsv_min.saturation, color[i]->hsv_max.saturation,
					color[i]->hsv_min.value, color[i]->hsv_max.value);
	}
	return (true);
}


bool Segmentation::getThreshold(int colorid,
					int &h_low, int &h_high,
					int &s_low, int &s_high,
					int &v_low, int &v_high) {
	return (true);

}

bool Segmentation::setThreshold(std::vector<sColor*>&color, int colorId,
				int h_low, int h_high,
				int s_low, int s_high,
				int v_low, int v_high) {

	sColor *c;
	unsigned k;

	if ((colorId < 0) || (colorId >= (int)color.size())) //(color >= NUM_COLOR_TYPES))
		return(false);

	c = color[colorId];
	k = 1 << colorId;
	//std::cout << "k : " << std::dec << k << std::endl;

	clear_bits(h_class, COLOR_LEVEL_HUE_OPENCV, c->hsv_min.hue, c->hsv_max.hue, k);
	clear_bits(s_class, COLOR_LEVELS, c->hsv_min.saturation, c->hsv_max.saturation, k);
	clear_bits(v_class, COLOR_LEVELS, c->hsv_min.value, c->hsv_max.value, k);

	c->hsv_min.hue = h_low;  		c->hsv_max.hue = h_high;
	c->hsv_min.saturation = s_low;  c->hsv_max.saturation = s_high;
	c->hsv_min.value = v_low;  		c->hsv_max.value = v_high;

	set_bits(h_class, COLOR_LEVEL_HUE_OPENCV, h_low, h_high, k);
	set_bits(s_class, COLOR_LEVELS, s_low, s_high, k);
	set_bits(v_class, COLOR_LEVELS, v_low, v_high, k);

	/*
	std::cout << "colorId : " << colorId << std::endl;
	for (int j=h_low; j <= h_high; ++j)
		std::cout << "h_class[" << j << "] : " << std::dec << h_class[j] << std::endl;
	for (int j=s_low; j <= s_high; ++j)
		std::cout << "s_class[" << j << "] : " << std::dec << s_class[j] << std::endl;
	for (int j=v_low; j <= v_high; ++j)
		std::cout << "v_class[" << j << "] : " << std::dec << v_class[j] << std::endl;
	*/
	return (true);
}

// sets bits in k in array arr[l..r]
void Segmentation::set_bits(std::vector<unsigned>&arr, int len, int l, int r, unsigned k) {
  int i;

  l = MAX(l,0);
  r = MIN(r+1,len);

  for(i=l; i<r; i++) arr[i] |= k; //arr[i] |= k; -->EQUIVALE A--> arr[i] = arr[i] | k;
}

void Segmentation::clear_bits(std::vector<unsigned>&arr, int len, int l, int r, unsigned k) {
  int i;

  l = MAX(l,0);
  r = MIN(r+1,len);

  k = ~k;
  for(i=l; i<r; i++) arr[i] &= k;  //arr[i] &= k; -->EQUIVALE A--> arr[i] = arr[i] & k;
}

void Segmentation::paint(IplImage *imageBGR, std::vector<sColor*>&color, int colorId) {


}

void Segmentation::colorPaint(IplImage *imageBGR, std::vector<sColor*>&color) {
	imageHSV = cvCreateImage(cvGetSize(imageBGR), 8, 3);
	convert.bgr2hsv(imageBGR, imageHSV);

	int hIn = imageHSV->height;
	int wIn = imageHSV->width;
	int rowSizeIn = imageHSV->widthStep;		// Size of row in bytes, including extra padding

	char *imOfsIn = imageHSV->imageData;	// Pointer to the start of the input image HSV pixels.
	//char *imOfsMask = segmentated->imageData;

	for (int y=0; y<hIn; y++) {
		for (int x=0; x<wIn; x++) {
			// Get the HSV pixel components
			uchar H = *(uchar*)(imOfsIn + y*rowSizeIn + x*3 + 0);	// Hue
	        uchar S = *(uchar*)(imOfsIn + y*rowSizeIn + x*3 + 1);	// Saturation
	        uchar V = *(uchar*)(imOfsIn + y*rowSizeIn + x*3 + 2);	// Value (Brightness)
	        //std::cout << "H : " << (int) H << std::endl;
	        //std::cout << "S : " << (int) S << std::endl;
	        //std::cout << "V : " << (int) V << std::endl;

	        // Determina de qué color es el píxel HSV.
	        unsigned c = ((h_class[(int)H] & s_class[(int)S]) & v_class[(int)V]);
	        //std::cout << "c : " << std::dec << c << std::endl;
	        //std::cout << "h_class : " << std::dec << h_class[H] << std::endl;
	        //std::cout << "s_class : " << std::dec << s_class[S] << std::endl;
	        //std::cout << "v_class : " << std::dec << v_class[V] << std::endl;


	        int colorId = hash[c];
	        //std::cout << "c : " << std::dec << c << std::endl;
	        //std::cout << "colorId : " << std::dec << colorId << std::endl;

	        if ((c != 0) && (c < HASH_INDEX_MAX) && (color[colorId]->habilitar)) {
	        		//data_list[ctype].segmentated->imageData[data_list[ctype].segmentated->widthStep * y + x ]=(char) 255;
	        		((uchar*)(imageBGR->imageData + imageBGR->widthStep*y))[x*3] = color[colorId]->rgb.blue;
	        		((uchar*)(imageBGR->imageData + imageBGR->widthStep*y))[x*3+1] = color[colorId]->rgb.green;
	        		((uchar*)(imageBGR->imageData + imageBGR->widthStep*y))[x*3+2] = color[colorId]->rgb.red;
	        }
		}//for
	}//for
	cvReleaseImage(&imageHSV);
}

void Segmentation::colorPaint(IplImage *imageBGR, std::vector<sColor*>&color, int colorId) {
	imageHSV = cvCreateImage(cvGetSize(imageBGR), 8, 3);
	convert.bgr2hsv(imageBGR, imageHSV);

	int hIn = imageHSV->height;
	int wIn = imageHSV->width;
	int rowSizeIn = imageHSV->widthStep;		// Size of row in bytes, including extra padding

	char *imOfsIn = imageHSV->imageData;	// Pointer to the start of the input image HSV pixels.
	//char *imOfsMask = segmentated->imageData;

	for (int y=0; y<hIn; y++) {
		for (int x=0; x<wIn; x++) {
			// Get the HSV pixel components
			uchar H = *(uchar*)(imOfsIn + y*rowSizeIn + x*3 + 0);	// Hue
	        uchar S = *(uchar*)(imOfsIn + y*rowSizeIn + x*3 + 1);	// Saturation
	        uchar V = *(uchar*)(imOfsIn + y*rowSizeIn + x*3 + 2);	// Value (Brightness)

	        // Determina de qué color es el píxel HSV.
	        int ctype = this->getPixelColorTypeHSV(H, S, V, color);

	        // Si se identificó un color ctype tendrá el índice, caso contrario ctype es igual a -1.
	        if (ctype == colorId) {
	        		//data_list[ctype].segmentated->imageData[data_list[ctype].segmentated->widthStep * y + x ]=(char) 255;
	        		((uchar*)(imageBGR->imageData + imageBGR->widthStep*y))[x*3] = color[colorId]->rgb.blue;
	        		((uchar*)(imageBGR->imageData + imageBGR->widthStep*y))[x*3+1] = color[colorId]->rgb.green;
	        		((uchar*)(imageBGR->imageData + imageBGR->widthStep*y))[x*3+2] = color[colorId]->rgb.red;
	        }
		}//for
	}//for
	cvReleaseImage(&imageHSV);
}

int Segmentation::getPixelColorType(int H, int S, int V) {
    int color;
    if (V < 75)
            color = cBLACK;
    else if (V > 190 && S < 27)
            color = cWHITE;
    else if (S < 53 && V < 185)
            color = cGREY;
    else {	// Is a color
            if (H < 14)
                    color = cRED;
            else if (H < 25)
                    color = cORANGE;
            else if (H < 34)
                    color = cYELLOW;
            else if (H < 73)
                    color = cGREEN;
            else if (H < 102)
                    color = cAQUA;
            else if (H < 127)
                    color = cBLUE;
            else if (H < 149)
                    color = cPURPLE;
            else if (H < 175)
                    color = cPINK;
            else	// full circle
                    color = cRED;	// back to Red
    }
    return color;
}

int Segmentation::getPixelColorTypeHSV(int H, int S, int V, std::vector<sColor*>&color) {
    if (V < color[0]->hsv_max.value)
            return 0; //cBLACK
    else if (V > color[1]->hsv_min.value && S < color[1]->hsv_max.saturation)
            return 1; //cWHITE;
    else if (S < color[2]->hsv_max.saturation && V < color[2]->hsv_max.value)
            return 2; //cGREY;
    else {	// Is a color
    	for (unsigned int i=3; i < color.size(); ++i) {
    		//if (color[i]->habilitar)
    			if ((color[i]->hsv_min.hue <= H) and (H <= color[i]->hsv_max.hue)) {
    				return i;
    			}
    	}//for
    }//else

    return (-1);
}



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
  \file    datastruct.h
  \brief   C++ Interface: sData
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef DATASTRUCT_H_
#define DATASTRUCT_H_

#include <opencv2/opencv.hpp>
#include <cvblob.h>
#include "team.h"
#include "ball.h"
#include "homography.h"


using namespace cvb;

#define DEVICES 4


enum colorIndex {cBLACK=0, cWHITE, cGREY, cRED, cBROWN, cORANGE, cYELLOW, cGREEN, cAQUA, cBLUE, cPURPLE, cPINK, NUM_COLOR_TYPES};

//#pragma pack(8)

struct sData {
public:
	bool enable; //=false; //procesar este color a segmentar
	//int color_index; //índice de la tabla de colores.
	IplImage* image_hsv;
	IplImage* segmentated;
	IplConvKernel* morphKernel;
	IplImage* labelImg;
	unsigned int result;
	CvBlobs blobs;
	CvTracks tracks;
	//ROI área de procesamiento
	Team *blue_team;
	Team *yellow_team;
	Ball *ball;
	Homography *homography;

	sData() {result=0; enable=false;}
} __attribute__ ((aligned));

typedef CvPoint Pixel;

struct sRGB{
public:
	int blue;
	int green;
	int red;
};

struct sHSV{
public:
	int hue;
	int saturation;
	int value;
};

struct sColor {
public:
	std::string name;
	sHSV hsv_min;
	sHSV hsv_max;
	sRGB rgb;
	bool mostrar; //muestra el color detectado durante el proceso de ajuste del color.
	bool habilitar; //lo habilita a buscarlo en el proceso de búsqueda de colores, para detectar el parche.
	bool background; //TODO: no tiene uso actualmente, identifica al color como background.

	sColor() {
		hsv_min.hue=0;
		hsv_min.saturation=0;
		hsv_min.value=0;
		hsv_max.hue=0;
		hsv_max.saturation=0;
		hsv_max.value=0;
		mostrar=habilitar=background=false;}
};

struct sResolution {
public:
	int width;
	int height;
};


#endif /* DATASTRUCT_H_ */

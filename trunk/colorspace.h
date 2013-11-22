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
  \file    colorspace.h
  \brief   C++ Interface: ColorSpace
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef COLORSPACE_H_
#define COLORSPACE_H_

#include <cv.h>
#include "datastruct.h"

class ColorSpace {
public:
	ColorSpace();
	virtual ~ColorSpace();
	bool bgr2hsv(const sRGB rgb, sHSV *hsv);
	bool bgr2hsv(const IplImage *imageBGR, const Pixel pixel, sHSV *pixel_hsv);
	bool bgr2hsv(IplImage *imageBGR, IplImage *imageHSV);

private:
	IplImage *imageHSV;
};

#endif /* COLORSPACE_H_ */

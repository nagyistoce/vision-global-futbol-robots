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
  \file    segmentation.h
  \brief   C++ Interface: Segmentation
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include <cv.h>
#include <vector>
#include "colorspace.h"
#include "datastruct.h"


#define MAX_COLORS				32
#define COLOR_LEVELS			256
#define COLOR_LEVEL_HUE_OPENCV	180
#define HASH_INDEX_MAX			2050


class Segmentation {
public:
	Segmentation();
	Segmentation(IplImage *frame, std::vector<sColor*>&color);
	virtual ~Segmentation();
	void colorPaint(IplImage *imageBGR, std::vector<sColor*>&color, int colorId);
	void colorPaint(IplImage *imageBGR, std::vector<sColor*>&color);

	int getPixelColorTypeHSV(int H, int S, int V, std::vector<sColor*>&color);
	int getPixelColorType(int H, int S, int V);

	bool resetThreshold();
	bool getThreshold(int colorid,
					int &h_low, int &h_high,
					int &s_low, int &s_high,
					int &v_low, int &v_high);
	bool setThreshold(std::vector<sColor*>&color,
				int colorid,
				int h_low, int h_high,
				int s_low, int s_high,
				int v_low, int v_high);
	bool buildThreshold(std::vector<sColor*>&color);
	void paint(IplImage *imageBGR, std::vector<sColor*>&color, int colorId);

protected:
	void clear_bits(std::vector<unsigned>&arr, int len, int l, int r, unsigned k);
	void set_bits(std::vector<unsigned>&arr, int len, int l, int r, unsigned k);

public:
	std::vector<unsigned> h_class;
	std::vector<unsigned> s_class;
	std::vector<unsigned> v_class;
	std::vector<int> hash;

protected:
	std::vector<sColor> color;
private:
	ColorSpace convert;
	IplImage *imageHSV;


};

#endif /* SEGMENTATION_H_ */

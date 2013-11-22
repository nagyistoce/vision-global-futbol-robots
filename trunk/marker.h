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
  \file    marker.h
  \brief   C++ Interface: Marker
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef MARKER_H_
#define MARKER_H_

#include <opencv2/opencv.hpp>

class Marker {
public:
	int colorid; // color id
	CvPoint center; // center point
	float area;
	float area_mean;
	float height;

	// The following two fields are for use by callers (i.e. FindRobots)
	float dist;         // distance from center marker
	float angle;        // angle around center marker
	float next_angle_dist;   // angular distance to next marker CW (always positive) around pattern
	float next_dist;    // distance to next marker CW around pattern

	Marker();
	virtual ~Marker();
};

#endif /* MARKER_H_ */

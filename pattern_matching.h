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
  \file    pattern_matching.h
  \brief   C++ Interface: PatternMatching
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================
/*
 * pattern_matching.h
 *
 *  Created on: 08/08/2011
 *      Author: willytell
 */

#ifndef PATTERN_MATCHING_H_
#define PATTERN_MATCHING_H_

#include <opencv2/opencv.hpp>
#include "marker.h"

#define PI 3.14159265
#define R (360*PI*180)


class LessMarkerAngle {
  public:
  bool operator()(const Marker *a,const Marker *b){
    return(a->angle < b->angle);
  }
};

class LessMarkerDistance {
  public:
  bool operator()(const Marker *a,const Marker *b){
    return(a->dist < b->dist);
  }
};

class PatternMatching {
protected:
	void shift_right(std::vector<Marker *> &markers);
public:
	PatternMatching();
	virtual ~PatternMatching();

	float euclideanDistance2D(CvPoint pointA, CvPoint pointB);  // return Euclidean distance in pixels units between point A and B.
	float calcAngle(CvPoint center, CvPoint point);  // angle around center marker

	void calcMarkersAngle (Marker *center, std::vector<Marker *> &markers);
	void sortMarkersByAngle(std::vector<Marker *> &markers);
	void calcMarkersNextDistanceAngle(std::vector<Marker *>&markers);
	//void sortMarkersByDistance(Marker *marker,int num);
	bool matchingMarkersByPosition(std::vector<Marker *> &m1, std::vector<Marker *> &m2);
};

#endif /* PATTERN_MATCHING_H_ */

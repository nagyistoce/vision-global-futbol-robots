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
  \file    pattern_matching.cpp
  \brief   C++ Implementation: PatternMatching
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "pattern_matching.h"
#include <stdio.h>
#include <iostream>

PatternMatching::PatternMatching() {
	// TODO Auto-generated constructor stub

}

PatternMatching::~PatternMatching() {
	// TODO Auto-generated destructor stub
}

// http://es.wikipedia.org/wiki/Función_trigonométrica
// http://www.cplusplus.com/reference/clibrary/cmath/atan2
// OUT: arc tangent of y/x, in the interval [-pi,+pi] radians
float PatternMatching::calcAngle(CvPoint center, CvPoint point) {
	return atan2( (float) (point.y - center.y), (float) (point.x - center.x) );
}

float PatternMatching::euclideanDistance2D(CvPoint pointA, CvPoint pointB) {
	return sqrt( pow((pointA.x - pointB.x), 2) + pow( (pointA.y - pointB.y) , 2) );
}

void PatternMatching::calcMarkersAngle (Marker *center, std::vector<Marker *> &markers) {
	for (unsigned int i=0; i < markers.size(); ++i) {
		markers[i]->angle = calcAngle(center->center, markers[i]->center);
	}
}

// http://www.cplusplus.com/reference/stl/vector
void PatternMatching::shift_right(std::vector<Marker *> &markers) {
	/*
	std::cout << ("Original : ");
	for (unsigned int d=0; d < markers.size(); ++d)
		std::cout << markers[d]->colorid;
	std::cout << std::endl;
	*/
	markers.insert(markers.begin(), markers[markers.size()-1]);
	markers.erase(markers.end()-1);
	/*
	std::cout << ("Modificado : ");
	for (unsigned int d=0; d < markers.size(); ++d)
		std::cout << markers[d]->colorid;
	std::cout << std::endl;
	*/

}

// http://www.cplusplus.com/reference/algorithm/sort
void PatternMatching::sortMarkersByAngle(std::vector<Marker *> &markers) {
	std::sort(markers.begin(), markers.end(), LessMarkerAngle());
}

void PatternMatching::calcMarkersNextDistanceAngle(std::vector<Marker *>&markers) {
	//float R = (float) (360*PI*180);
	for (unsigned int i=0; i < markers.size(); ++i) {
		if ((i+1) != markers.size()) {
			markers[i]->next_dist = euclideanDistance2D(markers[i]->center, markers[i+1]->center);
			markers[i]->next_angle_dist = (markers[i+1]->angle - markers[i]->angle);	//Revisar!!
		}
		else {
			markers[i]->next_dist = euclideanDistance2D(markers[0]->center, markers[i]->center);
			markers[i]->next_angle_dist = (markers[0]->angle + ( (float) R - markers[i]->angle) );	//Revisar!!
		}
	}
}

// OUT: matching by color position between two vectors of markers.
bool PatternMatching::matchingMarkersByPosition(std::vector<Marker *> &m1, std::vector<Marker *> &m2) {
	/*
	std::cout << "marcador original : ";
	for (unsigned int j=0; j < m1.size(); ++j) {
		std::cout << m1[j]->colorid;
	}
	std::cout << std::endl;
	*/

	if (m1.size() == m2.size()) {
		for (unsigned int j=0; j < m1.size(); ++j) {
			unsigned int i;
			for (i=0; i < m1.size(); ++i) {
				if (m1[i]->colorid != m2[i]->colorid)
					break;
			}//for
			/*
			std::cout << "i : " << i << std::endl;
			std::cout << "m2.size(): " << m2.size() << std::endl;
			*/

			if (i == m2.size())
				return true;

			shift_right(m2);

		}//for
	}
	return false;
}

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
  \file    pattern.h
  \brief   C++ Interface: Pattern
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef PATTERN_H_
#define PATTERN_H_

#include <opencv2/opencv.hpp>
#include "marker.h"

class Pattern {
public:
	bool enabled;
	std::vector<int> usesColor;	// color id used by the markers
	std::vector<Marker *> markers;
	int num_markers;	// number of markers
	Marker team_marker;

	int id;				// identifier number
	float orientation;	// orientation (first marker)
	CvPoint center;		// central position of the patch
	CvPoint field_pos;	// translated center point to field position using an homography matrix.
	float height;		// height of cover above ground plane
	int window;			// size of the window to search patch

	Pattern();
	virtual ~Pattern();
};

#endif /* PATTERN_H_ */

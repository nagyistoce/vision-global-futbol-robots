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
  \file    homography.h
  \brief   C++ Interface: Homography
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef HOMOGRAPHY_H_
#define HOMOGRAPHY_H_
#include "cv.h"
#include "highgui.h"
#include <stdio.h>

class Homography {
public:
	Homography();
	virtual ~Homography();

	void setImagePoints(CvPoint _p1, CvPoint _p2, CvPoint _p3, CvPoint _p4);
	void setRealPoints(CvPoint _u1, CvPoint _u2, CvPoint _u3, CvPoint _u4);
	void calcMH();

	CvPoint transPoint(CvPoint pixel);

private:
	CvPoint p1, p2, p3, p4;	//image points.
	CvPoint u1, u2, u3, u4;
	CvMat MH;  //matrix H
	double H[9];
};

#endif /* HOMOGRAPHY_H_ */

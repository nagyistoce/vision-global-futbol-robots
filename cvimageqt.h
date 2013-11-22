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
  \file    cvimageqt.h
  \brief   C++ Interface: CvImageQt
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef CVIMAGEQT_H_
#define CVIMAGEQT_H_

#include <QtGui>
#include <cv.hpp>

class CvImageQt {
public:
	CvImageQt();
	virtual ~CvImageQt();
	static QImage IplImage2QImage(const IplImage *iplImage);
	static IplImage* qImage2IplImage(const QImage& qImage);
};

#endif /* CVIMAGEQT_H_ */

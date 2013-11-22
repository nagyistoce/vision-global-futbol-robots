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
  \file    globaltracking.h
  \brief   C++ Interface: GlobalTracking
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef GLOBALTRACKING_H_
#define GLOBALTRACKING_H_

#include "trackingstrategy.h"
#include "team.h"
#include "ball.h"
#include "homography.h"
#include <QtGui>
#include <opencv2/highgui/highgui.hpp>
//#include <iostream>

class GlobalTracking: public TrackingStrategy {
	Q_OBJECT
protected:
	std::vector<sData *> data;
	IplImage *frameCopy;
	QImage qframe;
	int avgFPS;

public:
	GlobalTracking(IplImage *img, Team *blue_team, Team *yellow_team, Ball *ball, std::vector<sColor*>&color, Homography *h);
	GlobalTracking();
	virtual ~GlobalTracking();

	void process(IplImage *frame);
	//void postProcess(IplImage *frame);
	void stopTrackingStrategy();
	int getAvgFPS();

signals:
	void newFrame(const QImage &qframe);

protected:
	void run();
	void resetData();
	void iplimage_from_cvmat(CvMat input, IplImage * output);

private:
	QImage IplImage2QImage(const IplImage *iplImage);
};

#endif /* GLOBALTRACKING_H_ */

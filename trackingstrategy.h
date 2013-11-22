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
  \file    trackingstrategy.h
  \brief   C++ Interface: TrackingStrategy
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef TRACKINGSTRATEGY_H_
#define TRACKINGSTRATEGY_H_

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <cv.h>
#include "datastruct.h"
#include "visionstack.h"
#include "framedata.h"
#include "plugin_colorconversions.h"
#include "plugin_colorsegmentation.h"
#include "plugin_morphology.h"
#include "plugin_detect_balls.h"
#include "plugin_find_blobs.h"
#include "plugin_find_secondaries_blobs.h"
#include "plugin_networking.h"

using namespace std;
using namespace cv;

class TrackingStrategy : public QThread {
	Q_OBJECT
protected:
	IplImage *frame;
	CvRect roi;
	VisionStack s;
	FrameBuffer * rb;
	QMutex stack_mutex; //this mutex protects multi-threaded operations on the stack
	QMutex stoppedMutex;
	volatile bool stopped;

protected:
	virtual void run()=0;

public:
	TrackingStrategy();
	virtual ~TrackingStrategy();

	void setFrameBuffer(FrameBuffer * _rb);
	FrameBuffer * getFrameBuffer() const;

	virtual void process(IplImage *frame)=0;
	//virtual void postProcess(IplImage *frame)=0;

	virtual void stopTrackingStrategy()=0;
};

#endif /* TRACKINGSTRATEGY_H_ */

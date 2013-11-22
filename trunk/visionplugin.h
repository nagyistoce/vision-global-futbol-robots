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
  \file    visionplugin.h
  \brief   C++ Interface: VisionPlugin
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef VISIONPLUGIN_H_
#define VISIONPLUGIN_H_

#include <cv.h>
#include "datastruct.h"
//#include <string>
#include <QMutex>


class VisionPlugin {
protected:
    QMutex mutex;
    double time_proc;
    double time_post;
    void bbox2D(const CvSize imgSize, const int px_length, const CvPoint center, CvRect *r);
public:
	VisionPlugin();
	virtual ~VisionPlugin();

	virtual bool process(IplImage *frame, std::vector<sData *> &data) = 0;

	//you should overload this one to return the name of your plugin
	virtual std::string getName();

    void lock();
    void unlock();

    void setTimeProcessing(double val);
    void setTimePostProcessing(double val);
    double getTimeProcessing();
    double getTimePostProcessing();
};

#endif /* VISIONPLUGIN_H_ */

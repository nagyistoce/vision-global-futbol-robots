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
  \file    visionstack.h
  \brief   C++ Interface: VisionStack
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef VISIONSTACK_H_
#define VISIONSTACK_H_

#include <opencv2/opencv.hpp>
#include "visionplugin.h"
#include "datastruct.h"
#include "timer.h"


class VisionStack {
protected:
	double total;

public:
	VisionStack();
	virtual ~VisionStack();
	std::vector<VisionPlugin *> stack;

	void process(IplImage *frame, std::vector<sData *> &data);
	double getTotalProcessTime();
	//void postProcess(FrameData * data);
	//void updateTimingStatistics();

};

#endif /* VISIONSTACK_H_ */

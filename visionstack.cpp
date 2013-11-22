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
  \file    visionstack.cpp
  \brief   C++ Implementation: VisionStack
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "visionstack.h"

VisionStack::VisionStack() {
	// TODO Auto-generated constructor stub

}

VisionStack::~VisionStack() {
	// TODO Auto-generated destructor stub
}

double VisionStack::getTotalProcessTime(){
	return total;
}

void VisionStack::process(IplImage *frame, std::vector<sData *> &data) {
	double a=0.0;
	double b=0.0;
	unsigned int n=stack.size();
	VisionPlugin * p;
	total=0.0;
	bool show_timing = true;
	if (show_timing) printf("----------\n");
	for (unsigned int i=0;i<n;i++) {
		p=stack[i];
		p->lock();
	    a=GetTimeSec();
	    p->process(frame, data);
	    b=GetTimeSec();
	    p->setTimeProcessing(b-a);
	    total+=(p->getTimeProcessing());
	    if (show_timing) {
	    	printf("Plugin %s: %fms\n",p->getName().c_str(),  p->getTimeProcessing() * 1000.0);
	    }
	    p->unlock();
	}
	if (show_timing) printf("Total time: %fms\n",total * 1000.0);
	//counter_proc+=1.0;

}

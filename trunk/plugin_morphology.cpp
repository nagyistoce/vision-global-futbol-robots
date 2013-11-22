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
  \file    plugin_morphology.cpp
  \brief   C++ Implementation: PluginMorphology
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "plugin_morphology.h"

PluginMorphology::PluginMorphology() {
	// TODO Auto-generated constructor stub

}

PluginMorphology::~PluginMorphology() {
	// TODO Auto-generated destructor stub
}

bool PluginMorphology::process(IplImage *frame, std::vector<sData *> &data) {
	//for (std::vector<sData *>::iterator i = data.begin(); i != data.end(); ++i)
		//printf("hola\n");

	/*
	for (unsigned int i=0; i < data.size(); ++i) {
		if (data[i]->enable)
			cvMorphologyEx(data[i]->segmentated, data[i]->segmentated, NULL, data[i]->morphKernel, CV_MOP_OPEN, 1);
	}
	*/
	cvMorphologyEx(data[cBLUE]->segmentated, data[cBLUE]->segmentated, NULL, data[cBLUE]->morphKernel, CV_MOP_OPEN, 1);
	//cvMorphologyEx(data[cYELLOW]->segmentated, data[cYELLOW]->segmentated, NULL, data[cYELLOW]->morphKernel, CV_MOP_OPEN, 1);
	return true;
}

std::string PluginMorphology::getName() {
  return "Morphology";
}

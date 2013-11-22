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
  \file    plugin_morphology.h
  \brief   C++ Interface: PluginMorphology
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef PLUGIN_MORPHOLOGY_H_
#define PLUGIN_MORPHOLOGY_H_

#include "visionplugin.h"
//#include <stdio.h>

class PluginMorphology: public VisionPlugin {
public:
	PluginMorphology();
	virtual ~PluginMorphology();

	virtual bool process(IplImage *frame, std::vector<sData *> &data);

	virtual std::string getName();
};

#endif /* PLUGIN_MORPHOLOGY_H_ */

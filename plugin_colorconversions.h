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
  \file    plugincolorconversions.h
  \brief   C++ Interface: PluginColorConversions
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef PLUGINCOLORCONVERSIONS_H_
#define PLUGINCOLORCONVERSIONS_H_

#include "visionplugin.h"

class PluginColorConversions: public VisionPlugin {
public:
	PluginColorConversions();
	virtual ~PluginColorConversions();

	//void rgb2hsv(IplImage *src, IplImage *dst);
	virtual bool process(IplImage *frame, std::vector<sData *> &data);

	virtual std::string getName();
};

#endif /* PLUGINCOLORCONVERSIONS_H_ */

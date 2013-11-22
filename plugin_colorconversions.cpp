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
  \file    plugincolorconversions.cpp
  \brief   C++ Implementation: PluginColorConversions
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "plugin_colorconversions.h"

PluginColorConversions::PluginColorConversions() {
	// TODO Auto-generated constructor stub

}

PluginColorConversions::~PluginColorConversions() {
	// TODO Auto-generated destructor stub
}

bool PluginColorConversions::process(IplImage *frame, std::vector<sData *> &data) {
	//cv::cvtColor(src, data->image_hsv, CV_BGR2HSV); //OpenCV 2.x utiliza matrices en lugar de IplImage.
	cvCvtColor(frame, data[0]->image_hsv, CV_BGR2HSV); //CV_YCrCb2BGR);	// notar que OpenCV almacena las imágenes RGB en orden B, G, R.
	return true;
}

std::string PluginColorConversions::getName() {
  return "Color conversion";
}

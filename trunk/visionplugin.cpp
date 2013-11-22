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
  \file    visionplugin.cpp
  \brief   C++ Implementation: VisionPlugin
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "visionplugin.h"

VisionPlugin::VisionPlugin() {
	// TODO Auto-generated constructor stub

}

VisionPlugin::~VisionPlugin() {
	// TODO Auto-generated destructor stub
}

void VisionPlugin::bbox2D(const CvSize imgSize, const int px_length, const CvPoint center, CvRect *box) {
	int l = (int) (px_length/2);

	box->x = (center.x - l);
	if (box->x < 0)
		box->x=0;

	box->y = (center.y - l);
	if (box->y < 0)
		box->y=0;

	if (imgSize.width < (box->x + px_length))
		box->width = (imgSize.width - 1);
	else
		box->width = px_length;


	if (imgSize.height < (box->y + px_length))
		box->height = (imgSize.height - 1);
	else
		box->height = px_length;
}

std::string VisionPlugin::getName() {
  return "Unnamed";
}

void VisionPlugin::lock() {
  mutex.lock();
}

void VisionPlugin::unlock() {
  mutex.unlock();
}

void VisionPlugin::setTimeProcessing(double val) {
  time_proc=val;
}

void VisionPlugin::setTimePostProcessing(double val) {
  time_post=val;
}

double VisionPlugin::getTimeProcessing() {
  return time_proc;
}

double VisionPlugin::getTimePostProcessing() {
  return time_post;
}

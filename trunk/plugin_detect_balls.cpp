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
  \file    plugin_detect_balls.cpp
  \brief   C++ Implementation: PluginDetectBalls
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "plugin_detect_balls.h"

PluginDetectBalls::PluginDetectBalls() {
	// TODO Auto-generated constructor stub

}

PluginDetectBalls::~PluginDetectBalls() {
	// TODO Auto-generated destructor stub
}

bool PluginDetectBalls::process(IplImage *frame, std::vector<sData *> &data) {
	colorid = data[0]->ball->color_id;
	data[colorid]->result = cvLabel(data[colorid]->segmentated, data[colorid]->labelImg, data[colorid]->blobs);
	cvFilterByArea(data[colorid]->blobs, data[colorid]->ball->area_min, data[colorid]->ball->area_max);

	for (CvBlobs::iterator it=data[colorid]->blobs.begin(); it!=data[colorid]->blobs.end(); ++it) {
		int width = MAX( (*it).second->maxx - (*it).second->minx, (*it).second->maxy - (*it).second->miny );
		width= (int) width; //*1.5;
		//bbox2D(const CvSize imgSize, const int px_length, const CvPoint center, CvRect *box)
		bbox2D(cvGetSize(frame), width, cvPoint((*it).second->centroid.x, (*it).second->centroid.y), &r);  //calculate r box to set image roi later.
		cvRectangle(frame, cvPoint(r.x, r.y), cvPoint(r.x+r.width, r.y+r.height), cvScalar(0, 0, 255, 0), 1, 8, 0);

		data[colorid]->ball->center.x = (int) (*it).second->centroid.x;
		data[colorid]->ball->center.y = (int) (*it).second->centroid.y;
		data[colorid]->ball->field_pos = data[0]->homography->transPoint(data[colorid]->ball->center); //field position

		break;
	}

	return true;
}

std::string PluginDetectBalls::getName() {
  return "Ball detection";
}

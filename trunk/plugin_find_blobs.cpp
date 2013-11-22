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
  \file    plugin_find_blobs.cpp
  \brief   C++ Implementation: PluginFindBlobs
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "plugin_find_blobs.h"

PluginFindBlobs::PluginFindBlobs() {
	// TODO Auto-generated constructor stub

}

PluginFindBlobs::~PluginFindBlobs() {
	// TODO Auto-generated destructor stub
}

bool PluginFindBlobs::process(IplImage *frame, std::vector<sData *> &data) {
	data[cBLUE]->result = cvLabel(data[cBLUE]->segmentated, data[cBLUE]->labelImg, data[cBLUE]->blobs);
	cvFilterByArea(data[cBLUE]->blobs,5, 50000);


	//cvRenderBlobs(data[cBLUE]->labelImg, data[cBLUE]->blobs, frame, frame, CV_BLOB_RENDER_COLOR|CV_BLOB_RENDER_CENTROID|CV_BLOB_RENDER_BOUNDING_BOX|CV_BLOB_RENDER_ANGLE, 1);

	//data[cYELLOW]->result = cvLabel(data[cYELLOW]->segmentated, data[cYELLOW]->labelImg, data[cYELLOW]->blobs);
	//cvFilterByArea(data[cYELLOW]->blobs,100, 50000);
	//cvRenderBlobs(data[cYELLOW]->labelImg, data[cYELLOW]->blobs, frame, frame, CV_BLOB_RENDER_COLOR|CV_BLOB_RENDER_CENTROID|CV_BLOB_RENDER_BOUNDING_BOX|CV_BLOB_RENDER_ANGLE, 1);

/*
	for (int i=0; i < NUM_COLOR_TYPES; ++i) {
		data[i]->result = cvLabel(data[i]->segmentated, data[i]->labelImg, data[i]->blobs);
		cvFilterByArea(data[i]->blobs,1000, 50000);
		//cvRenderBlobs(data[i]->labelImg, data[i]->blobs, frame, frame, CV_BLOB_RENDER_COLOR|CV_BLOB_RENDER_CENTROID|CV_BLOB_RENDER_BOUNDING_BOX|CV_BLOB_RENDER_ANGLE, 1);
	}
	cvRenderBlobs(data[cBLUE]->labelImg, data[cBLUE]->blobs, frame, frame, CV_BLOB_RENDER_COLOR|CV_BLOB_RENDER_CENTROID|CV_BLOB_RENDER_BOUNDING_BOX|CV_BLOB_RENDER_ANGLE, 1);

*/
	return true;
}

std::string PluginFindBlobs::getName() {
  return "Find blobs";
}

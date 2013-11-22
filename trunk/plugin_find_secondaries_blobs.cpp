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
  \file    plugin_find_secondaries_blobs.cpp
  \brief   C++ Implementation: PluginFindSecondariesBlobs
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "plugin_find_secondaries_blobs.h"
#include <stdio.h>

PluginFindSecondariesBlobs::PluginFindSecondariesBlobs() {
	// TODO Auto-generated constructor stub
	matching = new PatternMatching();

	rot_mat = cvCreateMat(2, 2, CV_32FC1);
	r_mat = cvCreateMat(2, 1, CV_32FC1);

	M = cvCreateMat(2, 1, CV_32FC1);
	M->data.fl[ 0 * M->cols + 0 ] = (float)15.0; // M_x
	M->data.fl[ 1 * M->cols + 0 ] = (float)0.0; // M_y
}

PluginFindSecondariesBlobs::~PluginFindSecondariesBlobs() {
	// TODO Auto-generated destructor stub
}

bool PluginFindSecondariesBlobs::process(IplImage *frame, std::vector<sData *> &data) {
	int colorId=data[0]->blue_team->team_colorid;
	for (CvBlobs::iterator it=data[colorId]->blobs.begin(); it!=data[colorId]->blobs.end(); ++it) {
		int width = MAX( (*it).second->maxx - (*it).second->minx, (*it).second->maxy - (*it).second->miny );
		width= (int) width*2.5; //1.5;
		//bbox2D(const CvSize imgSize, const int px_length, const CvPoint center, CvRect *box)
		bbox2D(cvGetSize(frame), width, cvPoint((*it).second->centroid.x, (*it).second->centroid.y), &r);  //calculate r box to set image roi later.
		cvRectangle(frame, cvPoint(r.x, r.y), cvPoint(r.x+r.width, r.y+r.height), cvScalar(255, 0, 0, 0), 1, 8, 0);

		std::vector<Marker *> markers;
		Marker *mcenter = new Marker(); //main team marker

		mcenter->center.x = (int) (*it).second->centroid.x;
		mcenter->center.y = (int) (*it).second->centroid.y;

		for (unsigned int i=0; i < data[0]->blue_team->usesColor.size(); ++i) {
			int cid = data[0]->blue_team->usesColor[i];

			cvSetImageROI(data[cid]->segmentated, cvRect(r.x, r.y, r.width, r.height));
			data[cid]->result = cvLabel(data[cid]->segmentated, data[cid]->labelImg, data[cid]->blobs);
			cvFilterByArea(data[cid]->blobs,10, 50000);

			for (CvBlobs::iterator it2=data[cid]->blobs.begin(); it2!=data[cid]->blobs.end(); ++it2) {
				Marker *m = new Marker();
				m->center.x = (int) (*it2).second->centroid.x + r.x;
				m->center.y = (int) (*it2).second->centroid.y + r.y;
				m->colorid = cid;
				markers.push_back(m);

				cvCircle(frame, cvPoint((*it2).second->centroid.x+r.x, (*it2).second->centroid.y+r.y), 3, cvScalar(0, 255, 0, 0), 1, 8, 0);
				//cvCircle(frame, cvPoint((*it2).second->centroid.x, (*it2).second->centroid.y), 3, cvScalar(0, 255, 0, 0), 1, 8, 0);
			}
			cvResetImageROI(data[cid]->segmentated);
		}//for

		matching->calcMarkersAngle(mcenter, markers);
		//printf ("The arc tangent for (cx=%i, cy=%i) and (mx=%i, my=%i) is %f degrees and is %f\n", mcenter->center.x, mcenter->center.y, m->center.x, m->center.y, (float) (m->angle * 180 / 3.14159265), m->angle);
		matching->sortMarkersByAngle(markers);

		//TODO: it isn't efficient at all!
		for (unsigned int j=0; j < data[0]->blue_team->patches.size(); ++j) {
			bool f = matching->matchingMarkersByPosition(data[0]->blue_team->patches[j]->markers, markers);
			if (f) {
				//printf("SUCCESS\n");
				data[0]->blue_team->patches[j]->center = mcenter->center; //pixel position
				data[0]->blue_team->patches[j]->field_pos = data[0]->homography->transPoint(mcenter->center); //field position

				//data[0]->blue_team->patches[j]->orientation = markers[0]->angle + ( (markers[1]->angle - markers[0]->angle) / 2 );
				data[0]->blue_team->patches[j]->orientation = markers[1]->angle;
				//printf("orientación : %2.2f\n", data[0]->blue_team->patches[j]->orientation);
				rotation_matrix(data[0]->blue_team->patches[j]->orientation);

				//rotation
				r_mat->data.fl[ 0 * r_mat->cols + 0 ] = M->data.fl[ 0 * M->cols + 0 ] * rot_mat->data.fl[ 0 * rot_mat->cols + 0 ] + M->data.fl[ 1 * M->cols + 0 ] * rot_mat->data.fl[ 0 * rot_mat->cols + 1 ];
				r_mat->data.fl[ 1 * r_mat->cols + 0 ] = M->data.fl[ 0 * M->cols + 0 ] * rot_mat->data.fl[ 1 * rot_mat->cols + 0 ] + M->data.fl[ 1 * M->cols + 0 ] * rot_mat->data.fl[ 1 * rot_mat->cols + 1 ];
				int x = (int) cvRound(r_mat->data.fl[ 0 * r_mat->cols ]);
				int y = (int) cvRound(r_mat->data.fl[ 1 * r_mat->cols ]);

				//traslation
				x = x + data[0]->blue_team->patches[j]->center.x;
				y = y + data[0]->blue_team->patches[j]->center.y;
				cvCircle(frame, cvPoint(x, y), 2, cvScalar(255, 255, 0), CV_FILLED, CV_AA, 0);

				for (unsigned int k=0; k < markers.size(); ++k) {
					cvLine(frame, cvPoint(mcenter->center.x, mcenter->center.y), cvPoint(markers[k]->center.x, markers[k]->center.y), cvScalar(255,0,0), 1);
					data[0]->blue_team->patches[j]->markers[k]->dist = matching->euclideanDistance2D(mcenter->center, markers[k]->center);	// distance between central main marker and a marker.
				}
			}
		}//for

		//cleaning
		for (unsigned int j=0; j < markers.size(); ++j) {
			markers[j]->~Marker();
			markers.erase(markers.begin());
		}
		mcenter->~Marker();
	}
	return true;
}

std::string PluginFindSecondariesBlobs::getName() {
  return "Find secondaries blobs";
}

void PluginFindSecondariesBlobs::rotation_matrix(float tita) {
    //cvZero(rot_mat);
    rot_mat->data.fl[ 0 * rot_mat->cols + 0 ] = (float)cos(tita);
    rot_mat->data.fl[ 0 * rot_mat->cols + 1 ] = (float)-sin(tita);
    rot_mat->data.fl[ 1 * rot_mat->cols + 0 ] = (float)sin(tita);
    rot_mat->data.fl[ 1 * rot_mat->cols + 1 ] = (float)cos(tita);
}

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
  \file    capturefromcam.cpp
  \brief   C++ Implementation: CaptureFromCamera
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "capturefromcamera.h"

CaptureFromCamera::CaptureFromCamera(int _camId) {
	camId = _camId;
}

CaptureFromCamera::~CaptureFromCamera() {
	// TODO Auto-generated destructor stub
}

Mat CaptureFromCamera::getFrame() {
	capture >> frame;	// get a new frame from camera.
	return frame;
}

int CaptureFromCamera::getFrameHeight() {
	return frame_height;
}

int CaptureFromCamera::getFrameWidth() {
	return frame_width;
}

bool CaptureFromCamera::setFrameWidth(int width) {
	bool flag = capture.set(CV_CAP_PROP_FRAME_WIDTH, width);
	return flag;
}

//160x120, 176x144, 320x240, 352x288, 640x480
bool CaptureFromCamera::setFrameHeight(int height) {
	bool flag = capture.set(CV_CAP_PROP_FRAME_HEIGHT, height);
	return flag;
}

bool CaptureFromCamera::isCapturing() {
	return capture.isOpened();
}

void CaptureFromCamera::releaseFrame() {
}

bool CaptureFromCamera::startCapture() {
	if (!capture.open(camId)) {
		cout << "Failed to open video capture device: " << camId << endl;
		return (false);
	}
	// FIXME
	capture.set(CV_CAP_PROP_FRAME_WIDTH, 352);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 288);

	frame_height = (int) capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	frame_width = (int) capture.get(CV_CAP_PROP_FRAME_WIDTH);
	return true;
}

bool CaptureFromCamera::stopCapture() {
	capture.release();
	return true;
}

string CaptureFromCamera::getCaptureMethodName() const {
	return "Capturing from camera";
}



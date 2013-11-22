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
  \file    capturefromfile.cpp
  \brief   C++ Implementation: CaptureFromFile
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "capturefromfile.h"

CaptureFromFile::CaptureFromFile(string _filename) {
	// TODO Auto-generated constructor stub
	filename = _filename;
	fps = 1;
	frame_counter = 0;
}

CaptureFromFile::~CaptureFromFile() {
	// TODO Auto-generated destructor stub
}

Mat CaptureFromFile::getFrame() {
	// 1000000 microsec = 1 sec	// TODO: fps should be changeable to video reproduction speed
	usleep(1000000/fps);
	capture >> frame;	// get a new frame from camera.
	if (!frame.empty())
		frame_counter++;
	return frame;
}

bool CaptureFromFile::isCapturing() {
	return capture.isOpened();
}

void CaptureFromFile::releaseFrame() {
}

bool CaptureFromFile::startCapture() {
	if (!capture.open(filename)) {
		cout << "Failed to open video: " << filename << endl;
		return (false);
	}
	fps = (int) capture.get(CV_CAP_PROP_FPS);	// by default it's initialized to video's FPS.
	if (fps == 0) return false;
	total_frames = (int) capture.get(CV_CAP_PROP_FRAME_COUNT);
	frame_height = (int) capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	frame_width = (int) capture.get(CV_CAP_PROP_FRAME_WIDTH);
	return (true);
}

bool CaptureFromFile::stopCapture() {
	capture.release();
	return true;
}

string CaptureFromFile::getCaptureMethodName() const {
	return "Capturing from file";
}

int CaptureFromFile::getFrameRate() {
	return fps;
}

bool CaptureFromFile::setFrameRateToPlay(int _fps) {
	if (_fps == 0) {
		cout << "Warning: It's not possible to set FPS to 0." << endl;
		return false;
	}
	fps = _fps;
	return true;
}

int CaptureFromFile::getFrameHeight() {
	return frame_height;
}

int CaptureFromFile::getFrameWidth() {
	return frame_width;
}

int CaptureFromFile::getTotalFrames(){
	return total_frames;
}

int CaptureFromFile::getCurrentFrameIndex() {
	int idx = (int) capture.get(CV_CAP_PROP_POS_FRAMES);
	return idx;
}

bool CaptureFromFile::goToFrame( int _frameNumber) {
	bool flag = capture.set(CV_CAP_PROP_POS_FRAMES, (double) _frameNumber);
	return (flag);
}

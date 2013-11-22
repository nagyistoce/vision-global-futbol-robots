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
  \file    capturefromfile.h
  \brief   C++ Interface: CaptureFromFile
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef CAPTUREFROMFILE_H_
#define CAPTUREFROMFILE_H_

#include <iostream>
#include "captureinterface.h"

/*!
  \class   CaptureFromFile
  \brief   Get frames capturing it from a video file.
*/

class CaptureFromFile: public CaptureInterface {
public:
	CaptureFromFile(string _filename);
	virtual ~CaptureFromFile();

    virtual Mat 	getFrame();
    virtual int  	getFrameHeight();
    virtual int  	getFrameWidth();
    virtual bool	isCapturing();
    virtual void	releaseFrame();
    virtual bool	startCapture();
    virtual bool	stopCapture();
    virtual string	getCaptureMethodName() const;

    int  getFrameRate();
    bool setFrameRateToPlay(int _fps);
    int  getTotalFrames();
    int  getCurrentFrameIndex();
    bool goToFrame( int _frameNumber);


protected:
	string filename;
	VideoCapture capture;
	Mat frame;
	int fps;
	int total_frames;
	int frame_height;
	int frame_width;
	int frame_counter;

};

#endif /* CAPTUREFROMFILE_H_ */

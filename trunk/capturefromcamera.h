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
  \file    capturefromcamera.h
  \brief   C++ Interface: CaptureFromCamera
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef CAPTUREFROMCAMERA_H_
#define CAPTUREFROMCAMERA_H_

#include <iostream>
#include "captureinterface.h"

using namespace std;
using namespace cv;

/*!
  \class   CaptureFromCamera
  \brief   Get frames capturing it from a camera device.
*/

class CaptureFromCamera : public CaptureInterface {

public:
	CaptureFromCamera(int _camId);
	virtual ~CaptureFromCamera();

    virtual Mat 	getFrame();
    virtual int  	getFrameHeight();
    virtual int  	getFrameWidth();
    virtual bool	isCapturing();
    virtual void	releaseFrame();
    virtual bool	startCapture();
    virtual bool	stopCapture();
    virtual string	getCaptureMethodName() const;

    bool setFrameWidth(int width);
    bool setFrameHeight(int height);

protected:
    int camId;
	VideoCapture capture;
	Mat frame;
	int frame_height;
	int frame_width;

};

#endif /* CAPTUREFROMCAMERA_H_ */

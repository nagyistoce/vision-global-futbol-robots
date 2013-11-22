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
  \file    captureinterface.h
  \brief   C++ Interface: CaptureInterface
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef CAPTUREINTERFACE_H
#define CAPTUREINTERFACE_H
#include <string>
#include <stdio.h>
//#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class CaptureInterface
{
public:
    CaptureInterface();
    virtual ~CaptureInterface();

    virtual Mat getFrame()     = 0;

    virtual int  	getFrameHeight() = 0;
    virtual int  	getFrameWidth()	= 0;

    /// This function should return true, if your method is currently
    /// actively capturing data.
    virtual bool     isCapturing() = 0;

    /// This releases the pointer of a previous \c getFrame() call.
    virtual void     releaseFrame() = 0;

    /// This will make your method start capturing data
    /// Note, that upon construction, your class should NOT be starting
    /// to capture data automatically.
    /// Instead a call to startCapture() is required.
    virtual bool     startCapture() = 0;

    /// This will make your method stop capturing data
    virtual bool     stopCapture() = 0;

    /// If applicable, this will enforce a reinitialization / reset
    /// on your capturing hardware, in case something went wrong.
    ///
    /// This is applicable, for example for DC1394 based systems
    /// where a firewire bus is able to 'freeze up' and can be
    /// reinitialized by a bus reset.
    virtual bool     resetBus();

    /// Return a string describing your capture method
    /// e.g. DC1394B, or GigEVision, or V4LCapture, or USBCam,...
    virtual string   getCaptureMethodName() const = 0;
};

#endif

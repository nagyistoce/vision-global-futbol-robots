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
  \file    capture_thread.h
  \brief   C++ Interface: CaptureThread
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef CAPTURE_THREAD_H
#define CAPTURE_THREAD_H

#include <QThread>
#include <QtGui>
#include "ringbuffer.h"
#include "framedata.h"
#include "framecounter.h"
#include "visionstack.h"
#include "capturestats.h"
#include "opencv/highgui.h"
#include "captureinterface.h"
#include "capturefromcamera.h"
#include "capturefromfile.h"

using namespace std;

/*!
  \class   CaptureThread
  \brief   A thread for capturing and processing video data
*/
class CaptureThread : public QThread
{
Q_OBJECT
protected:
	QMutex stoppedMutex;
	QMutex capture_mutex; //this mutex protects multi-threaded operations on the capture control
	QMutex showMutex;
	FrameCounter * counter;
	CaptureInterface * capture;
	CaptureFromCamera * captureFromCamera;
	CaptureFromFile * captureFromFile;
	FrameBuffer *rb;
	int camId;
	Timer timer;
	volatile bool stopped;
	QImage qframe;
	volatile bool show;
	string captureMethod;
	int avgFPS;

public slots:
	bool init();
	bool stop();
//  bool reset();
//  void refresh();
//  void selectCaptureMethod();

public:
	CaptureThread(int cam_id);  // only for one camera -> mono-vision
	CaptureThread(string _filename); // only for a video file
	//CaptureThread(int camId1, int camId2); // for two cameras -> stereo-vision
	~CaptureThread();
	void setFrameBuffer(FrameBuffer * _rb);
	FrameBuffer * getFrameBuffer() const;
	void stopCaptureThread();
	void display(bool _show);
	int getFPS();

signals:
	void newFrame(const QImage &qframe);

protected:
	virtual void run();

private:
	QImage IplImage2QImage(const IplImage *iplImage);

};

#endif

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
  \file    capture_thread.cpp
  \brief   C++ Implementation: CaptureThread
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "capture_thread.h"

CaptureThread::CaptureThread(int cam_id) {
  counter=new FrameCounter();
  stopped=false;
  show=false;
  rb=0;
  camId=cam_id;
  capture = new CaptureFromCamera(camId);
  captureMethod = "camera";
  avgFPS = 0;
}

CaptureThread::CaptureThread(string _filename) {
  counter=new FrameCounter();
  stopped=false;
  show=true;
  rb=0;
  capture = new CaptureFromFile(_filename);
  captureMethod = "file";
  avgFPS = 0;
}

CaptureThread::~CaptureThread() {
  delete counter;
  delete capture;
}

void CaptureThread::setFrameBuffer(FrameBuffer * _rb) {
  rb=_rb;
}

FrameBuffer * CaptureThread::getFrameBuffer() const {
  return rb;
}

bool CaptureThread::init() {
  capture_mutex.lock();
  bool res = capture->startCapture();
  capture_mutex.unlock();
  return res;
}

bool CaptureThread::stop() {
  capture_mutex.lock();
  bool res = capture->stopCapture();
  capture_mutex.unlock();
  return res;
}

void CaptureThread::display(bool _show) {
	showMutex.lock();
	show = _show;
	showMutex.unlock();
}

void CaptureThread::stopCaptureThread() {
    stoppedMutex.lock();
    stopped=true;
    stoppedMutex.unlock();
} // stopCaptureThread()

int CaptureThread::getFPS() {
	return avgFPS;
}

void CaptureThread::run() {
	double t;
	long long num=1;
	long ac=0;

    while(true) {
        /////////////////////////////////
        // Stop thread if stopped=TRUE //
        /////////////////////////////////
    	stoppedMutex.lock();
    	if (stopped) {
    		stopped=false;
    		stoppedMutex.unlock();
    		break;
    	}
    	stoppedMutex.unlock();
        /////////////////////////////////
        /////////////////////////////////

    	if (rb!=0) {
    		//cout << "capture thread" << endl;
    		int idx=rb->curWrite();
    		FrameData * d=rb->getPointer(idx);
    		if ((capture != 0) && (capture->isCapturing())) {
    			//time needed to take a frame
    			t = (double)cvGetTickCount();
    			d->video = capture->getFrame(); // capture and add frame to buffer
    			t = (double)cvGetTickCount() - t;
    			d->time = t/((double)cvGetTickFrequency()*1000.);
    			//cout << "getFrame time: " << d->time << endl;

    			//calculating average fps
    			ac += d->time;
    			avgFPS = (int) (ac/num);

    			if (d->video.empty()) stopCaptureThread();
    			d->number=num++;
    			rb->nextWrite(true); //allow_lapping. This means that we are overwriting old frames which have not been read yet.
    			if (show) {
    				IplImage img = d->video;
    				qframe = IplImage2QImage(&img);
    				emit newFrame(qframe);
    			}
    		}
    	}

    } // while
}


QImage CaptureThread::IplImage2QImage(const IplImage *iplImage)
{
    int height = iplImage->height;
    int width = iplImage->width;

    if  (iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 3)
    {
      const uchar *qImageBuffer = (const uchar*)iplImage->imageData;
      QImage img(qImageBuffer, width, height, QImage::Format_RGB888);
      return img.rgbSwapped();
    } else if  (iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 1){
	const uchar *qImageBuffer = (const uchar*)iplImage->imageData;
	QImage img(qImageBuffer, width, height, QImage::Format_Indexed8);

	QVector<QRgb> colorTable;
	for (int i = 0; i < 256; i++){
	    colorTable.push_back(qRgb(i, i, i));
	}
	img.setColorTable(colorTable);
	return img;
    }else{
      qWarning() << "Image cannot be converted.";
      return QImage();
    }
}

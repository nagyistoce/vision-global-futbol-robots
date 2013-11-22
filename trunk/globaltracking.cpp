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
  \file    globaltracking.cpp
  \brief   C++ Implementation: GlobalTracking
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "globaltracking.h"
GlobalTracking::GlobalTracking() {
	stopped=false;
}
GlobalTracking::GlobalTracking(IplImage *img, Team *blue_team, Team *yellow_team, Ball *ball, std::vector<sColor*>&color, Homography *h) {
	// TODO Auto-generated constructor stub
	stopped=false;
	rb=0;
	avgFPS=0;

	CvSize imgSize = cvGetSize(img);

	for (int j=0; j < NUM_COLOR_TYPES; j++)
		printf("NUM_COLOR_TYPES = %i\n", NUM_COLOR_TYPES);

	for (int i=0; i < NUM_COLOR_TYPES; i++) {
		data.push_back(new sData());
		data[i]->image_hsv = cvCreateImage(imgSize, img->depth, img->nChannels);
		data[i]->segmentated=cvCreateImage(imgSize, 8, 1);
		cvSet(data[i]->segmentated, cvScalar(0));	// Clear image to black.
		data[i]->morphKernel = cvCreateStructuringElementEx(2, 2, 1, 1, CV_SHAPE_RECT, NULL);
		data[i]->labelImg = cvCreateImage(imgSize, IPL_DEPTH_LABEL, 1);
		cvReleaseBlobs(data[i]->blobs);
		cvReleaseTracks(data[i]->tracks);
		data[i]->blue_team = blue_team;
		data[i]->yellow_team = yellow_team;
		data[i]->ball = ball;
		data[i]->enable=false;
		data[i]->homography=h;
	}

	// enable colors to find by each team (blue and yellow)
	data[blue_team->team_colorid]->enable = true;
	for (unsigned int i=0; i < blue_team->usesColor.size(); ++i) {
		data[blue_team->usesColor[i]]->enable = true;
	}

	// enable color to find the ball
	data[ball->color_id]->enable = true;

	//data[cBLUE]->enable=true;
	//data[cYELLOW]->enable=true;

	s.stack.push_back(new PluginColorConversions());
	s.stack.push_back(new PluginColorSegmentation(color));
	s.stack.push_back(new PluginMorphology());
	s.stack.push_back(new PluginDetectBalls());
	s.stack.push_back(new PluginFindBlobs());
	s.stack.push_back(new PluginFindSecondariesBlobs());
	s.stack.push_back(new Plugin_Networking());
}

GlobalTracking::~GlobalTracking() {
	// TODO Auto-generated destructor stub
}

void GlobalTracking::process(IplImage *frame) {
	s.process(frame, data);
	frameCopy=cvCloneImage(frame);
	qframe = IplImage2QImage(frameCopy);
	cvReleaseImage(&frameCopy);
	emit newFrame(qframe);
	this->resetData();
}

void GlobalTracking::resetData() {
	for (int i=0; i < NUM_COLOR_TYPES; ++i) {
		cvSet(data[i]->segmentated, cvScalar(0));	// Clear image to black.
		data[i]->result=0;
		cvReleaseBlobs(data[i]->blobs);
		cvReleaseTracks(data[i]->tracks);
	}
	/*
	cvSet(data[cBLUE]->segmentated, cvScalar(0));	// Clear image to black.
	data[cBLUE]->result=0;
	cvReleaseBlobs(data[cBLUE]->blobs);
	cvReleaseTracks(data[cBLUE]->tracks);
	*/
}

void GlobalTracking::stopTrackingStrategy() {
	stoppedMutex.lock();
	stopped=true;
	stoppedMutex.unlock();
}

int GlobalTracking::getAvgFPS(){
	return avgFPS;
}

void GlobalTracking::run() {
	long long prevFrameNum, curFrameNum;
	prevFrameNum = -1;
	curFrameNum = 0;
	double ac = 0;
	long long num=1;
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
    		int idx=rb->curRead();
    		FrameData *d=rb->getPointer(idx);
    		IplImage img = d->video;
    		curFrameNum = d->number;
    		if (prevFrameNum < curFrameNum) {
    			frameCopy = cvCloneImage(&img);
				s.process(frameCopy, data);

				//calculating average fps
				ac += s.getTotalProcessTime();
				avgFPS = (int) (ac*1000.0/num);
				num++;

				qframe = IplImage2QImage(frameCopy);
				cvReleaseImage(&frameCopy);
				emit newFrame(qframe);
				resetData();
    		}
    		else {
    			//cout << "frame already processed!" << endl;
    			//usleep(5000);
    		}
    		rb->nextRead(true);
    		prevFrameNum=curFrameNum;
    		//usleep(5000);
    		/*
    		stack_mutex.lock();
    		if (stack!=0) {
    			stack->process(d);
    			stack->postProcess(d);
    		}
    		stack_mutex.unlock();
    		rb->nextRead(true);
    		*/

    	} // if
    } // while
}

QImage GlobalTracking::IplImage2QImage(const IplImage *iplImage)
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


void GlobalTracking::iplimage_from_cvmat(CvMat input, IplImage * output)
{
  int x,y;
  for( x=0; x < output->width; x++ ){
    for( y=0; y < output->height; y++) {
      // note: CvMat is indexed (row, column) but IplImage is indexed (x,y)
      // so the indexes must be interchanged!
      cvSetReal2D( output, x, y, CV_MAT_ELEM(input, uchar, y, x) );
    }
  }
}

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
  \file    cvimageqt.cpp
  \brief   C++ Implementation: CvImageQt
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "cvimageqt.h"

CvImageQt::CvImageQt() {
	// TODO Auto-generated constructor stub

}

CvImageQt::~CvImageQt() {
	// TODO Auto-generated destructor stub
}

QImage CvImageQt::IplImage2QImage(const IplImage *iplImage)
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

IplImage* CvImageQt::qImage2IplImage(const QImage& qImage) {
    int width = qImage.width();
    int height = qImage.height();

    // Creates a iplImage with 3 channels
    IplImage *img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
    char * imgBuffer = img->imageData;

    //Remove alpha channel
    int jump = (qImage.hasAlphaChannel()) ? 4 : 3;

    for (int y=0;y<img->height;y++){
      QByteArray a((const char*)qImage.scanLine(y), qImage.bytesPerLine());
      for (int i=0; i<a.size(); i+=jump){
          //Swap from RGB to BGR
          imgBuffer[2] = a[i];
          imgBuffer[1] = a[i+1];
          imgBuffer[0] = a[i+2];
          imgBuffer+=3;
      }
  }

  return img;
}

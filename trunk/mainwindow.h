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
  \file    mainwindow.h
  \brief   C++ Interface: MainWindow
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutex>
#include <QWaitCondition>
#include <cv.hpp>
#include <cvaux.h>
#include <highgui.h>
#include "cvimageqt.h"
#include "capture_thread.h"
#include "globaltracking.h"
#include "team.h"
#include "ball.h"
#include "pattern.h"
#include "marker.h"
#include "datastruct.h"
#include "editcolorgui.h"
#include "homography.h"
//#include "editcamgui.h"
#include "framedata.h"
#include "segmentation.h"

namespace Ui {
    class MainWindow;
}

using namespace std;

class CaptureConnectDialog;
class DimensionsFieldDialog;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::vector<sColor*> color;

protected:
    void changeEvent(QEvent *e);
    QWaitCondition next_capture;
    QMutex capture_mutex; //this mutex protects multi-threaded operations on the capture control

    //test
    CaptureFromCamera *capture;

private:
    static QImage IplImage2QImage(const IplImage *iplImage);

protected slots:
    void about();
    void editCamara1();
    void editColor();
    void editDimensionsFieldDialog();
    void iniciar_hiloA();
    void detener_hiloA();
    void iniciar_hiloB();
    void detener_hiloB();
    void updateMouseCursorPosLabel();
    void updateDimension(QPoint p);
    void colorPicker(QPoint p);
    void colorGUIClosed();

private slots:
    void updateFrame(const QImage &frame);
    void putImage(IplImage *cvimage);

signals:
	void pixelPick(const QImage, QPoint);

private:
    Ui::MainWindow *ui;
    EditColorGUI *colorGUI;
    CaptureConnectDialog *captureConnectDialog;
    DimensionsFieldDialog *dimensionsFieldDialog;
    CaptureThread *hilo_captura;
    GlobalTracking *hilo_gt;
    bool flag_gt, done;
    Team blue_team;
    Ball ball;
    sColor *c;
    Homography h;
    double tt;
    FrameBuffer *rb;
    int deviceNumber;
    CvPoint p1, p2, p3, p4;
    CvPoint u1, u2, u3, u4;
    bool flag_dimension;
    bool rightButtonPressed, fp1, fp2, fp3, fp4;
    int x,y;
    bool flag_rbclick;
    QPoint point;
    Segmentation segmentation;
    CvImageQt conv;
    bool showColors;

    QImage qimage;
    CvImageQt cvimageqt;
    IplImage *frame, *frameCopy;
    CvSize frame_sz;;
    QMutex image_mutex;
};

#endif // MAINWINDOW_H

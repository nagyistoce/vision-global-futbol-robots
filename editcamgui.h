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
  \file    editcamgui.h
  \brief   C++ Interface: editCamGUI
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef EDITCAMGUI_H
#define EDITCAMGUI_H

#include <QWidget>
#include <camara.h>
#include <mono.h>
#include <vision.h>
#include "cvimageqt.h"

namespace Ui {
    class editCamGUI;
}

class editCamGUI : public QWidget {
    Q_OBJECT
public:
    editCamGUI(QWidget *parent = 0);
    editCamGUI(vision *v, int index, QWidget *parent = 0);
    ~editCamGUI();

protected:
    void changeEvent(QEvent *e);
    void timerEvent(QTimerEvent*);
    void closeEvent(QCloseEvent *event);

protected slots:
    void spinBoxCamaraIndex();
    void buttonStart();
    void buttonStop();
    void buttonIntrinsics();
    void buttonDistortion();
    void buttonApply();
    void buttonClear();
    void buttonConfiguration();

private:
    Ui::editCamGUI *ui;
    Camara *cam;
    IplImage *frame;
    Mono *mono;
    bool monoFlag;
    CvSize frame_sz;
    bool intrinsicsFlag;
    bool distortionFlag;
    bool applyFlag;

    QImage image;
    CvImageQt cvimageqt;
    int timerID;
    bool timerFlag;

    vision *v;
    int vlIndex;

    void putImage(IplImage *cvimage);
};

#endif // EDITCAMGUI_H

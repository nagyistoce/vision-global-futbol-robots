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
  \file    mainwindow.cpp
  \brief   C++ Implementation: MainWindow
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include <QtGui>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "captureconnectdialog.h"
#include "dimensionsfielddialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionAcerca_de, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionEditCamara1, SIGNAL(triggered()), this, SLOT(editCamara1()));
    connect(ui->actionDimensionsField, SIGNAL(triggered()), this, SLOT(editDimensionsFieldDialog()));
    connect(ui->actionEditColor, SIGNAL(triggered()), this, SLOT(editColor()));
    connect(ui->actionIniciar, SIGNAL(triggered()), this, SLOT(iniciar_hiloA()));
    //connect(ui->actionDetener, SIGNAL(triggered()), this, SLOT(detener_hiloA()));
    connect(ui->actionIniciarTrackingGlobal, SIGNAL(triggered()), this, SLOT(iniciar_hiloB()));
    connect(ui->actionDetenerTrackingGlobal, SIGNAL(triggered()), this, SLOT(detener_hiloB()));
    connect(ui->imageLabel, SIGNAL(onMouseMoveEvent()), this, SLOT(updateMouseCursorPosLabel()));
    connect(ui->imageLabel, SIGNAL(rightButtonClicked(QPoint)), this, SLOT(updateDimension(QPoint)));
    connect(ui->imageLabel, SIGNAL(leftButtonClicked(QPoint)), this, SLOT(colorPicker(QPoint)));


    // Create connection between processing thread (emitter) and GUI thread (receiver/listener)
    //connect(hilo_gt, SIGNAL(newFrame(QImage)), this, SLOT(updateFrame(QImage)), Qt::UniqueConnection);
    hilo_captura = 0;
    hilo_gt = 0;
    flag_gt=false;
    done=true;

    flag_rbclick=false;
    point.setX(0);
    point.setY(0);

    showColors=false;

    ui->imageLabel->setText(QString::fromUtf8("Ninguna cámara conectada."));
    //cBlack
    c = new sColor();
    c->hsv_min.hue = 0;
    c->hsv_max.hue = 179;
    c->hsv_min.saturation = 0;
    c->hsv_max.saturation = 255;
    c->hsv_min.value = 0;
    c->hsv_max.value = 75;
    c->background = true;
    color.push_back(c);

    //cWHITE
    c = new sColor();
    c->hsv_min.hue = 0;
    c->hsv_max.hue = 179;
    c->hsv_min.saturation = 0;
	c->hsv_max.saturation = 27;
    c->hsv_min.value = 190;
    c->hsv_max.value = 255;
    c->background = true;
    color.push_back(c);

    //cGREY
    c = new sColor();
    c->hsv_min.hue = 0;
	c->hsv_max.hue = 179;
    c->hsv_min.saturation = 0;
    c->hsv_max.saturation = 53;
    c->hsv_min.value = 0;
    c->hsv_max.value = 185;
    color.push_back(c);

    //cRED
    c = new sColor();
    c->hsv_min.hue = 0;
	c->hsv_max.hue = 14;
	c->hsv_min.saturation = 28;
	c->hsv_max.saturation = 255;
	c->hsv_min.value = 76;
	c->hsv_max.value = 255;
    color.push_back(c);

    //cBROWN
    c = new sColor();
    c->hsv_min.hue = 15;
	c->hsv_max.hue = 18;
	c->hsv_min.saturation = 28;
	c->hsv_max.saturation = 255;
	c->hsv_min.value = 76;
	c->hsv_max.value = 255;
    color.push_back(c);

    //cORANGE
    c = new sColor();
    c->hsv_min.hue = 19;
	c->hsv_max.hue = 25;
	c->hsv_min.saturation = 28;
	c->hsv_max.saturation = 255;
	c->hsv_min.value = 76;
	c->hsv_max.value = 255;
	color.push_back(c);

    //cYELLOW
    c = new sColor();
    //c->habilitar = true;
    c->hsv_min.hue = 26;
    c->hsv_max.hue = 34;
	c->hsv_min.saturation = 28;
	c->hsv_max.saturation = 255;
	c->hsv_min.value = 76;
	c->hsv_max.value = 255;
    color.push_back(c);

    //cGREEN
    c = new sColor();
    //c->habilitar = true;
    c->hsv_min.hue = 35;
    c->hsv_max.hue = 73;
	c->hsv_min.saturation = 28;
	c->hsv_max.saturation = 255;
	c->hsv_min.value = 76;
	c->hsv_max.value = 255;
    color.push_back(c);

    //cAQUA
    c = new sColor();
    c->hsv_min.hue = 74;
	c->hsv_max.hue = 102;
	c->hsv_min.saturation = 28;
	c->hsv_max.saturation = 255;
	c->hsv_min.value = 76;
	c->hsv_max.value = 255;
	color.push_back(c);

    //cBLUE
    c = new sColor();
    //c->habilitar = true;
    c->hsv_min.hue = 103;
    c->hsv_max.hue = 127;
	c->hsv_min.saturation = 28;
	c->hsv_max.saturation = 255;
	c->hsv_min.value = 76;
	c->hsv_max.value = 255;
	c->rgb.red = 0;
	c->rgb.blue = 255;
	c->rgb.green = 0;
    color.push_back(c);

    //cPURPLE
    c = new sColor();
    c->hsv_min.hue = 128;
	c->hsv_max.hue = 149;
	c->hsv_min.saturation = 28;
	c->hsv_max.saturation = 255;
	c->hsv_min.value = 76;
	c->hsv_max.value = 255;
	color.push_back(c);

    //cPINK
    c = new sColor();
    c->hsv_min.hue = 150;
	c->hsv_max.hue = 175;
	c->hsv_min.saturation = 28;
	c->hsv_max.saturation = 255;
	c->hsv_min.value = 76;
	c->hsv_max.value = 255;
    color.push_back(c);

    /*
    for (unsigned int i=0; i < color.size(); ++i) {
    	std::cout << color[i]->hsv_max.hue << " " << color[i]->habilitar << std::endl;
	}
	*/

    /*
    for (short i=0; i < NUM_COLOR_TYPES; ++i) {
    	color.push_back(*(new sColor()));
    }
    */

    //std::cout << "Num: " << NUM_COLOR_TYPES;

    //ball
    ball.enabled = true;
    ball.color_id = cRED;
    ball.area_min = 15;
    ball.area_max = 5000;

    //team
    blue_team.enabled = true;
    blue_team.team_id = 1;
    blue_team.team_colorid = cBLUE;
    blue_team.usesColor.push_back(cYELLOW); //colors used by a team
    blue_team.usesColor.push_back(cGREEN); //colors used by a team
    blue_team.usesColor.push_back(cPINK); //colors used by a team

    //patch of a team
    blue_team.patches.push_back(new Pattern());
    blue_team.patches[0]->enabled=true;
    blue_team.patches[0]->num_markers=4;
    blue_team.patches[0]->id=1;
    blue_team.patches[0]->usesColor.push_back(cYELLOW); //colors used by a particular patch
    blue_team.patches[0]->usesColor.push_back(cGREEN); //colors used by a particular patch

    //markers of a patch
    blue_team.patches[0]->markers.push_back(new Marker());
    blue_team.patches[0]->markers[0]->colorid=cYELLOW;
    blue_team.patches[0]->markers.push_back(new Marker());
	blue_team.patches[0]->markers[1]->colorid=cGREEN;
	blue_team.patches[0]->markers.push_back(new Marker());
	blue_team.patches[0]->markers[2]->colorid=cGREEN;
	blue_team.patches[0]->markers.push_back(new Marker());
	blue_team.patches[0]->markers[3]->colorid=cGREEN;

	//patch of a team
	blue_team.patches.push_back(new Pattern());
	blue_team.patches[1]->enabled=true;
	blue_team.patches[1]->num_markers=4;
	blue_team.patches[1]->id=2;
	blue_team.patches[1]->usesColor.push_back(cYELLOW); //colors used by a particular patch
	blue_team.patches[1]->usesColor.push_back(cGREEN); //colors used by a particular patch

	//markers of a patch
	blue_team.patches[1]->markers.push_back(new Marker());
	blue_team.patches[1]->markers[0]->colorid=cYELLOW;
	blue_team.patches[1]->markers.push_back(new Marker());
	blue_team.patches[1]->markers[1]->colorid=cYELLOW;
	blue_team.patches[1]->markers.push_back(new Marker());
	blue_team.patches[1]->markers[2]->colorid=cGREEN;
	blue_team.patches[1]->markers.push_back(new Marker());
	blue_team.patches[1]->markers[3]->colorid=cGREEN;

	//patch of a team
	blue_team.patches.push_back(new Pattern());
	blue_team.patches[2]->enabled=true;
	blue_team.patches[2]->num_markers=4;
	blue_team.patches[2]->id=3;
	blue_team.patches[2]->usesColor.push_back(cYELLOW); //colors used by a particular patch
	blue_team.patches[2]->usesColor.push_back(cPINK); //colors used by a particular patch

	//markers of a patch
	blue_team.patches[2]->markers.push_back(new Marker());
	blue_team.patches[2]->markers[0]->colorid=cYELLOW;
	blue_team.patches[2]->markers.push_back(new Marker());
	blue_team.patches[2]->markers[1]->colorid=cPINK;
	blue_team.patches[2]->markers.push_back(new Marker());
	blue_team.patches[2]->markers[2]->colorid=cYELLOW;
	blue_team.patches[2]->markers.push_back(new Marker());
	blue_team.patches[2]->markers[3]->colorid=cPINK;


	//patch of a team
	blue_team.patches.push_back(new Pattern());
	blue_team.patches[3]->enabled=true;
	blue_team.patches[3]->num_markers=4;
	blue_team.patches[3]->id=4;
	blue_team.patches[3]->usesColor.push_back(cGREEN); //colors used by a particular patch
	blue_team.patches[3]->usesColor.push_back(cPINK); //colors used by a particular patch


	//markers of a patch
	blue_team.patches[3]->markers.push_back(new Marker());
	blue_team.patches[3]->markers[0]->colorid=cGREEN;
	blue_team.patches[3]->markers.push_back(new Marker());
	blue_team.patches[3]->markers[1]->colorid=cGREEN;
	blue_team.patches[3]->markers.push_back(new Marker());
	blue_team.patches[3]->markers[2]->colorid=cPINK;
	blue_team.patches[3]->markers.push_back(new Marker());
	blue_team.patches[3]->markers[3]->colorid=cPINK;

	for (unsigned int j=0; j < blue_team.patches.size(); ++j) {
		blue_team.patches[j]->field_pos=cvPoint(0,0);
		blue_team.patches[j]->orientation=0;
		blue_team.patches[j]->center=cvPoint(0,0);
	}

	// dimensions
	flag_dimension=false;
	rightButtonPressed = fp1 = fp2 = fp3 =fp4 = false;

	p1.x=0;p1.y=240;
	p2.x=320;p2.y=240;
	p3.x=320;p3.y=0;
	p4.x=0;p4.y=0;
	h.setImagePoints(p1, p2, p3, p4);

	// Dimensions for robot soccer field
	x=1850;
	y=1500;

	u1.x=0;u1.y=1500;//0-1
	u2.x=1850;u2.y=1500;//1-1
	u3.x=1850;u3.y=0;//1-0
	u4.x=0;u4.y=0;//0-0
	h.setRealPoints(u1, u2, u3, u4);

	h.calcMH();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::iniciar_hiloA() {
	hilo_captura = new CaptureThread(0);
	//hilo_captura = new CaptureThread("/home/willytell/out.avi");
	hilo_captura->setFrameBuffer(new FrameBuffer(10));
	hilo_captura->init();
	if (!hilo_captura->isRunning()) {
		connect(hilo_captura, SIGNAL(newFrame(QImage)), this, SLOT(updateFrame(QImage)), Qt::UniqueConnection);
		hilo_captura->start(QThread::TimeCriticalPriority); //QThread::IdlePriority);
	}
	//	else cout << "error init capture" << endl;
}

void MainWindow::detener_hiloA() {
	if (hilo_captura!=0) {
		if (hilo_captura->isRunning()) {
			hilo_captura->stop();
			hilo_captura->stopCaptureThread();
		}
		hilo_captura->~CaptureThread();
		hilo_captura=0;
	}
}

void MainWindow::iniciar_hiloB() {
	frame = cvCreateImage(cvSize(352,288), 8, 3);
	hilo_gt = new GlobalTracking(frame, &blue_team, &blue_team, &ball, color, &h);
	//hilo_gt = new GlobalTracking();
	hilo_gt->setFrameBuffer(hilo_captura->getFrameBuffer());
	disconnect(hilo_captura, SIGNAL(newFrame(QImage)),0,0);
	connect(hilo_gt, SIGNAL(newFrame(QImage)), this, SLOT(updateFrame(QImage)), Qt::UniqueConnection);
	hilo_gt->start(QThread::TimeCriticalPriority); //QThread::IdlePriority);
}

void MainWindow::detener_hiloB() {
	if (hilo_gt->isRunning())
		hilo_gt->terminate();
	hilo_gt->terminate();
}

void MainWindow::about()
{
    QMessageBox::about(this, QString::fromUtf8("Acerca de Sistema de Visión Global"),
    		QString::fromUtf8("<h2>Visión Global 0.3.1</h2>"
               "<p>Visión Global es una aplicación para detección de parches "
               "para Fútbol de Robots.</p>"));

}

void MainWindow::editDimensionsFieldDialog() {
    // Create dialog
	dimensionsFieldDialog = new DimensionsFieldDialog(this);
	dimensionsFieldDialog->setLength(x);
	dimensionsFieldDialog->setWidth(y);
	// PROMPT USER:
	// If user presses OK button on dialog, get new values for dimensions field; else do nothing
	if (dimensionsFieldDialog->exec()==1){
		// Set private member variables in dimensionsFieldDialog to values in dialog
		dimensionsFieldDialog->dimensionsFromDialog();
		// Get values from dialog
		x = dimensionsFieldDialog->getLength();
		y = dimensionsFieldDialog->getWidth();

		u1.x=0;u1.y=y;//0-1
		u2.x=x;u2.y=y;//1-1
		u3.x=x;u3.y=0;//1-0
		u4.x=0;u4.y=0;//0-0
		h.setRealPoints(u1, u2, u3, u4);
		h.calcMH();
	}
	delete dimensionsFieldDialog;
}

void MainWindow::editCamara1() {
    // Create dialog
	captureConnectDialog = new CaptureConnectDialog(this);
    // PROMPT USER:
    // If user presses OK button on dialog, connect to camera; else do nothing
    if(captureConnectDialog->exec()==1) {
        // Set private member variables in captureConnectDialog to values in dialog
    	captureConnectDialog->captureMethodSelected();
    	string s=captureConnectDialog->getCaptureMethod();
    	if (s == "camera") {
			// Store device number in local variable
			int deviceNumber=captureConnectDialog->getDeviceNumber();
			// Connect to camera
			hilo_captura = new CaptureThread(deviceNumber);
    	}
		else {
			// s=="filename"
			string video=captureConnectDialog->getFilename();
			hilo_captura = new CaptureThread(video);

		}
        if (hilo_captura->init()) {
        	hilo_captura->setFrameBuffer(new FrameBuffer(10));
        	hilo_captura->display(true);
        	if (!hilo_captura->isRunning()) {
        		connect(hilo_captura, SIGNAL(newFrame(QImage)), this, SLOT(updateFrame(QImage)), Qt::UniqueConnection);
        		hilo_captura->start(QThread::TimeCriticalPriority); //QThread::IdlePriority);
        	}
        }
        else {
        	QMessageBox::warning(this,"ERROR:","Could not connect to camera.");
        	delete hilo_captura;
        	//delete captureConnectDialog;
        }

    }
    delete captureConnectDialog;
}

void MainWindow::colorGUIClosed() {
	showColors=false;
}

void MainWindow::editColor() {
	//QMessageBox::about(this, tr("Edicion de Colores"), tr("<h2>Editando Colores</h2>"));

	//Colores *c = new Colores(); //Colores::Colores();

	colorGUI = new EditColorGUI(color, 0);
	connect(this, SIGNAL(pixelPick(QImage, QPoint)), colorGUI, SLOT(clickedImage(QImage, QPoint)));
	connect(colorGUI, SIGNAL(closeEditGUI()), this, SLOT(colorGUIClosed()));
	showColors=true;

	if (!colorGUI->isVisible()) {
		colorGUI->show();
    }
    else {
    	colorGUI->raise();
    	colorGUI->activateWindow();
    }

}

void MainWindow::updateDimension(QPoint p) {
	static int idx=0;

	idx++;
	std::cout<<"right button click!! "<< idx << ' ' << p.rx()<< ' ' <<p.ry()<<std::endl;
	switch (idx) {
		case 1: {
			p1.x=p.rx();
			p1.y=p.ry();
			flag_dimension=false;
			fp1=true;
			fp2=fp3=fp4=false;
			rightButtonPressed=true;
			break;
		}
		case 2: {
			p2.x=p.rx();
			p2.y=p.ry();
			fp2=true;
			break;
		}
		case 3: {
			p3.x=p.rx();
			p3.y=p.ry();
			fp3=true;
			break;
		}
		case 4: {
			p4.x=p.rx();
			p4.y=p.ry();
			fp4=true;
			h.setImagePoints(p1, p2, p3, p4);
			h.setRealPoints(u1, u2, u3, u4);
			h.calcMH();
			std::cout<<"Dimension completada."<<std::endl;
			flag_dimension=true;
			idx=0;
			break;
		}
		default: {
			break;
		}
	}
}

void MainWindow::updateMouseCursorPosLabel()
{
    // Update mouse cursor position in mouseCursorPosLabel in main window
    ui->mouseCursorPosLabel->setText(QString("(")+QString::number(ui->imageLabel->getMouseCursorPos().x())+
                                 QString(",")+QString::number(ui->imageLabel->getMouseCursorPos().y())+
                                 QString(")"));
    if (flag_dimension) {
    	CvPoint p, r;
    	p.x=ui->imageLabel->getMouseCursorPos().x();
    	p.y=ui->imageLabel->getMouseCursorPos().y();
    	r = h.transPoint(p);

    	ui->mouseCursorRealPosLabel->setText(QString("(")+QString::number(r.x)+
    	                                 QString(",")+QString::number(r.y)+
    	                                 QString(")"));
    }
    else {
    	ui->mouseCursorRealPosLabel->setText(QString(""));
    }

} // updateMouseCursorPosLabel()

void MainWindow::colorPicker(QPoint p) {
	point=p;
	flag_rbclick=true;
}

void MainWindow::updateFrame(const QImage &frame) {
	QPixmap pm;
	QImage qtframe;

	if (flag_rbclick) {
		emit pixelPick(frame, point);
		flag_rbclick=false;
	}


	if (showColors) {
		IplImage *iplimage=conv.qImage2IplImage(frame.copy());
		segmentation.buildThreshold(color);
		segmentation.colorPaint(iplimage, color);
		qtframe=conv.IplImage2QImage(iplimage);
		cvReleaseImage(&iplimage);
		pm = QPixmap::fromImage(qtframe);
	}
	else
		pm = QPixmap::fromImage(frame);



	// this place is appropiated to show all information related to frame statistics.
	if (flag_dimension) {
		// Draw lines between points
		QPainter p(&pm);
		p.setRenderHint(QPainter::Antialiasing, true);
		QPen pen(Qt::blue, 1);
		p.setPen(pen);
		p.drawLine(p1.x,p1.y,p2.x,p2.y);
		p.drawLine(p2.x,p2.y,p3.x,p3.y);
		p.drawLine(p3.x,p3.y,p4.x,p4.y);
		p.drawLine(p4.x,p4.y,p1.x,p1.y);
	}
	else
		if (rightButtonPressed) {
			// Draw each point
			QPainter p(&pm);
			p.setRenderHint(QPainter::Antialiasing, true);
			QPen pen(Qt::blue, 2); //QPen Red((QColor::QColor(255,0,0)),1);
			p.setPen(pen);
			QBrush brush(Qt::green);
			p.setBrush(brush);
			if (fp1) p.drawEllipse(p1.x, p1.y, 3, 3);
			if (fp2) p.drawEllipse(p2.x, p2.y, 3, 3);
			if (fp3) p.drawEllipse(p3.x, p3.y, 3, 3);
			if (fp4) p.drawEllipse(p4.x, p4.y, 3, 3);
		}

	// Display frame in main window
	ui->imageLabel->setPixmap(pm); //QPixmap::fromImage(frame));
	ui->imageLabel->adjustSize();
	ui->captureRateLabel->setNum(hilo_captura->getFPS());
	ui->captureRateLabel->setText(ui->captureRateLabel->text()+" fps");
	if (hilo_gt != 0) {
		ui->processingRateLabel->setNum(hilo_gt->getAvgFPS());
		ui->processingRateLabel->setText(ui->processingRateLabel->text()+" fps");
	}
}

QImage MainWindow::IplImage2QImage(const IplImage *iplImage)
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

void MainWindow::putImage(IplImage *cvimage)
{
	qimage=cvimageqt.IplImage2QImage(cvimage);
	ui->imageLabel->setPixmap(QPixmap::fromImage(qimage));
}

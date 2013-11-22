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
  \file    editcamgui.cpp
  \brief   C++ Implementation: editCamGUI
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "editcamgui.h"
#include "ui_editcamgui.h"
#include <QFileDialog>
#include <QMessageBox>

editCamGUI::editCamGUI(vision *v, int index, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editCamGUI)
{
    ui->setupUi(this);
    connect(ui->spinBoxCamaraIndex, SIGNAL(valueChanged(int)), this, SLOT(spinBoxCamaraIndex()));
    connect(ui->pushButtonStart, SIGNAL(clicked()), this, SLOT(buttonStart()));
    connect(ui->pushButtonStop, SIGNAL(clicked()), this, SLOT(buttonStop()));
    connect(ui->pushButtonConfiguration, SIGNAL(clicked()), this, SLOT(buttonConfiguration()));
    connect(ui->pushButtonIntrinsics, SIGNAL(clicked()), this, SLOT(buttonIntrinsics()));
    connect(ui->pushButtonDistortion, SIGNAL(clicked()), this, SLOT(buttonDistortion()));
    connect(ui->pushButtonApply, SIGNAL(clicked()), this, SLOT(buttonApply()));
    connect(ui->pushButtonClear, SIGNAL(clicked()), this, SLOT(buttonClear()));

    ui->imageLabel->hide();

    //new QImage(image);

    timerID=0;
    timerFlag=false;


    // TODO: Debería estar en la clase Visión, para abstraerse de las cámaras calibradas o no, si es visión mono o estereo.
    vlIndex=index;
    this->v=v;

    //if ((0 <= vlIndex) and (vlIndex < MAX_VL)) {
    if (v->get_vlCamFlag(vlIndex)) {
        cam = v->get_vlCam(vlIndex);
        ui->spinBoxCamaraIndex->setValue(cam->get_index());
        if (v->get_vlMonoFlag(vlIndex)) {
                mono = v->get_vlMono(vlIndex);
                monoFlag=true;
                intrinsicsFlag=true;
                distortionFlag=true;
                //applyFlag=true;
        }//if
        //this->buttonStart();  // <- error en el 2do intento!!! no usar!!!
    }//if
    else {
        cam = new Camara();
        cam->set_index(0);
        //cam->prepare();

        monoFlag=false;
        intrinsicsFlag=false;
        distortionFlag=false;
        applyFlag=false;
    }
}

editCamGUI::~editCamGUI()
{
    //delete &cam;
    delete ui;
}

void editCamGUI::closeEvent(QCloseEvent *event)
{
    this->buttonStop();
    //if (timerFlag) {
    //    killTimer(timerID);
    //    cam->release();
    //}
}

void editCamGUI::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void editCamGUI::timerEvent(QTimerEvent*)
{
    frame = cam->get_frame();
    if (applyFlag) {
        IplImage *t = cvCloneImage(frame);
        mono->undistort(frame, t);
        this->putImage(t);
        cvReleaseImage (&t);
    }
    else
        this->putImage(frame);
}

void editCamGUI::spinBoxCamaraIndex()
{
    cam->set_index(ui->spinBoxCamaraIndex->value());
}

void editCamGUI::buttonStart()
{
    if (!timerFlag) {
        cam->prepare();
        cam->get_frameSize(&frame_sz);
        if (!monoFlag) {
            mono = new Mono(5, 5, 8, &frame_sz);
            monoFlag=true;
        }
        timerID=startTimer(33.33);
        timerFlag=true;
        if ((intrinsicsFlag) and (distortionFlag))
            applyFlag=true;
        if (ui->imageLabel->isHidden())
            ui->imageLabel->show();
    }//if
}

void editCamGUI::buttonStop()
{
    if (timerFlag) {
        killTimer(timerID);
        cam->release();        
        applyFlag=false;
        timerFlag=false;
    }
}

void editCamGUI::buttonConfiguration()
{
    //if (0 <= vlIndex) {
        if (applyFlag) {
            v->set_vl(vlIndex, cam, mono);
        }
        else
            v->set_vl(vlIndex, cam);
    //}
    //this->close();
}

void editCamGUI::buttonIntrinsics()
{
    if (monoFlag) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Parametros Intrinsecos"),
                                                         ".",
                                                         tr("XML (*.xml)"));

        if (!fileName.isEmpty()) {
            char c[256];

            for (int i=0; i < fileName.length(); i++) {
                c[i] = fileName[i].toLatin1();
            }

            c[fileName.length()] = '\0';
            //printf("file : %s\n", (char *)c);
            if (mono->loadIntrinsics((char *)c)) {
                intrinsicsFlag=true;
                QMessageBox::information(this,
                                         tr("Cargando Parametros Intrinsecos"),
                                         tr("Los parametros intrinsecos se han cargado correctamente."));
            }//if
        }//if
    }//if
    else
        QMessageBox::warning(this,
                             tr("Cargar Parametros"),
                             tr("Se requiere: \n1. Definir el inidice de camara y luego presionar el boton Start.\n2. Luego cargar los parametros intrinsecos y coeficientes de distorsion.\n3. Finalmente presionar el boton Aplicar."));
}

void editCamGUI::buttonDistortion()
{
    if (monoFlag) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Coeficientes de Distorsion"),
                                                         ".",
                                                         tr("XML (*.xml)"));

        if (!fileName.isEmpty()) {
            char c[256];

            for (int i=0; i < fileName.length(); i++) {
                c[i] = fileName[i].toLatin1();
            }

            c[fileName.length()] = '\0';
            //printf("file : %s\n", (char *)c);
            if (mono->loadDistortion((char *)c)) {
                distortionFlag=true;
                QMessageBox::information(this,
                                         tr("Cargando Coeficientes de Distorsion"),
                                         tr("Los coeficientes de distorsion se han cargado correctamente."));
            }//if

        }//if
    }//if
    else
        QMessageBox::warning(this,
                             tr("Cargar Parametros "),
                             tr("Se requiere: \n1. Definir el inidice de camara y luego presionar el boton Start.\n2. Luego cargar los parametros intrinsecos y coeficientes de distorsion.\n3. Finalmente presionar el boton Aplicar."));
}

void editCamGUI::buttonApply()
{
    if ((intrinsicsFlag) and (distortionFlag)) {
        mono->initUndistort();
        applyFlag=true;
    }
    else
        QMessageBox::warning(this,
                             tr("Aplicar Calibracion"),
                             tr("Se requiere cargar primero los P. Intrinsecos y los C. Distorsion."));
}

void editCamGUI::buttonClear()
{
    if (applyFlag) {
        intrinsicsFlag=false;
        distortionFlag=false;        
        applyFlag=false;
        delete mono;
        monoFlag=false;
        QMessageBox::information(this,
                                 tr("Limpiar Parametros y Coeficientes"),
                                 tr("Se han limipiado los parametros y coeficientes. Si desea utilizarlos, debe cargar los archivos nuevamente y luego presionar el boton Aplicar."));
    }
}

void editCamGUI::putImage(IplImage *cvimage)
{
	qimage=cvimageqt.IplImage2QImage(cvimage);
	ui->imageLabel->setPixmap(QPixmap::fromImage(qimage));
}

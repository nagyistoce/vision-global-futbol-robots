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
  \file    editcolorgui.cpp
  \brief   C++ Implementation: EditColorGUI
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "editcolorgui.h"

#include "ui_editcolorgui.h"
#include <QtGui>
#include <QMap>

EditColorGUI::EditColorGUI(/* CaptureThread *captureThread, */ std::vector<sColor*>&color_, QWidget *parent) :
	QWidget(parent),
    ui(new Ui::EditColorGUI)
{
	ui->setupUi(this);

	//connect(ui->pushButtonStart, SIGNAL(clicked()), this, SLOT(buttonStart()));
    //connect(ui->pushButtonStop, SIGNAL(clicked()), this, SLOT(buttonStop()));

    //connect(ui->listWidgetColors, SIGNAL(clicked(QModelIndex)), this, SLOT(listWidgetColors())); //"clicked" esta contemplada en la señal itemSelectionChanged.
    connect(ui->listWidgetColors, SIGNAL(itemSelectionChanged()), this, SLOT(listWidgetColors()));

    connect(ui->checkBoxMostrar, SIGNAL(clicked()), this, SLOT(checkBoxMostrar()));
    connect(ui->checkBoxHabilitar, SIGNAL(clicked()), this, SLOT(checkBoxHabilitar()));
    connect(ui->checkBoxBackground, SIGNAL(clicked()), this, SLOT(checkBoxBackground()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(buttonBoxAccept()));
    connect(ui->pushButtonLimpiar, SIGNAL(clicked()), this, SLOT(buttonLimpiar()));

    row=0;
    itemColor.mostrar=false;
    segmentarFlag=false;

    color = color_;
    segmentation.buildThreshold(color);
    /*
	for (unsigned int i=0; i < color.size(); ++i) {
		std::cout << color[i]->hsv_max.hue << " " << color[i]->habilitar << std::endl;
	}
	*/
    loadColorsList();

    model = new QStringListModel();
    leaders.clear();
    model->setStringList(leaders);
    ui->listViewSalida->setModel(model);
    //segmentation.buildThreshold(color);
}

QIcon EditColorGUI::iconForSymbol(const QString &symbolName)
{
	QString fileName = "images/" + symbolName.toLower();
	fileName.replace(' ', '-');
	return QIcon(fileName);
}

void EditColorGUI::loadColorsList() {
	//{cBLACK=0,cWHITE, cGREY, cRED, cBROWN, cORANGE, cYELLOW, cGREEN, cAQUA, cBLUE, cPURPLE, cPINK,  NUM_COLOR_TYPES};
	QMap<int, QString> symbolMap;
	symbolMap.insert(10, QObject::tr("Black"));
    symbolMap.insert(20, QObject::tr("White"));
    symbolMap.insert(30, QObject::tr("Grey"));
    symbolMap.insert(40, QObject::tr("Red"));
    symbolMap.insert(50, QObject::tr("Brown"));
    symbolMap.insert(60, QObject::tr("Orange"));
    symbolMap.insert(70, QObject::tr("Yellow"));
    //symbolMap.insert(80, QObject::tr("Field Green"));
    symbolMap.insert(90, QObject::tr("Green"));
    symbolMap.insert(100, QObject::tr("Aqua"));
    symbolMap.insert(110, QObject::tr("Blue"));
    symbolMap.insert(120, QObject::tr("Purple"));
    symbolMap.insert(130, QObject::tr("Pink"));
    //symbolMap.insert(140, QObject::tr("Red"));

    ui->listWidgetColors->setIconSize(QSize(25,25));

    QMapIterator<int, QString> i(symbolMap);
    while (i.hasNext()) {
    	i.next();
    	QListWidgetItem *item = new QListWidgetItem(i.value(), ui->listWidgetColors);
    	item->setIcon(iconForSymbol(i.value()));
    	item->setData(Qt::UserRole, i.key());
    }
}

EditColorGUI::~EditColorGUI() {
	segmentation.~Segmentation();
	delete ui;
}

void EditColorGUI::closeEvent(QCloseEvent *event) {
	emit closeEditGUI();
}

void EditColorGUI::changeEvent(QEvent *e) {
    QWidget::changeEvent(e);
    switch (e->type()) {
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
		default:
			break;
    }
}

void EditColorGUI::clickedImage(QImage qimage, QPoint p) {
	char string[50];

	frame=conv.qImage2IplImage(qimage);
	pixel = cvPoint(p.rx(), p.ry());
	colorSpace.bgr2hsv(frame, pixel, &hsv);    //hsv = segmentar.get_HSVpixel(frame, pixel);
	//printf("h=%i, s=%i, v=%i\n", hsv.h, hsv.s, hsv.v);
	sprintf(string, "hsv(%i, %i, %i)", hsv.hue, hsv.saturation, hsv.value);    //http://www.cppreference.com/wiki/c/io/sprintf
	leaders.append(string);        //http://www.informit.com/articles/article.aspx?p=1405547&seqNum=3
	model->setStringList(leaders);
	ui->listViewSalida->setModel(model);
}

void EditColorGUI::listWidgetColors() {
	row = ui->listWidgetColors->currentIndex().row();
	//printf("color size = %i, listWidgetColors row = %i\n", (int) color.size(), row);

	itemColor = *color[row]; //	itemColor = listaColores->getColor(row);
	ui->checkBoxMostrar->setChecked(itemColor.mostrar);
	ui->checkBoxHabilitar->setChecked(itemColor.habilitar);
	ui->checkBoxBackground->setChecked(itemColor.background);

	ui->spinBoxHmin->setValue(itemColor.hsv_min.hue);
	ui->spinBoxSmin->setValue(itemColor.hsv_min.saturation);
	ui->spinBoxVmin->setValue(itemColor.hsv_min.value);

	ui->spinBoxHmax->setValue(itemColor.hsv_max.hue);
	ui->spinBoxSmax->setValue(itemColor.hsv_max.saturation);
	ui->spinBoxVmax->setValue(itemColor.hsv_max.value);
}

void EditColorGUI::checkBoxMostrar() {
	itemColor.mostrar=ui->checkBoxMostrar->isChecked();
	*color[row] = itemColor; //	listaColores->setColor(row, itemColor);
}

void EditColorGUI::checkBoxHabilitar() {
	itemColor.habilitar=ui->checkBoxHabilitar->isChecked();
	*color[row] = itemColor; //	listaColores->setColor(row, itemColor);

	/*
	for (unsigned int i=0; i < color.size(); ++i) {
			std::cout << this->color[i]->hsv_max.hue << " " << this->color[i]->habilitar << std::endl;
	}
	*/
}

void EditColorGUI::checkBoxBackground() {
	itemColor.background=ui->checkBoxBackground->isChecked();
	*color[row] = itemColor; //	listaColores->setColor(row, itemColor);
}

void EditColorGUI::buttonBoxAccept() {
	itemColor.hsv_min.hue=ui->spinBoxHmin->value();
	itemColor.hsv_max.hue=ui->spinBoxHmax->value();
	itemColor.hsv_min.saturation=ui->spinBoxSmin->value();
	itemColor.hsv_max.saturation=ui->spinBoxSmax->value();
	itemColor.hsv_min.value=ui->spinBoxVmin->value();
	itemColor.hsv_max.value=ui->spinBoxVmax->value();

	*color[row] = itemColor;

	//segmentation.resetThreshold();
	segmentation.buildThreshold(color);
	/*
	segmentation.setThreshold(color, row, \
			itemColor.hsv_min.hue, itemColor.hsv_max.hue, \
			itemColor.hsv_min.saturation, itemColor.hsv_max.saturation, \
			itemColor.hsv_min.value, itemColor.hsv_max.value);
	*/
}

void EditColorGUI::buttonLimpiar() {
	leaders.clear();
	model->setStringList(leaders);
	ui->listViewSalida->setModel(model);
}


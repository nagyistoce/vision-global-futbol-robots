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
  \file    dimensionsfielddialog.cpp
  \brief   C++ Implementation: DimensionsFieldDialog
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "dimensionsfielddialog.h"

DimensionsFieldDialog::DimensionsFieldDialog(QWidget *parent) : QDialog(parent) {
	// Setup dialog
	setupUi(this);
	// lengthXEdit (axis x) input string validation
	QRegExp rx1("[0-9]\\d{0,3}"); // Integers 0 to 9999
	QRegExpValidator *validator1 = new QRegExpValidator(rx1, 0);
	lengthXEdit->setValidator(validator1);
	// lengthYEdit (axis y) input string validation
	QRegExp rx2("[0-9]\\d{0,3}"); // Integers 0 to 9999
	QRegExpValidator *validator2 = new QRegExpValidator(rx2, 0);
	lengthYEdit->setValidator(validator2);
}

DimensionsFieldDialog::~DimensionsFieldDialog() {
	// TODO Auto-generated destructor stub
}


void DimensionsFieldDialog::dimensionsFromDialog() {
	lengthX = lengthXEdit->text().toInt();
	widthY = lengthYEdit->text().toInt();
	//deviceNumber=deviceNumberEdit->text().toInt();
}

int DimensionsFieldDialog::getLength() {
	return lengthX;
}

void DimensionsFieldDialog::setLength(int _lengthX) {
	lengthX = _lengthX;
	lengthXEdit->setText(QString::number(lengthX));
}

int DimensionsFieldDialog::getWidth() {
	return widthY;
}

void DimensionsFieldDialog::setWidth(int _widthY) {
	widthY = _widthY;
	lengthYEdit->setText(QString::number(widthY));
}

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
  \file    dimensionsfielddialog.h
  \brief   C++ Interface: DimensionsFieldDialog
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef DIMENSIONSFIELDDIALOG_H_
#define DIMENSIONSFIELDDIALOG_H_

// Qt header files
#include <QtGui>
#include "ui_DimensionsFieldDialog.h"
//#include <iostream>
using namespace std;

class DimensionsFieldDialog : public QDialog, private Ui::DimensionsFieldDialog {
	Q_OBJECT
public:
	DimensionsFieldDialog(QWidget *parent = 0); //int _lengthX, int _widthY
	~DimensionsFieldDialog();
	void dimensionsFromDialog();
	int  getLength(); // X
	void setLength(int _lengthX);
	int  getWidth(); // Y
	void setWidth(int _widthY);

private:
	int lengthX;
	int widthY;
};
#endif /* DIMENSIONSFIELDDIALOG_H_ */

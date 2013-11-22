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
  \file    subqlabel.h
  \brief   C++ Interface: SubQLabel
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef SUBQLABEL_H_
#define SUBQLABEL_H_

#include <QLabel>
#include <QtGui>
#include "datastruct.h"

class SubQLabel : public QLabel {
	Q_OBJECT

public:
	SubQLabel(QWidget *parent = 0);
	virtual ~SubQLabel();
	void mousePressEvent(QMouseEvent *event);
	Pixel get_pixel();
	void set_pixel(Pixel p);

signals:
	void clicked();

private:
	Pixel pixel;
};

#endif /* SUBQLABEL_H_ */

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
  \file    subqlabel.cpp
  \brief   C++ Implementation: SubQLabel
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "subqlabel.h"
using namespace std;

SubQLabel::SubQLabel(QWidget *parent) : QLabel(parent) {
	// TODO Auto-generated constructor stub
}

SubQLabel::~SubQLabel() {
	// TODO Auto-generated destructor stub
}

void SubQLabel::set_pixel(Pixel p) {
	pixel = p;
}

Pixel SubQLabel::get_pixel(){
	return pixel;
}

void SubQLabel::mousePressEvent(QMouseEvent *event) {
	pixel.x = event->x();
	pixel.y = event->y();
	//printf("x=%i, y=%i\n", pixel.x, pixel.y);
	this->set_pixel(pixel);
	emit clicked();
}




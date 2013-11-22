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
  \file    editcolorgui.h
  \brief   C++ Interface: EditColorGUI
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef EDITCOLORGUI_H_
#define EDITCOLORGUI_H_

#include <QWidget>
#include <cv.h>
#include <QStringListModel>
#include <QStringList>
#include "subqlabel.h"
#include "datastruct.h"
#include "capture_thread.h"
#include "colorspace.h"
#include "segmentation.h"
#include "cvimageqt.h"

namespace Ui {
    class EditColorGUI;
}

class EditColorGUI : public QWidget
{
    Q_OBJECT

public:
    EditColorGUI(std::vector<sColor*> &color_, QWidget *parent = 0);
    ~EditColorGUI();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event);

protected slots:
    void listWidgetColors();
    void checkBoxMostrar();
    void checkBoxHabilitar();
    void checkBoxBackground();
    void buttonBoxAccept();
    void buttonLimpiar();

public slots:
	void clickedImage(QImage qimage, QPoint p);

signals:
	void closeEditGUI();

private:
    Ui::EditColorGUI *ui;

    IplImage *frame, *frameCopy, *frameColor;
    CvImageQt conv;
    CvSize frame_sz;
    bool copyFlag;
    QImage image;
    ColorSpace colorSpace;
    Segmentation segmentation;
    bool segmentarFlag;
    sHSV hsv;
    Pixel pixel;

    QStringListModel *model;
    QStringList leaders;
    QModelIndex index;

    int row, currentRow;
    std::vector<sColor*> color;  //Colores* listaColores;
    sColor itemColor;
    QIcon iconForSymbol(const QString &symbolName);
    void loadColorsList();
};

#endif /* EDITCOLORGUI_H_ */

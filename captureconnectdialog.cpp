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
  \file    captureconnectdialog.cpp
  \brief   C++ Implementation: CaptureConnectDialog
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================


#include "captureconnectdialog.h"

CaptureConnectDialog::CaptureConnectDialog(QWidget *parent) : QDialog(parent) {
    // Setup dialog
    setupUi(this);
    // deviceNumberEdit (device number) input string validation
    QRegExp rx1("[0-9]\\d{0,2}"); // Integers 0 to 999
    QRegExpValidator *validator1 = new QRegExpValidator(rx1, 0);
    deviceNumberEdit->setValidator(validator1);
    // Initially set deviceNumber and captureMethod to defaults
    deviceNumber=-1;
    captureMethod="camera";
}

CaptureConnectDialog::~CaptureConnectDialog() {
	// TODO Auto-generated destructor stub
}

void CaptureConnectDialog::captureMethodSelected()
{
    // "Any available camera"
    if(anyCameraButton->isChecked())
        deviceNumber=-1;
    // "Device number"
    else {
    	if (deviceNumberButton->isChecked()) {
			// Set device number to default (any available camera) if field is blank
			if(deviceNumberEdit->text().isEmpty())
			{
				QMessageBox::warning(this->parentWidget(), "WARNING:","Device Number field blank.\nAutomatically set to 'any available camera'.");
				deviceNumber=-1;
			}
			// User-specified camera
			else
				deviceNumber=deviceNumberEdit->text().toInt();
    	}
    	// User-specified video file
    	else {
    		captureMethod="file";
    		filename=filenameEdit->text().toUtf8().constData();
    	}
    }
} // setDeviceNumber()

string CaptureConnectDialog::getCaptureMethod() {
	return captureMethod;
}

int CaptureConnectDialog::getDeviceNumber()
{
    return deviceNumber;
} // getDeviceNumber()

string CaptureConnectDialog::getFilename() {
	return filename;
}

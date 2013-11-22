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
  \file    plugin_networking.cpp
  \brief   C++ Implementation: Plugin_Networking
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "plugin_networking.h"

Plugin_Networking::Plugin_Networking() {
	// TODO Auto-generated constructor stub
	destAddress = "10.0.2.255";
	destPort = 9998;
	sendString = "Hello, World!";
}

Plugin_Networking::~Plugin_Networking() {
	// TODO Auto-generated destructor stub
}

bool Plugin_Networking::process(IplImage *frame, std::vector<sData *> &data) {
	try {
		// is it sending the string (not including \0)???
		//cout << "sendString: " << sendString << endl;
		for (unsigned int j=0; j < data[0]->blue_team->patches.size(); ++j) {
			cout << data[0]->blue_team->patches[j]->field_pos.x << " , " << data[0]->blue_team->patches[j]->field_pos.y << endl;
		}

		sock.sendTo(&sendString, (int) sendString.size(), destAddress, destPort);
	} catch (SocketException &e) {
	    cerr << e.what() << endl;
	    //exit(1);
	  }

	return true;
}


std::string Plugin_Networking::getName() {
  return "Networking";
}

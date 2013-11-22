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
  \file    plugin_networking.h
  \brief   C++ Interface: Plugin_Networking
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef PLUGIN_NETWORKING_H_
#define PLUGIN_NETWORKING_H_

#include "visionplugin.h"
//#include "send.h"
#include <string.h>
#include "practicalsocket.h"

using namespace std;

class Plugin_Networking: public VisionPlugin {
public:
	Plugin_Networking();
	virtual ~Plugin_Networking();

	virtual bool process(IplImage *frame, std::vector<sData *> &data);
	virtual std::string getName();

public:
	UDPSocket sock;
	string destAddress;
	unsigned short destPort;
	string sendString;
};

#endif /* PLUGIN_NETWORKING_H_ */

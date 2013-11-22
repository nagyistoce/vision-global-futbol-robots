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
  \file    team.h
  \brief   C++ Interface: Team
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#ifndef TEAM_H_
#define TEAM_H_

#include "pattern.h"

class Team {
public:
	bool enabled;
	int team_id;
	int team_colorid;
	std::vector<int> usesColor;  // color id used by markers
	std::vector<Pattern *> patches;

	Team();
	virtual ~Team();
};

#endif /* TEAM_H_ */

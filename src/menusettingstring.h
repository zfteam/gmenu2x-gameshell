/***************************************************************************
 *   Copyright (C) 2006 by Massimiliano Torromeo   *
 *   massimiliano.torromeo@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef MENUSETTINGSTRING_H
#define MENUSETTINGSTRING_H

#include "menusettingstringbase.h"

class MenuSettingString : public MenuSettingStringBase {
protected:
	virtual void edit();

	std::string diagTitle, diagIcon;

public:
	MenuSettingString(GMenu2X *gmenu2x, const std::string &name,
					  const std::string &description, std::string *value,
					  const std::string &diagTitle = "",
					  const std::string &diagIcon = "");
	virtual ~MenuSettingString() {}
};

#endif

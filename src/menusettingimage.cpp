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
#include "menusettingimage.h"
#include "imagedialog.h"
#include "utilities.h"

using std::string;

MenuSettingImage::MenuSettingImage(GMenu2X *gmenu2x, const string &name, const string &description, string *value, const string &filter, const string &startPath)
	: MenuSettingFile(gmenu2x, name, description, value, filter, startPath) {}

void MenuSettingImage::edit() {
	string _value = value();
	if (_value.empty())
		_value = startPath+"/";
	ImageDialog id(gmenu2x, description, filter, _value);
	if (id.exec()) setValue(id.getPath() + "/" + id.getFile());
}

void MenuSettingImage::setValue(const string &value) {
	string skinpath(gmenu2x->getExePath() + "skins/" + gmenu2x->confStr["skin"]);
	bool inSkinDir = value.substr(0, skinpath.length()) == skinpath;
	if (!inSkinDir && gmenu2x->confStr["skin"] != "Default") {
		skinpath = gmenu2x->getExePath() + "skins/Default";
		inSkinDir = value.substr(0, skinpath.length()) == skinpath;
	}
	if (inSkinDir) {
		string tempIcon = value.substr(skinpath.length(), value.length());
		string::size_type pos = tempIcon.find("/");
		if (pos != string::npos) {
			*_value = "skin:" + tempIcon.substr(pos + 1, value.length());
		} else {
			*_value = value;
		}
	} else {
		*_value = value;
	}
}

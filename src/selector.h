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

#ifndef SELECTOR_H_
#define SELECTOR_H_

#include <string>
#include "gmenu2x.h"
#include "utilities.h"
#include "dialog.h"

#define SELECTOR_ELEMENTS 11

class LinkApp;
class FileLister;

using std::string;
using std::vector;

class Selector : protected Dialog {
private:
	int selRow;
	LinkApp *link;

	string file, dir;
	unordered_map<string, string> aliases;
	void loadAliases();
	string getAlias(const string &key);
	void prepare(FileLister *fl, vector<string> *screens, vector<string> *titles);
	void freeScreenshots(vector<string> *screens);
	
public:
	Selector(GMenu2X *gmenu2x, LinkApp *link, const string &selectorDir="");
	
	int exec(int startSelection=0);
	
	const string &getFile() { return file; }
	const string &getDir() { return dir; }
};

#endif /*SELECTOR_H_*/

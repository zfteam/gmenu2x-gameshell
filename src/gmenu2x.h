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

#ifndef GMENU2X_H
#define GMENU2X_H

#include "surfacecollection.h"
#include "iconbutton.h"
#include "translator.h"
#include "FastDelegate.h"
#include "utilities.h"
#include "touchscreen.h"
#include "inputmanager.h"
#include "surface.h"
#include "fonthelper.h"

#include <iostream>
#include <string>
#include <vector>
#include <tr1/unordered_map>

const int MAX_VOLUME_SCALE_FACTOR = 200;
// Default values - going to add settings adjustment, saving, loading and such
const int VOLUME_SCALER_MUTE = 0;
const int VOLUME_SCALER_PHONES = 65;
const int VOLUME_SCALER_NORMAL = 100;
const int VOLUME_MODE_MUTE = 0;
const int VOLUME_MODE_PHONES = 1;
const int VOLUME_MODE_NORMAL = 2;
const int BATTERY_READS = 10;

const int LOOP_DELAY=30000;

#if defined(TARGET_GP2X)
	#define DEFAULT_CPU_CLK 200
#else
	#define DEFAULT_CPU_CLK 533
#endif

extern const char *CARD_ROOT;
extern const int CARD_ROOT_LEN;

// Note: Keep this in sync with colorNames!
enum color {
	COLOR_TOP_BAR_BG,
	COLOR_BOTTOM_BAR_BG,
	COLOR_SELECTION_BG,
	COLOR_MESSAGE_BOX_BG,
	COLOR_MESSAGE_BOX_BORDER,
	COLOR_MESSAGE_BOX_SELECTION,
	COLOR_FONT,
	COLOR_FONT_OUTLINE,

	NUM_COLORS,
};

using std::string;
using std::vector;
using fastdelegate::FastDelegate0;

typedef FastDelegate0<> MenuAction;
typedef unordered_map<string, string, hash<string> > ConfStrHash;
typedef unordered_map<string, int, hash<string> > ConfIntHash;

typedef struct {
	unsigned short batt;
	unsigned short remocon;
} MMSP2ADC;

struct MenuOption {
	string text;
	MenuAction action;
};

class Menu;

class GMenu2X {
private:
	string path; //!< Contains the working directory of GMenu2X
	/*!
	Retrieves the free disk space on the sd
	@return String containing a human readable representation of the free disk space
	*/
	string getDiskFree();
	unsigned short cpuX; //!< Offset for displaying cpu clock information
	unsigned short volumeX; //!< Offset for displaying volume level
	unsigned short manualX; //!< Offset for displaying the manual indicator in the taskbar
	/*!
	Reads the current battery state and returns a number representing it's level of charge
	@return A number representing battery charge. 0 means fully discharged. 5 means fully charged. 6 represents a gp2x using AC power.
	*/
	unsigned short getBatteryLevel();
	int batteryHandle;
	void browsePath(const string &path, vector<string>* directories, vector<string>* files);
	/*!
	Starts the scanning of the nand and sd filesystems, searching for gpe and gpu files and creating the links in 2 dedicated sections.
	*/
	void scanner();
	/*!
	Performs the actual scan in the given path and populates the files vector with the results. The creation of the links is not performed here.
	@see scanner
	*/
	void scanPath(string path, vector<string> *files);

	/*!
	Displays a selector and launches the specified executable file
	*/
	void explorer();

	bool inet, //!< Represents the configuration of the basic network services. @see readCommonIni @see usbnet @see samba @see web
		usbnet,
		samba,
		web;
	string ip, defaultgw, lastSelectorDir;
	int lastSelectorElement;
	void readConfig();
	void readConfigOpen2x();
	void readTmp();
	void readCommonIni();
	void writeCommonIni();

	void initServices();
	void initFont();
	void initMenu();

	IconButton *btnContextMenu;

	unsigned int memdev;
	volatile unsigned short *memregs;
#ifdef TARGET_GP2X
	volatile unsigned short *MEM_REG;
	int cx25874; //tv-out
#endif
	void gp2x_tvout_on(bool pal);
	void gp2x_tvout_off();
	void gp2x_init();
	void gp2x_deinit();
	void toggleTvOut();

public:
	GMenu2X();
	~GMenu2X();
	void quit();

	/*
	 * Variables needed for elements disposition
	 */
	uint resX, resY, halfX, halfY;
	uint bottomBarIconY, bottomBarTextY, linkColumns, linkRows;

	/*!
	Retrieves the parent directory of GMenu2X.
	This functions is used to initialize the "path" variable.
	@see path
	@return String containing the parent directory
	*/
	const string &getExePath();

	InputManager input;
	Touchscreen ts;

	//Configuration hashes
	ConfStrHash confStr, skinConfStr;
	ConfIntHash confInt, skinConfInt;
	RGBAColor skinConfColors[NUM_COLORS];

	//Configuration settings
	bool useSelectionPng;
	void setSkin(const string &skin, bool setWallpaper = true);
	//firmware type and version
	string fwType, fwVersion;
	//gp2x type
	bool f200;

	// Open2x settings ---------------------------------------------------------
	bool o2x_usb_net_on_boot, o2x_ftp_on_boot, o2x_telnet_on_boot, o2x_gp2xjoy_on_boot, o2x_usb_host_on_boot, o2x_usb_hid_on_boot, o2x_usb_storage_on_boot;
	string o2x_usb_net_ip;
	int volumeMode, savedVolumeMode;		//	just use the const int scale values at top of source

	//  Volume scaling values to store from config files
	int volumeScalerPhones;
	int volumeScalerNormal;
	//--------------------------------------------------------------------------

	SurfaceCollection sc;
	Translator tr;
	Surface *s, *bg;
	FontHelper *font;

	//Status functions
	void main();
	void options();
	void settingsOpen2x();
	void skinMenu();
	void activateSdUsb();
	void activateNandUsb();
	void activateRootUsb();
	void about();
	void viewLog();
	void contextMenu();
	void changeWallpaper();
	void saveScreenshot();

	void applyRamTimings();
	void applyDefaultTimings();

	void setClock(unsigned mhz);
	void setGamma(int gamma);

	void setVolume(int vol);
	int getVolume();
	void setVolumeScaler(int scaler);
	int getVolumeScaler();

	void setInputSpeed();

	void writeConfig();
	void writeConfigOpen2x();
	void writeSkinConfig();
	void writeTmp(int selelem=-1, const string &selectordir="");

	void ledOn();
	void ledOff();

	void addLink();
	void editLink();
	void deleteLink();
	void addSection();
	void renameSection();
	void deleteSection();

	void initBG();
	int drawButton(Button *btn, int x=5, int y=-10);
	int drawButton(Surface *s, const string &btn, const string &text, int x=5, int y=-10);
	int drawButtonRight(Surface *s, const string &btn, const string &text, int x=5, int y=-10);
	void drawScrollBar(uint pagesize, uint totalsize, uint pagepos, uint top, uint height);

	void drawTopBar(Surface *s=NULL);
	void drawBottomBar(Surface *s=NULL);

	Menu* menu;
};

#endif

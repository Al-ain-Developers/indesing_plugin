/***********************************************************************
 *
//  Copyright 1988 - 2010 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2008.
 *
 ***********************************************************************/

/*
 *	WRServices
 *
 *	WRVer.h
 *
 */

#ifndef WRVer_H_
#define WRVer_H_
/* The DLL Version will show up as MAJOR.MINOR.ENG */ 
#define WR_VERSION_MAJOR		0xF
#define	WR_VERSION_MAJORSTR 	"15"
#define WR_VERSION_MINOR		0x03
#define	WR_VERSION_MINORSTR 	"3"
#define WR_VERSION_ENG 0x00
#define WR_VERSION_ENGSTR "0"

/**
	Current version number of WRServices
 
	The WRServices version number is a 32 bit integer with four sub-fields.  It consists
	of a "debug vs. release" field, a "major version" field, a "minor version" field,
	and an "engineering" or "build number" field.  The highest bit (0x80000000) of
	the integer is set to 1 for debug builds of WRServices and is set to 0 for release
	builds.  The next highest 15 bits (0x7fff0000) are the major version.  The next
	highest 8 bits (0x0000ff00) are the minor version.  The lowest 8 bits
	(0x000000ff) are the engineering version.

	On Windows the WRServices version number number is displayed in the WRServices.dll file
	by looking in the Properties dialog (right-click on the WRServices.dll file and choose
	"Properties" from the pop-up menu).  In this dialog, look at the "Version" panel.
	The version number is displayed as the "File version:"

	On Macintosh the version number can be seen by selecting the WRServicesLib file in the
	Finder and choosing "Get Info" from the "File" menu.  In that dialog (in the "General
	Information" panel) the version number is displayed at the beginning of the "Version:"
	field.

	The version number can be programatically determined by calling the WRGetVersion function
	from WRServices.h.

	@see WRGetVersion	
*/
#define WR_VERSION				((WR_VERSION_MAJOR << 16) | (WR_VERSION_MINOR << 8) | WR_VERSION_ENG)


#endif /* WRVer_H_ */


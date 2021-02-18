//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CInterfaceFontInfo.h $
//  
//  Owner: Michael Burbidge
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __CInterfaceFontInfo_h__
#define __CInterfaceFontInfo_h__

#include "PMString.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

class IPMFont;

const int16 kInterfaceFontPlain	= 0x0000;
const int16 kInterfaceFontBold	 = 0x0001;
const int16 kInterfaceFontItalic = 0x0002;

/**	Base class for platform specific implementation of UI font structure.

	@see IUIFontSpec for the interface which allows widgets to override their default UI font.
	@see IInterfaceFonts for the main interface to get InterfaceFontInfo from an interface font IDs
	@see InterfaceFontInfo for the platform specific implementations of this structure
	@see DrawStringUtils.h for the main routines that use InterfaceFontInfo
*/
class DV_WIDGET_DECL CInterfaceFontInfo
{
public:
	/** Constructor */
	CInterfaceFontInfo();

	/** Constructor from font name*/
	CInterfaceFontInfo(const PMString& fontName);

	/** Copy Constructor */
	CInterfaceFontInfo(const CInterfaceFontInfo& other);

	/** Destructor */
	~CInterfaceFontInfo();

	/** Assignment */
	CInterfaceFontInfo& operator=(const CInterfaceFontInfo& other);
	
	/** Get the name of the font for this UI font structure */
	const PMString&			GetFontName() const;

	/** Get the InDesign font from this UI font */
	IPMFont*					GetFont() const;

protected:
	PMString				fFontName;
	IPMFont*					fFont;
};

#pragma export off

#endif

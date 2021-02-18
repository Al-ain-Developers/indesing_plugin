//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IInterfaceFonts.h $
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
#ifndef __IInterfaceFonts_h__
#define __IInterfaceFonts_h__

#include "IPMUnknown.h"
#include "InterfaceFontInfo.h"

/** Interface for specifying which set of UI fonts to use for the application
*/
class IInterfaceFonts : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINTERFACEFONTS };
	/** Get the font used for a given interface font ID. 
		@param interfaceElementId specifies which interface font we're interested in. @see ShuksanID.h for interface font IDs, i.e. kPaletteWindowFontId
		@return which font to use for this interface font id 
	*/
	virtual const InterfaceFontInfo&	GetFont(const int32& interfaceElementId) const = 0;

	/** Get the font used for a given interface font ID.
		@param locale specifies which locale we're interested in. Different locales may use different fonts
		@param interfaceElementId specifies which interface font we're interested in. @see ShuksanID.h for interface font IDs, i.e. kPaletteWindowFontId
		@return which font to use for this interface font id 
	*/
	virtual const InterfaceFontInfo&	GetFont(const PMLocaleId& locale,
												const int32& interfaceElementId) const = 0;

	/** Set the font used for a given interface font ID.  
		@param locale specifies which locale we're interested in. Different locales may use different fonts
		@param interfaceElementId specifies which interface font we're interested in. @see ShuksanID.h for interface font IDs, i.e. kPaletteWindowFontId
		@param fontName specifies the name of the font to use for the specified interface font id in the specified locale.
		@param fontSize specifies the font size to use for the specified interface font id in the specified locale
		@param fontAttributes specifies the font attributes to use for the specified interface font id in the specified locale, i.e. kInterfaceFontBold
	*/
	virtual void						SetFont(const PMLocaleId& locale,
												const int32& interfaceElementId,
												const PMString& fontName,
												const int16& fontSize,
												const int16& fontAttributes) = 0;
};

#endif

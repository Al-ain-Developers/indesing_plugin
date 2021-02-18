//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IUIFontSpec.h $
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
#ifndef __IUIFontSpec_h__
#define __IUIFontSpec_h__

#include "IPMUnknown.h"
#include "widgetid.h"

/** Interface for specifying which UI font to use for a control. Default fonts for controls are
	determined by the window the control is in. @see IWindow::GetFont 
	This interface is used to override this default behavior.
*/
class IUIFontSpec : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IUIFONTSPEC };

	/** Set the font ID. This is an ID that can be used to look up the corresponding interface font 
		in IInterfaceFonts interface. @see ShuksanID.h for interface font IDs
		@param interfaceElementId specifies which UI font to use for this widget, i.e. kPaletteWindowFontId
	*/
	virtual void		SetFontID(const int32& interfaceElementId) = 0;

	/** Get the font ID. This is an ID that can be used to look up the corresponding interface font 
		in IInterfaceFonts interface. @see ShuksanID.h for interface font IDs
		@return which UI font to use for this widget, i.e. kPaletteWindowFontId
	*/
	virtual int32		GetFontID() const = 0;

	/** Set the hilite font ID. This is an ID that can be used to look up the corresponding interface font 
		in IInterfaceFonts interface. @see ShuksanID.h for interface font IDs. The hilite font is used when
		drawing some widgets in a selected state.
		@param interfaceElementId specifies which UI font to use for this widget when selected, i.e. kPaletteWindowHiliteFontId
	*/
	virtual void		SetHiliteFontID(const int32& interfaceElementId) = 0;

	/** Get the hilite font ID. This is an ID that can be used to look up the corresponding interface font 
		in IInterfaceFonts interface. @see ShuksanID.h for interface font IDs. The hilite font is used when
		drawing some widgets in a selected state.
		@return which UI font to use for this widget when selected, i.e. kPaletteWindowHiliteFontId
	*/
	virtual int32		GetHiliteFontID() const = 0;
};

#endif // __IUIFontSpec_h__

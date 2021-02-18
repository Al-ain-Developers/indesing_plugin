//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IMenuUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IMenuUtils__
#define __IMenuUtils__

// ----- Interfaces -----

#include "IInterfaceColors.h"
#include "IPMUnknown.h"

// ----- Includes -----

#include "InterfaceFontInfo.h"
#include "LocaleSetting.h"
#include "PMString.h"

// ----- Utility files -----

#include "Utils.h"

// ----- ID.h files -----

#include "AppFrameworkID.h"

class IGraphicsContext;

/** This provides some utility routines commonly used by menu code.
		i.e. Utils<IMenuUtils>()->PlatformStripMenuAccelerator( ... ) ;
*/
class IMenuUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMENUUTILS };


	/** Strips the menu accelerator from the string, if this platform doesn't need it. Generally a no-op on windows. On the mac, this strips single '&' characters from the string
		(for English and most other languages. Some languages like Japanese use different accelerator characters)
		@param inOutString This is a pointer to the string to remove the accelerator from
		@param uiLocale describes what UI this string is for.
	*/
	virtual void PlatformStripMenuAccelerator(PMString* inOutString, int16 uiLocale = LocaleSetting::GetLocale().GetUserInterfaceId()) = 0;

	/** Strips the menu accelerator from the string. Generally, this strips single '&' characters from the string
		(for English and most other languages. Some languages like Japanese use different accelerator characters)
		@param inOutString This is a pointer to the string to remove the accelerator from
		@param uiLocale describes what UI this string is for.
	*/
	virtual void StripMenuAccelerator(PMString* inOutString, int16 uiLocale) = 0;
	
	/** Inserts extra '&' characters into a string, doubling up each one. This is required for strings
		that actually contain non-accelerator ampersand characters. e.g. Style names, master names, layer names, 
		swatch names or other user-entered strings. Can be useful before call to ReplaceStringParameters, which is often
		followed by a call to SetNthActionName, or SetTextControlData.
		Should only be called on strings that don't contain accelerator ampersands. Safe to call on both
		platforms.
		@param inOutString This is a pointer to the string to insert extra ampersands into
		@param uiLocale describes what UI this string is for.
	*/
	virtual void InsertAmpersandForDisplay(PMString* inOutString, int16 uiLocale = LocaleSetting::GetLocale().GetUserInterfaceId()) = 0;

	/** takes a menu path, removes the last item (i.e. if you pass in 'Main:Type:Font:Times', the string you passed in is now 'Main:Type:Font')
		@param inOutString This is a pointer to the string to remove the last part of the menu path from
		@return kFalse if string has 0 or 1 part, else kTrue
	*/
	virtual bool16 RemoveLastMenuPart(PMString *inOutString) = 0;
	
	/** takes a menu path, removes all but the last item (i.e. if you pass in 'Main:Type:Font:Times', the string you passed in is now 'Times')
		@param inOutString This is a pointer to the string to remove the last part of the menu path from
		@return kFalse if string has 0 or 1 part, else kTrue
	*/
	virtual bool16 RemoveAllButLastMenuPart(PMString *inOutString) = 0;	
	
	/** counts # of menu parts. i.e. if you pass in 'Main:Type:Font:Times', this would return 4. Note: If you pass in 'Main:Type:Font:' this will return 3.
		@param menuPath the string to count the menu parts of
		@return number of menu parts in the passed in string
	*/
	virtual int32 GetNumMenuParts(const PMString& menuPath) = 0;
	
	/** get the nth part of a menu path. i.e. if you pass in 'Main:Type:Font:Times' and 2, this would return 'Font'
		@param menuPath the string of menu parts
		@param index which menu part you want
		@return string with the nth menu part
	*/
	virtual PMString GetNthMenuPart(const PMString& menuPath,int32 index) = 0;

	/** DEPRECATED: draw the specified string in the the current port, using menu theme. This is mostly intended for use in OwnerDrawn menus
		@param port the port to draw into
		@param menuString the menu item string to draw
		@param bounds the bounds to draw the string into
		@param alignment the alignment for the string in the box, i.e. kAlignLeft
		@param hilited whether or not the menu item should be drawn hilited
		@param disabled whether or not the menu item should be drawn disabled
	*/
	virtual void DrawMenuString(SysPort port, const PMString& menuString, const SysRect& bounds, int16 alignment, bool16 hilited, bool16 disabled ) = 0;

	/** draw the specified string in the the current port, using menu theme. This is mostly intended for use in OwnerDrawn menus
		@param gc the graphics context to draw into
		@param startPt where to start drawing
		@param str the menu item string to draw
		@param fontInfo the font to draw with
		@param color the color to draw with
		@param convertAmpersandToUnderline whether or not to convert '&' to underlines, like windows does
		@param disabled whether or not the menu item should be drawn disabled
	*/
	virtual void DrawMenuString(IGraphicsContext* gc, const PMPoint& startPt, const PMString& str, const InterfaceFontInfo& fontInfo,
						  IInterfaceColors::InterfaceColor color = kInterfaceBlack, bool16 convertAmpersandToUnderline = kFalse, bool16 disabled = kFalse) = 0;

	/** Translate a menu name. Menu names preceeded by the kDontTranslateChar (@see ActionDefs.h) 
			won't be translated, but the kDontTranslateChar will be stripped.
		@param untranslatedName of the menu IN/OUT
	*/
	virtual void TranslateMenuName(PMString& untranslatedName) = 0 ;
	
 	/** Create the text of recent file. It will
 		1. Add the Number and accelerator on Windows
 		2. If the fileName is a path and exeeds a fixed number of characters, it will remove path tokens from the 
 		   middle of the path and replace them with an ellipses.
 		3. If the filename exceeds the width, ellipses are added to the end.
 		Width is based on characters, not screen width since we don't know the font information for menus.
		@param path or path and filename of the file IN
		@param menu position used when adding the Window accelerators.
		@return string that is ready for the menu.
	*/
	virtual PMString GetMenuNameFromFileName(const PMString &fileName, int32 position) = 0;
};

#endif	// __IMenuUtils__

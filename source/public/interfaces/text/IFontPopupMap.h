//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFontPopupMap.h $
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
//  
//  IFontPopupMap 
//  See also bug #570
//  
//========================================================================================

#pragma once
#ifndef __IFontPopupMap__
#define __IFontPopupMap__

#include "IPMUnknown.h"
#include "PMString.h"

class IPMFont;

//----------------------------------------------------------------------------------------
// Interface IFontPopupMap
//----------------------------------------------------------------------------------------

/** This is an interface of the FontPopup- it maps between the items of the FontPopup
	and the  FontMenu. Because the application's font menu is hierarchical and a standard MAC popup
	does not hierarchical menus this class has to be created to map between them.
	@ingroup text_font
*/
class IFontPopupMap : public IPMUnknown
{
public:
	virtual void				Init() = 0;
			// --- initializes the map

	virtual uint32				GetPopupEntryCount() const = 0;
			// --- returns the count of the maps
		
	virtual const PMString *	GetNthPopupEntry( uint32 nAt ) const = 0;
			// --- returns the nth FontName of the map

	virtual int32 				GetIndexOfFontName( const PMString& FontName ) const = 0;
			// --- returns the index of a given font name

	virtual IPMFont *				QueryFont( uint32 nAt ) = 0; 
			// --- returns the font at the given index

	virtual const PMString&	GetDefaultFontName() const = 0;
			// --- returns the default font name: Times Roman
};

#endif

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CColorContext.h $
//  
//  Owner: Mouhammad Fakhoury
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
#ifndef __CColorContext__
#define __CColorContext__

#include "IInterfaceColors.h"

#pragma export on

//
// CColorContext
//

/**
 Simple class wrapper around IInterfaceColors. Also the base class for a pair
 of platform-specific helper classes, MColorContext and WColorContext
 
 @see IInterfaceColors
 @see MColorContext
 @see WColorContext
 */
class DV_WIDGET_DECL CColorContext{
public:
	/**
	 Default constructor. Acquires session's IInterfaceColors interface
	 */
	CColorContext();
	
	/**
	 Destructor. Releases IInterfaceColor acquired in constructor
	 */
	~CColorContext();

	/**
	 Gets the RGB color specified by the given UI color selector as an RGBColor.
	 
	 @param index		IN The selector for the UI color to return
	 @param rgb			OUT The color being requested
	 @return kTrue if method succeeds, else kFalse
	 @see IInterfaceColors::InterfaceColor
	 @see IInterfaceColors::GetRGBColor
	 */
	bool16 GetRGBColor(const IInterfaceColors::InterfaceColor index, RGBColor& rgb )const;

	/**
	 Gets the RGB color specified by the given UI color selector as a 
	 RealAGMColor.
	 
	 @param index		IN The selector for the UI color to return
	 @param rgb			OUT The color being requested
	 @return kTrue if method succeeds, else kFalse
	 @see IInterfaceColors::InterfaceColor
	 @see IInterfaceColors::GetRealAGMColor
	 */
	bool16 GetRealAGMColor(const IInterfaceColors::InterfaceColor index, RealAGMColor& rgb )const;

protected:
	IInterfaceColors* fIInterfaceColors;
};

#pragma export off



#endif //__CColorContext__

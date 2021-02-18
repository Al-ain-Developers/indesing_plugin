//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/WFontContext.h $
//  
//  Owner: Dave Burnard
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
#ifndef __WFontContext__
#define __WFontContext__

#include "InterfaceFontInfo.h"
#include "IGraphicsContext.h"

#pragma export on

/**	Utility class for setting & restoring a UI font into an HDC. This object is intended to be declared on the stack. This object will
	restore the previous font in the HDC when it goes out of scope.
*/
class WIDGET_DECL WFontContext
{
public:
	/** Constructor using a graphics context. This class will get the HDC from the graphics context, and set the font for that HDC */
	WFontContext(const IGraphicsContext* gc, const InterfaceFontInfo& fontInfo);
	WFontContext(HDC dc, const InterfaceFontInfo& fontInfo);

	~WFontContext();
	
	void						SetFont(const InterfaceFontInfo& fontInfo);

private:
	HDC							fDC;
	HFONT						fPreviousFont;
	HFONT						fCurrentFont;
};

#pragma export off



#endif //__WFontContext__

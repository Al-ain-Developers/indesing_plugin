//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IFontNames.h $
//  
//  Owner: Steve Flenniken
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
//  IFontNames.h
//  
//========================================================================================

#pragma once
#ifndef __IFontNames__
#define __IFontNames__

#include "K2Vector.h"
#include "PDFID.h"

/** Interface to hold font information for a graphic, such as EPS and PDF.
*/
class IFontNames : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFONTNAMES };

	/** This routine is used to get the font names of the fonts needed (not supplied) by the graphic.
		@param nameList OUT a vector of font name strings that are needed but not supplied
	*/
	virtual void FontsNeeded(K2Vector<PMString> &nameList) = 0;

	/** This routine is used to get the font names of the fonts supplied or embedded in the graphic.
		@param nameList OUT a vector of font name strings that are supplied
	*/
	virtual void FontsSupplied(K2Vector<PMString> &nameList) = 0;

	/** Set the list of font names needed by this graphic.
		@param nameList IN a vector of font name strings that are needed but not supplied
	*/
	virtual void SetFontsNeeded(K2Vector<PMString> &nameList) = 0;

	/**	Set the list of font names that are supplied by this graphic.
		@param nameList IN a vector of font name strings that are supplied
	*/
	virtual void SetFontsSupplied(K2Vector<PMString> &nameList) = 0;
};

#endif // __IFontNames__




//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ITextAreaPrefs.h $
//  
//  Owner: psorrick
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
#ifndef __ITextAreaPrefs__
#define __ITextAreaPrefs__

#include "IPMUnknown.h"
#include "PMReal.h"
#include "InCopyCoreID.h"

class ITextAreaPrefs : public IPMUnknown
{
public:	
	////
	//// InCopy Text Area Preferences
	////
	/**
		Define the default IID for ITextAreaPrefs.
	*/
	enum { kDefaultIID = IID_ITEXTAREAPREFERENCES };

	/**
		Define the unit index for text area depth
	*/
	enum TextAreaDepthUnit { kUnitChars = 0, kUnitWords, kUnitLines, kUnitPages, kUnitColumnInches } ;

	// The width, depth and depth unit of the text area
	virtual void SetTextAreaWidth(const	PMReal	width) = 0;
	virtual PMReal GetTextAreaWidth() = 0;

	virtual void SetTextAreaDepth(const	PMReal depth) = 0;
	virtual PMReal GetTextAreaDepth() = 0;

	virtual void SetTextAreaDepthUnit(TextAreaDepthUnit index) = 0;
	virtual TextAreaDepthUnit GetTextAreaDepthUnit() = 0;
};

#endif

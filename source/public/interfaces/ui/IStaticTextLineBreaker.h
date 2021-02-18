//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IStaticTextLineBreaker.h $
//  
//  Owner: Rich Gartland
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
#ifndef __ISTATICTEXTLINEBREAKER__
#define __ISTATICTEXTLINEBREAKER__

#include "IPMUnknown.h"
#include "InterfaceFontInfo.h"
#include "widgetid.h"

class IGraphicsContext;
class PMRect;
class PMPoint;


/** This interface is used to break a long string into multiple lines. It's mainly used by multiline static text widgets.
*/
class IStaticTextLineBreaker : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTATICTEXTLINEBREAKER };

	/** Breaks the string into a set of lines, based on the given max line width and the font.
		@param stringToBreak The string we're breaking into lines.
		@param maxLineWidth The max line width.
		@param fontInfo the font to use in computing text width.
	*/
	virtual void CreateLineBreaks(const PMString& stringToBreak, const PMReal maxLineWidth,  
						const InterfaceFontInfo& fontInfo) = 0;

	/** Gets the nth line from the last call to CreateLineBreaks
		@param lineIndex which line to return
		@return the string for the desired line.
	*/
	virtual PMString GetNthLine(int32 lineIndex) const = 0;

	/** Gets the width and height for the nth line from the last call to CreateLineBreaks
		@param lineIndex which line to return
		@return the point describing the width and height of the desired line
	*/
	virtual PMPoint GetNthLineSize(int32 lineIndex) const = 0;

	/** Gets the line count from the last call to CreateLineBreaks
		@return the count of lines
	*/
	virtual int32 GetNumLines() const = 0;
};

#endif

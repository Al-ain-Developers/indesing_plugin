//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextRanges.h $
//  
//  Owner: Danielle Bessette
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
#ifndef __ITextRanges__
#define __ITextRanges__

#include "IPMUnknown.h"
#include "TextID.h"
#include "TextRange.h"

/**
	@ingroup text_datatype
*/
class ITextRanges : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTRANGES };

	/**	Creates a Vector of TextRanges.  Resulting ranges may cross story thread boundaries.
		@return a vector of text ranges. The caller is responsible for delete'ing the memory allocated for this K2Vector.
	*/
	virtual K2Vector<InDesign::TextRange>* CreateTextRanges() = 0;

	/**	Creates a Vector of TextRanges.  Resulting ranges will not cross story thread boundaries.
		@return a vector of text ranges. The caller is responsible for delete'ing the memory allocated for this K2Vector.
	*/
	virtual K2Vector<InDesign::TextRange>* CreateThreadSafeTextRanges() = 0;

	/**	An easier way to determine there are multiple ranges than asking for them all.
		The definition of multiple text ranges is somewhat up to the implementation. For example, if you select
		text across 2 frames, you have 1 selection, but if you select 2 text frames you have 2.
		@return whether there are multiple text ranges.
	*/
	virtual bool16 HasMultipleTextRanges() = 0;

	/**	Return a single text range the represents the first part of the selection.
		@return whatever the implementation calls the first text range.
	*/
	virtual InDesign::TextRange GetFirstTextRange() = 0;

	/** Return a list of all TextModel UIDs in the selected ranges.
		@ return a UIDList of all TextModel UIDs.
	*/
	virtual UIDList GetSelectedStories() = 0;

};

#endif

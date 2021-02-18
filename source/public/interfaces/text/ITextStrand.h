//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextStrand.h $
//  
//  Owner: EricM
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
#ifndef __ITEXTSTRAND__
#define __ITEXTSTRAND__


#include "DataWrapper.h"
#include "IPMUnknown.h"
#include "TextID.h"

class WideString;

/** Abstract interface that all textstrands must implement.
	@ingroup text_story
*/
class ITextStrand : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTSTRAND };

		/**
			Find the contiguous chunk of text stored in the strand (text in strand may be fragmented).
			@param begin IN position to look at.
			@param len OUT  number of characters from offset @param begin IN to the end of the chunk.
			@param chukstart OUT is the text index where the chunk starts.
			@return DataWrapper is a reference to the contiguous text chunk which allows
			iteration over the text one character at a time. Using index 0 gives the character
			which happens to be at offset begin in the story.
		*/
		virtual DataWrapper<textchar> FindChunk(TextIndex begin, int32 *len, TextIndex *chunkstart = nil) = 0;
};



#endif		// __ITEXTSTRAND__

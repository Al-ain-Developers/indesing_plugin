//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IRubyStrand.h $
//  
//  Owner: Ric Kamicar
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

#include "IPMUnknown.h"
#include "CJKID.h"

#ifndef __IRubyAttrStrand__
#define __IRubyAttrStrand__

class AttributeBossList;

/** Strand interface for the Japanese attribute: Ruby.
*/
class IRubyAttrStrand : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IRUBYATTRSTRAND };

	/** Setup the ruby strand at the given location over the given length of text based on the attributes in the overrides list.
	@param startpos IN Where in the text to start the ruby
	@param numchars IN How many chars to apply the state to. Method is a NOP if *numchars <= 0
	@param over IN The overrides to apply.

	@see Strands, Text Attributes
	*/
	virtual void SetRubyState(TextIndex* startpos, int32* numchars, const AttributeBossList* over) = 0;

	/** Return ruby range, if any, at the given position.
	@param position IN Desired text index. NOP if position < 0
	@param count OUT if non-nil, return the distance from position to the end of the strand
	@param runBegin OUT  if non-nil, return the text index of the beginning of the ruby
	@return if ruby is on or not at the given position.
	*/
	virtual bool16 GetRubyRun(TextIndex position, int32* count, TextIndex* runBegin = nil) = 0;
};

#endif


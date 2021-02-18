//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/text/LineDescriptionME.h $
//  
//  Owner: prubini
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Usage rights licenced to Adobe Inc. 1993 - 2008.
//  
//========================================================================================

#pragma once
#ifndef __LineDescriptionME__
#define __LineDescriptionME__

//#include "ShuksanCoolType.h"
#include "PMRealGlyphPoint.h"

#ifdef PUBLIC_BUILD
#pragma export on
#endif

class TEInputOutputMapping;
class TESubLog;
class TEInputOutputHB;

class EffectiveTextMap;

class PUBLIC_DECL LineDescriptionME
{
public:
	LineDescriptionME();
	LineDescriptionME(const LineDescriptionME& rhs)
		{ *this = rhs; }
	virtual ~LineDescriptionME();

	/** internal use only undo/redo support. */
	void ReadWrite(IPMStream *s, StoryDescription *storyDesc);
	void ChangeMappingType(int mappingType);

	virtual const LineDescriptionME& operator = (const LineDescriptionME& rhs);

	EffectiveTextMap	fEffectiveTextMap;
	TESubLog*		fSubLog;
	TEInputOutputHB* fInputOutputHB;
	TEInputOutputMapping* fTempInputOutputMapping;
	TEInputOutputMapping* fIOMapping;
	int fMappingType = 2;
	// one item per glyph, sorted by visual order
	WRVector<WRRealGlyphPoint>	fStrikes;
	WRVector<WRFloat>	fGlyphWidths;
	WRVector<WRFloat>	fDiacXOffsets;
	WRVector<WRFloat>	fDiacYOffsets;

	// one item per run
	WRVector<int32>		fLogicalToVisualRunIndex;
	WRVector<int32>		fVisualToLogicalRunIndex;

	bool16				fIsRTL;
	PMReal				fOriginalXPosition; // HACK
	bool16				fWasRTLAdjusted; // ADHESIVE TAPE
};

#ifdef PUBLIC_BUILD
#pragma export off
#endif

#endif //__LineDescriptionME__

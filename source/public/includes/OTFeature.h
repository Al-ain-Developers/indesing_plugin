//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/OTFeature.h $
//  
//  Owner: Tommy Donovan
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
//  ABSTRACT:
//  This file defines the struct OneOTFeature, which is used to represent an
//  OpenType feature.
//  
//========================================================================================

#pragma once
#ifndef __OTFEATURE__
#define __OTFEATURE__

#include "K2Vector.h"

struct OneOTFeature
{
	typedef base_type data_type;
	OneOTFeature() : fFeature(0), fChoice(0)
		{}
	OneOTFeature(const char *c, int32 choice) : fChoice(choice)
		{ fFeature = *((int32*)(c)); }

	void SetFeature(const char* c)
		{ fFeature = *((int32*)(c)); }
	const char* GetFeature() const
		{ return (char *)(&fFeature); }

	void SetChoice(int32 choice)
		{ fChoice = choice; }
	const int32 GetChoice() const
		{ return fChoice; }

	int32	fFeature;
	int32	fChoice;
};

/*
template<>
inline int32 K2Vector<OneOTFeature>::Location(const OneOTFeature& ) const
{ ASSERT_FAIL("not supported"); return -1; }
*/

inline int operator==(const OneOTFeature&, const OneOTFeature&)
{
	ASSERT_FAIL("not supported"); return -1;
}

typedef K2Vector<OneOTFeature>	OpenTypeFeatureList;

// also in InDesignComposerDef.h as kHL_AutoOpenTypePositionalFormsFeatureTag
// not as a constant in a namespace because it adds the code for every obj
#define kOT_AutoOpenTypePositionalFormsFeatureTag		(*((int32*)("_APF")))


#endif		// __OTFEATURE__

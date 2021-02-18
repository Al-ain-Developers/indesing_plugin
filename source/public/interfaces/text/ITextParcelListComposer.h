//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextParcelListComposer.h $
//  
//  Owner: dwaterfa
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
#ifndef __ITextParcelListComposer__
#define __ITextParcelListComposer__

#include "IPMUnknown.h"
#include "TextID.h"
#include "ParcelKey.h"


/** 
	@ingroup text_comp
*/
class ITextParcelListComposer : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTPARCELLISTCOMPOSER };

	/**
	Compose all the Parcels in the ParcelList.
	*/
	virtual void RecomposeThruLastParcel() = 0;

	/**
	Compose upto and including the specified Parcel. Passing in an invalid
	ParcelKey is the same as calling RecomposeThruLastParcel().
	*/
	virtual void RecomposeThru(ParcelKey key) = 0;

	//
	// Compose upto and including the specified TextIndex. The TextIndex MUST
	// be part of the TextStoryThread mapped to the ParcelList.
	//
	virtual void RecomposeThruTextIndex(TextIndex composeUpThruThisIndex) = 0;

};

#endif

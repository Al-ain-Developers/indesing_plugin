//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlinkTextDestinationState.h $
//  
//  Owner: Brendan O'Shea
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
#ifndef __IHyperlinkTextDestinationState__
#define __IHyperlinkTextDestinationState__

#include "IPMUnknown.h"
#include "HyperlinkID.h"

#include "ParcelKey.h"


/**
	@ingroup layout_hyper
*/
class IHyperlinkTextDestinationState : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHYPERLINKTEXTDESTINATIONSTATE };

	/**
	Returns the ParcelKey where the Destination was last composed. Will return
	and invalid ParcelKey if the Destination was composed into overset.
	@return ParcelKey
	*/
	virtual ParcelKey	GetParcelKey() const = 0;

	/**
	Sets the ParcelKey where the Destination was last composed. Setting this
	to a different value than is currently stored will automatically bump the
	ChangeCount below.
	@param key ParcelKey of the WaxLine containing the Destination.
	*/
	virtual void		SetParcelKey(ParcelKey key) = 0;

	/**
	The Change Count provides a simple mechanism to communicate changes in the
	ParcelKey.
	@return int32 value incremented whenver the ParcelKey changes.
	*/
	virtual uint32		GetChangeCount() const = 0;

	/**
	Increments the Change Count.
	*/
	virtual void		IncrementChangeCount() = 0;
	
};


#endif // __IHyperlinkTextDestinationState__


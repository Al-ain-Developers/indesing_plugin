//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IStandOffUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IStandOffUtils__
#define __IStandOffUtils__

#include "GenericID.h"
#include "IPMUnknown.h"
#include "Utils.h"

class UIDList;
class PMUnknownRefList;

/**
	StandOff utilities.
	i.e. Utils<IStandOffUtils>()->StripStandOffs( ... ) ;
	@ingroup layout_util
*/
class IStandOffUtils : public IPMUnknown
{
public:
	/** Default IID of IStandOffUtils */
	enum { kDefaultIID = IID_ISTANDOFFUTILS };

	/** Removes the standoffs from a UIDList of items 
		@param pPageItems IN/OUT. UIDList with page items to be stripped from StandOffs.
		@return pPageItems;
	*/
	virtual UIDList* StripStandOffs(UIDList* pPageItems) const = 0;

	/** Removes the standoffs from a PMUnknownRefList of items.
		@param pPageItems IN/OUT. PMUnknownRefList with page items to be stripped from StandOffs.
		@return pPageItems;
	*/
	virtual PMUnknownRefList* StripStandOffs(PMUnknownRefList* pPageItems) const = 0;

	/** Adds standoffs to the list. For use by sprites. 
		@param pPageItems IN/OUT. UIDList with page items to which StandOffs are being added to.
		@return pPageItems;
	*/
	virtual UIDList* AddStandOffs(UIDList* pPageItems) const = 0;
};


#endif	// __IStandOffUtils__

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ISpreadMultiColumnFrames.h $
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
#ifndef __ISpreadMultiColumnFrames__
#define __ISpreadMultiColumnFrames__

#include "IPMUnknown.h"
#include "UIDList.h"
#include "StandOffID.h"

class IMultiColumnTextFrame;

/** Interface for storing a list of UID to MCFs that are on the Spread.
	@ingroup text
*/
class ISpreadMultiColumnFrames : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISPREADMULTICOLUMNFRAMES };

	/** Adds a value to the list. Duplicates are not allowed.
	@param mcf Pointer to IMultiColumnTextFrame to add to the list
	*/
	virtual void	Add(const IMultiColumnTextFrame* mcf) = 0;
	
	/** Returns kTrue if the specified MultiColumnTextFrames is known.
	@param mcfUID UID of MCF
	@return kTrue/kFalse
	*/
	virtual bool16	GetHas(UID mcfUID) const = 0;

	/** Returns the list of MultiColumnTextFrames previously added.
	@param pList Pointer to UIDList of MCFs on the Spread.
	@return Count of MCFs on the spread.
	*/
	virtual int32	GetAll(UIDList* pList = nil) const = 0;

	/** Removes a previously added value from the list. The value must be valid.
	@param mcf Pointer to IMultiColumnTextFrame to remove from the list
	*/
	virtual void	Remove(const IMultiColumnTextFrame* mcf) = 0;

};

#endif // __ISpreadMultiColumnFrames__


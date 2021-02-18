//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IGoToPositionBehaviorData.h $
//  
//  Owner: Michael Brubidge
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
#ifndef __IGoToPositionBehaviorData_h__
#define __IGoToPositionBehaviorData_h__

#include "IGoToZoomBehaviorData.h"
#include "BehaviorID.h"

class IDocument;

//========================================================================================
// CLASS IGoToPositionBehaviorData
//========================================================================================

/** Data interface for Go To Position Behavior */
class IGoToPositionBehaviorData : public IGoToZoomBehaviorData
{
public:
	typedef int32 Position;
	enum PositionConstants { kFirstPage = 0, kLastPage, kPreviousPage, kNextPage, kPreviousView, kNextView, kSpecificPage };
	
	/** Get the destination position
		 Position is a static property. It can't be changed once the behavior is created.
		 @return the destination position ( kFirstPage, kLastPage, kPreviousPage, kNextPage, kPreviousView, kNextView, kSpecificPage )
	*/
	virtual Position	GetPosition() const = 0;
	
	/** If the Position is kSpecificPage, then use SetSpecificPageIndex to set a one-based page index.
		@param oneBasedIndex [IN]: the zero-based page index of the destination page
	*/
	virtual void SetSpecificPageIndex(uint32 zeroBasedIndex) = 0;

	/** GetSpecificPage only makes sense when Position == kSpecificPage.  GetSpecificPage will return the zero-based destination page index
		to GoTo.
		 @return zero-based destination page index.
	*/
	virtual uint32	GetSpecificPageIndex() const = 0;
};

#endif // __IGoToPositionBehaviorData_h__

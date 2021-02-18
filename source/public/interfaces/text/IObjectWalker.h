//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IObjectWalker.h $
//  
//  Owner: Raveendra Madala	
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
#ifndef __IObjectWalker__
#define __IObjectWalker__

#include "IPMUnknown.h"
#include "TextWalkerServiceProviderID.h"
#include "ObjectWalkerScopeOptions.h"

/**
	This interface tries to iterate/walk through all the pageitems (including inlines and anchored objects) as per
	the options specified. 
 */
class IObjectWalker : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IOBJECTWALKER };
	
	enum WalkerState
	{
		/**
			Informs the caller that the document has been walked completely.
		 */
		kEndOfDocumentReached,
		/**
			Informs the caller that the walking is complete.
		 */
		kWalkCompleted,
		/**
			Informs the caller that the walking is happening on the same spread
		 */
		kWalkingOnSameSpread,
		/**
			Informs the caller that walking is completed on the current spread and will be moving to
			next spread.
		 */
		kSpreadEndReached,
		/**
			Informs the caller that walker has moved to next spread
		 */
		kMovedToNextSpread,
		/**
			Informs the caller that walker has moved to next document
		 */
		kMovedToNextDocument,
	};
	
	/**
		Initializes the walker with the appropriate options.
		
		@see also ObjectWalkerScopeOptions
	 */
	virtual void Initialize(ObjectWalkerScopeOptions options) = 0;
	
	/**
		Gets the next page item
		
		@param outRef holds the next page item
		@return WalkerState informs the caller of the walker state.
	 */
	virtual WalkerState GetNextItem(UIDRef& ourRef) = 0;
	
	/**
		Gets the current page item

		@return UIDRef of the page item that has been just traversed.
	 */
	virtual UIDRef GetCurrentItem() const = 0;
	/**
		Gets the UIDRef of the spread being walked
		
		@return UIDRef of the sperad being walked.
	 */
	virtual UIDRef GetCurrentSpread() const = 0;
	
	/**
		Tells the walker to move to the specified unwalked spread
		
		@param inSpreadRef is the UIDRef of the spread being requested to move to.
		@return kTrue if Walker is able to move to the requested spread. 
		        kFalse if move failed. This failure can happen when the spread is already walked 
	 */
	virtual bool16 MoveToSpread(UIDRef inSpreadRef) = 0;
	
	/**
		Skips the specified spread from walking. If the spread specified is current walking spread then the walking will move to next spread.
		
		@param inSpreadRef is the UIDRef of the spread being requested to skip.
		@return kTrue if Walker can skip the requested spread. 
				kFalse if the skip fails. This failure can happen when walker is on last spread and that spread is being 
					   requested to skip. Also, when already walked spread is specified.
	 */
	virtual bool16 SkipSpread(UIDRef inSpreadRef) = 0;
	
	/**
		Start with the specified page item.
		
		@param inItemRef is the UIDRef of the page item being requested to start the walking with.
		@return kTrue if Walker can be set to start with the item being requested.
				kFalse if Walker can not be set to start with the item being requested. This can happen, if the walking has already started or 
				       when the item being requested is not in the scope.
	 */
	virtual bool16 StartWithItem(UIDRef inItemRef) = 0;
};

#endif
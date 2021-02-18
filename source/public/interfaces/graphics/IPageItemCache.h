//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPageItemCache.h $
//  
//  Owner: jargast
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
//  Attach this interface to pageitems to provide cache invalidation notifications
//  
//========================================================================================

#pragma once
#ifndef __IPageItemCache__
#define __IPageItemCache__

//
// This interface is private to the caching pageitems implementation and should not
// be used outside of that context
//

#include "IPMUnknown.h"
#include "GenericID.h"

/** Attach this interface to pageitems to provide cache invalidation notifications
NOTE: This interface is private to the caching pageitems implementation and should not
be used outside of that context.
*/
class IPageItemCache : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPAGEITEMCACHE };

	/** Set all of the cache states to invalid */
	virtual void InvalidateCaches() = 0;
	
	/** Set whether or not the geometry cache is valid
	@param isValid - kTrue for valid, kFalse for invalid
	*/
	virtual void 	SetGeometryCacheValid (bool16 isValid) = 0;

	/** Determine whether or not the geometry cache is valid
	@return bool16 - kTrue for valid, kFalse for invalid
	*/
	virtual bool16 	IsGeometryCacheValid() const = 0;
	
	/** Set whether or not the path geometry cache is valid
	@param isValid - kTrue for valid, kFalse for invalid
	*/
	virtual void 	SetPathGeometryCacheValid (bool16 isValid) = 0;
	
	/** Determine whether or not the path geometry cache is valid
	@return bool16 - kTrue for valid, kFalse for invalid
	*/
	virtual bool16 	IsPathGeometryCacheValid() const = 0;
	
	/** Set whether or not the shape cache is valid
	@param isValid - kTrue for valid, kFalse for invalid
	*/
	virtual void 	SetShapeCacheValid (bool16 isValid) = 0;
	
	/** Determine whether or not the shape cache is valid
	@return bool16 - kTrue for valid, kFalse for invalid
	*/
	virtual bool16 	IsShapeCacheValid() const = 0;

	
	/** Set whether or not the path item cache is valid
	@param isValid - kTrue for valid, kFalse for invalid
	*/
	virtual void 	SetPathItemCacheValid (bool16 isValid) = 0;
	
	/** Determine whether or not the path item cache is valid
	@return bool16 - kTrue for valid, kFalse for invalid
	*/
	virtual bool16 	IsPathItemCacheValid() const = 0;

	/** Called by the implementation of IPageItemCache telling the parent
	that this item has changed
	@param iChild - The child whose parent needs to be notified
	*/
	virtual void ChildInvalidated(IPMUnknown* iChild) = 0;
};

#endif

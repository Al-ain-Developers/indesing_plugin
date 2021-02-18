//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IItemContextUtils.h $
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
#ifndef __IItemContextUtils__
#define __IItemContextUtils__

#include "GenericID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "PMRect.h"

class IHierarchy;
class IControlView;
class IItemContext;
class ISnapTo;


/** Utilities related to item context.
	@ingroup layout_util
*/
class IItemContextUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IITEMCONTEXTUTILS };

	virtual IItemContext* QueryItemContext1(IHierarchy* item /*, bool16 includeItem*/) const = 0;
		// Returns the nearest enclosing item in the hierarchy which implements IItemContext
		// Includes the item itself in the search, if includeItem is true.


	virtual IItemContext* QueryCreationContext(IControlView* layoutView, const PBPMPoint& where) const = 0;
		// Find the context for a creation tracker. The search for an IItemContext implementation
		// begins with the hit-detected item rather than its parent


	virtual IItemContext* QueryItemContext3(IControlView* layoutView, const PBPMPoint& where /*, bool16 includeItem*/) const = 0;
		// Find the itemcontext of a hit-detected item at the given location.
		// If includeItem is true, the hit-detected item itself is included in the search,
		// otherwise it begins with its parent.


	virtual ISnapTo* QuerySnapTo(IItemContext* context) const = 0;
		// Searches the ItemContext parent chain for an implementation of ISnapTo
};


#endif	// __IItemContextUtils__

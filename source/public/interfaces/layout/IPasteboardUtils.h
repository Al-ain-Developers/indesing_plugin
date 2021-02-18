//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPasteboardUtils.h $
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
#ifndef __IPasteboardUtils__
#define __IPasteboardUtils__

#include "GenericID.h"
#include "IPMUnknown.h"
#include "RequestContext.h"
#include "Utils.h"

#include "PMRect.h"

class ISpread;
class IHierarchy;
class IControlView;
class UIDList;

/**
	This interface contains pasteboard related utility functions. 
	
	For example, <pre>Utils<IPasteboardUtils>()->QuerySpread( ... );</pre>

	@ingroup layout_util
	@ingroup layout_paste
*/
class IPasteboardUtils : public IPMUnknown
{
public:
	/**
		Define the default IID for IPasteboardUtils.
	*/
	enum { kDefaultIID = IID_IPASTEBOARDUTILS };

	/**
		Query the spread containing a particular item. The caller should deference the return interface.

		@param item the condition for querying spread.
		@return ISpread* that contains the given item.
	*/
	virtual ISpread* QuerySpread(IHierarchy* item) const = 0;
			
	/**
		For script provider implementations (@see CScriptProvider): Query the spread on which a page item rests. 
		Forces recompose first for inline page items.

		@param page item for which to get the spread
		@param context is the script request context
		@param useLastFrameIfOverset if kTrue and item is an inline object in overset text, return the spread for the last frame
			in the text's story (instead of nil)
		@return spread that contains the given item
	*/
	virtual ISpread* QuerySpread(IHierarchy* item, const ScriptInfo::RequestContext& context, bool16 useLastFrameIfOverset = kFalse) const = 0;

	/**
		Query the spread containing the particular location in the view. The caller should deference the return interface.

		@param layoutView the given layout view, one of the condition for querying spread. 
		@param location the given location, one of the condition for querying spread.
		@return ISpread* spread that satisfies the given conditions. May return nil for points outside any spread (e.g. no man's land gray area)
	*/
	virtual ISpread* QuerySpread(IControlView* layoutView, const PBPMPoint& location) const = 0;
			
	/**
		Query the spread with the particular coordinate in a horizontal or vertical direction in the view. 
		The caller should deference the return interface.

		@param layoutView the given layout view, one of the condition for querying spread.
		@param location the given location, one of the condition for querying spread.
		@param horizontal the given direction, one of the condition for querying spread. 
		@return ISpread* spread that satisfies the given conditions. May return nil for points outside any spread (e.g. no man's land gray area)
	*/
	virtual ISpread* QuerySpread(IControlView* layoutView, const PMReal& location, bool16 horizontal) const = 0;
			
	/**
		Query the closest spread to the indicated location in the view. It's biased towards vertical measurements,
		i.e. it finds the spread closest to the vertical component of the location.  
		If there is at least one spread then it will be returned even if the point is in the floor area
		The caller should deference the return interface.

		@param layoutView the given layout view, one of the condition for querying spread.
		@param location the given location, one of the condition for querying spread.
		@return ISpread* spread that satisfies the given conditions.
	*/
	virtual ISpread* QueryNearestSpread(IControlView* layoutView, const PBPMPoint& location) const = 0;
			
};


#endif	// __IPasteboardUtils__

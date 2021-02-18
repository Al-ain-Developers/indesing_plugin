//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IBatchPlaceTrackerHelper.h $
//  
//  Owner: Rich Gartland
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
#ifndef __IBatchPlaceTrackerHelper__
#define __IBatchPlaceTrackerHelper__

// Interfaces
#include "IEvent.h"
#include "IPlaceBehavior.h"

// Includes
#include "PMPoint.h"
#include "UIDList.h"

// ID files
#include "OpenPlaceID.h"

class IControlView ;
class ITextTarget ;

/** Abstract interface for a helper class to assist a tracker in doing "batch place" operations; that
	is, imports that immediately put potentially many pageitems onto the page, but still need to have
	the standard place-gun capabilities of positioning where the item(s) should be put, import preview, etc.
	This class aids in the proper positioning of the items after the user clicks a position for placement.
*/

class IBatchPlaceTrackerHelper : public IPMUnknown 
{
	public:
		enum { kDefaultIID = IID_IBATCHPLACETRACKERHELPER };

		/** Perform the adjustments needed to properly position the already placed items according to the user's click. 
			Typically this would mean a translation of the items from their import-time locations to the user's click location.
			@param startPnt IN where the snippet was initially imported
			@param controlView IN the view clicked in by the user
			@param parent IN the parent item for the pageitem(s)
			@param points IN two points -- first button-down location, and if a drag-box, the button-up location
			@param theEvent IN the event record
			@param afterPlace OUT what behavior to take after the place operation
			@return UIDList of the adjusted items
		*/
		virtual UIDList AdjustAlreadyPlacedItems(PMPoint startPnt, IControlView* controlView, const UIDRef& parent, 
			const PMPointList& points, const IEvent& theEvent, IPlaceBehavior::eAfterPlace* afterPlace) = 0;

		/** Convert the placed snippet into an inline at the indicated text location.
			Only succeeds if the snippet contains a single object with IHierarchy.
			@param iTextTarget IN is the text location at which to create the inline
			@return the UIDRef of the inline
		*/
		virtual UIDRef ConvertPlacedItemsToInline( ITextTarget* iTextTarget ) = 0 ;
};

#endif

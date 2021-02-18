//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILayoutTrackerAccess.h $
//  
//  Owner: Paul Sorrick
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
#ifndef __LAYOUTTRACKERACCESS__
#define __LAYOUTTRACKERACCESS__

#include "LayoutUIID.h"
#include "ILayoutTarget.h"

//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------

class UIDList;
class ITracker;

//----------------------------------------------------------------------------------------
// LayoutTrackerAccess: Access interface for layout trackers to layout item list.
//----------------------------------------------------------------------------------------

class ILayoutTrackerAccess : public IPMUnknown
{
	//____________________________________________________________________________________________
	//  Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_ILAYOUTTRACKERACCESS };

	public:

		/**	Returns a UIDList from the Layout CSB (ILayoutTarget) for use by layout trackers.
			@param stripStandoffs, kStripStandoffs to strip standoffs,  kDontStripStandoffs to retain them from returned UIDList. 
			@param PMIID, Will call CreateFlattenedUIDList before returning the UIDList. If kInvalidInterfaceID is used, list is not flattened.
			@return UIDList 
		 */
		virtual UIDList GetUIDList (ITracker* tracker, ILayoutTarget::StandoffChoice stripStandoffs, const PMIID& iid = kInvalidInterfaceID) const = 0;

		/**	Returns whether or not a page item is selected from the Layout CSB (ILayoutTarget) for use by layout trackers.
			@param pageItemUID, The page item to check
			@return bool16 
		 */
		virtual bool16 IsSelected (ITracker* tracker, UID pageItemUID) const = 0;

	};

#endif	//__LAYOUTTRACKERACCESS__

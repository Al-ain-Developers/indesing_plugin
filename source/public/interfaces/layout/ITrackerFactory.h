//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ITrackerFactory.h $
//  
//  Owner: Lonnie Millett
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

#ifndef __ITRACKERFACTORY__
#define __ITRACKERFACTORY__

#include "IPMUnknown.h"
#include "ShuksanID.h"

//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------
class ITracker;

//----------------------------------------------------------------------------------------
// class ITrackerFactory
//----------------------------------------------------------------------------------------

/** Abstract interface for the tracker factory. There is a single implementation of this
	interface installed on the kSessionBoss. It handles installing all trackers, which get
	registered via the ITrackerRegister interface.

	Provides an extensible mechanism for creating new tracking behavior. Trackers are
	uniquely identified by two classIDs. These IDs usually identify the context in
	which the tracker will be created. For example the tracker that is used for
	rotation of page items is installed with a widgetID of kLayoutWidgetBoss,
	a toolID of kRotateToolBoss. When a mouse down occurs in the layout widget
	and the active tool is the rotate tool, a tracker with a class of kRotateTrackerBoss
	will be created. Trackers can be installed on the fly with Install or at startup
	with ITrackerRegister.

	@see ITrackerRegister.h
	@see ITracker.h
*/
class ITrackerFactory : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITRACKERFACTORY };
	

		/**	Registers all trackers for classes that implement the ITrackerRegister interface
		 */
		virtual void Startup() = 0;

		/**	Install a tracker with the indicated widgetID and toolID. These can be any
			ID values and are not required to be IDs of actual widgets or tools.

			@param widgetID [IN] the widget associated with this tracker.
			@param toolID [IN] the tool the tracker is associated with. If not associated with a toolbox tool 
			(e.g. a widget tracker) just use the same value as widgetID.
			@param trackerID [IN] the boss ID for the tracker.
		 */
		virtual void InstallTracker(ClassID widgetID, ClassID toolID, ClassID trackerID) = 0;

		/**	Remove the tracker if it exists
			@param widgetID [IN] the widget associated with this tracker.
			@param toolID [IN] the tool the tracker is associated with. 
		 */
		virtual void RemoveTracker(ClassID widgetID, ClassID toolID) = 0;

		/**	Determine if a tracker has already been installed with these ID values.
			@param widgetID [IN] the widget associated with this tracker.
			@param toolID [IN] the tool the tracker is associated with. 
			@return bool16 return kTrue if tracker with these ID values, kFalse otherwise.
		 */
		virtual bool16 HasTracker(ClassID widgetID, ClassID toolID) = 0;

		/**	Returns an instantiated tracker if registered
			@param widgetID [IN] the widget associated with this tracker.
			@param toolID [IN] the tool the tracker is associated with. 
			@return ITracker* return a bumped reference to the tracker. May return nil.
		 */
		virtual ITracker* QueryTracker(ClassID widgetID, ClassID toolID) = 0;
};


#endif

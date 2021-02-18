//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IControlStripWidgetSuite.h $
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
//  
//  Note:
//  
//========================================================================================

#pragma once
#ifndef __ICONTROLSTRIPWIDGETSUITE__
#define __ICONTROLSTRIPWIDGETSUITE__

#include "IPMUnknown.h"
#include "ControlStripID.h"
#include "K2Vector.h"
#include "ControlStripWidgetInfo.h"

class ITracker;

class IControlStripWidgetSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICONTROLSTRIPWIDGETSUITE };
	
	/**	Get the list of information about widgets to show in Control Strip for current selection.
		Append your ControlStripWidgetInfo(s) onto this list. This method will be called for
		active control strip suites when a selection change occurs. See also IControlStripRegister in
		order to tell Control Strip what your suite IID is.

		@param infoList a list of widgets to be enabled and shown in the control strip for the current selection. 
		@param suiteIID the interface IID of the suite. Will be the value return from IControlStripRegister.
	 */
	virtual void		GetEnabledWidgets (K2Vector<ControlStripWidgetInfo>& infoList, const PMIID& suiteIID) const = 0;

	/**	Get the list of information about widgets to show in Control Strip during tracking.
		
		Append your ControlStripWidgetInfo(s) onto this list. This method will be called for
		trackers that broadcast the IID_IDYNAMICTRACKERDATA protocol. Generally these are creation trackers
		See also IControlStripRegister in order to tell Control Strip what your suite IID is.
		Don't append any values if you want standard creation tracker widgets.

		@param infoList a list of widgets to be enabled and shown in the control strip for the current selection. 
		@param suiteIID the interface IID of the suite. Will be the value return from IControlStripRegister.
		@param tracker the tracker that is currently operating. Can be nil in case of drag and drop.
	 */
	virtual void		GetEnabledTrackingWidgets (K2Vector<ControlStripWidgetInfo>& infoList, const PMIID& suiteIID, const ITracker* tracker) const = 0;
};

#endif // __IControlStripWidgetSuite__

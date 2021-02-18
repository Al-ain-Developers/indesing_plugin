//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IControlStripPrefs.h $
//  
//  Owner: Matt Joss
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
#ifndef __ICONTROLSTRIPPREFS__
#define __ICONTROLSTRIPPREFS__

#include "ControlStripID.h"
#include "K2Vector.h"
#include "KeyValuePair.h"
#include "IPMUnknown.h"

/** Preferences for control strip display preferences, persisted on session workspace. */
class IControlStripPrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICONTROLSTRIPPREFS };

	enum
	{
		kCharacterMode = 0x00000001,
		kParagraphMode = 0x00000002
	};

	/**	How a control strip widget suite should display it's info.
		Used in calls to IControlStripWidgetSuite::GetEnabledWidgets
		
		@return  the display mode of the control strip
	 */
	virtual	int32						GetDisplayMode() const = 0;

	/**	Specify the display mode for the control strip
		@param displayMode specifies how the control strip should display its widgets
	 */
	virtual	void						SetDisplayMode(int32 displayMode) = 0;

	/**	Return the size of the control strip. Used for floating mode when coming out the dock
		and by the detail controller on this panel.
		
		@return  the dimeions of control strip when in floating mode
	 */
	virtual	PMPoint						GetFloatingDimensions() const = 0;

	/**	Set the dimensions of the control strip when in floating mode. Used internally by
		palette resizing code and detail controller code.
		@param dimesions specifies the default size of the control strip when going into floating mode.
	 */
	virtual	void						SetFloatingDimensions(const PMPoint& dimensions) = 0;

	/**	Return a list of the names of all the control sets (PMString) and corresponding visibility (bool16)
		@param K2Pair<PMString, bool16>& IN/OUT list parameter that will be filled out.
	 */
	virtual void GetControlStripSetsVisibility(K2Vector< KeyValuePair<PMString, bool16> >& controlSetsVisibility) = 0;

	/**	Set the visibility of one or more control sets. kTrue for visible, kFalse for hidden.
		@param K2Pair<PMString, bool16>& IN list parameter containing the name/visibility key value pair for those control sets to set their visibility. 
	 */
	virtual void SetControlStripSetsVisibility(K2Vector< KeyValuePair<PMString, bool16> >& controlSetsVisibility) = 0;
};


#endif

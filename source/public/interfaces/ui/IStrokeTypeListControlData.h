//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IStrokeTypeListControlData.h $
//  
//  Owner: Greg St. Pierre
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
#ifndef __IStrokeTypeListControlData__
#define __IStrokeTypeListControlData__

#include "widgetid.h"

class IWorkspace;
class IGraphicAttributeSuite;

/** Control Data Interface associated with widgets based on a list of stroke types.
*/
class IStrokeTypeListControlData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTROKETYPELISTCONTROLDATA };

	/**	Set up stroke type control data based on path stroker data for the given workspace.
		@param workspace is the workspace from which the stroke types are obtained.
		@param attrSuite specifies the graphic attribute suite to use to set up the control.
		@param listModified is true if the list has been modified.
		@return kTrue if control data was rebuilt, else kFalse.
	*/
	virtual bool16 Setup(IWorkspace const *workspace, IGraphicAttributeSuite *attrSuite = nil, bool16 listModified = kFalse) = 0;

	/** Selects stroke type with given ClassID/UID pair from list.
		@param classID is the stroke type class ID.
		@param uid is the UID of the stroke type, or kInvalidUID if the stroke class is a built-in stroke style.
		@param inval is set to true if the associated view should be invalidated.
		@param notify is set to true if notification should be broadcast.
	*/
	virtual void Select(ClassID const &classID, UID const &uid, bool16 inval = kTrue, bool16 notify = kTrue) = 0;

	/** Sets control to no selection state.
		@param inval is set to true if the associated view should be invalidated.
		@param notify is set to true if notification should be broadcast.		
	*/
	virtual void Deselect(bool16 inval = kTrue, bool16 notify = kTrue) = 0;

	/** Retrieves ClassID/UID pair for selected stroke type in the list.
		@param classID is an output parameter to receive the stroke style's class ID.
		@param uid is an output parameter to receive the stroke style's UID.
	*/
	virtual void GetSelection(ClassID &classID, UID &uid) const = 0;

	/** Adds an "(Ignore)" entry to end of list, if none exists already.
	*/
	virtual void AddIgnore() const = 0;

	/** Removes "(Ignore)" entry, if in list.
	*/
	virtual void RemoveIgnore() const = 0;

	/** Adds an "None" entry to list, if none exists already.
	*/
	virtual void AddNone() const = 0;
};

#endif //!def __IStrokeTypeListControlData__

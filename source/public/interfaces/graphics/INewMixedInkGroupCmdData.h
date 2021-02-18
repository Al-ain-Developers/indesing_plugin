//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/INewMixedInkGroupCmdData.h $
//  
//  Owner: SusanCL
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
#ifndef __INewMixedInkGroupCmdData__
#define __INewMixedInkGroupCmdData__

#include "ColorSystemID.h"

/**	A data interface for NewMixedInkGroupCmd. This interface sets and retrieve
	data required creating mixed ink swatch group. Mixed ink swatch group is created
	based on an ink list. Each ink has an initial value, a step value, and a repeat count.
*/
class INewMixedInkGroupCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_INEWMIXEDINKGROUPCMDDATA };
		
		/**	Returns the ink UIDList for the creation of the mixed ink group.
		*/
		virtual const UIDList*		GetInkUIDListRef (void) = 0;
		
		/**	Add a ink and the corresponding data to the command's ink UIDList.
			@param inkRef the ink UIDRef to add to the list.
			@param initialValue the initial value for this ink. The initial value should be between 0% and 100%.
			@param stepValue the incremental value for this ink each time it is repeated. The step value
			should be between 0% and 100%.
			@param repeatCount the number of increments for this ink. The repeat count should be between 1 and 100.
		*/
		virtual void				AddInk (const UIDRef& inkRef, const PMReal& initialValue, const PMReal& stepValue, int32 repeatCount) = 0;

		/**	Get the initial value for the specified ink.
			@param inkUID is the specified ink.
			@returns the initial value for this ink.
			If value is -1, this means the specified ink is not in the ink list.
		*/
		virtual	PMReal				GetInkStartValue (UID inkUID) = 0;
		
		/**	Get the step value for the specified ink.
			@param inkUID is the specified ink.
			@returns the step value for this ink.
			If value is -1, this means the specified ink is not in the ink list.
		*/
		virtual	PMReal				GetInkStepValue (UID inkUID) = 0;

		/**	Get the repeat count for the specified ink.
			@param inkUID is the specified ink.
			@returns the repeat count for this ink.
			If value is -1, this means the specified ink is not in the ink list.
		*/
		virtual	int32				GetInkRepeatCount (UID inkUID) = 0;
		
		/** Sets the name for the new mixed ink group.
			@param name is the name for the new mixed ink group.
		*/
		virtual void				SetInkGroupName (const PMString& name) = 0;

		/** Returns the name for the new mixed ink group.
			@returns the name for the new mixed ink group.
		*/
		virtual PMString			GetInkGroupName (void) = 0;
};

#endif	//	__INewMixedInkGroupCmdData__
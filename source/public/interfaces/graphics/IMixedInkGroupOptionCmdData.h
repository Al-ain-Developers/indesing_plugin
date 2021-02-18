//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IMixedInkGroupOptionCmdData.h $
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
#ifndef __IMixedInkGroupOptionCmdData__
#define __IMixedInkGroupOptionCmdData__

#include "ColorSystemID.h"

/**	A data interface for NewMixedInkGroupCmd. This interface sets and retrieve
	data required creating mixed ink swatch group. Mixed ink swatch group is created
	based on an ink list. Each ink has an initial value, a step value, and a repeat count.
*/
class IMixedInkGroupOptionCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IMIXEDINKGROUPOPTIONCMDDATA };
		
		/**	Specify the old ink UID list. to be changed. This should match the exising mixed ink parent
			swatch's ink UID list.
			@param oldInkUIDList the old ink UID list..
		*/
		virtual void				SetOldInkUIDList (const UIDList& oldInkUIDList) = 0;
		
		
		/**	Returns the mixed ink group's old ink UID list..
			@returns a const UIDList* to the mixed ink group's old ink UID list..
		*/
		virtual const UIDList*		GetOldInkUIDListRef (void) = 0;

		/**	Set the replacement ink UIDs for the ink list specified by call to
			SetOldInkUIDList. Inks that are not replaced are specified in the same
			location by kInkUIDNotChanged. Inks that are removed are specified in the same location by
			kInvalidUID. The size of the list should match the size of the oldInkUIDList specified.
			@param replacementInkUIDList the replacement ink UID list..
		*/
		virtual void				SetInkReplacementUIDList (const UIDList& replacementInkUIDList) = 0;

		/**	Returns the mixed ink group's replacement ink UID list..
			@returns a const UIDList* to the mixed ink group's replacement ink UIDList.
		*/
		virtual const UIDList*		GetInkReplacementUIDListRef (void) = 0;

		/**	Set the replacement swatch UIDs for the ink list specified by call to
			SetOldInkUIDList. Inks can be (1) unchanged, (2) converted to process, (3) replaced by spot color UID,
			and (4) replaced by a process color swatch.
			(1) Inks that are not replaced are specified in the same location by kInkUIDNotChanged.
			(2) Inks that are converted to process are specified in the same location by
				kInvalidUID. 
			(3) Inks that are repalced by another spot color swatch are specifiec in the same location by
				the spot color swatch UID. 
			(4) Inks replaced by a process color swatch are specified in the same location by the process color UID.
			The size of the list should match the size of the oldInkUIDList specified.
			@param replacedSpotInkUIDList is the list of spot inks to be replaced.
			@param replacementSwatchUIDList is the list of swatch replacement UIDs.
		*/
		virtual void				SetSpotInksReplacementSwatchUIDList (const UIDList& replacedSpotInkUIDList, const UIDList& replacementSwatchUIDList) = 0;

		/**	Returns the mixed ink group's replacement swatch UID list.
			@returns a const UIDList* to the mixed ink group's replacement swatch UIDList.
			This UID list contains kInkUIDNotChanged, spot color swatch, process color swatch and/or kInvalidUID.
		*/
		virtual const UIDList*		GetReplacementSwatchUIDListRef (void) = 0;

		/**	Returns the list of spot ink UIDs to be replaced.
			@returns a const UIDList* to list of spot ink UIDs that will be replaced.
		*/
		virtual const UIDList*		GetReplacedSpotInkUIDListRef (void) = 0;

		/**	Sets convert to process flag. If this is set to kTrue, then
			ink list replacement settings are ignored.
		*/
		virtual void				SetConvertToProcess (bool16) = 0;

		/**	Returns convert to process flag.
			@returns kTrue if converting mixed ink group to proces.
		*/
		virtual bool16				GetConvertToProcess (void) = 0;

		
		/** Sets the name for the new mixed ink group.
			If this is set, then the names of all the mixed ink swatches that are linked to
			the parent swatch will be changed.
			@param name is the new name for the mixed ink group.
		*/
		virtual void				SetInkGroupName (const PMString& name) = 0;

		/** Returns the name for the new mixed ink group.
			@returns the name for the new mixed ink group.
		*/
		virtual PMString			GetInkGroupName (void) = 0;
};

#endif	//	__IMixedInkGroupOptionCmdData__
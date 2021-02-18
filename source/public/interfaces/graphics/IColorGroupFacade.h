//========================================================================================
//  
//  ADOBE CONFIDENTIAL
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IColorGroupFacade.h $
// 
//  Owner: Ankur Gupta
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 2014 Adobe Systems Incorporated
//  All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef _ICOLORGROUPFACADE_
#define _ICOLORGROUPFACADE_

#include "ColorSystemID.h"
#include "IColorGroupList.h"
#include "UIDList.h"

namespace Facade
{
	class IColorGroupFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_ICOLORGROUPFACADE };

	public:
		
		 /** Create and add a color group to the color group list. 
             @param colorGroupList IN the color group list in which the color group is created and added.
             @param name IN The name of the color group. 
             @param pos IN 0 based position at which to add the color group. Specify -1 to add to the end.
             @return UID of the added color group. 
        */ 
		virtual UID CreateAndAddColorGroup(IColorGroupList* colorGroupList, const PMString& name, int32 pos = -1) = 0;
		
		/** Move color groups to a new position within the same color group list.
			@param colorGroupList IN The UIDList of color groups to be moved.
			@param toPos IN 0 based starting position to which the color groups will be moved.
			@return kSuccess if the color groups were successfully moved, else an error code.
		*/
		virtual ErrorCode MoveColorGroups(const UIDList& colorGroupList, int32 toPos) = 0;
		
		/** Set the name of a color group.
			@param colorGroup IN The color group to be renamed.
			@param name IN The name of the color group.
			@return kSuccess if the color group name was successfully set, else an error code.
		*/
		virtual ErrorCode SetColorGroupName(const UIDRef& colorGroup, const PMString& name) = 0;

		/** Add members to a color group at the specified position. A member can be only in one color group.
			If it is already in any other color group then it would be removed from it.
			@param colorGroup IN The color group to which members need to be added.
			@param memberList IN The ordered list of members that need to be added.
			@param pos IN 0 based starting position at which the members will be added. Specify -1 to add to the end.
			@return kSuccess if the members were successfully added, else an error code.
		*/
		virtual ErrorCode AddMembers(const UIDRef& colorGroup, const UIDList& memberList, int32 pos = -1) = 0 ;

		/** Remove members from a color group.
			@param colorGroup IN The color group from which the members need to be removed.
			@param memberList IN The list of members that need to be removed.
			@return kSuccess if the members were successfully removed, else an error code.
		*/
		virtual ErrorCode RemoveMembers(const UIDRef& colorGroup, const UIDList& memberList) = 0 ;

		/** Deletes a list of color groups.
			@param colorGroupList IN The list of color groups to be deleted
			@param deleteChildren IN kTrue means children will also be deleted otherwise it will be moved
			@return kSuccess if the color groups were successfully deleted, else an error code.
		*/
		virtual ErrorCode DeleteColorGroups(const UIDList& colorGroupList, bool16 deleteChildren = kFalse) = 0 ;

		/** @param memberList IN The list of members to be removed from respective color groups.
			@return kSuccess if the members were successfully removed, else an error code.
		*/
		virtual ErrorCode RemoveFromRespectiveColorGroups(const UIDList& memberList) = 0 ;

		/** @param colorGroupList IN The list of color group that need to be duplicated.
			@param newColorGroupList OUT The list of newly color groups created.
			@return kSuccess if the members were successfully duplicated, else an error code.
		*/
		virtual ErrorCode DuplicateColorGroups(const UIDList& colorGroupList, UIDList& newColorGroupList) = 0 ;
	};
}
#endif // _ICOLORGROUPFACADE_

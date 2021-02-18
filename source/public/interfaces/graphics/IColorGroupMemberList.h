//========================================================================================
//  
//  ADOBE CONFIDENTIAL
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IColorGroupMemberList.h $
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
#ifndef __ICOLORGROUPMEMBERLIST__
#define __ICOLORGROUPMEMBERLIST__

#include "IPMUnknown.h"
#include "ColorSystemID.h"

/** Provides access to the members of a color group.
*/
class IColorGroupMemberList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOLORGROUPMEMBERLIST };

	/** Get the number of members in the color group.
		@return the number of members in the color group.
	*/
	virtual int32 CountMembers() const = 0 ;

	/** Add a member at the specified position in the color group.
		@param memberUID IN the UID of the member that needs to be added.
		@param pos IN 0 based position at which to add the member. Specify -1 to add to the end.
	*/
	virtual void AddMember(UID memberUID, int32 pos = -1) = 0 ;

	/** Remove a member from the color group
		@param memberUID IN the UID of the member that needs to be removed.
	*/
	virtual void RemoveMember(UID memberUID) = 0 ;
	
	/** Remove a member from the color group.
		@param pos IN the position of the member in the color group.
	*/
	virtual void RemoveNthMember(int32 pos) = 0 ;
	
	/** Remove all members from the color group.
	*/
	virtual void RemoveAllMembers() = 0 ;

	/** Get the Nth member UID from the color group.
		@param pos IN the 0 based index of the member in the color group.
		@return the UID of the member.
	*/
	virtual UIDRef GetNthMemberUID(int32 pos) const = 0 ;
	
	/** Get the position of the member in the color group.
		@param memberUID IN the UID of the member in the color group.
		@return the position of the member.
	*/
	virtual int32 GetMemberPosition(UID memberUID) const = 0 ;
};

#endif // __ICOLORGROUPMEMBERLIST__

//========================================================================================
//  
//  ADOBE CONFIDENTIAL
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IColorGroupList.h $
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
#ifndef __ICOLORGROUPLIST__
#define __ICOLORGROUPLIST__

#include "IPMUnknown.h"
#include "ColorSystemID.h"


/** Provides access to the color groups in the color group list
*/

class IColorGroupList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOLORGROUPLIST };
	
	/** Add a color group at the specified position in the color group list.
		@param colorGroupUID IN the UID of the color group that needs to be added.
		@param pos IN 0 based position at which to add the color group. Specify -1 to add to the end.
	*/
	virtual void AddColorGroup(UID colorGroupUID, int32 pos = -1) = 0 ;

	/** Remove a color group from the color group list.
		@param colorGroupUID IN the UID of the color group that needs to be removed.
	*/
	virtual void RemoveColorGroup(UID colorGroupUID) = 0 ;
	
	/** Remove a color group from the color group list.
		@param pos IN the position of the color group in the color group list.
	*/
	virtual void RemoveNthColorGroup(int32 pos) = 0 ;
	
	/** Remove all color groups from the color group list.
	*/
	virtual void RemoveAllColorGroups() = 0 ;

	/** Get the number of color groups in the color group list.
		@return the number of color groups.
	*/	
	virtual int32 CountColorGroups() const = 0 ;
	
	/** Get the Nth color group UID from the color group list.
		@param pos IN the 0 based index of the color group in the color group list.
		@return the UID of the color group.
	*/
	virtual UIDRef GetNthColorGroup(int32 pos) const = 0 ;
	
	/** Get the position of the color group in the color group list.
		@param colorGroupUID IN the UID of the color group in the color group list.
		@return the position of the color group.
	*/
	virtual int32 GetColorGroupPosition(UID colorGroupUID) const = 0 ;

	/** Find color group in the color group list by name.
		@param name IN the name of the color group in the color group list.
		@return the UIDRef of the color group.
	*/
	virtual UIDRef  FindColorGroup(const PMString& name) const = 0; 

};

#endif // __ICOLORGROUPLIST__

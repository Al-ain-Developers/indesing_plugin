//========================================================================================
//  
//  ADOBE CONFIDENTIAL
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IArticleChildList.h $
// 
//  Owner: Paresh Goel
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 2010 Adobe Systems Incorporated
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
#ifndef __IARTICLECHILDLIST__
#define __IARTICLECHILDLIST__

#include "IPMUnknown.h"
#include "ArticleID.h"

/** Group children can be reordered inside an Article independent of their Layout hierarchy.
	This Interface provides access to this reordering.
*/
class IArticleChildList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IARTICLECHILDLIST };

	/** Get the number of direct children of the Group.
	*/
	virtual int32 CountChildren() const = 0 ;

	/** Add a child at the specified position in the Group.
		@param childUID IN the UID of the child that needs to be added.
		@param pos IN 0 based position at which to add the child. Specify -1 to add to the end.
	*/
	virtual void AddChild(UID childUID, int32 pos = -1) = 0 ;

	/** Remove a child from the Group.
		@param childUID IN the UID of the child that needs to be removed.
	*/
	virtual void RemoveChild(UID childUID) = 0 ;
	
	/** Remove a child from the Group.
		@param pos IN the position of the child in the Group.
	*/
	virtual void RemoveNthChild(int32 pos) = 0 ;
	
	/** Remove all children from the Group.
	*/
	virtual void RemoveAllChildren() = 0 ;

	/** Get the Nth child UID from the Group.
		@param pos IN the 0 based index of the child in the Group.
		@return the UID of the child.
	*/
	virtual UID GetNthChildUID(int32 pos) const = 0 ;
	
	/** Get the position of the child in the Group.
		@param childUID IN the UID of the child in the Group.
		@return the position of the child.
	*/
	virtual int32 GetChildPosition(UID childUID) const = 0 ;
};

#endif // __IARTICLECHILDLIST__

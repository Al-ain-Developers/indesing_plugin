//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IStylePositionInfo.h $
//  
//  Owner: Sanjay Kumar
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
#ifndef __IStylePositionInfo__
#define __IStylePositionInfo__

#include "IPMUnknown.h"
#include "TextID.h"

class IStyleGroupHierarchy;
class IDataBase;
class IWorkspace;

/** Data Interface for style sets attributes 
*/

class IStylePositionInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTYLEPOSITIONINFO };

	/** Sets the parent of this style
		@param parent [IN] parent of this style
	*/
	virtual void SetParent(const IStyleGroupHierarchy* parent) = 0;

	/**  Returns the parent of this style
	*/
	virtual IStyleGroupHierarchy*  QueryParent() const = 0;
	
	/** Sets the parent uid of this style
		@param parentUID [IN] parent uid.
	*/
	virtual void SetParentUIDRef(const UIDRef& parentUID) = 0;
	
	/** Returns the parent uid of this style
	*/
	virtual UIDRef GetParentUIDRef() const =0;

	/** Sets the parent location and the database
		@param parentLocation [IN] the location of the parent
	*/
	virtual void SetParentLocation(const PMString& parentLocation) = 0;
	
	/** Returns the parent location 
		@return  the parent location path.
	*/
	virtual PMString GetParentLocation() const = 0;

	/** Sets the Style Set Manager IID
	*/
	virtual void SetStyleGroupManagerIID(const PMIID& ssmiid) = 0;

	/** Returns the StyleGroupManager IID
	*/
	virtual PMIID GetStyleGroupManagerIID() const = 0;

	/** Sets the Style set manager workspace UID
	*/
	virtual void SetWorkspaceUIDRef(const UIDRef& uidref) = 0;

	/** Returns the workspace UID Ref
	*/
	virtual UIDRef GetWorkspaceUIDRef() const = 0;

	/** Returns the position of this style with in its parent.
	*/
	virtual int32 GetPosition() const = 0;

	/** Sets the position of this style with in its parent.
		@param pos [IN] the postion of this style
	*/
	virtual void SetPosition(int32 pos) = 0;
};

#endif //__IStyleGroupInfo__
//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILinkEditAction.h $
//  
//  Owner: Michael Easter
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
//  Description:
//  This class defines an interface that allows an ILinkObject to have limited control
//  over the editing of the link that is linking the object.
//  
//========================================================================================

#pragma once
#ifndef __ILinkEditAction__
#define __ILinkEditAction__

// ----- Includes -----
#include "IPMUnknown.h"
#include "LinksID.h"


/**
 ILinkEditAction is used to implement limited control over the editing of the link(s)
 an ILinkObject is linked to.  When a link is edited, an attempt is made to get an
 ILinkEditAction interface off the ILinkObject the link links by calling the
 ILinkObject::QueryLinkedObject method.  If the interface is found, a check is made to
 ensure the object allows editing of the link.
 
 If editing is allowed, the BeforeOpen method is called before the link is opened
 for editing.  Any pre-edit processing that needs to be performed by the object can be
 done in the BeforeOpen method.  The method can also cause the edit operation to be
 aborted by returning false.  If BeforeOpen returns true, the edit operation continues,
 and the link's resource is opened for edit.

 After the resource is successfully opened for edit, the AfterOpen method is called to
 allow processing of any post open for edit operations required. 

 @see ILink
 @see ILinkFacade
 @see ILinkObject
 @see ILinkResource
 */
class ILinkEditAction : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKEDITACTION };

	/**
	 Called to determine if it is OK to allow a link resource to be edited.
	 @param linkRef [IN] UIDRef of the link whose resource to check.
	 @return True to allow the link resource to be edited, else false.
	 */ 
	virtual bool CanEdit(const UIDRef& linkRef) const = 0;

	/**
	 Called before a link resource is opened for edit.
	 @param linkRef [IN] UIDRef of the link whose resource is to be edited.
	 @return True to continue and open the link resource for edit, else false to abort the edit operation.
	 */ 
	virtual bool BeforeOpen(const UIDRef& linkRef) const = 0;

	/**
	 Called right after a link resource is opened for edit.
	 @param linkRef [IN] UIDRef of the link whose resource is being edited.
	 */
	virtual void AfterOpen(const UIDRef& linkRef) const = 0;
};

#endif // __ILinkEditAction__

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ICopyLinkToLinkObjectCmdData.h $
//  
//  Owner: Adrian O'Lenskie
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
#ifndef __ICopyLinkToLinkObjectCmdData__
#define __ICopyLinkToLinkObjectCmdData__

#include "IPMUnknown.h"

#include "LinksID.h"

/** Command data for the CopyLinkToLinkObject command. The interface contains three elements, the source link
	(to be copied) the target link object (to be associated with the new link) and the link UID (of the copied link).
	@see kCopyLinkToLinkObjectCmdBoss
*/
class ICopyLinkToLinkObjectCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOPYLINKTOLINKOBJECTCMDDATA };

	/** Set the input data.
		@param sourceLinkUIDRef IN UIDRef of the source link.
		@param targetObjectUIDRef IN UIDRef of the target link object.
	*/
	virtual void Set(const UIDRef sourceLinkUIDRef, const UIDRef targetObjectUIDRef) = 0;

	/** Set the output data.
		@param newLinkUID IN UID of the newly copied link.
	*/
	virtual void SetLink(const UID newLinkUID) = 0;

	/** Get the data base for the source link.
		@return the data base.
	*/
	virtual IDataBase *GetSourceDataBase() const = 0;

	/** Get the data base for the target link object.
		@return the data base.
	*/
	virtual IDataBase *GetTargetDataBase() const = 0;

	/** Get the source link
		@return the source link.
	*/
	virtual UID GetSourceLink() const = 0;

	/** Get the target link object.
		@return the target link object.
	*/
	virtual UID GetTargetLinkObject() const = 0;

	/** Get the newly created link.
		@return the newly created link.
	*/
	virtual UID GetLink() const = 0;
};

#endif

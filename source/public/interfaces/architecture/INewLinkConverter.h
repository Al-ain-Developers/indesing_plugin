//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/INewLinkConverter.h $
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
//  
//  Description:
//  This class defines an interface used to convert IDatalinks to the new link
//  architecture.
//  
//========================================================================================

#pragma once
#ifndef __INewLinkConverter__
#define __INewLinkConverter__

// ----- Includes -----
#include "IPMUnknown.h"
#include "LinksID.h"

/**
 INewLinkConverter is used to convert old IDataLink, IDataLinkReference,
 IDataLinkListReference and ILinkObjectReference objects to ILink, ILinkResource and
 ILinkObject objects. 

 @see ILink
 @see ILinkObject
 @see ILinkResource
 */
class INewLinkConverter : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_INEWLINKCONVERTER };
	
	/**
	 Called convert a link.
	 @param oldLinkRef [IN] UIDRef of an ILinkObjectReference object.
	 @return kSuccess if the conversion succeded, else an error code.
	 */ 
	virtual ErrorCode DoConvert (const UIDRef& oldLinkRef) = 0;

protected:
	/**
	 Called create an ILinkObject. Default is to assume direct reference
	 to the link object from data link.
	 @param oldLinkRef [IN] UIDRef of an ILinkObjectReference object.
	 @return UID of the resulting link object.
	 */ 
	virtual UID CreateNewLinkObject (const UIDRef& oldLinkRef) = 0;

	/**
	 Called perform custom conversion as needed. Default is to do nothing.
	 @param oldLinkRef [IN] UIDRef of an ILinkObjectReference object.
	 @return kSuccess if the custom conversion succeded, else an error code.
	 */ 
	virtual ErrorCode DoCustomConversion (const UIDRef& oldLinkRef) = 0;
};

#endif // __INewLinkConverter__

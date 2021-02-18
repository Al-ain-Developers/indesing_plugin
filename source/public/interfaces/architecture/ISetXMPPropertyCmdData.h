//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISetXMPPropertyCmdData.h $
//  
//  Owner: Lin Xia
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
#ifndef __ISetXMPPropertyCmdData_h__
#define __ISetXMPPropertyCmdData_h__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- Includes -----

#include "MetaDataTypes.h"

// ----- ID.h files -----

#include "MetaDataID.h"


//========================================================================================
// INTERFACE ISetXMPPropertyCmdData
//========================================================================================

/** 
	Data interface for the command (kSetXMPPropertyCmdBoss) to set XMP property values.
*/

class ISetXMPPropertyCmdData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ISETXMPPROPERTYCMDDATA };

	/** Set the XMP namespace, path, and value triplet in the given target object.
		@param targetObject IN pointer to the XMP object (must have a IID_IMETADATAACCESS interface)
		@param ns IN string containing the name space of the XMP value
		@param path IN string containing the path of the XMP value
		@param value IN string containing the value of the XMP value
	*/
	virtual void 				Set(IPMUnknown* targetObject,
									const PMString& ns,
									const PMString& path,
									const PMString& value) = 0;
	
	/** Get XMP namespace, path, and value triplet.
		@param ns OUT string containing the name space of the XMP value
		@param path OUT string containing the path of the XMP value
		@param value OUT string containing the value of the XMP value
	*/
	virtual void				Get(PMString& ns, PMString& path, PMString& value) const = 0;

	/** Query XMP target object.
		@return the pointer to the XMP object this command is being executed against.
	*/
	virtual IPMUnknown*			QueryTargetObject(const PMIID& iid) const = 0;
};

#endif // __ISetXMPPropertyCmdData_h__

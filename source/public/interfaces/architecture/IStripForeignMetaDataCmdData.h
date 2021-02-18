//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IStripForeignMetaDataCmdData.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IStripForeignMetaDataCmdData_h__
#define __IStripForeignMetaDataCmdData_h__

#include "IPMUnknown.h"
#include "MetaDataID.h"

//========================================================================================
// INTERFACE IStripForeignMetaDataCmdData
//========================================================================================

/**
    A data interface used by StripForeignMetaDataCmd.
*/

class IStripForeignMetaDataCmdData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ISTRIPFOREIGNMETADATACMDDATA };

	/** Set the command data.
		@param	targetObject	IN	The target object of the command. It must have a IID_IMETADATA interface.
		@see IID_IMETADATA
	*/
	virtual void 				Set(IPMUnknown* targetObject) = 0;

    /** Query an interface on the target object.
        @param		iid    IN    The ID of the interface to query.
		@return		IPMUnknown	pointer to the interface iid or nil, if interface iid doesn't exist.
    */
	virtual IPMUnknown*			QueryTargetObject(const PMIID& iid) const = 0;
};

#endif // __IStripForeignMetaDataCmdData_h__

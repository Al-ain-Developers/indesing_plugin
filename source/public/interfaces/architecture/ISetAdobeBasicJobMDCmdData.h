//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISetAdobeBasicJobMDCmdData.h $
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
#ifndef __ISetAdobeBasicJobMDCmdData_h__
#define __ISetAdobeBasicJobMDCmdData_h__

// ----- Interfaces -----

#include "IAdobeBasicJobMetaData.h"
#include "IPMUnknown.h"

// ----- Includes -----

#include "K2Vector.h"
#include "MetaDataTypes.h"

// ----- ID.h files -----

#include "MetaDataID.h"

//========================================================================================
// INTERFACE ISetAdobeBasicJobMDCmdData
//========================================================================================

/**
    A data interface used by SetAdobeBasicJobMDCmd.
*/

class ISetAdobeBasicJobMDCmdData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ISETADOBEBASICJOBMDCMDDATA };


	/** Set the command data.
		@param targetObject		IN	The target object of the command. It must have a IID_IADOBEBASICJOBMETADATA interface.
		@param jobs				IN	A list of jobs.
		@see IID_IADOBEBASICJOBMETADATA
	 */
	virtual void 		Set(IPMUnknown* targetObject,
							const K2Vector<IAdobeBasicJobMetaData::Job>& jobs) = 0;

    /** Query an interface on the target object.
        @param		iid    IN    The ID of the interface to query.
		@return		IPMUnknown	pointer to the interface iid or nil, if interface iid doesn't exist.
    */
	virtual IPMUnknown*								QueryTargetObject(const PMIID& iid) const = 0;

	/** Returns a list of jobs specified by 'xapBJ:JobRef' property.
		@return A list of jobs.
		@see Job
	*/
	virtual K2Vector<IAdobeBasicJobMetaData::Job>	GetJobs() const = 0;
};

#endif // __ISetAdobeBasicJobMDCmdData_h__

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISetAdobeRightsMgmtMDCmdData.h $
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
#ifndef __ISetAdobeRightsMgmtMDCmdData_h__
#define __ISetAdobeRightsMgmtMDCmdData_h__

// ----- Interfaces -----

#include "IAdobeRightsMgmtMetaData.h"
#include "IPMUnknown.h"

// ----- Includes -----

#include "MetaDataTypes.h"
#include "UIDRef.h"
#include "UnspecifiableOf.h"

// ----- ID.h files -----

#include "MetaDataID.h"

//========================================================================================
// INTERFACE ISetAdobeRightsMgmtMDCmdData
//========================================================================================

/**
    A data interface used by SetAdobeRightsMgmtMDCmd.
*/

class ISetAdobeRightsMgmtMDCmdData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ISETADOBERIGHTSMGMTMDCMDDATA };

	/** Set the command data.
		@param	targetObject			IN	The target object of the command. It must have a IID_IADOBERIGHTSMGMTMETADATA interface.
		@param	marked					IN	The rights status.
		@param	copyright				IN	The legal copyright notice.
		@param	webStatementReference	IN	The Location of web page describing the owner and/or rights statement.
		@see IID_IADOBERIGHTSMGMTMETADATA
	*/
	virtual void 				Set(IPMUnknown* targetObject,
									const UnspecifiableOf<IAdobeRightsMgmtMetaData::RightsStatus>& marked = kUnspecified,
									const UnspecifiableOf<PMString>& copyright = kUnspecified,
									const UnspecifiableOf<metadata::URI>& webStatementReference = kUnspecified) = 0;
    /** Query an interface on the target object.
        @param		iid    IN    The ID of the interface to query.
		@return		IPMUnknown	pointer to the interface iid or nil, if interface iid doesn't exist.
    */
	virtual IPMUnknown*												QueryTargetObject(const PMIID& iid) const = 0;

	/** Returns the legal copyright notice specified by 'xapRights:Copyright' property.
		@return	The legal copyright notice.
	*/
	virtual UnspecifiableOf<PMString>								GetCopyright() const = 0;

	/** Returns the status indicating if this is a rights managed resource specified by 'xapRights:Marked' property.
		@see RightsStatus
		@return	The rights status.
	*/
	virtual UnspecifiableOf<IAdobeRightsMgmtMetaData::RightsStatus> GetMarked() const = 0;

	/** Returns the Location of web page describing the owner and/or rights statement for this 
		resource specified by 'xapRights:WebStatement' property.
		@see metadata
		@return	The Location of web page describing the owner and/or rights statement.
	*/
	virtual UnspecifiableOf<metadata::URI>							GetWebStatementReference() const = 0;
};

#endif // __ISetAdobeRightsMgmtMDCmdData_h__

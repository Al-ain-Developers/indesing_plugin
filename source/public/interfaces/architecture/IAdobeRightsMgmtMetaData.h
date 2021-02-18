//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IAdobeRightsMgmtMetaData.h $
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
#ifndef __IAdobeRightsMgmtMetaData_h__
#define __IAdobeRightsMgmtMetaData_h__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- Includes -----

#include "MetaDataTypes.h"

// ----- ID.h files -----

#include "MetaDataID.h"


//========================================================================================
// CLASS IAdobeRightsMgmtMetaData
//========================================================================================
/**
	This interface encapsulates routines of the XMPToolkit for accessing XMP Rights Management properties 
	defined in 'xapRights' namespace.
	@see IAdobeCoreMetaData
	@see IAdobeMediaMgmtMetaData
	@see IAdobeBasicJobMetaData
	@see IMetaDataAccess
*/
class IAdobeRightsMgmtMetaData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IADOBERIGHTSMGMTMETADATA };

	// ----- xapRights:Certificate
	
	// ----- xapRights:Copyright
	/** Sets the legal copyright notice specified by 'xapRights:Copyright' property.
		@param	copyright	IN	The legal copyright notice.
	*/
	virtual void SetCopyright(const PMString& copyright) = 0;

	/** Returns the legal copyright notice specified by 'xapRights:Copyright' property.
		@return	The legal copyright notice.
	*/
	virtual PMString GetCopyright() const = 0;
	
	// ----- xapRights:Marked
	/** Possible values for Rights status.
	*/
	enum RightsStatus {
		/** Managed */
		kRightsManaged = 0, 

		/** Unmanaged */
		kRightsUnmanaged, 

		/** Unknown */
		kRightsUnknown 
	};

	/** Sets the status indicating if this is a rights managed resource specified by 'xapRights:Marked' property.
		@param	marked	IN	The rights status.
		@see RightsStatus
	*/
	virtual void SetMarked(const RightsStatus& marked) = 0;

	/** Returns the status indicating if this is a rights managed resource specified by 'xapRights:Marked' property.
		@see RightsStatus
		@return	The rights status.
	*/
	virtual RightsStatus GetMarked() const = 0;
	
	// ----- xapRights:Owner
	// ----- xapRights:UsageTerms
	
	// ----- xapRights:WebStatement
	/** Sets the Location of web page describing the owner and/or rights statement for this 
		resource specified by 'xapRights:WebStatement' property.
		@see metadata
		@param	webStatementReference	IN	The Location of web page describing the owner and/or rights statement.
	*/
	virtual void SetWebStatementReference(const metadata::URI& webStatementReference) = 0;

	/** Returns the Location of web page describing the owner and/or rights statement for this 
		resource specified by 'xapRights:WebStatement' property.
		@see metadata
		@return	The Location of web page describing the owner and/or rights statement.
	*/
	virtual metadata::URI GetWebStatementReference() const = 0;
};


#endif // __IAdobeRightsMgmtMetaData_h__

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISetAdobeMediaMgmtMDCmdData.h $
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
#ifndef __ISetAdobeMediaMgmtMDCmdData_h__
#define __ISetAdobeMediaMgmtMDCmdData_h__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- Includes -----

#include "K2Vector.h"
#include "MetaDataTypes.h"
#include "UnspecifiableOf.h"

// ----- ID.h files -----

#include "MetaDataID.h"

//========================================================================================
// INTERFACE ISetAdobeMediaMgmtMDCmdData
//========================================================================================

/**
    A data interface used by SetAdobeMediaMgmtMDCmd.
*/

class ISetAdobeMediaMgmtMDCmdData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ISETADOBEMEDIAMGMTMDCMDDATA };

	/** Set the command data.
		@param	targetObject	IN	The target object of the command. It must have a IID_IADOBEMEDIAMGMTMETADATA interface.
		@param	documentID		IN	The common identifier for all versions and renditions of a document.
		@param	origDocumentID	IN	The common identifier for the original document.
		@param	versionID		IN	The version id.
		@param	renditionClass	IN	The rendition class name for this resource.
		@param	renditionParams	IN	The additional rendition parameters.
		@param	derivedFrom		IN	The resource reference from which this one is derived.
		@param	manageTo		IN	A URI identifying the managed resource to the asset management system.
		@param	manager			IN	The name of the asset management system that manages this resource.
		@param	manageUI		IN	A URI that can be used to access information about the managed resource through a webbrowser.
		@param	managerVariant	IN	A particular variant of the asset management system.
		@param	managedFrom		IN	A reference to the document as obtained from a separate asset management system.
		@see IID_IADOBEMEDIAMGMTMETADATA
	*/
	virtual void 				Set(IPMUnknown* targetObject,
									const UnspecifiableOf<metadata::URI>& documentID = kUnspecified,
									const UnspecifiableOf<metadata::URI>& origDocumentID = kUnspecified,
									const UnspecifiableOf<PMString>& versionID = kUnspecified,
									const UnspecifiableOf<PMString>& renditionClass = kUnspecified,
									const UnspecifiableOf<PMString>& renditionParams = kUnspecified,
									const UnspecifiableOf<metadata::ResourceRef>& derivedFrom = kUnspecified,
									const UnspecifiableOf<metadata::URI>& manageTo = kUnspecified,
									const UnspecifiableOf<PMString>& manager = kUnspecified,
									const UnspecifiableOf<metadata::URI>& manageUI = kUnspecified,
									const UnspecifiableOf<PMString>& managerVariant = kUnspecified,
									const UnspecifiableOf<metadata::ResourceRef>& managedFrom = kUnspecified) = 0;

    /** Query an interface on the target object.
        @param		iid    IN    The ID of the interface to query.
		@return		IPMUnknown	pointer to the interface iid or nil, if interface iid doesn't exist.
    */
	virtual IPMUnknown*									QueryTargetObject(const PMIID& iid) const = 0;

	/** Returns the reference to the original document from which this one is derived, 
		defined by 'xapMM:DerivedFrom' property.
		@return		The resource reference from which this one is derived.
	*/
	virtual UnspecifiableOf<metadata::ResourceRef>		GetDerivedFrom() const = 0;

	/** Returns the common identifier for all versions and renditions of a document, 
		defined by 'xapMM:DocumentID' property.
		@return		The common identifier for all versions and renditions of a document.
	*/
	virtual UnspecifiableOf<metadata::URI> 				GetDocumentID() const = 0;
	
	/** Returns the common identifier for the origianl document from which all deriviatives, conversions, versions, and renditions came from, 
	 defined by 'xapMM:OriginalDocumentID' property.
	 @return		The common identifier for the original document (should stay the same for all derivatives, conversions, versions, and renditions of the document).
	 */
	virtual UnspecifiableOf<metadata::URI> 				GetOrigDocumentID() const = 0;

	/** Returns the reference to the document as obtained from a separate asset management system, 
		defined by 'xapMM:ManagedFrom' property.
		@return		The reference to the document as obtained from a separate asset management system, defined by 'xapMM:ManagedFrom'.
	*/
	virtual UnspecifiableOf<metadata::ResourceRef>		GetManagedFrom() const = 0;

	/** Returns the name of the asset management system that manages this resource,	
		defined by 'xapMM:Manager' property.
		@return		The name of the asset management system that manages this resource.
	*/
	virtual UnspecifiableOf<PMString>					GetManager() const = 0;

	/** Returns the URI identifying the managed resource to the asset management system, 
		defined by 'xapMM:ManageTo' property.
		@return		A URI identifying the managed resource to the asset management system.
	*/
	virtual UnspecifiableOf<metadata::URI>				GetManageTo() const = 0;

	/** Returns the URI that can be used to access information about the managed resource through a webbrowser, 
		defined by 'xapMM:ManageUI' property.
		@return		The URI that can be used to access information about the managed resource through a webbrowser.
	*/
	virtual UnspecifiableOf<metadata::URI>				GetManageUI() const = 0;

	/** Returns a particular variant of the asset management system, defined by 'xapMM:ManagerVariant' property.
		@return		A particular variant of the asset management system.
	*/
	virtual UnspecifiableOf<PMString>					GetManagerVariant() const = 0;

	/** Returns the rendition class name for this resource, defined by 'xapMM:RenditionClass' property.
		@return		The rendition class name for this resource.
	*/
	virtual UnspecifiableOf<PMString>					GetRenditionClass() const = 0;

	/** Returns the additional rendition parameters that are too complex or verbose to encode in 
		RenditionClass, defined by 'xapMM:RenditionParams'.
		@return		The additional rendition parameters.
	*/
	virtual UnspecifiableOf<PMString>					GetRenditionParams() const = 0;

	/** Returns the version id defined by 'xapMM:VersionID' property.
		@return		The version id.
	*/
	virtual UnspecifiableOf<PMString>					GetVersionID() const = 0;
};

#endif // __ISetAdobeMediaMgmtMDCmdData_h__

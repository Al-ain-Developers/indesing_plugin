//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IAdobeMediaMgmtMetaData.h $
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
#ifndef __IAdobeMediaMgmtMetaData_h__
#define __IAdobeMediaMgmtMetaData_h__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- Includes -----

#include "MetaDataTypes.h"

// ----- ID.h files -----

#include "MetaDataID.h"


//========================================================================================
// CLASS IAdobeMediaMgmtMetaData
//========================================================================================
/**
	This interface encapsulates routines of the XMPToolkit for accessing XMP Media Management Schema
	Properties defined in 'xapMM' namespace.
	@see IAdobeBasicJobMetaData
	@see IAdobeCoreMetaData
	@see IAdobeRightsMgmtMetaData
	@see IMetaDataAccess
*/
class IAdobeMediaMgmtMetaData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IADOBEMEDIAMGMTMETADATA };

	// ----- xapMM:Manifest
	/** Adds an resource references to a bag of references to linked documents that are part of 
		this compound document,	defined by 'xapMM:Manifest' property.
		@param	linkForm	IN	Link form.
		@param	resource	IN	The resource references to added.
		@param	xRes		IN	x resolution of the added item.
		@param	yRes		IN	y resoulution of the added item.
	*/
	virtual void					AddManifestItem(metadata::LinkForm linkForm, const metadata::ResourceRef& resource, Fixed xRes, Fixed yRes) = 0;
	
	/** Remove the nth resource references from the bag of references to linked documents, 
		defined by 'xapMM:Manifest' property.
		@param	nth		IN	The index of the item to be removed, starts from 1.
	*/
	virtual void					RemoveManifestItem(const int32& nth) = 0;
	
	/**	Returns the nth item in the the bag of references to linked documents, 
		defined by 'xapMM:Manifest' property.
		@param	nth			IN	The index of the item to be removed, starts from 1.
		@param	linkForm	IN	Link form.
		@param	resource	OUT	The resource reference at nth location.
		@return kTrue if nth item exist, kFalse otherewise.
	*/
	virtual bool16					GetNthManifestItem(const int32& nth, metadata::LinkForm linkForm, metadata::ResourceRef& resource) const = 0;

	/** Returns the number of resource references in the bag of references to linked documents, 
		defined by 'xapMM:Manifest' property.
		@return		The number of resource references in bag of the references to linked documents.
	*/
	virtual int32					GetManifestItemCount() const = 0;

	/** Clears all the resource references from the bag of references to linked documents, 
		defined by 'xapMM:Manifest' property.
	*/
	virtual void					ClearManifest() = 0;
	
	// ----- xapMM:DerivedFrom
	/** Sets the reference to the original document from which this one is derived, 
		defined by 'xapMM:DerivedFrom' property.
		@param	resource	IN	The resource reference from which this one is derived.
	*/
	virtual void					SetDerivedFrom(const metadata::ResourceRef& resource) = 0;

	/** Returns the reference to the original document from which this one is derived, 
		defined by 'xapMM:DerivedFrom' property.
		@return		The resource reference from which this one is derived.
	*/
	virtual metadata::ResourceRef	GetDerivedFrom() const = 0;

	// ----- xapMM:DocumentID
	/** Sets the common identifier for all versions and renditions of a document, 
		defined by 'xapMM:DocumentID' property.
		@param	documentID	IN	The common identifier for all versions and renditions of a document.
	*/
	virtual void					SetDocumentID(const metadata::URI& documentID) = 0;

	/** Returns the common identifier for all versions and renditions of a document, 
		defined by 'xapMM:DocumentID' property.
		@return		The common identifier for all versions and renditions of a document.
	*/
	virtual metadata::URI			GetDocumentID() const = 0;
	
	// ----- xmpMM:OriginalDocumentID
	/** Sets the  common identifier for the original document (should stay the same for all derivatives, conversions, versions, and renditions of the document), 
	 defined by 'xapMM:OriginalDocumentID' property.
	 @param	origDocumentID	IN	The common identifier for the original document.
	 */
	virtual void					SetOrigDocumentID(const metadata::URI& origDocumentID) = 0;
	
	/** Returns the common identifier for the origianl document from which all deriviatives, conversions, versions, and renditions came from, 
	 defined by 'xapMM:OriginalDocumentID' property.
	 @return		The common identifier for the original document (should stay the same for all derivatives, conversions, versions, and renditions of the document).
	 */
	virtual metadata::URI			GetOrigDocumentID() const = 0;
	
	// ----- xapMM:History

	// ----- xapMM:ManagedFrom
	/** Sets a reference to the document as obtained from a separate asset management system, 
		defined by 'xapMM:ManagedFrom' property.
		@param	resource	IN	A reference to the document as obtained from a separate asset management system.
	*/
	virtual void					SetManagedFrom(const metadata::ResourceRef& resource) = 0;

	/** Returns the reference to the document as obtained from a separate asset management system, 
		defined by 'xapMM:ManagedFrom' property.
		@return		The reference to the document as obtained from a separate asset management system, defined by 'xapMM:ManagedFrom'.
	*/
	virtual metadata::ResourceRef	GetManagedFrom() const = 0;

	// ----- xapMM:Manager
	/** Sets the name of the asset management system that manages this resource, defined 
		by 'xapMM:Manager' property.
		@param	manager		IN	The name of the asset management system that manages this resource.
	*/
	virtual void					SetManager(const PMString& manager) = 0;
	
	/** Returns the name of the asset management system that manages this resource,	
		defined by 'xapMM:Manager' property.
		@return		The name of the asset management system that manages this resource.
	*/
	virtual PMString				GetManager() const = 0;

	// ----- xapMM:ManageTo  
	/** Sets a URI identifying the managed resource to the asset management system, defined by 
		'xapMM:ManageTo' property.
		@param	serverURL	IN	A URI identifying the managed resource to the asset management system.
	*/
	virtual void					SetManageTo(const metadata::URI& serverURL) = 0;
	
	/** Returns the URI identifying the managed resource to the asset management system, 
		defined by 'xapMM:ManageTo' property.
		@return		A URI identifying the managed resource to the asset management system.
	*/
	virtual metadata::URI			GetManageTo() const = 0;

	// ----- xapMM:ManageUI  
	/** Sets a URI that can be used to access information about the managed resource through a webbrowser, 
		defined by 'xapMM:ManageUI' property.
		@param	manageUI	IN	A URI that can be used to access information about the managed resource through a webbrowser.
	*/
	virtual void					SetManageUI(const metadata::URI& manageUI) = 0;
	
	/** Returns the URI that can be used to access information about the managed resource through a webbrowser, 
		defined by 'xapMM:ManageUI' property.
		@return		The URI that can be used to access information about the managed resource through a webbrowser.
	*/
	virtual metadata::URI			GetManageUI() const = 0;

	// ----- xapMM:ManagerVariant  
	/** Sets a particular variant of the asset management system, defined by 'xapMM:ManagerVariant' property.
		@param	managerVariant	IN	A particular variant of the asset management system.
	*/
	virtual void					SetManagerVariant(const PMString& managerVariant) = 0;
	
	/** Returns a particular variant of the asset management system, defined by 'xapMM:ManagerVariant' property.
		@return		A particular variant of the asset management system.
	*/
	virtual PMString				GetManagerVariant() const = 0;

	// ----- xapMM:PacketOffset

	// ----- xapMM:RenditionClass
	/** Sets the rendition class name for this resource, defined by 'xapMM:RenditionClass' property. This property should be 
		absent or set to "default" for a document version that is not a derived rendition.
		@param	renditionClass	IN	The rendition class name for this resource.
	*/
	virtual void					SetRenditionClass(const PMString& renditionClass) = 0;
	
	/** Returns the rendition class name for this resource, defined by 'xapMM:RenditionClass' property.
		@return		The rendition class name for this resource.
	*/
	virtual PMString				GetRenditionClass() const = 0;

	// ----- xapMM:RenditionParams	
	/** Sets the additional rendition parameters that are too complex or verbose to encode in 
		RenditionClass, defined by 'xapMM:RenditionParams' property.
		@param	renditionParams		IN	The additional rendition parameters.
	*/
	virtual void					SetRenditionParams(const PMString& renditionParams) = 0;
	
	/** Returns the additional rendition parameters that are too complex or verbose to encode in 
		RenditionClass, defined by 'xapMM:RenditionParams'.
		@return		The additional rendition parameters.
	*/
	virtual PMString				GetRenditionParams() const = 0;

	// ----- xapMM:VersionID
	/** Sets the version id defined by 'xapMM:VersionID' property. This property should be 
		used primarily by a media management system.
		@param	documentID	IN		The version id.
	*/
	virtual void					SetVersionID(const PMString& documentID) = 0;
	
	/** Returns the version id defined by 'xapMM:VersionID' property.
		@return		The version id.
	*/
	virtual PMString				GetVersionID() const = 0;

	// ----- xapMM:Versions
};

#endif // __IAdobeMediaMgmtMetaData_h__

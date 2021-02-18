//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/layout/IHyperlinkLinkUtils.h $
//  
//  Owner: Brendan O'Shea
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

#include "Utils.h"
#include "HyperlinkID.h"

class URI;
class IHyperlink;
class ILinkResource;

/** Helps with links in the Hyperlinks plug-in; cross document hyperlinks 
	have an associated link resource (ILinkResource) which refers to the 
	linked document.

	The link resources are owned by the link manager. Hyperlink bosses
	refer to any associated link resource by UID. This UID is stored in 
	an IPersistUIDData interface on a hyperlink boss using the PMIID 
	IID_ILINKRESOURCEPERSISTUIDDATA.

	IHyperlinkUtils only works with bosses that have an IPersistUIDData 
	interface aggregated using the PMIID IID_ILINKRESOURCEPERSISTUIDDATA.
	The hyperlinkUIDRef parameter taken by the the methods in 
	IHyperlinkLinkUtils must refer to such a boss.

	@see ILinkResource
*/
class IHyperlinkLinkUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHYPERLINKLINKUTILS };

	/**	Returns kTrue if the given hyperlink has a link, kFalse otherwise.
		@param linkObjUIDRef [IN] refers to the link object.
		@return kTrue if the given hyperlink has a link, kFalse otherwise.
	*/
	virtual  bool16 HasLink(const UIDRef& linkObjUIDRef) const = 0;

	/**	Returns kTrue if the given hyperlink needs a link to the file, kFalse otherwise.
		A link is only required if the file being linked has a different path from the path
		to the database that contains the hyperlink (if that database has not yet been
		saved this function returns kTrue).
		@param linkObjUIDRef [IN] refers to the link object.
		@param file [IN] gives the file to be linked.
		@return kTrue if the given hyperlink needs a link to the file, kFalse otherwise.
	*/
	virtual  bool16 CanLinkResource(const UIDRef& linkObjUIDRef, const IDFile& file) const = 0;

	/** Returns reference to the link resource (ILinkResource) associated with the given hyperlink.
		@param linkObjUIDRef [IN] refers to the link object.
		@return reference to the associated link resource (ILinkResource)
	*/
	virtual UIDRef	GetLinkResource(const UIDRef& linkObjUIDRef) const = 0;

	/**	Returns kTrue if a file can be obtained for the hyperlink, kFalse otherwise.
		@param linkObjUIDRef [IN] refers to the link object.
		@param file [OUT] the file the hyperlink refers to.
		@return kTrue if a file can be obtained, kFalse otherwise.
	*/
	virtual  bool16 GetIDFile(const UIDRef& linkObjUIDRef, IDFile& file) const = 0;

	/**	Returns the short name of the hyperlink's associated link resource.
		@param linkObjUIDRef [IN] refers to the link object.
		@return the short name of the hyperlink's associated link resource.
		@see ILinkResource::GetShortName
	*/
	virtual WideString GetShortName(const UIDRef& linkObjUIDRef) const = 0;

	/**	Returns the long name of the hyperlink's associated link resource.
		@param linkObjUIDRef [IN] refers to the link object.
		@return the long name of the hyperlink's associated link resource.
		@see ILinkResource::GetLongName
	*/
	virtual WideString GetLongName(const UIDRef& linkObjUIDRef) const = 0;

	/**	Returns kTrue if the both hyperlinks refer to the same external resource, kFalse otherwise.
		@param linkObj1UIDRef [IN] refers to a link object.
		@param linkObj2UIDRef [IN] refers to another link object.
		@return kTrue if the both link objects refer to the same external resource, kFalse otherwise.
		@see ILinkResource::IsIdEquivalent
	*/
	virtual  bool16 IsLinkResourceIdEquivalent(const UIDRef& linkObj1UIDRef, const UIDRef& linkObj2UIDRef) const = 0;

	/** Creates a link links to the link resource associated with the given file. A new link resource will
		be created if one does not exist. 
		
		@param linkObjUIDRef [IN] refers to a hyperlink object or external page destination object.
		@param file [IN] the file to be linked.
		@return kSuccess on success, another ErrorCode otherwise.
	*/
	virtual ErrorCode CreateLink(const UIDRef& linkObjUIDRef, const IDFile& file) const = 0;

	/** Changes a hyperlink's link appropriately depending on whether
		or not it already has a link.

		When the given hyperlink already has a link. If the given file is the same as the file
		currently linked to, no change is made. Otherwise the existing link on the hyperlink 
		will be deleted and a new link will be created on the hyperlink if the given file can be 
		linked (e.g. if you pass a file parameter that does not have a path then the associated 
		link will be deleted).

		When the given hyperlink does not have a link. If the given file can 
		be linked to a new link is created for the hyperlink. Otherwise no action
		is taken and kSuccess is returned.

		@param linkObjUIDRef [IN] refers to a hyperlink object or external page destination object.
		@param file [IN] the file to be linked.
		@return kSuccess on success, another ErrorCode otherwise.
		@see IHyperlinkLinkUtils::CanLinkResource
		@see IHyperlinkLinkUtils::DeleteLinks
		@see IHyperlinkLinkUtils::CreateLink
	*/
	virtual ErrorCode ChangeLink(const UIDRef& linkObjUIDRef, const IDFile& file) const = 0;

	/** Deletes the link associated with the given hyperlinks.
		@param linkObjUIDs [IN] lists the hyperlinks or external page destinations whose links are to be deleted.
		@return kSuccess on success, another ErrorCode otherwise.
	*/
	virtual ErrorCode DeleteLinks(const UIDList& linkObjUIDs) const = 0;

	/** Returns the link resource associated with the hyperlink or its external
		page destination (if it has one). The hyperlink is examined first. If
		it has no link resource and the bExamineDestination flag is set
		the hyperlink's external page destination is examined and its link
		resource is returned.
		@param hyperlink
		@param bExamineDestination kTrue to check any associated external page destination for a link resource, kFalse otherwise.
		@returns link resource interface pointer if found, nil otherwise.
	*/
	virtual ILinkResource* QueryLinkResource(IHyperlink* hyperlink, bool16 bExamineDestination) const = 0;
};


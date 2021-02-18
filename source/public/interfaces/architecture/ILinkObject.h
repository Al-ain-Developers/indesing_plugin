//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILinkObject.h $
//  
//  Owner: Michael Easter
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
//  
//========================================================================================

#pragma once
#ifndef __ILinkObject__
#define __ILinkObject__

// ----- Includes -----
#include "IPMUnknown.h"
#include "LinksID.h"

class ILinkResource;

/**
 Proxy used to represent the item in an InDesign database being linked to.
 For example, a page item, an XML element, a style, or a range of text.
 @see ILink
 */
class ILinkObject : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKOBJECT };

	/**
	 Returns the object's link client identifier.
	 @return Object's link client identifier.
	 */ 
	virtual LinkClientID GetClientID() const = 0;

	/**
	 Determines whether this object is on the same boss as the object that
	 owns the link (a direct link), or is on a different boss than the object
	 that owns the link (an indirect link). \\
	 A UID based object like a page item is an example of a direct link.
	 A non-UID based object like an XML element is an example of an indirect link.
	 @return True if the link is a direct link, else false if an indirect link.
	 */
	virtual bool IsDirectLink() const = 0;

	/**
	 Returns the object with the given interface identifier that is on the same
	 boss as the object that owns the link. \\
	 If a direct link, the returned object will be on the same boss as this object.
	 If an indirect link, the returned object will be on a different boss.
	 @param interfaceId [IN] Interface identifier of the object to retrieve.
	 @return Object with the given interface identifier. \\
			 Nil if the no object can be instantiated.
	 */
	virtual IPMUnknown* QueryLinkedObject(const PMIID& interfaceId) const = 0;

	/**
	 Determines whether the goto linked object operation link is supported.
	 @return True if the operation is supported, else false.
	 */
	virtual bool CanGotoLinkedObject() const = 0;

	/**
	 Displays the object that is linked.
	 @param errorString	[OUT] If the goto fails, this fills out an error
							  message when the string pointer is non-nil
	 @return kSuccess if the goto operation succeeds, else an error code.
	 */
	virtual ErrorCode GotoLinkedObject(PMString* errorString) const = 0;

	/**
	 Determines if an update should be allowed to proceed.
	 @param iResource [IN]  Associated link resource.
	 @param linkUID	  [IN]  UID of the associated link.
	 @param uiFlags	  [IN]  Denotes whether to allow UI.
	 @param err		  [OUT] Error code.
	 @return True to proceed with the update, else false.
	 */
	virtual bool CanUpdate(const ILinkResource* iResource, UID linkUID, UIFlags uiFlags, ErrorCode& err) const = 0;

	/**
	 Returns the class id of the update link service provider used to import
	 the contents of an resource into the object.
	 @param iResource [IN] Link resource to import from.
	 @param linkUID	  [IN] UID of the associated link.
	 @return Id of the update link service provider to use to import.
			 kInvalidClass if no provider is available and the object
			 should do the import.
	 */
	virtual ClassID GetImportProvider(const ILinkResource* iResource, UID linkUID) const = 0;

	/**
	 Called by the associated link to initiate an import
	 of the contents of an resource into the object. \\
	 NOTE: Import() should not be called directly, instead
	       call Update() on the associated link.
	 @param iResource [IN] Link resource to import from.
	 @param linkUID	  [IN/OUT] UID of the associated link. \\
							   If a new link is created as a result of the import,
							   then the returned UID will be the UID of the new link.
	 @param uiFlags	  [IN] Denotes whether to allow UI during the import operation.
	 @return kSuccess if the import succeeds, else an error code.
	 */
	virtual ErrorCode Import(const ILinkResource* iResource, UID& linkUID, UIFlags uiFlags) = 0;

	/**
	 Returns the class id of the update link service provider used to export
	 the contents of the object out to an resource.
	 @param iResource [IN] Link resource to export to.
	 @param linkUID	  [IN] UID of the associated link.
	 @return Id of the update link service provider to use to export.
			 kInvalidClass if no provider is available and the object
			 should do the export.
	 */
	virtual ClassID GetExportProvider(const ILinkResource* iResource, UID linkUID) const = 0;

	/**
	 Called by the associated link to initiate an export
	 of the contents of the object out to an resource. \\
	 NOTE: Export() should not be called directly, instead
	       call Update() on the associated link.
	 @param iResource [IN] Link resource to export to.
	 @param linkUID	  [IN/OUT] UID of the associated link. \\
							   If a new link is created as a result of the export,
							   then the returned UID will be the UID of the new link.
	 @param uiFlags	  [IN] Denotes whether to allow UI during the export operation.
	 @return kSuccess if the export succeeds, else an error code.
	 */
	virtual ErrorCode Export(const ILinkResource* iResource, UID& linkUID, UIFlags uiFlags) const = 0;

	/**
	 Returns the class id of the update link service provider used to export
	 and/or an import when both the object and the link resource have changed
	 and the link needs to perform an update
	 @param iResource [IN] Link resource that has also changed.
	 @param linkUID	  [IN] UID of the associated link.
	 @return Id of the update link service provider to use to resolve.
			 kInvalidClass if no provider is available and the object
			 should do the resolve.
	 */
	virtual ClassID GetResolveProvider(const ILinkResource* iResource, UID linkUID) const = 0;

	/**
	 Called by the associated link to initiate an export and/or
	 an import when both the object and the link resource have changed
	 and the link needs to perform an update. \\
	 NOTE: Resolve() should not be called directly, instead call
		   Update() on the associated link.
	 @param iResource [IN] Link resource that has also changed.
	 @param linkUID	  [IN/OUT] UID of the associated link. \\
							   If a new link is created as a result of the resolve,
							   then the returned UID will be the UID of the new link.
	 @param uiFlags	  [IN] Denotes whether to allow UI during the resolve operation.
	 @return kSuccess if the resolve succeeds, else an error code.
	 */
	virtual ErrorCode Resolve(const ILinkResource* iResource, UID& linkUID, UIFlags uiFlags) = 0;

	/**
	 Gets the list of links that reference the object.
	 @return List of links that reference the object.
	 */ 
	virtual UIDList GetLinks() const = 0;

	/**
	 Called to notify all associated links that the object
	 has been modified.
	 */
	virtual void MarkLinksModified() const = 0;

	/**
	 Called to notify all associated links that the object
	 in no longer modified.
	 */
	virtual void ClearLinksModified() const = 0;

private:
	friend class LinkManager;
	friend class ScrapLinkManager;

	virtual void AddLinkRef(UID linkUID) = 0;
	virtual void RemoveLinkRef(UID linkUID) = 0;
};

#endif // __ILinkObject__

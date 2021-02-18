//======================================================================================== 
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/sharedcontent/ISharedContentFacade.h $ 
//   
//  Owner: Ashish Duggal
//   
//  $Author: pmbuilder $ 
//   
//  $DateTime: 2020/11/06 13:08:29 $ 
//   
//  $Revision: #2 $ 
//   
//  $Change: 1088580 $ 
//
//  ADOBE CONFIDENTIAL
//   
//  Copyright 2010 Adobe Systems Incorporated
//  All Rights Reserved.
//   
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received 
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//	Description: 
//  A high level API for dealing with shared content links, link resources and link objects.
//   
//======================================================================================== 

#pragma once 
#ifndef __ISharedContentFacade__ 
#define __ISharedContentFacade__ 

// ----- Includes ----- 
#include "IPMUnknown.h" 

#include "SharedContentID.h"
#include "Utils.h" 
#include "URI.h"

// -----Forward Declarations------
class ILink;
class ILinkResource;
class ITextModel;


/** 
Interface used to manage shared content linked resources and links.
When possible, interaction with a shared content linked resource or
link should be performed via the methods in this interface. 
@see ILink 
@see ILinkResource 
@see ILinkObject 
@see UID 
@see UIDRef 
@see URI 
*/ 
namespace Facade 
{ 

	class ISharedContentFacade : public IPMUnknown 
	{ 
		public: 
			enum { kDefaultIID = IID_ISHAREDCONTENTFACADE }; 

			/**
				Link Options available for page item Links
			*/
			enum LinkPageItemOption{ kPIUpdateOnSave,
				kPIWarnOnUpdateOfEditedPageItem,
				kPIStyleMappingExceptions,
				kPIPathgeometryOverride,
				kPIGraphicAttributesOverride,
				kPIInteractiveAttributesOverride,
				kPIContentOverride, 
				kPIOtherAttributesOverride};	

			/**
				Link Options available for Story Links
			*/
			enum LinkStoryOption{ kUpdateOnSave,
				kWarnOnUpdateOfEditedStory,
				kRemoveForcedLineBreaks,
				kMapStyles, };

			/**
				 Creates a Shared Content link between two existing (already placed) objects. 
				 @param sourceRef [IN] the source object for the content being shared.
				 @param targetRef [IN] the target object for the shared content.
				 @param outLinkUID [OUT] the link UID of the ILink object in target database.
				 @return kSuccess if link gets created. 
			*/

			virtual ErrorCode CreateSharedContentLink (const UIDRef& sourceRef, const UIDRef& targetRef, UID& outLinkUID) const = 0;

			/**
				 Return kTrue is a shared content link can be created between two existing (already placed) objects. 
				 @param sourceRef [IN] the source object for the content being shared.
				 @param targetRef [IN] the target object for the shared content.
				 @return kTrue if a shared content link can be created betrween these two objects, kFalse otherwise. 
			*/
			virtual bool16 CanCreateSharedContentLink (const UIDRef& sourceRef, const UIDRef& targetRef) const = 0;

			/** 
				 Returns the ILink UIDRef of Shared Content link object passed. 
				 @param linkObj [IN] UIDRef of the link object.
				 @return UIDRef of the ILink, if found. Invalid UIDRef otherwise 
			 */ 
			virtual UIDRef GetLinkForSharedContentLinkObject(const UIDRef& linkObj) const = 0;
			
			/** 
				 Returns the UIDRef of Resource Object for the link given its URI and Link Resource. 
				 @param linkResourceRef [IN] UIDRef of the link resource.
				 @param linkedContentURI [IN] URI of the link.
				 @return UIDRef of the Resource Object
			 */ 
			virtual UIDRef GetResourceObjectForSharedContentLink(const UIDRef& linkResourceRef,const URI& linkedContentURI) const = 0;
						
			/** 
				 Checks if the link is a shared content link. 
				 @param link [IN] the link to be checked.
				 @return kTrue if it is a Shared Content link, kFalse otherwise.
			 */ 
			virtual bool16 IsSharedContentLink(const ILink* link) const = 0;

			/** 
				 Checks if the link is a shared content internal link (internal links mean link within same file). 
				 @param link [IN] the link to be checked.
				 @return kTrue if it is a Shared Content internal link, kFalse otherwise.
			 */ 
			virtual bool16 IsSharedContentInternalLink(const ILink* link) const = 0;

			/** 
				 Checks if the link is a shared content external link. (external link mean across document link) 
				 @param link [IN] the link to be checked.
				 @return kTrue if it is a Shared Content external link, kFalse otherwise.
			 */ 
			virtual bool16 IsSharedContentExternalLink(const ILink* link) const = 0;

			/** 
				 Checks if the link is a shared content link resource. 
				 @param linkResource [IN] the link resource to be checked.
				 @return kTrue if it is a Shared Content link resource, kFalse otherwise.
			 */ 
			virtual bool16 IsSharedContentLinkResource(const ILinkResource* linkResource) const = 0;

			/** 
				 Checks if the link is a shared content external link resource. (external link mean across document link) 
				 @param linkResource [IN] the link resource to be checked.
				 @return kTrue if it is a Shared Content external link, kFalse otherwise.
			 */ 
			virtual bool16 IsSharedContentExternalLinkResource(const ILinkResource* linkResource) const = 0;

			/**
				Checks whether this particular text model is a story link object
				@param textModelRef [IN] the text model reference.
			*/
			virtual bool16 IsSharedStoryLinkObject(const UIDRef& textModelRef) const = 0;

			/**
				Checks whether this particular object is a page item link object
				@param pageItemRef [IN] the page item reference.
			*/
			virtual bool16 IsSharedPageItemLinkObject(const UIDRef& pageItemRef) const = 0;

			/** 
				 Checks if the link is a shared Article link. 
				 @param link [IN] the link to be checked.
				 @return kTrue if it is a Shared Article link, kFalse otherwise.
			 */ 
			virtual bool16 IsSharedPageItemLink(const ILink* link) const = 0;

			 /** 
				 Checks if the link is a shared story link. 
				 @param link [IN] the link to be checked.
				 @return kTrue if it is a Shared story link, kFalse otherwise.
			 */ 
			virtual bool16 IsSharedStoryLink(const ILink* link) const = 0;

			/** 
				 Checks if the link resource is a shared Article link. 
				 @param linkResource [IN] the link resource to be checked.
				 @return kTrue if it is a Shared Article link, kFalse otherwise.
			 */ 
			virtual bool16 IsSharedPageItemLinkResource(const ILinkResource* linkResource) const = 0;

			 /** 
				 Checks if the link resource is a shared story link resource. 
				 @param linkResource [IN] the link resource to be checked.
				 @return kTrue if it is a Shared story link, kFalse otherwise.
			 */ 
			virtual bool16 IsSharedStoryLinkResource(const ILinkResource* linkResource) const = 0;
				
			/**
				Returns true if a particular option ( parameter ) is turned on for the link. 
				@param link [IN] the link to be checked.
				@param option [IN] which option to be checked.
			*/
			virtual bool16 IsSharedPageItemOptionSet(ILink* link, LinkPageItemOption option) const = 0;

			/**
				Returns true if a particular option ( parameter ) is turned on for the Story link.
				@param link [IN] the link to be checked.
				@param option [IN] which option to be get status of.
			*/
			virtual bool16 IsSharedStoryOptionSet(ILink* link, LinkStoryOption option) = 0;
			
			/**
				Returns true if a particular option ( parameter ) is turned on for the Story link object. 
				@param textModel [IN] the target object for the shared content.
				@param option [IN] which option to be get status of.
			*/
			virtual bool16 IsSharedStoryOptionSet(const UIDRef& textModel, LinkStoryOption option) = 0;

			/**
				Copies link options from source page item to target page item.
				@param sourceRef [IN] the source object from which options have to be copied.
				@param targetRef [IN] the target object to which options will be copied.
			*/
			virtual ErrorCode CopySharedPageItemOptions(const UIDRef& sourceRef, const UIDRef& targetRef) = 0;

			/**
				Copies link options from source Text model to target text Model 
				@param sourceModel [IN] the source text model from which options have to be copied.
				@param targetModel [IN] the target text model to which options will be copied.
			*/
			virtual ErrorCode CopySharedStoryOptions(const UIDRef& sourceModel, const UIDRef& targetModel) = 0;
			
			/**
				Sets the link option on the story
				 @param textModel [IN] the target object for the shared content.
				 @param option [IN] which option to be set
				 @param newValue [IN] the new value of the option.
				 @return kSuccess if option was successfully set. 

			*/
			virtual ErrorCode SetSharedStoryOption(const UIDRef& textModel, LinkStoryOption option, const bool16 newValue) = 0;

			/**
				Sets the link option on the page item
				 @param pageItem [IN] the target object for the shared content.
				 @param option [IN] which option to be set
				 @param newValue [IN] the new value of the option.
				 @return kSuccess if option was successfully set. 

			*/
			virtual ErrorCode SetSharedPageItemOption(const UIDRef& pageItem, LinkPageItemOption option, const bool16 newValue) = 0;
			
			/** 
				 Internal Use. Used by LinksUI project. Returns the UIDRef of Resource Object for the link 
				 @param linkRef [IN] the UIDRef of the link.
				 @return UIDRef of the Resource Object
			 */ 
			virtual UIDRef GetResourceObjectForSharedStoryLink(const UIDRef& linkRef) const = 0;

			/** 
				Internal Use. Used by LinksUI project. Checks if atleast one Shared Content link exists in the list of Link UIDs passed.. 
				@param linkList [IN] list of Link UIDs to be checked.
				@return kTrue if atleast one Shared Content link is found 
			*/ 
			virtual bool16 ContainsSharedStoryLink(const UIDList& linkList) const = 0;			
	}; 

} // namespace Facade


#endif    // __ISharedContentFacade__ 

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ITextFragmentLinkFacade.h $
//  
//  Owner: Nitin Kumar
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
//  Copyright 2017 Adobe 
//  All Rights Reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in 
//  accordance with the terms of the Adobe license agreement accompanying 
//  it. If you have received this file from a source other than Adobe, 
//  then your use, modification, or distribution of it requires the prior 
//  written permission of Adobe.
//  
//  Description:
//  A high level API for dealing with links, link resources and link objects.
//  
//========================================================================================

#pragma once
#ifndef __ITextFragmentLinkFacade__
#define __ITextFragmentLinkFacade__

// ----- Includes -----
#include "IPMUnknown.h"

#include "Utils.h"
#include "LinksID.h"
#include "XMLReference.h"
#include "ILinkObject.h"

class ILink;
class IPMStream;
class IPMUnknown;
class URI;
class ILinkResource;
class ISpread;
class ITextModel;
class RangeData;
class IHierarchy;

/*
 AdobePatentID="P7225-US"
 AdobePatentID="P7609-US"
 */

/**
 Experimental interface - will be modified/documented in future.
 Interface used to manage linked resources and links.  When possible,
 interaction with a linked resource or link should be performed via the
 methods in this interface rather than directly with ILinkResource or
 ILink.
 @see ILink
 @see ILinkResource
 @see ILinkObject
 @see UID
 @see UIDRef
 @see URI
*/
namespace Facade
{
	class ITextFragmentLinkFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_ITEXTFRAGMENTLINKFACADE };

		/**
		** Create the text fragment link
		*/
		virtual ErrorCode CreateTextFragmentLink(IDataBase* db, const URI& uri, const UID& spreadLayerUID, const WideString* tagName = NULL, const WideString* customCMSData = NULL, const PMRect* viewBounds = NULL, PMString textFragmentCmdSeqName=PMString("")) const = 0;
		
		/**
		**relink the text fragment link
		*/
		virtual ErrorCode RelinkTextFragmentLink(IDataBase* db, ILinkObject* linkObject, const URI& uri, const WideString* tagName = NULL) const = 0;
		
		/**
		**Insert the text specified with metadataContent into range specified by rangeData and set the newRange after insertion.
		*/
		virtual ErrorCode InsertText(const ITextModel* textModel, const RangeData& rangeData, const WideString& metadataContent, RangeData& newRange) const = 0;
		
		/**
		** Delete text and set the newRange after deletion.
		*/
		virtual ErrorCode DeleteText(ITextModel* textModel, const RangeData& rangeData, RangeData& newRange) const = 0;
		
		/**
		** Fetch the content into metadataContent for the metadatakey appended in uri.
		*/
		virtual ErrorCode FetchAssetMetadataContent(const URI& uri, WideString& metadataContent) const = 0;

		/**
		** Creates the LinkResource and also fills the metadataContent and also set the metadataKey.
		*/
		virtual ErrorCode CreateLinkResourceAndFetchMetadataContent(IDataBase* db, const URI& uri, const WideString* tagName, UID& linkResourceUID, WideString& metadataKey, WideString& metadataContent) const = 0;
		
		/**
		**Insert Text and gives the range of inserted text and for inserted text it create a Link.
		*/
		virtual ErrorCode InsertTextAndCreateLink(IDataBase* db, const URI& uri, const ITextModel* textModel, const RangeData& currentRange, XMLReference& newElementReference,
												   UID& linkUID, RangeData& newRange, bool createTag = true, const WideString* tagName = NULL, const WideString* customCMSData = NULL) const = 0;


		/**
		** Create the MetaData Link based on XMLref and results linkUID.
		*/
		virtual ErrorCode CreateMetadataLinkFromXMLReference(const XMLReference& newElementReference, IDataBase* db, const UID& linkResourceUID, UID& linkUID) const = 0;
		
		/**
		**Creates the XML Attributes 
		*/
		virtual ErrorCode CreateXMLAttributes(const XMLReference& xmlRef, const WideString* uriWideString, const WideString* customCMSData, bool isTextFragmentLink = true) const = 0;
		
		/**
		** Delete the tags/XMLRef surrounding/ associated with the LinkObject. 
		*/
		virtual ErrorCode DeleteXMLrefandAssociateLinkobject(const UIDRef& linkObjectUIDRef) const = 0;

		/**
		**Checks whether the Link Object w.r.t linkObjectUIDRef is a text Fragment Link Object.
		*/
		virtual bool16 IsTextFragmentLinkObject(const UIDRef& linkObjectUIDRef) const = 0;
		
		/**
		** Checks whether the LinkObject corresponding to the XMLRef is a text Fragment Link Object. 
		*/
		virtual bool16 IsTextFragmentLinkObject(const XMLReference& xmlRef) const = 0;
		
		/**
		** return the Text Fragment Link Object Hierarchy
		*/
		virtual IHierarchy* GetTextFragmentHierarchy(const ILinkObject* linkObject) const = 0;

	};
} // namespace Facade

#endif // __ITextFragmentLinkFacade__

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILinksManager.h $
//  
//  Owner: Steve Flenniken
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
#ifndef __ILinksManager__
#define __ILinksManager__

#include "LinksID.h"

class UIDList;

/**
This interface contains methods to manipulate a list of data links.

To get the list of links in a document you can use:
IDocument *document = theDocument;
InterfacePtr<ILinksManager> linksManager(document, IID_ILINKSMANAGER);
*/
class ILinksManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKSMANAGER };
	
	/**
		ReadWrite method.  This class is persistent.
	*/
	virtual void ReadWrite(IPMStream *s, ImplementationID prop) = 0;

	/**
		Add data links to a document.
		@param UIDList *list: A list of data link (IDataLink) UIDs to add to the document.
		@return int32: Return 0 when successful. 
	*/
	virtual int32 AddLinks(const UIDList *list) = 0;
	/**
		Remove data links from a document.
		@param UIDList *list: A list of data link (IDataLink) UIDs to remove from the document.
		@return int32: Return 0 when successful. 
	*/
	virtual int32 RemoveLinks(const UIDList *list) = 0;

	/**
		Get a data link from the list.
		@param int32 index: The index of the item to get.
		@return UIDRef: UIDRef of the data link. 
	*/
	virtual UIDRef GetNthLinkUID(int32 index) = 0;
	/**
		Get the number of data links in the list.
		@return int32: Return the number of data links. 
	*/
	virtual int32 GetLinkCount() = 0;
	/**
		Find the specified data link in the list.
		@return int32: Return the index of data link when found, otherwise return -1. 
	*/
	virtual int32 GetLinkIndex(UID link) = 0;
};

#endif
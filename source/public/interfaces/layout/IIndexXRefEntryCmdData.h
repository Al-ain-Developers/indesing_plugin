//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IIndexXRefEntryCmdData.h $
//  
//  Owner: Michel Hutinel
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
//  Purpose: Interface data for creating, editing an XRef Page Entry
//  
//========================================================================================

#pragma once
#ifndef __IIndexXRefEntryCmdData__
#define __IIndexXRefEntryCmdData__

#include "IPMUnknown.h"
#include "IndexingID.h"
#include "UIDRef.h"
#include "IIndexXRefEntryData.h"

class IndexTopicEntry;

/** Interface data used by kCreateIndexXRefEntryCmdBoss and kEditIndexXRefEntryCmdBoss
	that contains information regarding the referenced topic entry.
	@see kCreateIndexXRefEntryCmdBoss, kEditIndexXRefEntryCmdBoss
	@ingroup layout_index
*/
class IIndexXRefEntryCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINDEXXREFENTRYCMDDATA };

		/** Gets the cross-reference type.
			@param customString [OUT] - if this pointer is not nil,
			it will to be set to the custom string used for custom cross-references.
			@return the type of the cross-reference.
		*/
		virtual IIndexXRefEntryData::XRefType	GetXRefType(WideString* customString = NULL) const = 0;	

		/** Sets the type of the cross-reference and the custom string.
			@param xRefType [IN] - the type of the cross-reference.
			@param customString [IN] - tthe custom string used for cross-reference.
			This parameter is mandatory if the xRefType is
			IIndexXRefEntryData::kCustomBefore or IIndexXRefEntryData::kCustomAfter.
		*/
		virtual void		SetXRefType(const IIndexXRefEntryData::XRefType xRefType, const WideString* customString = NULL) = 0;

		/** Retrieves the referenced topic entry.
			@return the referenced index topic entry.
		*/
		virtual const IndexTopicEntry&	GetRefedTopicEntry() const = 0;

		/** Sets the referenced topic entry.
			The client of the command should either use this method
			or use SetRefedTopicSectionUID together with SetRefedTopicNodeId.
			@param refedTopicEntry [IN] - the referenced topic entry.
		*/
		virtual void					SetRefedTopicEntry(const IndexTopicEntry& refedTopicEntry) = 0;

		/** Retrieves the UID of the section which contains the referenced topic entry.
			@return the UID of the topic section that contains the referenced index topic entry.
		*/
		virtual const UID	GetRefedTopicSectionUID() const = 0;

		/** Sets the section ID of the referenced topic.
			The caller should also call SetRefedTopicNodeId	if it calls this method.
			@param refedTopicSectionUID [IN] - the UID of the section ID that contains
			the referenced topic entry. 
		*/
		virtual void		SetRefedTopicSectionUID(const UID refedTopicSectionUID) = 0;

		/** Retrieves the node ID of the referenced topic entry.
			@return the node ID of the referenced index topic entry.
		*/
		virtual int32		GetRefedTopicNodeId() const = 0;

		/** Sets the node ID of the referenced topic.
			The caller should also call SetRefedTopicSectionUID	if it calls this method.
			@param refedTopicNodeId [IN] - the node id of the referenced topic entry. 
		*/
		virtual void		SetRefedTopicNodeId(int32 refedTopicNodeId) = 0;
};

#endif	// __IIndexXRefEntryCmdData__
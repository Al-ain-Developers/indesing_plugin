//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ICreateIndexPageEntryCmdData.h $
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
//  Purpose: Interface data for creating an Index Page Entry
//  
//========================================================================================

#pragma once
#ifndef __ICreateIndexPageEntryCmdData__
#define __ICreateIndexPageEntryCmdData__

#include "IPMUnknown.h"
#include "IndexingID.h"
#include "UIDRef.h"
#include "IIndexPageEntryData.h"

class IndexTopicEntry;

/** Interface data for creating an index page entry.
*/
class ICreateIndexPageEntryCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICREATEINDEXPAGEENTRYCMDDATA };

		/** Gets the target topic list UIDRef.
			@return the UIDRef of the topic list
		*/
		virtual const UIDRef&	GetTopicListUIDRef() const = 0;

		/** Sets the target topic list UIDRef.
			@param topicListUID [IN] - the UIDRef of the topic list.
		*/
		virtual void			SetTopicListUIDRef(const UIDRef& topicListUID) = 0;

		/** Gets the IndexTopicEntry.
			@return the IndexTopicEntry.
		*/
		virtual const IndexTopicEntry&	GetTopicEntry() const = 0;

		/** Sets the IndexTopicEntry.
			@param topicEntry [IN] - the IndexTopicEntry data.
		*/
		virtual void					SetTopicEntry(const IndexTopicEntry& topicEntry) = 0;

		/** Gets the topic section UID.
			@return the UID of the topic section.
		*/
		virtual const UID	GetTopicSectionUID() const = 0;

		/** Sets the topic section UID.
			@param topicSectionUID [IN] - the UID of the topic section.
		*/
		virtual void		SetTopicSectionUID(const UID topicSectionUID) = 0;

		/** Gets the topic node id.
			@return the id of the topic node.
		*/
		virtual int32		GetTopicNodeId() const = 0;

		/** Sets the topic node id.
			@param indexTopicNodeId [IN] - the id of the topic node.
		*/
		virtual void		SetTopicNodeId(int32 indexTopicNodeId) = 0;

		/** Gets the notification flag's value.
			@return the value of the notify flag.
		*/
		virtual bool16		GetDoNotifyFlag() const = 0;

		/** Sets the notification flag's value.
			@notify [IN] - the value of the notify flag.
		*/
		virtual void		SetDoNotifyFlag(bool16 notify) = 0;

		/** Gets the sort flag value (if the page references should be sorted).
			@return the value of the sort flag.
		*/
		virtual bool16	GetSortPRefs() const = 0;

		/** Sets the sort flag value (if the page references should be sorted).
			@bSortPRefs [IN] - the value of the sort flag.
		*/
		virtual void	SetSortPRefs(bool16 bSortPRefs) = 0;
};

#endif	// __ICreateIndexPageEntryCmdData__
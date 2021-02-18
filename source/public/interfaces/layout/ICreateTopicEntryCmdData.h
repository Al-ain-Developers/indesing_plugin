//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ICreateTopicEntryCmdData.h $
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
//  Purpose: Interface data for creating a topic Entry
//  
//========================================================================================

#pragma once
#ifndef __ICreateTopicEntryCmdData__
#define __ICreateTopicEntryCmdData__

#include "IPMUnknown.h"
#include "IndexingID.h"
#include "UIDRef.h" 

class IndexTopicEntry;

/** Command data interface used for creating a topic entry.
	@ingroup layout_index
*/
class ICreateTopicEntryCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICREATETOPICENTRYCMDDATA };

		/**	Retrieves the topic list property.
			@return UIDRef of the topic list. 
		 */
		virtual const UIDRef& GetTopicListUIDRef() const = 0;

		/**	Sets the topic list property.
			@param topicListUIDRef [IN] - UIDRef of the topic list.
		 */
		virtual void SetTopicListUIDRef(const UIDRef& topicListUIDRef) = 0;

		/**	Retrieves the topic entry property.
			@see IndexTopicEntry.
			@return the topic entry property.
		 */
		virtual const IndexTopicEntry& GetTopicEntry() const = 0;

		/**	Sets the topic entry property.
			@param topicEntry [IN] - the topic entry that needs to be created.
		 */
		virtual void SetTopicEntry(const IndexTopicEntry& topicEntry) = 0;

		/**	Retrieves the "notify" flag.
			@return the value of the flag.
		 */
		virtual bool16 GetDoNotifyFlag() const = 0;

		/**	Sets the "notify" flag.
			@param notify [IN] - value of the flag.
		 */
		virtual void SetDoNotifyFlag(bool16 notify) = 0;

		/**	Retrieves the topic section where the entry was created.
			This method can be called by the client of the command only after the command is done.
			@return UID 
		 */
		virtual const UID	GetTopicSectionUID() const = 0;

		/**	Retrieves the node id of the created topic.
			This method can be called by the client of the command only after the command is done.
			@return the node id of the topic.
		 */
		virtual const int32	GetTopicNodeId() const = 0;

		/**	Sets the topic section UID of the created topic.
			This method should be called only by the command itself.
			@param sectionUID [IN] - the UID of the topic section.
		 */
		virtual void		SetTopicSectionUID(const UID sectionUID) = 0;

		/**	Sets the topic node id of the created topic.
			This method should be called only by the command itself.
			@param nodeId [IN] - the topic node id. 
		 */
		virtual void		SetTopicNodeId(const int32 nodeId) = 0;
};

#endif	// __ICreateTopicEntryCmdData__
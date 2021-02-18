//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDeleteTopicEntryCmdData.h $
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
//  Purpose: Interface data for deleting a topic Entry
//  
//========================================================================================

#pragma once
#ifndef __IDeleteTopicEntryCmdData__
#define __IDeleteTopicEntryCmdData__

#include "IPMUnknown.h"
#include "IndexingID.h"
#include "UIDRef.h" 
#include "K2Vector.h" 

class IndexTopicEntry;

/** Command data interface used for deleting a topic entry.
	@ingroup layout_index
*/
class IDeleteTopicEntryCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDELETETOPICENTRYCMDDATA };

		/**	Retrieves the topic list property.
			@return UIDRef of the topic list. 
		 */
		virtual const UIDRef&	GetTopicListUIDRef() const = 0;

		/**	Sets the topic list property.
			@param topicListUIDRef [IN] - UIDRef of the topic list.
		 */
		virtual void			SetTopicListUIDRef(const UIDRef& topicListUIDRef) = 0;

		/**	Retrieves the topic section UIDRef property.
			@return UIDRef of the topic section.
		 */
		virtual const UIDRef&	GetTopicSectionUIDRef() const = 0;

		/**	Sets the topic section UIDRef property.
			@param topicSectionUIDRef [IN] - UIDRef of the topic section.
		 */
		virtual void			SetTopicSectionUIDRef(const UIDRef& topicSectionUIDRef) = 0;

		/**	Sets the topic section id property.
			@param topicSectionId [IN] -  the topic section id.
		 */
		virtual void			SetTopicSectionId(int32 topicSectionId) = 0;

		/**	Retrieves the topic section id.
			@return the id of the topic section. 
		 */
		virtual int32			GetTopicSectionId() const = 0;

		/**	Retrieves the topic entry set in the command's data.
			@return the topic entry stored in the command's data. 
		 */
		virtual const	IndexTopicEntry& GetTopicEntry() const = 0;

		/**	Sets the topic entry data.
			@param topicEntry [IN] - the topic entry.
		 */
		virtual void	SetTopicEntry(const IndexTopicEntry& topicEntry) = 0;

		/**	Retrieves the topic node id.
			This method should be used only by the index panel.
			@return the topic node id.
		 */
		virtual			int32 GetTopicNodeId() const = 0;

		/**	Sets the topic node id.
			This method should be used only by the index panel.
			@param indexTopicNodeId [IN] - the topic node id. 
		 */
		virtual void	SetTopicNodeId(int32 indexTopicNodeId) = 0;

		/**	Retrieves the "notify" flag.
			@return the value of the flag.
		 */
		virtual bool16	GetDoNotifyFlag() const = 0;

		/**	Sets the "notify" flag.
			@param notify [IN] - value of the flag.
		 */
		virtual void	SetDoNotifyFlag(bool16 notify) = 0;

		/**	Retrieves the list of the deleted topic nodes.
			This list is set by the command and is valid only after the command is done.
			@return array of ids of deleted topic nodes.
		 */
		virtual const K2Vector<int32>&	GetDeletedTopicNodeIdList() const = 0;

		/**	Sets the list of the deleted topic nodes.
			This method should be called only by the command (DeleteTopicEntryCmd).
			@param deletedNodeIdList [IN] - list of ids of deleted topic nodes.
		 */
		virtual void	SetDeletedTopicNodeIdList(K2Vector<int32>& deletedNodeIdList) = 0;
};

#endif	// __IDeleteTopicEntryCmdData__
//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ICreateIndexXRefEntryCmdData.h $
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
//  Purpose: Interface data for creating an Index XRef Entry
//  
//========================================================================================

#pragma once
#ifndef __ICreateIndexXRefEntryCmdData__
#define __ICreateIndexXRefEntryCmdData__

#include "IPMUnknown.h"
#include "IndexingID.h"
#include "UIDRef.h"
#include "IIndexPageEntryData.h"

class IndexTopicEntry;

/** Command data interface used for creating an index cross-reference entry.
	@ingroup layout_index
*/
class ICreateIndexXRefEntryCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICREATEINDEXXREFENTRYCMDDATA };

		/**	Retrieves the topic list property.
			@return UIDRef of the topic list. 
		 */
		virtual const UIDRef&	GetTopicListUIDRef() const = 0;

		/**	Sets the topic list property.
			@param topicListUIDRef [IN] - UIDRef of the topic list.
		 */
		virtual void			SetTopicListUIDRef(const UIDRef& topicListUID) = 0;

		/**	Retrieves the topic entry where the cross-reference will be inserted.
			@see IndexTopicEntry.
			@return the topic entry property.
		 */
		virtual const IndexTopicEntry&	GetTopicEntry() const = 0;

		/**	Sets the topic entry where the cross-reference will be inserted.
			The clients of the command should either
			call this method or SetTopicSectionUID() AND SetTopicNodeId().
			@param topicEntry [IN] - the topic entry.
		 */
		virtual void					SetTopicEntry(const IndexTopicEntry& topicEntry) = 0;

		/**	Retrieves the topic section where the cross-reference will be inserted.
			@return UID of the topic section.
		 */
		virtual const UID	GetTopicSectionUID() const = 0;

		/**	Sets the topic section where the cross-reference will be inserted.
			@param topicSectionUID [IN] - the UID of the topic section.
		 */
		virtual void		SetTopicSectionUID(const UID topicSectionUID) = 0;

		/**	Retrieves the topic node id where the cross-reference will be inserted.
			@return the topic node id.
		 */
		virtual int32		GetTopicNodeId() const = 0;

		/**	Sets the topic node id where the cross-reference will be inserted.
			@param indexTopicNodeId 
		 */
		virtual void		SetTopicNodeId(int32 indexTopicNodeId) = 0;

		/**	Retrieves the "notify" flag.
			@return the value of the flag.
		 */
		virtual bool16		GetDoNotifyFlag() const = 0;

		/**	Sets the "notify" flag.
			This flag is default set to kTrue.
			@param notify [IN] - value of the flag.
		 */
		virtual void		SetDoNotifyFlag(bool16 notify) = 0;

		/**	Retrieves the "allow recursive cross-reference" flag.
			If a topic AAA references another topic BBB (see "BBB") and BBB references AAA (see "AAA")
			it is called a recursive cross-reference.
			@return kTrue if recursive cross-references are allowed, kFalse if not.
		 */
		virtual bool16		GetAllowRecursiveXRef() const = 0;

		/**	Sets the "allow recursive cross-reference" flag.
			This flag is default set to kFalse.
			If a topic AAA references another topic BBB (see "BBB") and BBB references AAA (see "AAA")
			it is called a recursive cross-reference.
			@param allow [IN] - value of the flag.
		 */
		virtual void		SetAllowRecursiveXRef(bool16 allow) = 0;
};

#endif	// __ICreateIndexXRefEntryCmdData__
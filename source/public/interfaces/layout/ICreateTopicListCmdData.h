//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ICreateTopicListCmdData.h $
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
//  Purpose: Interface data for creating a topic List
//  
//========================================================================================

#pragma once
#ifndef __ICREATETOPICLISTCMDDATA__
#define __ICREATETOPICLISTCMDDATA__

#include "IPMUnknown.h"
#include "IndexingID.h"
#include "UIDRef.h" 
#include "IIndexHeaderSet.h"

class PMString;
class TopicSectionHeadersSet;

/** Command data interface used for creating a topic list.
	@ingroup layout_index
*/
class ICreateTopicListCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICREATETOPICLISTCMDDATA };

		/**	Retrieves the target item for the command.
			The target is the document workspace that will own the topic list.
			@return the UID of the target 
		 */
		virtual const UIDRef& GetTargetItem() const = 0;

		/**	Sets the target item for the command.
			The target is the document workspace that will own the topic list.
			@param targetItem [IN] - UIDRef of the target item.
		 */
		virtual void SetTargetItem(const UIDRef& targetItem) = 0;

		/**	Retrieves the flag that specifies if the command should use the topiclist list.
			@return the flag's value. 
		 */
		virtual bool16	GetUseTopicListListFlag() const = 0;

		/**	Sets the flag that specifies if the command should use the topiclist list.
			Currently this flag is always set to kFalse (we don't use topiclist lists).
			@param useIt [IN] - the value of the flag.
		 */
		virtual void	SetUseTopicListListFlag(bool16 useIt) = 0;

		/**	Retrieves the "notify" flag.
			@return the value of the flag.
		 */
		virtual bool16	GetDoNotifyFlag() const = 0;

		/**	Sets the "notify" flag.
			@param notify [IN] - value of the flag.
		 */
		virtual void	SetDoNotifyFlag(bool16 notify) = 0;
};

#endif	// __ICREATETOPICLISTCMDDATA__
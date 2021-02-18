//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ICapitalizeTopicEntryCmdData.h $
//  
//  Owner: Bertrand Lechevalier
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
//  Purpose: Command data interface for capitalizing a topic entry
//  
//========================================================================================

#pragma once
#ifndef __ICapitalizeTopicEntryCmdData__
#define __ICapitalizeTopicEntryCmdData__

#include "IPMUnknown.h"
#include "IndexingID.h"
#include "UIDRef.h" 

class IndexTopicEntry;

/** Command data interface used to capitalize a topic entry.
*/
class ICapitalizeTopicEntryCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICAPITALIZETOPICENTRYCMDDATA };

		/** Options for capitalization.
		*/
		enum CapitalizeOption { kSelected, kSelectedAndChildren, kAllLevel1, kAll };

		/** Retrieves the capitalization option.
			@return capitalization option
		*/
		virtual const	CapitalizeOption& GetCapitalizeOption() const = 0;

		/** Sets the capitalization option.
			@param capitalizeOption[IN] - capitalization option
		*/
		virtual void	SetCapitalizeOption(const CapitalizeOption& capitalizeOption) = 0;

		/** Retrieves the target topic list.
			@return UIDRef of the target topic list.
		*/ 
		virtual const UIDRef&	GetTopicListUIDRef() const = 0;

		/** Sets the target topic list.
			@param topicListUIDRef[IN] - UIDRef of the target topic list.
		*/ 
		virtual void			SetTopicListUIDRef(const UIDRef& topicListUIDRef) = 0;

		/** Retrieves the target topic section.
			@return UIDRef of the target topic section.
		*/ 
		virtual const UIDRef&	GetSelectedTopicSectionUIDRef() const = 0;

		/** Sets the target topic section.
			@param selectedTopicSectionUIDRef[IN] - UIDRef of the target topic section.
		*/
		virtual void			SetSelectedTopicSectionUIDRef(const UIDRef& selectedTopicSectionUIDRef) = 0;

		/** Retrieves the target topic id.
			@return id of the target topic.
		*/ 
		virtual const int32		GetSelectedTopicId() const = 0;

		/** Sets the target topic id.
			@param selectedTopicId[IN] - id of the target topic.
		*/ 
		virtual void			SetSelectedTopicId(const int32 selectedTopicId) = 0;
};

#endif	// __ICapitalizeTopicEntryCmdData__

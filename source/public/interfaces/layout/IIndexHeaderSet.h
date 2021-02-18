//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IIndexHeaderSet.h $
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
//  Comments: This interface saves the information about an Index instance (generated index).
//  
//========================================================================================

#pragma once
#ifndef __IIndexHeaderSet__
#define __IIndexHeaderSet__

#include "IPMUnknown.h"
#include "IndexingID.h"
#include "IndexSectionHeader.h"
#include "IndexHeaderGroup.h"

class PMString;
class WideString;
class IndexTopicEntry;

/**
	@ingroup layout_index
*/
class IIndexHeaderSet : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINDEXHEADERSET };
	
	virtual void				Set(const IIndexHeaderSet* newHeaderSet) = 0;
	virtual bool16				SetHeaderSetHandlerClassID(const ClassID handlerClassID, int32 groupingValue = -1, int32 groupingOptionValue = -1, bool16 rebuildSet = kTrue) = 0;
	virtual const ClassID&		GetHeaderSetHandlerClassID(int32* groupingValue = nil, int32* groupingOptionValue = nil) const = 0;
	virtual void				Clear(bool16 onlyGroups = kFalse) = 0;

	virtual bool16				Equal(const IIndexHeaderSet* otherSet) const = 0;

	virtual void				SetName(const PMString& name) = 0;
	virtual const PMString&		GetName() const = 0;

	virtual void				SetLanguageID(const LanguageID language) = 0;
	virtual LanguageID			GetLanguageID() const = 0;

	virtual void				AppendGroup(const IndexHeaderGroup& topicHeaderGroup) = 0;
	virtual const int32			GetNumSectionHeader(const int32 groupId = -1) const = 0;
	virtual const IndexSectionHeader&			GetNthSectionHeader(int32 nth, const int32 groupId = -1) const = 0;
	virtual const int32			GetNumGroup() const = 0;
	virtual const IndexHeaderGroup&			GetNthGroup(int32 nth) const = 0;
	virtual const bool16		GetGroup(PMString UIGroupName, IndexHeaderGroup& groupFound) const = 0;
	virtual const int32			GetNumVisibleGroup() const = 0;
	virtual const int32			GetNumSectionOfAllInvisibleGroup() const = 0;
	virtual const int32			GetGroupIdOfSection(int32 sectionId) const = 0;
	virtual const int32			GetSectionIdInWholeList(int32 groupId, int32 sectionIdInGroup) const = 0;
	virtual const int32			GetSectionIdInWholeList(const IndexSectionHeader& sectionHeader) const = 0;
	virtual const int32			GetSectionIdInGroup(int32 sectionIdInWholeList) const = 0;
	virtual const bool16		IsNthGroupVisible(int32 nth) const = 0;

	virtual bool16				FindTopicSectionUIDRef(const IndexTopicEntry& topicEntry, UIDRef& sectionRef, bool16 stripQuotes = kTrue) const = 0;
	virtual bool16				FindTopicSectionId(const IndexTopicEntry& topicEntry, int32& sectionId, bool16 stripQuotes = kTrue) const = 0;
};

#endif // __IIndexHeaderSet__
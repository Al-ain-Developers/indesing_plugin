//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IIndexingHeaderSetHandler.h $
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
//========================================================================================

#pragma once
#ifndef __IIndexingHeaderSetHandler__
#define __IIndexingHeaderSetHandler__

#include "IPMUnknown.h"
#include "IndexingID.h"

class IIndexHeaderSet;
class IndexTopicEntry;
class PMString;

/**
	@ingroup layout_index
*/
class IIndexingHeaderSetHandler : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINDEXINGHEADERSETHANDLER };
	
	virtual void	GetName(PMString& name) const = 0;

	virtual int32	GetNumGroupingValues() const = 0;
	virtual int32	GetNumGroupingOptionValues() const = 0;

	virtual void	GetDefaultGroupingValues(int32& grouping, int32& groupingOption) const = 0;

	virtual int32	GetNthGroupingValue(int32 nth) const = 0;
	virtual int32	GetNthGroupingOptionValue(int32 nth) const = 0;

	virtual int32	GetGroupingValueId(int32 value) const = 0;
	virtual int32	GetGroupingOptionValueId(int32 value) const = 0;

	virtual void	GetNthGroupingValueName(int32 nth, PMString& name) const = 0;
	virtual void	GetNthGroupingOptionValueName(int32 nth, PMString& name) const = 0;

	virtual	void	BuildHeaderSet(IIndexHeaderSet* headerSet) const = 0;

	virtual bool16	FindTopicSectionId(const IIndexHeaderSet* headerSet, const IndexTopicEntry& topicEntry, int32& sectionId, bool16 stripQuotes = kTrue) const = 0;
};

#endif // __IIndexingHeaderSetHandler__
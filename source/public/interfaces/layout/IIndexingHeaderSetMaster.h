//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IIndexingHeaderSetMaster.h $
//  
//  Owner: mvogel
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
#ifndef __IIndexingHeaderSetMaster__
#define __IIndexingHeaderSetMaster__

#include "IPMUnknown.h"
#include "IndexingID.h"
#include <vector>
#include "IndexHeaderGroup.h"

class IIndexHeaderSet;
class PMString;

class HeaderRangeTypes
{
public:
	typedef object_type data_type;

		/** Default constructor.
		*/
		HeaderRangeTypes() : fInclude(kFalse), fSelection(0) {}

		HeaderRangeTypes(
				const PMString& headerRangeName,
				const bool16& include,
				const int32& selection,
				const std::vector<IndexHeaderGroup> groupList):
			fHeaderRangeName(headerRangeName),
			fInclude(include),
			fSelection(selection),
			fGroupList(groupList) {}

		bool16 operator==(const HeaderRangeTypes& other) const
		{
			return ( (fHeaderRangeName == other.fHeaderRangeName) &&
				     (fInclude == other.fInclude) &&
 				     (fSelection == other.fSelection) &&
				     (fGroupList == other.fGroupList) );
		}

		void ReadWrite(IPMStream *s)
		{
			fHeaderRangeName.ReadWrite(s);
			s->XferBool(fInclude);
			s->XferInt32(fSelection);

			int32	numGroup = static_cast<int32>(fGroupList.size());

			s->XferInt32(numGroup);
			if (s->IsReading())
			{
				fGroupList.clear();
				fGroupList.reserve(numGroup);

				int32 i;
				for (i = 0; i < numGroup; i++)
				{
					IndexHeaderGroup	topicHeaderGroup;

					topicHeaderGroup.ReadWrite(s);

					fGroupList.push_back(topicHeaderGroup);
				}
			}
			else
			{
				int32 i;
				for (i = 0; i < numGroup; i++)
					fGroupList[i].ReadWrite(s);
			}

		}

	PMString fHeaderRangeName;
	bool16 fInclude;
	int32 fSelection;
	std::vector<IndexHeaderGroup> fGroupList;
};

/**
	Contains all the possible headers for indexing.

	@ingroup layout_index
*/
class IIndexingHeaderSetMaster : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINDEXINGHEADERSETMASTER };

	/**
		Get number of header groups.
		These groups are unicode ranges like Latin, Cyrillic, and Numbers.

		@return	int32		 number of header groups
	*/
	virtual	int32		GetNumGroups() const = 0;

	/**
		Get name of nth header group.
		These names are like Latin, Cyrillic, and Numbers.

		@param	nth			number of header group to get info for. < GetNumGroups.
		@return	PMString	name header group
	*/
	virtual const PMString&	GetNthGroupName(int32 nth) const = 0;

	/**
		Get names of types for nth header group.
		For example Latin has Basic Latin, Spanish, and Cyrillic has
		ones like Russian and Bulgarian.

		@param	nth		number of header group to get info for. < GetNumGroups.
		@return	std::vector<PMString>	names of types
	*/
	virtual std::vector<PMString>	GetNthGroupTypes(int32 nth) const = 0;

	/**
		Get selection for nth header group.
		Which type is selected. Use GetNthGroupTypes to see vector of types.

		@param	nth		number of header group to get info for. < GetNumGroups.
		@return	int32	which type is selected
	*/
	virtual int32		GetNthGroupSelection(int32 nth) const = 0;

	/**
		Set selection for nth header group.
		Which type is selected. Use GetNthGroupTypes to see vector of types.

		@param	nth		number of header group to get info for. < GetNumGroups.
		@param	selection	which type to select
	*/
	virtual void		SetNthGroupSelection(int32 nth, int32 selection) = 0;

	/**
		Get if nth header group is included.
		Only included groups will show in the index palette.

		@param	nth		number of header group to get info for. < GetNumGroups.
		@return	bool16	if header group is included
	*/
	virtual bool16		GetNthInclude(int32 nth) const = 0;

	/**
		Set if nth header group is included.
		Only included groups will show in the index palette.

		@param	nth		number of header group to get info for. < GetNumGroups.
		@param	bool16	if header group is included
	*/
	virtual void		SetNthInclude(int32 nth, bool16 include) = 0;

	/**
		Move groups around.

		@param	oldPos	header group to move. < GetNumGroups.
		@param	newPos	position to move header group before. <= GetNumGroups.
	*/
	virtual void		Move(int32 oldPos, int32 newPos) = 0;

	/**
		Add header group.
		Added to end position

		@param	headerGroup	header group to add.
		@param	include		if header should be included by default
	*/
	virtual void		AddGroup(const IndexHeaderGroup &headerGroup, bool16 include = kTrue) = 0;

	/**
		Uses data to build a header set

		@param	headerSet	header set to build. set is cleared before building.
	*/
	virtual	void		BuildHeaderSet(IIndexHeaderSet* headerSet) const = 0;

	virtual void	SetAllGroupInfo(const std::vector<HeaderRangeTypes>& headerRangeList) = 0;

	/**
		Copy these values TO the passed in interface (iTarget).

		@param iTarget is filled out with the current interface's values.
	*/
	virtual void CopyData(IIndexingHeaderSetMaster *iTarget ) const = 0;


	enum GroupOrder
    {
		kDefault = -1,
		kSymbolLatin,
		kSymbolNumbersLatinKana,
		kKanaLatinNumbersSymbol,
		kLatinNumbersSymbol,
		kSymbolNumbersLatinKorean,
		kSymbolNumbersPinYin,
		kSymbolNumbersLatinHanziStrokes
		,kSymbolNumbersLatinME
		,kSymbolNumbersLatin			/*WR_SymbolNumericAlphabet*/
		,kSymbolArabic				/*WR_SymbolArabic*/
		,kSymbolNumbersArabic		/*WR_SymbolNumericArabic*/
		,kSymbolNumbersArabicLatin	/*WR_SymbolNumericArabicAlphabet*/
		,kSymbolNumbersLatinArabic	/*WR_SymbolNumericAlphabetArabic*/
		,kSymbolHebrew				/*WR_SymbolHebrew*/
		,kSymbolNumbersHebrew		/*WR_SymbolNumericHebrew*/
		,kSymbolNumbersHebrewLatin	/*WR_SymbolNumericHebrewAlphabet*/
		,kSymbolNumbersLatinHebrew	/*WR_SymbolNumericAlphabetHebrew*/
    };
	/**
		Set to default values based on current UI

		@param	order	order for groups. Common orders for things like Japanese featureset.
						KDefault uses current featureset and UI to create headersetmaster.
	*/
	virtual void	SetDefault(GroupOrder order = kDefault) = 0;
};

#endif // __IIndexingHeaderSetMaster__
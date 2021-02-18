//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageList.h $
//  
//  Owner: Tommy Donovan
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
//  IPageList is a list of pages contained within a given document. 
//  It is used to get page number strings.
//  
//========================================================================================

#pragma once
#ifndef __IPAGELIST__
#define __IPAGELIST__

/** Minimum number of pages in a document. */
#define kMinNumPages				1

/** Maximum number of pages in a document. */
#define kMaxNumPages				9999

/** Minimum number of pages per spread. */
#define kMinNumPagesPerSpread		1

/** Maximum number of pages per spread. */
#define kMaxNumPagesPerSpread		10

#ifndef __ODFRC__	// when used for core resource compilation, provide just the parameter range constants

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "ILayoutUtils.h"
#include "ITextDataValidation.h"

class UIDList;
class PMString;
class IMargins;
class IColumns;

	/**
	 Specifiers for how page strings are created and parsed.
		 kDefaultNumber: create or parse string according to the session setting (IPageNumberPrefs)
		 kActualType: create or parse string with as the actual page number in document.
		 kOrdinalType: create and parse strings with page numbers as ordinals.
		 kActualWithNamedLayoutType: create or parse string with as the actual page number prefixed with the its named layout and a colon. e.g. iPadH:1 or iPadV:7
	 */
enum PageNumberType { kDefaultPageType = 0, kActualType, kOrdinalType, kActualWithNamedLayoutType };

	/** Pass in to InvalidateCache to invalidate just the masters in page cache */
const int kInvalidateMasterCache = kMaxInt32;

class IPageNameToUIDCache;

/**
	IPageList is a non-persistent interface off the document, which caches commonly needed information about 
	pages in the document. All the information is computed only when needed. It is *much* more efficient to 
	use this than to compute the same information from other sources.
 */
class IPageList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPAGELIST };

	/**
		GetPageCount - Return the number of layout pages in the document (does not include master pages)
	
		@return	int32 - the number of layout pages in the document
	*/
	virtual int32 GetPageCount() const= 0;

	/**
		GetNthPageUID - Given a page location within a pub (ie the 3rd page of the overall
			pub), returns the UID of the page.  

		@param	pageIndex - page index of interest
		@return	UID
	*/
	virtual UID GetNthPageUID(int32 pageIndex) const = 0;

	/**
		GetPageIndex - Given a page UID, returns the location of the page within a pub
			(ie the overall 3rd page of the pub). 
	
		@param	pageUID
		@return	int32
	*/
	virtual int32 GetPageIndex(UID pageUID) const = 0;

	/**
		GetPageType - Returns the page type of the given page (left, right, or unisex)
	
		@param	pageUID - page of interest
		@return	PageType - the page type of the given page
	*/
	virtual PageType GetPageType (UID pageUID) const = 0;
		
	/**
		QueryPageMargins - Returns the margins for the given page as would be returned by QueryFrontMargins
	
		@param	pageUID - page of interest
		@return	IMargins* - the margins for the given page as would be returned by QueryFrontMargins
	*/
	virtual IMargins* QueryPageMargins (UID pageUID) const = 0;
		
	/**
		QueryPageColumns - Returns the columns for the given page as would be returned by QueryFrontColumns
	
		@param	pageUID - page of interest
		@return	IColumns* - the columns for the given page as would be returned by QueryFrontColumns
	*/
	virtual IColumns* Query__PageColumns (UID pageUID) const = 0;
		
	/**
		GetPageString - Given a page UID (or spread UID), returns the page string (eg "A:12"). 
	
		@param	IN pageUID - page of interest
		@param	OUT pPageString - page string
		@param	IN bIncludeSectionName - kTrue == Include the section name if any with the string
		@param	IN bUseIntegerStyle - kTrue == Use arabic numerals in string; kFalse == use the style of this section (eg iv for 4)
		@param	IN pageNumberType - See PageNumberType enum above
		@param	IN bAbbreviate - For spreadUIDs, use short or long form (eg MP or A-Master, or PB or PB: 1)
	*/
	virtual void GetPageString(UID pageUID, PMString* pPageString,
					bool16 bIncludeSectionName = kTrue,
					bool16 bUseIntegerStyle = kTrue,
					PageNumberType pageNumberType = kDefaultPageType,
					bool16 bAbbreviate = kTrue) const = 0;

	/**
		GetPageRangeString - Given a UIDList of pages, returns the page range string (eg  "A:12-C:21,D:41").
	
		@param	IN pageUIDList - list of page UIDs. Can also handle UIDs for master spreads/pages.
		@param	OUT pPageString - result page range string
		@param	IN bIncludeSectionName - kTrue == Include the section name if any with the string
		@param	IN bUseIntegerStyle - kTrue == Use arabic numerals in string; kFalse == use the style of this section (eg  iv for 4)
		@param	IN pageNumberType - See PageNumberType enum above
		@param	IN bSortPageUIDList - kTrue == Sort page uids before formatting range string
		@param	IN bAbbreviate - For spreadUIDs, use short or long form (eg MP or A-Master, or PB or PB: 1)
	*/
	virtual void GetPageRangeString(UIDList& pageUIDList, PMString* pPageString,
					bool16 bIncludeSectionName = kFalse,
					bool16 bUseIntegerStyle = kTrue,
					PageNumberType pageNumberType = kDefaultPageType,
					bool16 bSortPageUIDList = kFalse,
					bool16 bAbbreviate = kTrue) const = 0;	
		 
	/**
		PageStringToUID - Given a page string (eg  "S1:12" (sectionName:pageNumber) or "7"(ordinal
			page number)), returns the UID of the page. If kInvalidUID is returned,
			it means an error in parsing occured. Error state, caller should handle.

	
		@param	IN pageString - name of page
		@param	IN pageNumberType - See PageNumberType enum above
		@param	OUT nError - error, if returned UID is kInvalidUID
		@param	IN pCache - cached off list of strings->UID mappings (created by calling CreatePageNameToUIDCache); may help performance if calling PageStringToUID repeatedly
		@return	UID - UID of page named
	*/
	virtual UID PageStringToUID(PMString& pageString, PageNumberType pageNumberType = kDefaultPageType, ITextDataValidation::RangeError* nError = nil, IPageNameToUIDCache* pCache = nil) const = 0;

	/**
		PageRangeStringToUIDList - 		Given a string for a range of pages (eg  "1-5, 6, 8-10" or 
			"Section-1:3-Section-3:7,Section-5:1"), parses the string and
			returns UIDList of the pages indicated. If the pageUIDList is empty
			on return, it means the string could not be parsed. Error state, caller should handle.
			The return value contains more detailed error information, or kSuccess if successful.
	
		@param	IN pageString - page range string
		@param	OUT pageUIDList -  UIDList of the pages indicated
		@param	IN pageNumberType - See PageNumberType enum above
		@return	ITextDataValidation::RangeError
	*/
	virtual ITextDataValidation::RangeError PageRangeStringToUIDList(PMString& pageString, UIDList* pageUIDList, PageNumberType pageNumberType = kDefaultPageType) const = 0;

	/**
		GetSectionIndex - returns index into the section list of the section that contains that page
	
		@param	pageUID - page of interest
		@param bRequireNamedLayout - if kTrue, section returned will have a named layout. This section
		may differ from the one that the page falls in.
		@return	int32 - index into the section list of the section that contains that page
		@see ISection, GetNamedLayout
	*/
	virtual int32 GetSectionIndex(UID pageUID, bool16 bRequireNamedLayout = kFalse) const= 0;

	/**
		GetSectionString - returns the marker text for the section within which
			the given page falls. If given a master page UID, returns "Section." 
	
		@param	pageUID - page of interest
		@param	pSectionMarkerString - the marker text for the section within which
			the page falls. If given a master page UID, returns "Section." 
	*/
	virtual void GetSectionString(UID pageUID, PMString* pSectionMarkerString) const = 0;

	/**
		InvalidateCache - The page list is kept as a cached list of page UID's. If pages
			or spreads are added, deleted, or moved, we need to update
			this list. This routine marks the UIDList of pages as needing
			to be rebuilt. By default, invalidates everything, with the 
			parameter, invalidates everything after (or including) the specified
			spread. Calling this frequently can degrade performance significantly.
	
		@param	startingFromSpreadIndex
	*/
	virtual void InvalidateCache(int32	startingFromSpreadIndex = 0) = 0;	

	/**
		InvalidateMarginsCache - Invalidate just the cached margin info.
	
		@param	startingFromSpreadIndex
	*/
	virtual void InvalidateMarginsCache(int32 startingFromSpreadIndex = 0) = 0;	

	/**
		InvalidateMarginsCache - Invalidate just the cached margin info.
	
		@param	invalidSpreadUIDs
	*/
	virtual void InvalidateMarginsCache(const UIDList *invalidSpreadUIDs) = 0;	

	/**
		InvalidateColumnsCache - Invalidate just the cached column info.
	
		@param	startingFromSpreadIndex
	*/
	virtual void InvalidateColumnsCache(int32 startingFromSpreadIndex = 0) = 0;	

	/**
		InvalidateColumnsCache - Invalidate just the cached column info.
	
		@param	invalidSpreadUIDs
	*/
	virtual void InvalidateColumnsCache(const UIDList *invalidSpreadUIDs) = 0;	

	/**
	  Creates a cache object which can be passed to certain calls that are repeatedly
	  executed to improve performance.
	 */
	virtual IPageNameToUIDCache* CreatePageNameToUIDCache() const= 0;

	/**
	 * Cleans up the cache.
	 */
	virtual void DestroyPageNameToUIDCache(IPageNameToUIDCache* pCache) const= 0;

	/**
	GetLastPageUID - Given a UIDlist of  pages within a pub, returns the UID of the last page.

		@param	IN pageUIDList - list of page UIDs. Can also handle UIDs for master spreads/pages.
		@param	IN bSortPageUIDList - kTrue == Sort page uids before formatting range string
	@return	UID
	*/
	virtual UID GetLastPageUID(UIDList& pageUIDList, bool16 bSortPageUIDList = kFalse) const = 0;
};
#endif	// __ODFRC__


#endif // __IPAGELIST__


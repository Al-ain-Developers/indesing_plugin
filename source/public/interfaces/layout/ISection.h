//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISection.h $
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
//========================================================================================

#pragma once
#ifndef __ISECTION__
#define __ISECTION__

/** Minimum starting page number of a section. */
#define kMinPageNumber				1

/** Maximum starting page number of a section. */
#define kMaxPageNumber				999999


#ifndef __ODFRC__

#include "IPMUnknown.h"
#include "SectionID.h"

class PMString;
class SectionStyle;

/** Abstract interface for describing a section. A section is an object, always
	owned by a page in a document, that is used for page numbering and page shuffling
	purposes.
	@ingroup layout_sect
	@see ISectionList.h
*/
class ISection : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISECTION };

	/**	Set all the attributes of a section.
		@param sectionName a PMString reference to the name of the new section
		@param sectionMarker a PMString reference to the section marker of the new section
		@param startPageUID a UID of the page to associate this section with.
		@param startPageNumber the starting page number of the section
		@param styleProviderClassID the class id for the page numbering style 
		@param bContinueFromPrevSection the section numbering to continue or not from previous section.
		@param offsetFromPrevSection offset from previous section for page numbering
		@see kNewSectionCmdBoss
		@see kSetSectionPaginationOptionsBoss
		@see IPageList.h
	 */
	virtual void Set(PMString& sectionName,
					PMString& sectionMarker,
					UID startPageUID,
					int32 startPageNumber,
					ClassID styleProviderClassID,
					bool16 bContinueFromPrevSection = kFalse,
					int32 offsetFromPrevSection = 0) = 0;

	/**	Set the name of the section (the prefix). May be empty.
		@param sectionName the name of the section.
	 */
	virtual void SetName(PMString& sectionName) = 0;

	/**	Set the name of the section marker, can be used on the page as a special character, kTextChar_SectionName.
		@param markerName the name of the marker.
	 */
	virtual void SetMarker(PMString& markerName) = 0;

	/**	The starting page UID for this section. kInvalidUID is assigned to the section on first page of document.
		@param startPageUID 
	 */
	virtual void SetStartPageUID(UID startPageUID) = 0;

	/**	Set the starting page number of the section. Ranges from kMinPageNumber to kMaxPageNumber.
		@param startPageNumber 
	 */
	virtual void SetStartPageNumber(int32 startPageNumber) = 0;

	/**	Set the class id for the page numbering style. This is the class id of the boss with
		a INumberConverter.h implementation. kArabicPageNumberingStyleServiceBoss is the default. 
		
		@param styleProviderClassID 
		@see INumberConverter.h
		@see SectionClass.fr
	 */
	virtual void SetStyleInfo(ClassID styleProviderClassID) = 0;

	/**	Set the section numbering to continue from previous section.
		@param bContinueFromPrevSection kTrue or kFalse
		@param offset int32 value 
	 */
	virtual void SetContinueFromPrevSection(bool16 bContinueFromPrevSection, int32 offset = 0) = 0;

	/**	Whether the section prefix (name) should be used when making page numbers for the section.
		@param includeSectionPrefix 
	 */
	virtual void SetPageNumberIncludeSectionPrefix(bool16 includeSectionPrefix) = 0;

	/**	Set the name of a named layout. May be empty.
		@param namedLayout the name for the named layout.
	 */
	virtual void SetNamedLayout(const PMString& namedLayout) = 0;

	/**	Return the name (prefix) of the section. Used in page number specification.
		@param pName 
	 */
	virtual void GetName(PMString* pName) = 0;

	/**	Returns the section marker. Used when section marker is inserted on page.
		@param pMarker 
	 */
	virtual void GetMarker(PMString* pMarker) = 0;

	/**	Returns UID of first page in the section, kInvalidUID for the default section of the document (on page 1).
		@return UID 
	 */
	virtual UID GetStartPageUID() = 0;

	/**	returns the first page number of the section. If page numbering
		is set to continue from previous section, returns the correct
		page number by looking back in section list.
		@return int32 
	 */
	virtual int32 GetStartPageNumber() = 0;

	/**	Returns info about page numbering style (Roman, numberic, etc.)
		@param styleProviderClassID 
		@see SectionClass.fr
	 */
	virtual void GetStyleInfo(ClassID* styleProviderClassID) = 0;

	/**	Is this the default section? default section cannot be deleted,
		@return bool16
	 */
	virtual bool16 IsDefaultSection() = 0;

	/**	Is the page number to continue from the last page number of the previous section?
		@return bool16 
	 */
	virtual bool16 GetContinueFromPrevSection() = 0;

	/**	Return the offset value for numbering from previous section. Used when GetContinueFromPrevSection is kTrue.
		@return int32 
	 */
	virtual int32 GetOffsetFromPrevSection() = 0;

	/**	Does the page number have the section prefix included in it?
		@return bool16 
	 */
	virtual bool16 GetPageNumberIncludeSectionPrefix() = 0;

	/**	Return the number of pages in this section. All sections have at least 1 page.
		@param bRequireNamedLayout - if kTrue, number of pages will be all within the same named layout, 
		which could span several non-named sections. kFalse means number of pages until next section.
		@return int32 
	 */
	virtual int32 GetNumPages(const bool16 bRequireNamedLayout = kFalse) = 0;

	/** Return the layout name for this section, maybe be kNullString.
		@param pNamedLayout
	 */
	virtual void GetNamedLayout(PMString* pNamedLayout) = 0;

	/** Pagination options for adding and removing pages in an alternate layout in HTML5 */
	typedef enum 
	{
		kInvalidPaginationOption = -1,	/** Not a legitimate value, used in command for skipping setting this value. */
		kAutomatic = 0,					/** Add/Remove pages automatically in HTML5 pagination (takes into account Optional pages). */
		kFromLastPage,					/** Add/Remove pages after the last page when doing HTML5 pagination. */
	} PaginationOption;

	/** Return the pagination option for adding and removing pages used when doing HTML5 pagination.
		@return AddPageOption
		@see AddPageOption enum for values.
	 */
	virtual PaginationOption GetPaginationOption() = 0;

	/** Set the pagination option for how pages are added and removed when doing HTML5 pagination.
		@param PaginationOption, one of the values from this enum
	*/
	virtual void SetPaginationOption(PaginationOption option) = 0;

	/** Return the master to use when pages are added doing HTML5 pagination.
		@return UID, either a UID of a specific master spread, or kInvalidUID when masters are being automatically applied.
	*/
	virtual UID GetPaginationMaster() = 0;

	/** Set the master page to use when pages are added when doing HTML5 pagination.
		@param UID, the UID of a specific master spread, or kInvalidUID to automatically apply a master page.
	*/
	virtual void SetPaginationMaster(UID masterUID) = 0;
};

#endif	// __ODFRC__
#endif	// __ISECTION__

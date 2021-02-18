//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISectionList.h $
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
#ifndef __ISECTIONLIST__
#define __ISECTIONLIST__

#include "IPMUnknown.h"
#include "IPageList.h"
#include "SpreadID.h"
#include "SectionID.h"

class ISection;
class UIDList;
class PMString;

/** This is an interface off the document which contains the
	list of sections (UIDs) in a given document. This list is persistent.
	IMPORTANT NOTE: The order of the sections in this list has no implicit
	meaning. In other words, it is not guaranteed that the sections are
	kept in order of the relative positions of their start pages within the
	pub.

	@ingroup layout_sect
	@see ISection.h
*/
class ISectionList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISECTIONLIST };

	/**	enum value for use in InsertSections and MoveSection.
	 */
	enum { kAtTheEnd = -1 };

	/**	Create a new section in the section list.
		@return UID of the created section.
		@see kNewSectionCmdBoss
	 */
	virtual UID NewSection() = 0;

	/**	Insert a list of sections at the given index.
		@param sectionsToInsert a UIDList reference to the list of sections to move.
		@param posForInsert the int32 position for where to insert. 0 is start of list, kAtEndEnd is the end.
		@see kNewSectionCmdBoss
	 */
	virtual void InsertSections(const UIDList& sectionsToInsert, int32 posForInsert) = 0;

	/**	Delete 'count' sections, starting at 'firstIndex'.
		@param firstIndex int32 the starting index for removal.
		@param count int32 number of sections to remove from the list.
		@see kDeleteSectionCmdBoss
	 */
	virtual void RemoveSections(int32 firstIndex, int32 count) = 0;

	/**	Reorder the section list. Should not be necessary for client code to call this.
		Move the section at the given index to the a new position in the list.
		Note that the section is first removed from the list, then
		inserted at the "to" position. Caller may need to adjust indexes
		in order to compensate for this behavior. Note that the default
		section cannot be moved, nor can a section be moved into its position (0).

		@param from int32 index of section to move
		@param to int32 index of position to move to
		@see QueryOrderedList
	 */
	virtual void MoveSection(int32 from, int32 to) = 0;

	/**	Return the ISection interface associated with the 'sectionIndex' section.
		This will add a ref count, and will instantiate the section (if necessary).

		@param sectionIndex int32 index from the list to query
		@return ISection the add-refed section interface.
	 */
	virtual ISection * QueryNthSection(int32 sectionIndex) = 0;

	/**	Returns the 'sectionIndex' section's UID
		@param sectionIndex the index in the list
		@return UID the UID of the section at this index.
	 */
	virtual UID GetNthSectionUID(int32 sectionIndex) = 0;

	/**	Return the number of sections in this list (i.e. in the document)
		@return int32 number of sections in the list. All documents have at least one.
	 */
	virtual int32 GetSectionCount() = 0;

	/**	Given a sections's ISection, return its index into the section list
		@param section the ISection pointer to look up in the list.
		@return int32 the index of this section, -1 if not found.
	 */
	virtual int32 GetSectionIndex(ISection * section) = 0;

	/**	Given a sections's UID, return the section's index into the section list.
		@param sectionUID the UID of the section to look up in the list.
		@return int32 the index of this section, -1 if not found.
	 */
	virtual int32 GetSectionIndex(UID sectionUID) = 0;

	/**
		Given a page UID, spread UID, masterpage UID, master spread UID, return its string representation.
		@param pageUID the UID of a page, spread, master page, or master spread for which you'd like a string description.
		@param OUT pPageString the string to populate with the page numbers.
		@param bIncludeSectionName Include the section name if any with the string		
		@param bUseIntegerStyle Use arabic numerals in string, or use the style of this section (e.g. iv for 4)	
		@param pageNumberType @see PageNumberType
		@param bAbbreviate For spreadUIDs, use short or long form (e.g. MP or A-Master, or PB or PB: 1)
	*/
	virtual void GetPageString(UID pageUID, PMString* pPageString,
					bool16 bIncludeSectionName = kTrue,	
					bool16 bUseIntegerStyle = kTrue,		
					PageNumberType pageNumberType = kDefaultPageType,	
					bool16 bAbbreviate = kTrue) = 0;	


	/**	Generates a unique section name, of the form "Sec1", "Sec2", ....
		As of CS4, we no longer use this method by default. So via our UI, sections will not have a
		name/prefix at all by deafult, so it is possible to have overlapping page numbers if the
		section doesn't use SetContinueFromPrevSection in ISection
		@param pName [IN/OUT] a pointer to the returned name.  
		@see kNewSectionCmdBoss
		@see ISection.h, SetContinueFromPrevSection
	 */
	virtual void GenerateNewSectionName(PMString* pName) = 0;

	/**	This call returns a UID list of section in order of the	the relative positions of 
		their start pages within the pub. All sections have at least 1 page in this.
		See also ISection::GetNumPages.
		Note: The caller is responsible for deleting this list when done.

		@return UIDList* the allocated list of section UIDs
		@see ISection.h
	 */
	virtual UIDList* QueryOrderedList() = 0;

	/**	Return the page number of the specified page, always returns a "real" page number, not an
		ordinal page number. (useful to determine even/oddness of a page).
		@param pageUID the UID of the page to get its page number.
		@return the "page number" of this page.
	 */
	virtual int32	GetPageNumber(UID pageUID) = 0;

	/**	This call returns a UID list of section in order of the	the relative positions of
	their start pages within the pub. All sections have at least 1 page in this.
	See also ISection::GetNumPages.
	Note: The caller should NOT delete this list when done as it is cached and owned by the implementation of this interface.

	@return UIDList* the cached ordered list of section UIDs
	@see ISection.h
	*/
	virtual UIDList* GetOrderedList() = 0;
};


#endif // __ISECTIONLIST__


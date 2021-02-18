//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISectionCmdData.h $
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
#ifndef __ISECTIONCMDDATA__
#define __ISECTIONCMDDATA__

#include "IPMUnknown.h"
#include "ISection.h"

class PMString;

/** Data interface for the NewSectionCmd (kNewSectionCmdBoss) and ModifySectionSettingsCmd (kModifySectionSettingsCmdBoss) 
	Also used as data interface for the SetSectionPaginationOptions (kSetSectionPaginationOptionsBoss). 
	@ingroup layout_sect
	@see ISection.h
*/
class ISectionCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISECTIONCMDDATA };

	/**	Set up the values for creating a new section via the kNewSectionCmdBoss.
		@param sectionList a reference to the section list to create a new section or modify. The ISectionList interface is on the kDocBoss.
		@param startPageUID which page should the section start on, or which section to modify. kInvalidUID is the value for the default section associated with the first page of every document. 
		@param startPageNumber the starting page number for the section
		@param name pointer to PMString, name/prefix of section. Used for page number specification. Must be unique (or empty).
		@param marker, pointer to PMString, text for section marker. Used when a section marker is inserted on page.
		@param styleProviderClassID, the ClassID for the page numbering style. kInvalidClass means to use kArabicPageNumberingStyleServiceBoss. 
		@param bContinueFromPrevSection, bool16 kTrue if section continues numbering from previous section, kFalse otherwise. 
		@param offsetFromPrevSection, int32 offset value for numbering from previous section. Used when GetContinueFromPrevSection is kTrue. 
	 */
	virtual void Set(const UIDRef& sectionList,
						UID startPageUID = kInvalidUID,
						int32 startPageNumber = 1,
						const PMString *name = nil,		
						const PMString *marker = nil,	
						ClassID styleProviderClassID = kInvalidClass,
						bool16 bContinueFromPrevSection = kTrue,
						int32 offsetFromPrevSection = 0) = 0;

	/**	Get function to return the section list.
		@return const UIDRef& a reference to the section list.
	 */
	virtual const UIDRef& GetSectionList() = 0;

	/**	Get function for the starting page of a section (UID of kPageBoss).
		@return UID the UID for the starting page of the section.
	 */
	virtual UID GetStartPageUID() = 0;

	/**	Set the starting page number of the section. Ranges from kMinPageNumber to kMaxPageNumber.
		@return int32 
	 */
	virtual int32 GetStartPageNumber() = 0;

	/**	Get the name of the section (the prefix).
		@return const PMString& the prefix name
	 */
	virtual const PMString& GetName() = 0;

	/**	Get the name of the section marker, can be used on the page as a special character, kTextChar_SectionName.
		@return const PMString& the marker
	 */
	virtual const PMString& GetMarker() = 0;

	/**	Return the ClassID for the page numbering style. kInvalidClass means to use kArabicPageNumberingStyleServiceBoss.
		@param styleProviderClassID* IN/OUT will be filled in by the ClassID of the page numbering style. 
		@see kService_PageNumberingStyles
	 */
	virtual void GetStyleInfo(ClassID* styleProviderClassID) = 0;

	/**	Does this section continue numbering from the previous section?
		@return bool16 kTrue if section continues numbering from previous section, kFalse otherwise.
	 */
	virtual bool16 GetContinueFromPrevSection() = 0;

	/**	Return the offset value for numbering from previous section. Used when GetContinueFromPrevSection is kTrue.
		@return int32 
	 */
	virtual int32 GetOffsetFromPrevSection() = 0;

	/**	Do page number characters in this section include the prefix string. Used for page number
		characters that are present into a document story.
		@return const bool16& kTrue if prefix is prepending to page number, kFalse otherwise.
		@see ITextEditSuite::kThisPage
	 */
	virtual const bool16& GetPageNumberIncludeSectionPrefix() = 0;

	/**	Set whether this function includes prefix in page number strings.
		@param includeSectionPrefix, kTrue to include prefix, kFalse to just use the page number.
	 */
	virtual void SetPageNumberIncludeSectionPrefix(const bool16& includeSectionPrefix) = 0;

	/**	Get the name of the named layout.
		@return const PMString& the layout name
	 */
	virtual const PMString& GetNamedLayout() = 0;

	/**	Set the name of the named layout.
		@param pNamedLayout pointer to PMString, page layout name. Used for alternate/named layouts. Must be unique (or empty).
	 */
	virtual void SetNamedLayout(const PMString* pNamedLayout) = 0;

	/** Return the pagination option for adding and removing pages from the command--used when doing HTML5 pagination.
		@return PaginationOption, one of the values from this enum
		@see ISection.h for enum values
		@see kSetSectionPaginationOptionsCmdBoss 
	 */
	virtual ISection::PaginationOption GetPaginationOption() = 0;

	/** Set the pagination option for the command for how pages are added and removed when doing HTML5 pagination.
		@param PaginationOption, one of the values from this enum
		@see ISection.h for enum values
		@see kSetSectionPaginationOptionsCmdBoss 
	*/
	virtual void SetPaginationOption(ISection::PaginationOption option) = 0;

	/** Return the master from the command to use when pages are added when doing HTML5 pagination.
		@return UID, either a UID of a specific master spread, or kInvalidUID when masters are being automatically applied.
		@see kSetSectionPaginationOptionsCmdBoss 
	*/
	virtual UID GetPaginationMaster() = 0;

	/** Set the master page for the command to use when pages are added when doing HTML5 pagination.
		@param UID, the UID of a specific master spread, or kInvalidUID to automatically apply a master page.
		@see kSetSectionPaginationOptionsCmdBoss 
	*/
	virtual void SetPaginationMaster(UID masterUID) = 0;

	/**	Get function for notification flag for kSetModifySectionSettingsCmdBoss.
		@return const bool16& kTrue to notify, kFalse to skip notification.
	 */
	virtual const bool16& GetNotifyFlag() = 0;

	/**	In general, INTERNAL USE only. Set a flag for kModifySectionSettingsCmdBoss to notify or not.
		@param kTrue to notify, kFalse to skip notification.
	 */
	virtual void SetNotifyFlag(const bool16& notify = kTrue) = 0;

	/** Set the data from an existing section. Can be useful for copying one section into another,
		or to set all the data fields for the kModifySectionSettingsCmdBoss at once.
	 */
	virtual void CopyFrom(ISection* section) = 0;

	/** Set the starting page for the section.
		@param startPageUID the starting page UID for the section.
	 */
	virtual void SetStartPageUID(const UID startPageUID) = 0;
};


#endif // __ISECTIONCMDDATA__

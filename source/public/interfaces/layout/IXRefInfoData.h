//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IXRefInfoData.h $
//  
//  Owner: Jianlan Song
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

#include "IPMUnknown.h"
#include "HyperlinkID.h"
#include "IXRefFormat.h"
#include "IHyperlinkUtils.h"

/** Structure used to cache story stamp information for source and destination story.
*/
typedef struct StampInfo
{
	StampInfo() : storyUID(kInvalidUID), version (0) {}
	StampInfo(UID initStoryUID, uint32 initVersion) : storyUID(initStoryUID), version(initVersion) {}
	
	StampInfo& operator=(const StampInfo& s) 
	{ 
		if (this != &s)
		{
			storyUID = s.storyUID; 
			version = s.version; 
		}
		return *this; 
	}

	bool operator==(const StampInfo& s) const
	{ 
		return ((storyUID == s.storyUID) &&
			   (version == s.version));
	}

	bool operator!=(const StampInfo& s) const
	{ 
		return !(*this == s);
	}
		
		
	UID storyUID;
	uint32 version;
} StampInfo;

/** This interface is used for kHyperlinkTextSourceBoss to
	store all the data related to cross reference text source.
	Both cross reference text source and hyperlink text source
	are represented by kHyperlinkTextSourceBoss. We distinguish
	the two by looking at the data in this interface.
	@ingroup layout_hyper
*/
class IXRefInfoData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXREFINFODATA };

	/**	Set whether or not this is a cross reference source
		@param isXRef - kTrue for cross reference source
	 */
	virtual void SetIsXRef(bool16 isXRef) = 0;
	/**	Return whether or not this is a cross reference source
		@return bool16 - kTrue if it is cross reference source
	 */
	virtual bool16 IsXRef() const = 0;
	
	/**	Get the UID of the format this cross reference uses
		@return UID - UID of the format 
	 */
	virtual UID GetXRefFormat() const = 0;
	/**	Set the UID of the format this cross reference uses
		@param formatUID - UID of the format to set to
	 */
	virtual void SetXRefFormat(UID formatUID) = 0;

	/**	Set the story stamp of the x-ref source
		@param storyUID - UID of the owning story
		@param version - version of the story
	 */
	virtual void SetSourceStamp(UID storyUID, uint32 version) = 0;
	virtual void GetSourceStamp(UID& storyUID, uint32& version) const = 0;
	virtual void GetSourceStamp(StampInfo& stamp) const = 0; 
	
	/**	Set the story stamp of the x-ref destination
		@param storyUID - UID of the owning story
		@param version - version of the story
	 */
	virtual void SetDestinationStamp(UID storyUID, uint32 version) = 0;
	virtual void GetDestinationStamp(UID& storyUID, uint32& version) const = 0;
	virtual void GetDestinationStamp(StampInfo& stamp) const = 0;

	/**	Set the document stamp of the external x-ref destination
		@param docStamp - document stamp of the external document which contains the x-ref destination
	 */
	virtual void SetExternDocStamp(uint32 docStamp) = 0;
	virtual uint32 GetExternDocStamp() const = 0;
	
	/** Set whether or not this xref source can be updated.
		@param doNotUpdate - kTrue for not to update
	*/
	virtual void SetDoNotUpdate(bool16 doNotUpdate) = 0;

	/** Returns whether or not this xref source can be updated.
		@return bool16 - kTrue not to update
	*/
	virtual bool16 DoNotUpdate() const = 0;

	/** Set destination status change count.
		@param destStatusChgCnt - destination status change count to set to.
	*/
	virtual void SetDestinationStatusChangeCount(uint32 destStatusChgCnt) = 0;

	/** Returns current destination status change count.
		@return uint32 - change count
	*/
	virtual uint32 GetDestinationStatusChangeCount() const = 0;
	
	/** Returns kTrue if one of following conditions is true:
		(1) source should not be updated;
		(2) destination is missing or in invalid location;
		(3) source is known to be out of date;
	*/
	virtual bool16 IsOutOfDate() const = 0;
	
	/** Checks whether or not we will need detailed check to determine if the source content
		if up to date or not. Returns kTrue if one of following conditions is true:
		(1) source story stamp changed;
		(2) destination story stamp changed for internal destination or external destination in opened documents;
		(3) document stamp changed for external destination in closed documents.
	*/
	virtual bool16 NeedStatusCheck() const = 0;

	/** Checks the status of the cross reference if it is marked as need status check. 
		@param linkChanged - [OUT] kTrue if the corresponding hyperlink object has changed. kFalse otherwise.
		@return bool16 - kTrue if the cross reference is up to date, kFalse if is out of date.
	*/
	virtual bool16 CheckXRefStatus(bool16& linkChanged) = 0;
	
	virtual PMString GetPageNumString() const = 0;

	virtual PMString GetChapterNumString() const = 0;
	
	/** Generate the cross reference source content from the destination
		@param destUIDRef - destination UIDRef
		@param newContent - [OUT] generated cross reference source content
		@param charStyleRanges - [OUT] contains ranges where to apply character styles in the generated new source content
		@param pageNumLocations - [OUT] contains offset of page number characters in the new source content
		@param variableLocations - [OUT] list of text variables and index offset in the new source content
		@param inlineLocations - [OUT] list of inline object locations in the source and destination
		@return IHyperlinkUtils::XRefDestStatus - status of the destination
	*/
	virtual IHyperlinkUtils::XRefDestStatus GetXRefSourceContent(UIDRef destUIDRef, PMString& newContent, K2Vector<CharStyleRange>& charStyleRanges,
		K2Vector<uint32>& pageNumLocations, K2Vector<uint32>& chapterNumLocations, std::map<TextIndex, WideString>* variableLocations,
		std::map<TextIndex, TextIndex>* inlineLocations) = 0;
};


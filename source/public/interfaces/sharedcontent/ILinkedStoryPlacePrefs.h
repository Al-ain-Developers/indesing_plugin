//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/sharedcontent/ILinkedStoryPlacePrefs.h $
//  
//  Owner: Shikha Arora
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 2010 Adobe Systems Incorporated
//  All Rights Reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __ILinkedStoryPlacePrefs__
#define __ILinkedStoryPlacePrefs__

#include "IPMUnknown.h"
#include "SharedContentID.h"

/** 
	Interface used to manage preference used for creating
	and managing shared content (Linked Text).
*/ 
class ILinkedStoryPlacePrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKEDSTORYPLACEPREFS };
	
	 /** 
		 Method to set preference for updating all out of date shared content
		 (Linked Text) links on document save.
		 @param bUpdate [IN] kTrue if you want update on save else kFalse.
	 */ 
	 virtual void SetUpdateLinkWhileSaving(bool16 bUpdate) = 0;

	 /** 
		 Method to get preference for updating all out of date shared content
		 (Linked Text) links on document save.
		 @return kTrue if update on save is enabled else kFalse.
	 */ 
	 virtual bool16 GetUpdateLinkWhileSaving() const = 0;

	 /** 
		 Method to set preference for showing warning on update of edited
		 shared content(Linked Text) story.
		 @param bWarn [IN] kTrue if you want to show warning else kFalse.
	 */ 
	 virtual void SetShowWarningOnUpdateOfEditedStory(bool16 bWarn) = 0;

	 /** 
		 Method to get preference for showing warning on update of edited
		 shared content(Linked Text) story.
		 @return kTrue if warning on update is enabled else kFalse.
	 */ 
	 virtual bool16 GetShowWarningOnUpdateOfEditedStory() const = 0;

	 /** 
		 Method to set preference for removing forced line breaks(soft returns)
		 while creating a shared content(Linked Text) story.
		 @param bRemove [IN] kTrue if you want to remove soft returns else kFalse.
	 */ 
	 virtual void SetRemoveForcedLineBreaks(bool16 bRemove) = 0;

	 /** 
		 Method to get preference for removing forced line breaks(soft returns)
		 while creating a shared content(Linked Text) story.
		 @return kTrue if remove soft returns is enabled else kFalse.
	 */ 
	 virtual bool16 GetRemoveForcedLineBreaks() const = 0;
	
	 /** 
		 Method to set preference for Style Mapping (used during link update)
		 @param bMapStyles [IN] kTrue if you want to map styles during link update else kFalse.
	 */ 
	 virtual void SetStyleMappingExceptions(bool16 bMapStyles) = 0;

	 /** 
		 Method to get preference for Style Mapping (used during link update)
		 @return kTrue if styles mapping is enabled else kFalse.
	 */ 
	 virtual bool16 GetStyleMappingExceptions() const = 0;

	/**
		Method which copies preferences set in input parameter 
		to shared content(Linked Text) preferences.
		@param pCopyFrom [IN] input preferences to copy from.
	*/
	virtual void CopyData(const ILinkedStoryPlacePrefs *pCopyFrom) = 0;	

	 /** 
		 Method to set preference for showing link options when creating linked page items.
		 @param bShow [IN] kTrue if you want to showing link options else kFalse.
	 */ 
	 virtual void SetShowLinkOptionsWhenCreatingLink(bool16 bShow) = 0;

	 /** 
		 Method to get preference for showing link options when creating linked page items.
		 @return kTrue if link options will be shown while creating link else kFalse.
	 */ 
	 virtual bool16 GetShowLinkOptionsWhenCreatingLink() const = 0;
};

#endif
		// __ILinkedStoryPlacePrefs__

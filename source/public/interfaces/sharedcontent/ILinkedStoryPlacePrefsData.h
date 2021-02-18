//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/sharedcontent/ILinkedStoryPlacePrefsData.h $
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
#ifndef __ILinkedStoryPlacePrefsData__
#define __ILinkedStoryPlacePrefsData__

#include "IPMUnknown.h"
#include "ILinkedStoryPlacePrefs.h"
#include "SharedContentID.h"

class ILinkedStoryPlacePrefsData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKEDSTORYPLACEPREFSDATA };
	
	/* Enumerates the state of an option.
	   The option's value should not be accessed if the state is "kValueNotSet" or "kValueMixed".
	*/
	typedef enum
	{
		/* No value set - invalid (clients should treat as opaque). This is the default state. */
		kValueNotSet = 0,
		/* Valid value set. */
		kValueSet,
		/* The value is different across the selection. */
		kValueMixed
	} OptionState;

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
		 Method to know whether preference for updating all out of date shared content
		 (Linked Text) links on document save is meaningful or not.
		 @return kValueMixed if this preference is different across selections.
		 kValueSet if it's same across selection & is also set else kValueNotSet.  
	*/ 
	virtual OptionState GetUpdateLinkWhileSavingState() const = 0;

	/** 
		 Method to set preference for setting style mapping exceptions, is set.
		 @param bUpdate [IN] kTrue if you want to set style mapping exceptions.
	*/ 
	virtual void SetStyleMappingExceptions(bool16 bUpdate) = 0;

	/** 
		 Method to get preference for setting style mapping exceptions.
		 @return kTrue if style mapping exceptions are set.
	*/ 
	virtual bool16 GetStyleMappingExceptions() const = 0;

	/** 
		 Method to know whether preference for setting style mapping exceptions
		 is meaningful or not.
		 @return kValueMixed if this preference is different across selections.
		 kValueSet if it's same across selection & is also set else kValueNotSet.  
	*/ 
	virtual OptionState GetStyleMappingExceptionsState() const = 0;

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
		 Method to know whether preference for showing warning on update of edited
		 shared content(Linked Text) story is meaningful or not.
		 @return kValueMixed if this preference is different across selections.
		 kValueSet if it's same across selection & is also set else kValueNotSet.  
	*/ 
	virtual OptionState GetShowWarningOnUpdateOfEditedStoryState() const = 0;

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
		 Method to know whether preference for removing forced line breaks(soft returns)
		 while creating a shared content(Linked Text) story is meaningful or not.
		 @return kValueMixed if this preference is different across selections.
		 kValueSet if it's same across selection & is also set else kValueNotSet.  
	*/ 
	virtual OptionState GetRemoveForcedLineBreaksState() const = 0;

	 /** 
		 Method to set preference for showing link options when creating linked story.
		 @param bShow [IN] kTrue if you want to showing link options else kFalse.
	 */ 
	 virtual void SetShowLinkOptionsWhenCreatingLink(bool16 bShow) = 0;

	 /** 
		 Method to get preference for showing dialog 
		 while creating a shared content(Linked Text) story.
		 @return kTrue if remove soft returns is enabled else kFalse.
	*/ 
	 virtual bool16 GetShowLinkOptionsWhenCreatingLink() const = 0;

	 /** 
		 Method to get preference for showing link options when creating linked story.
		 @return kTrue if link options will be shown while creating link else kFalse.
	 */ 
	 virtual OptionState GetShowLinkOptionsWhenCreatingLinkState() const = 0;

	/**
		Method which copies ILinkedStoryPlacePrefsData in input parameter 
		to ILinkedStoryPlacePrefsData on which this method is called.
		@param pCopyFrom [IN] input to copy from.
	*/
	virtual void CopyData(const ILinkedStoryPlacePrefsData *pCopyFrom) = 0;

	/**
		Method which copies preferences set in input parameter 
		to shared content(Linked Text) preferences.
		@param pCopyFrom [IN] input preferences to copy from.
	*/
    virtual void CopyPrefs(const ILinkedStoryPlacePrefs *pCopyFrom) = 0;

	/**
		Method to set shared content(Linked Text) preferences 
		to default value. 
	*/
	virtual void ResetState() = 0;
};

#endif
		// __ILinkedStoryPlacePrefsData__

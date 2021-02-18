//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/sharedcontent/ILinkedPageItemPrefsCmdData.h $
//  
//  Owner: Roey Horns
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
#ifndef __ILinkedPageItemPrefsCmdData__
#define __ILinkedPageItemPrefsCmdData__

#include "SharedContentID.h"
#include "IPMUnknown.h"

#include "GenericID.h"
#include "GraphicStylesID.h"
#include "GraphicsID.h"
#include "DynamicDocumentsID.h"
#include "ILinkedPageItemPrefs.h"

/** Data interface that stores the linked page items preferences to be used by the command.
*/

class ILinkedPageItemPrefsCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ILINKEDPAGEITEMPREFSCMDDATA };

		/* Enumerates the state of an option.
	   The option's value should not be accessed if the state is "kValueNotSet" or "kValueMixed".
	*/
	typedef enum
	{
		/* The  option is turned OFF*/
		kUnSet = 0,
		/* The  option is turned ON*/
		kSet,
		/* Do not change the option. This is the default */
		kDoNotChange,

	} OptionState;
		
			
		/**
			Method which copies preferences set in input parameter.
			@param pCopyFrom [IN] input preferences to copy from.
		*/
		virtual void CopyData(const ILinkedPageItemPrefs *pCopyFrom) = 0;
		
		/** Clear the preferences. Set to default.
		*/
		virtual void ResetState() = 0;

		virtual void SetOverridePathgeometry(OptionState bOverride) = 0;
		virtual void SetOverrideGraphicAttributes(OptionState bOverride) = 0;
		virtual void SetOverrideInteractiveAttributes(OptionState bOverride) = 0;
		virtual void SetOverrideContent(OptionState bOverride) = 0;
		virtual void SetOverrideOtherAttributes(OptionState bOverride) = 0;
		
		virtual OptionState GetOverridePathgeometry() = 0;
		virtual OptionState GetOverrideGraphicAttributes() = 0;
		virtual OptionState GetOverrideInteractiveAttributes() = 0;
		virtual OptionState GetOverrideContent() = 0;
		virtual OptionState GetOverrideOtherAttributes() = 0;

		/** 
		 Method to set preference for updating all out of date page item links on document save.
		 @param bUpdate [IN] kTrue if you want update on save else kFalse.
	 */ 
		virtual void SetUpdateLinkWhileSaving(OptionState bUpdate) = 0;

	 /** 
		 Method to get preference for updating all out of date page item links on document save.
		 @return kTrue if update on save is enabled else kFalse.
	 */ 
	 virtual OptionState GetUpdateLinkWhileSaving() const = 0;

	 /** 
		 Method to set preference for showing warning on update of edited
		 page item links.
		 @param bWarn [IN] kTrue if you want to show warning else kFalse.
	 */ 
	 virtual void SetShowWarningOnUpdateOfEditedPageItem(OptionState bWarn) = 0;

	 /** 
		 Method to get preference for showing warning on update of edited
		 page item links.
		 @return kTrue if warning on update is enabled else kFalse.
	 */ 
	 virtual OptionState GetShowWarningOnUpdateOfEditedPageItem() const = 0;
};

#endif

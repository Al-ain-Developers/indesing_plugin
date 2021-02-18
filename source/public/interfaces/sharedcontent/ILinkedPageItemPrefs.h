//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/sharedcontent/ILinkedPageItemPrefs.h $
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
#ifndef __ILinkedPageItemPrefs__
#define __ILinkedPageItemPrefs__

#include "SharedContentID.h"
#include "IPMUnknown.h"

#include "GenericID.h"
#include "GraphicStylesID.h"
#include "GraphicsID.h"
#include "DynamicDocumentsID.h"

/** Data interface that stores the linked page items preferences.
	@ingroup arch_coredata 
*/
class ILinkedPageItemPrefs : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ILINKEDPAGEITEMPREFS };
		
		/** Clear the preferences. Set to default.
		*/
		virtual void Clear() = 0;

		virtual void CopyData(const ILinkedPageItemPrefs* pCopyFrom) = 0;

		/** ILinkedPageItemPrefs maintains a list of PMIID's which are need to be 
			overriden while updation of page item Link

			Below are the API's to add, Remove & count PMIID's in the list.
		*/

		/** Add an interface ID to the list, if it does not already exists.
			@param id PMIID to add.
		*/
		virtual void AddInterfaceIDToOverride(PMIID id) = 0;

		/** Remove an interface ID from the list, if it exists.
			@param id PMIID to remove.
		*/
		virtual void RemoveInterfaceIDToOverride(PMIID id) = 0;

		/** Return the number of PMIIDs in the list.
		@return the number of PMIIDs.
		*/
		virtual int32 CountOverridenInterfaceID() const = 0 ;

		/** Return the nth interface ID.
			@return	The interfaceID
		*/
		virtual PMIID GetInterfaceID(int32 n) const = 0;

		/** Return whether a given interface ID exists in the list or not.
		@return	kTrue if id exists in the list, else return kFalse.
		*/
		virtual bool16 IsInterfaceIDAdded(PMIID id) const = 0;		

		/** 
		Method to set preference for updating all out of date page item links on document save.
		@param bUpdate [IN] kTrue if you want update on save else kFalse.
		*/ 
		virtual void SetUpdateLinkWhileSaving(bool16 bUpdate) = 0;

		/** 
			Method to get preference for updating all out of date page item links on document save.
			@return kTrue if update on save is enabled else kFalse.
		*/ 
		virtual bool16 GetUpdateLinkWhileSaving() const = 0;

		/** 
			Method to set preference for showing warning on update of edited
			page item links.
			@param bWarn [IN] kTrue if you want to show warning else kFalse.
		*/ 
		virtual void SetShowWarningOnUpdateOfEditedPageItem(bool16 bWarn) = 0;

		/** 
			Method to get preference for showing warning on update of edited
			page item links.
			@return kTrue if warning on update is enabled else kFalse.
		*/ 
		virtual bool16 GetShowWarningOnUpdateOfEditedPageItem() const = 0;
};

#endif

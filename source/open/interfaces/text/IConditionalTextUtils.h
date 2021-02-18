//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/text/IConditionalTextUtils.h $
//  
//  Owner: Michele Stutzman
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
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
#ifndef __IConditionalTextUtils__
#define __IConditionalTextUtils__

#include "IPMUnknown.h"
#include "ConditionalTextID.h"
#include "RequestContext.h"
#include "Utils.h"
#include "ITextFocus.h"

class IConditionalTextUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICONDITIONALTEXTUTILS };

	// Given a ref for document or text model, synchronize visiblity of text with current condition visible
	// states. Optionally, synchronizes only the conditions passed in the lists  (i.e. when apply a new condition set).
	virtual ErrorCode SynchronizeConditionalTextVisibility(const UIDRef& forRef, UIDList *hideTheseConditionsList = nil, UIDList *showTheseConditionsList = nil) = 0;
	
	/**
		Enum for specifying a hint for IsHiddenTextInSelection to use when the selection is an insertion point.
	*/
	enum HintForInsertionPoint
	{ 
		/** IsHiddenTextInSelection ignores. */
		kDontLook, 
		/** IsHiddenTextInSelection looks back. */
		kLookBack, 
		/** IsHiddenTextInSelection looks forward. */
		kLookForward 
	};

	/**
		Detect if there is hidden conditional text in the selection or at the insertion point.
		@param hintForIP How to detect if selection is an insertion point.
		@return kTrue is hidden condition text in selection.
	*/
	virtual bool16 IsHiddenTextInSelection(const ITextFocus* textFocus, HintForInsertionPoint hint = kDontLook) const = 0;

	/**
		Determines if user allows deleting hidden contional, displays alert asking user.
		@return kTrue is deleting is allowed.
	*/
	virtual bool16 AllowDeletingHiddenText() const = 0;

	/**
		Clears the specified conditions from the text state. If the condition is not being deleted then
		checks to see if there are other conditions applied and if so would the text remain visible in
		which case the condition is not cleared. If there are others applied and the text would not
		remain visible then they are cleared as well.
		@param conditions The list of conditions to clear from the text state.
		@param beingDeleted Whether or not the specified condition is being cleared due to deletion.
		@return kTrue If the condition was removed; otherwise, kFalse.
	*/
	virtual bool16 ClearFromTextState(const UIDList& conditions, bool16 beingDeleted) = 0;

	/*
		Determine if text would be visible if the specified condition's were applied.
		@param db The database for the conditions.
		@param testConditions UIDs of the conditions to check visibility.
		@return kTrue If the conditions were applied and text would be visible; otherwise, kFalse;
	*/
	virtual bool16 CheckIsVisible(IDataBase* db, const K2Vector<UID>& testConditions) = 0;

};

#endif	// __IConditionalTextUtils__

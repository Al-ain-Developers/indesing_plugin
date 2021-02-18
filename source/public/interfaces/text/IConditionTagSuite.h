//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IConditionTagSuite.h $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __IConditionTagSuite__
#define __IConditionTagSuite__

#include "ConditionalTextID.h"

/** Suite to manipulate condition tags for the current selection.
*/
class IConditionTagSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICONDITIONTAGSUITE };

	/**	This method gathers the condition tags that are applied to either all of the characters in
		the selection or that are applied to some of the characters in the selection.  These are
		returned in lists passed in by the callers.
		@param tagsAppliedToAllChars The condition tags applied to all of the characters.
		@param tagsAppliedToSomeChars The condition tags applied to some of the characters.
		@param rangeHasUnconditionalChars A pointer to bool for whether or not the range has characters that are unconditional (i.e. have no conditions applied).
		@return ErrorCode kSuccess unless an error occurred.
	 */
	virtual ErrorCode GetAppliedConditionTags(UIDList& tagsAppliedToAllChars, UIDList& tagsAppliedToSomeChars, bool16* rangeHasUnconditionalChars = nil) = 0;

	/**	Applies the specified condition tag(s) to the current selection.
		@param tagsToApply IN The condition tags to applied to the current selection.
		@param removeExisting IN Whether or not condition tags already applied are removed.
		@return ErrorCode kSuccess if operation could be completed successfully.
	 */
	virtual ErrorCode ApplyConditionTags(const K2Vector<UID>& tagsToApply, bool16 removeExisting) = 0;				
	
	/**	Determine whether or not the current selection can have a condition tag applied.
		@return bool16 kTrue if can apply condition tag to the selection.
	 */
	virtual bool16	CanApplyConditionTags() = 0;

	/**	Removes the specified condition tag(s) from the current selection.  Tags applied that are
		not in the specified list of condition tag(s) to be unapplied will remain applied.
		@param tagsToApply IN The condition tags to remove from the current selection.
		@return ErrorCode kSuccess if operation could be completed successfully.
	 */
	virtual ErrorCode UnapplyConditionTags(const K2Vector<UID>& tagsToUnapply) = 0;				
	
	/**	Determine whether or not the current selection can have a condition tag unapplied.
		@return bool16 kTrue if can unapply condition tag to the selection.
	 */
	virtual bool16	CanUnapplyConditionTags() = 0;
};

#endif // __IConditionTagSuite__

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/RunInStyleList.h $
//  
//  Owner: Eric_Menninga
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
#ifndef __RunInStyleList__
#define __RunInStyleList__

#include "WideString.h"
#include "K2Vector.h"

class IPMStream;


/**
	A description of a single run-in style, where a
	run-in style is an ordered application of character styles to text
	according to some simple rules. (next word, next sentence, etc).
	A paragraph will have a text attribute (kTextAttrRunInStylesBoss)
	specified by either a paragraph style or a locally applied attribute.
	This attribute contains a list of RunInStyleRule objects called
	a RunInStyleList.
	@see RunInStyleList
	@see ITextAttrRunInStyle
*/
class  RunInStyleRule
{
	public:
		typedef object_type		data_type;

		RunInStyleRule() : fCharacterStyle(kInvalidUID), fTriggerRegExp()
			{}

		RunInStyleRule(UID charstyle, const WideString& trigger)
				 : fCharacterStyle(charstyle), fTriggerRegExp(trigger)
			{}

		bool operator==(const RunInStyleRule&) const
			{ ASSERT_FAIL("appease K2Vector.Location"); return false; }

		/** Assign the rule that determines when to STOP applying the associated character style
				@param the trigger expression
				the format of the trigger expression should be: either  [x]n   or  (x)n
				-- if n is missing, "1" is assumed.
				-- if braces are missing, "()" is assumed
				where n = base-10 number (can be multi-digit)
				where x = list of characters, any of which will cause the expression to "succeed"
				where [] mean do NOT include the triggering character, and () means include it
				@see WideString
			*/
		void SetTriggerExpression(const WideString& s)
			{ fTriggerRegExp = s; }

			/** Is this rule a loop-back?
				@param pNextRuleIndex will be set to the next rule index specified by the loopback.
				@return kTrue if the rule is a loop-back rule.
			*/
		PUBLIC_DECL bool16 IsLoopbackStyleRule(int32 *pNextRuleIndex = nil) const;

			/** assign the character style associated with this run-in style
				@param character style UID
			*/
		void SetCharacterStyle(const UID& cs)
			{ fCharacterStyle = cs; }

			/** @return the character style associated with this run-in style */
		UID GetCharacterStyle() const
			{ return fCharacterStyle; }

			/** @return the trigger expression associated with this run-in style
				@see RunInStyleRule::SetTriggerExpression */
		const WideString& GetTriggerExpression() const
			{ return fTriggerRegExp; }

			/** read or write the single run-in style rule to the stream */
		PUBLIC_DECL void ReadWrite(IPMStream *stream);

			/** possible errors returned by RunInStyleRule::VerifyExpression() */
		typedef enum { kRI_NoError = 0, kRI_Empty, kRI_UnmatchedBraces, kRI_NoTrigger} RunInErrorType;

			/** verify that the trigger expression is considered legal
				@param the string to test
				@return error status of this test */
		PUBLIC_DECL static RunInErrorType VerifyExpression(const WideString& test);

	private:
		WideString	fTriggerRegExp;
		UID			fCharacterStyle;
};




/** A RunInStyleList is nothing more than a K2Vector of RunInStyleRules
	@see RunInStyleRule */
class RunInStyleList : public K2Vector<RunInStyleRule>
{
};

#endif
		//__RunInStyleList__

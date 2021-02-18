//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/RunInGrepStyleList.h $
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
#ifndef __RunInGrepStyleList__
#define __RunInGrepStyleList__

#include "WideString.h"
#include "K2Vector.h"

class IPMStream;


/**
	A description of a single grep-based style, where a
	grep-style is the application of a character style to text that matches
	a particular GREP expression.
	A paragraph will have a text attribute (kTextAttrGrepStylesBoss)
	specified by either a paragraph style or a locally applied attribute.
	This attribute contains a list of RunInGrepStyleRule objects called
	a RunInGrepStyleList.
	@see RunInGrepStyleList
	@see ITextAttrGrepStyle
*/
class  RunInGrepStyleRule
{
	public:
		typedef object_type		data_type;

		RunInGrepStyleRule() : fCharacterStyle(kInvalidUID), fGrepExp()
			{}

		RunInGrepStyleRule(UID charstyle, const WideString& trigger)
				 : fCharacterStyle(charstyle), fGrepExp(trigger)
			{}

		bool operator==(const RunInGrepStyleRule&) const
			{ ASSERT_FAIL("appease K2Vector.Location"); return false; }

			/** assign the character style associated with this run-in style
				@param character style UID
			*/
		void SetCharacterStyle(const UID& cs)
			{ fCharacterStyle = cs; }

			/** @return the character style associated with this run-in style */
		UID GetCharacterStyle() const
			{ return fCharacterStyle; }

			/** @return the GREP expression associated with this run-in style */
		WideString GetGrepExpression() const
			{ return fGrepExp; }

		void SetGrepExpression(const WideString& s)
			{ fGrepExp = s; }

			/** read or write the single run-in style rule to the stream */
		PUBLIC_DECL void ReadWrite(IPMStream *stream);

	private:
		WideString	fGrepExp;
		UID			fCharacterStyle;
};




/** A RunInStyleList is nothing more than a K2Vector of RunInGrepStyleRule
	@see RunInGrepStyleRule */
class RunInGrepStyleList : public K2Vector<RunInGrepStyleRule>
{
};

#endif
		//__RunInStyleList__

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/RunInLineStyleList.h $
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
#ifndef __RunInLineStyleList__
#define __RunInLineStyleList__

#include "WideString.h"
#include "K2Vector.h"

class IPMStream;


/**
	A description of a single line-based style, where a
	line-style is the application of a character style to some number
	of lines as determined by the composition engine.
	A paragraph will have a text attribute (kTextAttrLineStylesBoss)
	specified by either a paragraph style or a locally applied attribute.
	This attribute contains a list of RunInLineStyleRule objects called
	a RunInLineStyleList.
	@see RunInLineStyleList
	@see ITextAttrLineStyle
*/
class  RunInLineStyleRule
{
	public:
		typedef object_type		data_type;

		RunInLineStyleRule() : fCharacterStyle(kInvalidUID), fNumberLines(0)
			{}

		RunInLineStyleRule(UID charstyle, int32 n)
				 : fCharacterStyle(charstyle), fNumberLines(n)
			{}

		bool operator==(const RunInLineStyleRule&) const
			{ ASSERT_FAIL("appease K2Vector.Location"); return false; }

			/** assign the character style associated with this run-in style
				@param character style UID
			*/
		void SetCharacterStyle(const UID& cs)
			{ fCharacterStyle = cs; }

			/** @return the character style associated with this run-in style */
		UID GetCharacterStyle() const
			{ return fCharacterStyle; }

			/** assign the character style associated with this run-in style
				@param character style UID
			*/
		void SetNumberLines(int32 lines)
			{ fNumberLines = lines; }

			/** @return the character style associated with this run-in style */
		int32 GetNumberLines() const
			{ return fNumberLines; }

		bool IsLoopbackRule() const
			{ return (fCharacterStyle == kInvalidUID); }

			/** read or write the single run-in style rule to the stream */
		PUBLIC_DECL void ReadWrite(IPMStream *stream);

	private:
		UID			fCharacterStyle;
		int32		fNumberLines;
};




/** A RunInLineStylesList is nothing more than a K2Vector of RunInLineStyleRule.
	It is held in the ITextAttrLineStyle interface of the kTextAttrLineStylesBoss
	text attribute.
	@see RunInLineStyleRule */
class RunInLineStyleList : public K2Vector<RunInLineStyleRule>
{
};

#endif
		//__RunInStyleList__

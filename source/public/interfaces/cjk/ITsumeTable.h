//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ITsumeTable.h $
//  
//  Owner: nmccully
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
#ifndef __ITsumeTable__
#define __ITsumeTable__


#include "IPMUnknown.h"



/**
	Mojikumi aki and tsume are related: aki is the spacing the user sets for each character class,
	based on the widths _after_ tsume has been taken out. The tsume amount is the difference between
	the glyph width in the font and the width set by JIS X 4051 for that character, in em.
	Because of this dependency, tsume tables are attached to mojikumi tables, and accessing tsume amounts
	should be accomplished using IMojikumiTable::GetTsumeValue().
	
	@see IMojikumiTable
*/
class ITsumeTable : public IPMUnknown
{
	public:
			// methods to fill out the table
		/**  Clears all entries in the table
		*/
		virtual void Clear() = 0;
		/**  Sets the amount of left-side and right-side kerning for the given Unicode codepoint.
		@param c [IN] Unicode character
		@param before [IN] amount of left-side kerning in em units
		@param after [IN] amount of right-side kerning in em units
		*/
		virtual void SetTsume(UTF32TextChar c, const PMReal& before, const PMReal& after) = 0;
		/**  This method is called by the Mojikumi table when not using CID-based tsume. This table should not normally be accessed directly.
		@param c [IN] Unicode character
		@param before [OUT] amount of left-side kerning in em units
		@param after [OUT] amount of right-side kerning in em units
		@param isVertical [IN] is the tsume amount requested for use when the character is upright in vertical text
		*/
		virtual bool16 GetTsume(UTF32TextChar c, PMReal* before, PMReal* after, bool16 isVertical = kFalse) = 0;
		
		/** 
		@return kTrue if this Tsume table is editable/not a default table
		*/
		virtual bool16 GetEditability() const = 0;
		/**
		@param editability [IN] kTrue to set the table as user-editable
		*/
		virtual void SetEditability(bool16 editability) = 0;

		/**  Copies this table into another one
		@param to [IN/OUT] the table to copy this one into
		*/
		virtual void CopyTo(ITsumeTable *to) const = 0;
};



#endif
		// __ITsumeTable__
		
		

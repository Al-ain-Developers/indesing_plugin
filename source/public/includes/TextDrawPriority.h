//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TextDrawPriority.h $
//  
//  Owner: dwaterfa
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
#ifndef __TextDrawPriority__
#define __TextDrawPriority__

#include "DrawPassInfo.h"
#include "IPMStream.h"

//
// TextAdornments affect when they are called by the priority value they
// return via their GetDrawPriority() method. Higher priorities (smaller
// numbers) are called before lower priorities (larger numbers).
//
// In addition, drawing priorities are further broken down into two pieces -
// Pass (whole part) and Run (fractional part). For each unique Pass value
// across all the active adornments in a frame, a full iteration of the wax
// runs will be made calling all the adornments which share that pass value.
// Then, within each wax run, the adornments will be called based on their Run 
// priority.
//
namespace Text {

	const PMReal kTAMaxPassPri			= (Text::DrawPassInfo::kPassMax + 0.0);
	const PMReal kTAPassPriBackground	= (Text::DrawPassInfo::kPassBackground + 0.0);
	const PMReal kTAPassPriText			= (Text::DrawPassInfo::kPassText + 0.0);
	const PMReal kTAPassPriForeground	= (Text::DrawPassInfo::kPassForeground + 0.0);
	const PMReal kTAMinPassPri			= (Text::DrawPassInfo::kPassMin + 0.99998);

	//
	// Inner draw priority class to hide the implementation.
	//
	class DrawPriority {
	public:
		DrawPriority() : fVal(0)
		{ }
		DrawPriority(PMReal v)
		{
			if (v < kTAMaxPassPri)
				v = kTAMaxPassPri;
			else if (v > kTAMinPassPri)
				v = kTAMinPassPri;
			fVal = ToFixed(v);
		}

		DrawPriority(const DrawPriority& other)
		{ fVal = other.fVal; }
	
		DrawPriority& operator=(const DrawPriority& other)
		{ fVal = other.fVal; return *this; }

		bool16 operator==(const DrawPriority& other) const
		{ return (fVal == other.fVal); }
	
		bool16 operator<(const DrawPriority& other) const
		{ return (fVal < other.fVal); }
	
		bool16 operator>(const DrawPriority& other) const
		{ return (fVal > other.fVal); }
	
		Text::DrawPassInfo::Pass GetPass() const
		{ return (fVal / 65536); }

		void ReadWrite(IPMStream *s)
		{ s->XferInt32(fVal); }

		// Debug only.
		// To dump priority values of all adornments.
		#ifdef DEBUG
		int32 GetRunPriority() { return fVal % 65536; }
		#endif
	
	private:
		Fixed	fVal;
	};

}

#endif

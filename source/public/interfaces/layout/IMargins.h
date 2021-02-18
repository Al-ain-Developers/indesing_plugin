//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IMargins.h $
//  
//  Owner: Brendan O'Shea
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
#ifndef __IMARGINS__
#define __IMARGINS__

#include "IPMUnknown.h"
#include "MasterPageID.h"
#include "PMRect.h"
#include "SpreadID.h"

/** "Mixed" value for SetMargin calls to leave value unchanged. */
#define kMixedMargin	-1

/** Minimum value for a margin. */
#define kMinMargin		0

/**
	This interface is used to access the geometry information of page's margin.
	@ingroup layout_margin
	@see kPageBoss
*/
class IMargins : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMARGINS };

	/**
		Set a page's margins.

		@param insideLeft refers to inside (for facing pages case) or left margin.
		@param top refers to top margin.
		@param outsideRight refers to outside (for facing pages case) or right margin.
		@param bottom refers to bottom margin.
		@see kSetPageMarginsCmdBoss
	*/

	virtual void SetMargins
		(
			const	PMReal&	insideLeft,		/* inside (for facing pages case) or left margin */
			const	PMReal&	top,			/* top margin */
			const	PMReal&	outsideRight,	/* outside (for facing pages case) or right margin */
			const	PMReal&	bottom			/* bottom margin */
		) = 0;

	/**
		Get the margins for the page. All positive (or 0) numbers, values relative to page edge.

		@param marginRect refers to a rectangle holding four returned values(left/top/right/bottom).
		Note that the rectangle returned can be different in documents with
		two pages per spread based on the position of the page in the spread.
		@param wantMaster indicating return the margins of a master page.
		@see ILayoutUtils.h
		@see QueryMargins
	*/

	virtual void GetMargins(PMRect *marginRect, bool16 wantMaster = kTrue) = 0;

	/**
		Get the margins for the page. All positive (or 0) numbers, values relative to page edge.

		@param insideLeft refers to distance down from the top of page to the margin.
		@param top refers to distance up from the bottom of page to the margin.
		@param outsideRight refers to distance from left edge of page to the margin.
		@param bottom refers to distance from right edge of page to the margin.
		@param wantMaster indicating return the margins of a master page.
	*/

	virtual void GetMargins(PMReal* insideLeft, PMReal* top, PMReal* outsideRight, PMReal* bottom, bool16 wantMaster = kTrue) = 0;
	
	/**
		Check if margins are valid or just the default.

		@return bool16 kTrue = if SetMargins has been called; kFalse otherwise (i.e. the margin rects hold
		some value after). If not valid, master's margins are in effect.
	*/

	virtual bool16 MarginsAreValid() = 0;

	/**
		Set the margins to be valid or not for a page.
		On a regular page, if not valid, masters margins are in use.
		If valid, it means the margins have been overridden for that page.

		@param valid this could be either kTrue or kFalse.
		@see kSetPageMarginsValidCmdBoss
	*/

	virtual void SetMarginsAreValid(bool16 valid) = 0;
};

#endif

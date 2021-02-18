//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IMarginPrefs.h $
//  
//  Owner: psorrick
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
#ifndef __IMarginPrefs__
#define __IMarginPrefs__

#include "IPMUnknown.h"
#include "PMReal.h"
#include "SpreadID.h"

/** Abstract interface to margin preferences. This interface exists on both
	the session and document workspace.

	@ingroup layout_margin
	@see kPageBoss
	@see kSetMarginPrefsCmdBoss
*/
class IMarginPrefs : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IMARGINPREFERENCES };
	
	/**	Set the margins for default pages and new documents. 
		@param insideLeft refers to inside (for facing pages case) or left margin.
		@param top refers to top margin.
		@param outsideRight refers to outside (for facing pages case) or right margin.
		@param bottom refers to bottom margin.
	 */
	virtual void SetMargins(
			const	PMReal&	insideLeft,		/* inside (for facing pages case) or left margin */
			const	PMReal&	top,			/* top margin */
			const	PMReal&	outsideRight,	/* outside (for facing pages case) or right margin */
			const	PMReal&	bottom) = 0;	/* bottom margin */
	virtual void GetMargins(PMReal* insideLeft, PMReal* top, PMReal* outsideRight, PMReal* bottom) = 0;

	/**	Get the UI color index for the margins. DO NOT USE, used for conversion only.
		@return int32 index of the color in the IID_IUICOLORLIST.
	 */
	virtual int32 GetColorIndex_DURING_CONVERSION_ONLY() = 0;

	/**	Set the UI color by UID for the margins.
		@param uiColorUID the UID of the UI color to use for drawing the margin lines.
		@see IUIColorUtils.h
	 */
	virtual void SetColor(const UID uiColorUID) = 0;

	/**	Return the color to use for drawing margin lines.
		@return the UIDRef of the color from IID_IUICOLORLIST.
		@see IUIColorUtils.h
	 */
	virtual UIDRef GetColor() = 0;

	/** Tells that all margin values set from one value (top).
	    @param bUniform Whether to force all margin values to be uniform, using Top value.
	 */
	virtual void SetUseUniformMargins(bool16 bUniform) = 0;

	/** Tells whether all margin values are set from one value (top).
	 */
	virtual bool16 GetUseUniformMargins() = 0;

};

#endif

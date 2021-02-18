//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IMarginPrefsCmdData.h $
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
//  
//  Data interface for Margin prefs commands.
//  includes : 	Margin rect
//  
//========================================================================================

#pragma once
#ifndef __IMarginPrefsCmdData__
#define __IMarginPrefsCmdData__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "UIDRef.h" 
#include "PMReal.h"

class IDataBase;

/** Command data interface associated with commands to manipulate margin preferences.

	@ingroup layout_margin
	@see IMargins
	@see kSetMarginPrefsCmdBoss

*/
class IMarginPrefsCmdData : public IPMUnknown
{
public:
	virtual void Set(	const	UIDRef&	doc, 			/* which document to affect */
						const	PMReal&	insideLeft,		/* inside (for facing pages case) or left margin */
						const	PMReal&	top,			/* top margin */
						const	PMReal&	outsideRight,	/* outside (for facing pages case) or right margin */
						const	PMReal&	bottom,			/* bottom margin */
						const   int32& colorIndex = -1) = 0;
	virtual const UIDRef& GetDocument() const = 0;
	virtual void GetMargins(PMReal* insideLeft, PMReal* top, PMReal* outsideRight, PMReal* bottom) = 0;
	virtual const int32&  GetColorIndex() const = 0;

	/**    Tells that all margin values set from one value (top).
	    @param bUniform Whether to force all margin values to be uniform, using Top value.
	 */
	virtual void SetUseUniformMargins(bool16 bUniform) = 0;

	/**    Tells whether all margin values are set from one value (top).
	 */
	virtual bool16 GetUseUniformMargins() const = 0;
	
};


#endif // __IMarginPrefsCmdData__

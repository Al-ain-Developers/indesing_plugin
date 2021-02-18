//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IKRAdornmentData.h $
//  
//  Owner: rkamicar
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
#ifndef __IKRAdornmentData__
#define __IKRAdornmentData__

#include "IPMUnknown.h"

class IWaxRun;
class IPMFont;


/** Common interface for Kenten/Ruby IAdornmentData - they look pretty much the same once they are composed and
	their wax is built. This interface provides common code with a mechanism to deal with the common
	data elements of their specific adornment data.
	@ingroup text_adorn
*/
class IKRAdornmentData : public IPMUnknown
{
public:
	/** Is there kenten or ruby on this run?
	@return true if there is kenten
	*/
	virtual bool16 IsFeatureOn() const = 0;

	/** Number of characters in adorned base text run
	@return number of characters
	*/
	virtual int32 GetLength() const = 0;

	/** Custom impl of QueryFont for kenten or ruby font
	@param database of current pub
	@return kenten font
	*/
	virtual IPMFont* QueryFont(IDataBase *db) const = 0;

	/** Some code (PDF) requires access to the waxRun and waxLine so it can, for instance, convert to
	pasteboard coordinates or reference the containing parcel/frame.
	Since we are really associated with the baseText WaxRun/Line, that's what it'll want.
	@return base text IWaxRun
	*/
	virtual IWaxRun* QueryBaseTextRun() const = 0;

	/** Attaches this adornment to a base text IWaxRun
	@param baseTextWaxRun IN wax run to attach to
	*/
	virtual void SetBaseTextRun(IWaxRun* baseTextWaxRun) = 0;

	/** Splits adornment into two at offset
	@param other OUT ptr to split off adornment
	@param offsetInRun IN offset into base text run to split at
	@return true if split occurred
	*/
	virtual bool16 SplitInto(IKRAdornmentData* other, int32 offsetInRun) = 0;
};

#endif


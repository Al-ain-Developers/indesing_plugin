//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IMediaAdornmentInfo.h $
//  
//  Owner: wtislar
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
#ifndef __IMediaAdornmentInfo__
#define __IMediaAdornmentInfo__

#include "IPMUnknown.h"

#include "MediaID.h"
#include "PMString.h"

/**
	This is a call-back interface that provides information for constructing adornments
	that appear on media frames.

	If a media frame requires adornments, this interface should be aggregated by the
	media page item boss.
*/

class IMediaAdornmentInfo : public IPMUnknown
{
public:

	enum { kDefaultIID = IID_IMEDIAADORNMENTINFO };

	/** Retrieves the ClassID of the adornment that appears at the bottom of the frame.
		@return a valid ClassID if there is a bottom adornment; return kInvalidClass if
		no bottom adornment.
	*/
	virtual ClassID GetBottomAdornmentClassID() const = 0;

	/** Retrieves the name that displays as part of the adornment.
		@return a PMString containing the name.
	*/
	virtual const PMString GetName() const = 0;

	/** Retrieves the ClassID of the adornment that appears at the top of the frame.
		@return a valid ClassID if there is a top adornment; return kInvalidClass if
		no top adornment.
	*/
	virtual ClassID GetTopAdornmentClassID() const = 0;

}; // end IMediaAdornmentInfo interface

#endif // __IMediaAdornmentInfo__
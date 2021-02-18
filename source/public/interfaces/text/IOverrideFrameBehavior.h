//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IOverrideFrameBehavior.h $
//  
//  Owner:
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
//  Purpose: Provides access to footnote content in an opaque wrapper.
//  
//========================================================================================

#pragma once
#ifndef __IOverrideFrameBehavior__
#define __IOverrideFrameBehavior__

#include "IPMUnknown.h"
#include "TextID.h"

/**
	IOverrideFrameBehavior is a hack will affect vertical justification -- allowing it to run on non-rectangular frames by
	pretending the lines can actually be slid up and down in the frame.  This interface does not have an implementation,
	but is provided for possible use by third parties. Very dangerous and hacky, but can allow certain types of VJ to work.
*/
class IOverrideFrameBehavior : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IOVERRIDEFRAMEBEHAVIOR };

		/** TreatFrameAsRectangular -- override standard behavior for this text frame
			@return kTrue if you want the text frame to ignore its actual shape are report being rectangular.
				this hack will affect vertical justification -- allowing it to run on non-rectangular frames by
				pretending the lines can actually be shifted up and down.  This interface .
		*/
	virtual bool16 TreatFrameAsRectangular() const = 0;

};

#endif
		// __IOverrideFrameBehavior__


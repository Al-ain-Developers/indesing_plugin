//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IBulletsAndNumberingSuite.h $
//  
//  Owner: Anurag Wahi
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

#ifndef __IBulletsAndNumberingSuite__
#define __IBulletsAndNumberingSuite__

#include "BNTextAttrID.h" // For IID_IBULLETSANDNUMBERINGSUITE

/**
	IBulletsAndNumberingSuite represents the Bullets and Numbering selection suite that gets added to text, unthreaded 
	text frames and other selection bosses.
*/
class IBulletsAndNumberingSuite: public IPMUnknown
{
public:
    enum { kDefaultIID = IID_IBULLETSANDNUMBERINGSUITE };

    /**
        Checks whether the paragraph style passed as a parameter has bullets or numbering enabled.

		@param styleRef represents a UIDRef to a style
        @return kTrue if the style has bullets and numbering enabled, kFalse otherwise.
     */
	virtual bool16 DoesStyleApplyBulletsOrNumbering(const UIDRef &styleRef) const = 0;

    /**
        Converts the bullet or number in the specified paragraph style to text.

		@param styleRef represents a UIDRef to a style
        @return kSuccess if successful, kFailure otherwise.
     */
	virtual ErrorCode ConvertStyleBulletsAndNumberingToText(const UIDRef &styleRef) = 0;
};

#endif    // __IBulletsAndNumberingSuite__

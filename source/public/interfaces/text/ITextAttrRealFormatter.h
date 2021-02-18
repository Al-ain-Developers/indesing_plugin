//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrRealFormatter.h $
//  
//  Owner: Rich Gartland
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
 #ifndef __ITextAttrRealFormatter__
 #define __ITextAttrRealFormatter__

#include "IPMUnknown.h"

class PMReal;
class PMString;

/** Interface for formatting real numbers.
	@ingroup text_attr
*/
class ITextAttrRealFormatter : public IPMUnknown
{
	public:
		/** Convert the real number into a string, usually with the appropriate units added.
		@ The displayed units often depend on the Measurement properties.  The value is always treated as points.
		@see IMeasurementType, IMeasurementSystem, IUnitOfMeasure
		*/
		virtual void GetFormattedValueString(PMReal value, PMString *theString) const = 0;

};

#endif		// __ITextAttrRealFormatter__

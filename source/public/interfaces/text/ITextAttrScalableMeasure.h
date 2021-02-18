//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrScalableMeasure.h $
//  
//  Owner: Shawn Sheridan
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
#ifndef __ITextAttrScalableMeasure__
#define __ITextAttrScalableMeasure__

#include "IPMUnknown.h"
#include "TextAttrID.h"
#include "AttributeBossList.h"


/** Interface to scale a text attribute.
	@ingroup text_attr
*/
class ITextAttrScalableMeasure : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRSCALABLEMEASURE };
		/** Attribute independent interface to scale a text attribute.  The implementation should pick the appropriate arguments
				(not all may apply), scale the attribute and add it to the attrList.
		@param attrList INOUT The list of attributes to which the scaled attribute should be applied.
		@param xScale IN Scale in the x-direction.
		@param yScale IN Scale in the y-direction.
		@param isVertical IN Does the STORY text flow vertically?  I.e. does the main text flow vertically?
		@param isVerticalWritingMode IN Does THIS text flow vertically?  Some text, although in a vertical story, may actually be horizontally drawn. (c.f. TCY).
		@param scaleAffectsLineHeight IN Should the scale affect the line height, when appropriate?

		@note Not all parameters apply to all attributes (e.g. attributes using the kTextAttrScalableYMeasureImpl implementation ignores all but the yScale parameter)
		*/
		virtual void ScaleMeasure(AttributeBossList *attrList, PMReal xScale, PMReal yScale,
									bool16 isVertical, bool16 isVerticalWritingMode, bool16 scaleAffectsLineHeight) const = 0;

};

#endif

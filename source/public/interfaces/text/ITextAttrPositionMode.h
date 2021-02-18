//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrPositionMode.h $
//  
//  Owner: zwilliam
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
#ifndef __ITextAttrPositionMode__
#define __ITextAttrPositionMode__

#include "IPMUnknown.h"
#include "IDrawingStyle.h"
#include "TextAttrID.h"

/**	ITextAttrPositionMode is a simple data interface that is used to hold the
	desired position mode: normal, superscript, subscript, and the opentype features
	superior, inferior, numerator, denominator.
	The underlying character values are unchanged, but a different baseline & size
	may be used, or different glyphs used in the opentype cases.
	@ingroup text_attr
	@see IDrawingStyle
*/
class ITextAttrPositionMode : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRPOSITIONMODE };

		typedef IDrawingStyle::PositionMode		ValueType;

		/** Set the value.
			@param flag specifies the position mode.
		*/
		void Set(ValueType flag)
			{ SetMode(flag); }
		/** Get the value.
			@return the position mode.
		*/
		ValueType Get() const
			{ return GetMode(); }

		/** Set the value.
			@param pm specifies the position mode.
		*/
		virtual void SetMode(IDrawingStyle::PositionMode pm) = 0;
		/** Get the value.
			@return the position mode.
		*/
		virtual IDrawingStyle::PositionMode GetMode() const = 0;
};

#endif
		// __ITextAttrPositionMode__


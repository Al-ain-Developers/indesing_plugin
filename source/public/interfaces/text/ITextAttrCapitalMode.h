//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrCapitalMode.h $
//  
//  Owner: emenning
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
#ifndef __ITextAttrCapitalMode__
#define __ITextAttrCapitalMode__

#include "IPMUnknown.h"
#include "IDrawingStyle.h"
#include "TextAttrID.h"


/**	ITextAttrCapitalMode is a simple data interface that is used to hold the
	desired capitalization style: All-cap, small-cap, normal, all small-cap.
	The underlying character values are unchanged, but different glyphs may be drawn.
	OpenType font features are used for all small-cap and small-cap.
	We will fake small-cap buy not all small-cap at this time.
	OpenType fonts will be told to apply 'case' and 'cpsp' when All-cap is used.
	@ingroup text_attr
	@see IDrawingStyle
*/
class ITextAttrCapitalMode : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRCAPITALMODE };

		typedef IDrawingStyle::CapitalizeMode		ValueType;

		/** Set the value.
			@param flag specifies the capitalization mode.
		*/
		void Set(ValueType flag)
			{ SetMode(flag); }
		/** Get the value.
			@return the capitalization mode.
		*/
		ValueType Get() const
			{ return GetMode(); }

		/** Set the value.
			@param cm specifies the capitalization mode.
		*/
		virtual void SetMode(IDrawingStyle::CapitalizeMode cm) = 0;
		/** Get the value.
			@return the capitalization mode.
		*/
		virtual IDrawingStyle::CapitalizeMode GetMode() const = 0;
};

#endif
		// __ITextAttrCapitalMode__


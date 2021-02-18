//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrUnderlineMode.h $
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
#ifndef __ITextAttrUnderlineMode__
#define __ITextAttrUnderlineMode__

#include "IPMUnknown.h"
#include "IDrawingStyle.h"
#include "TextAttrID.h"

/** 
	A holds the underline mode value for the underline text attribute
	@ingroup text_attr
*/
class ITextAttrUnderlineMode : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRUNDERLINEMODE };

		typedef IDrawingStyle::UnderlineMode		ValueType;

		/**
			Sets the underline mode to the param passed in
			@param flag		IDrawingStyle::UnderlineMode
		*/
		void Set(ValueType flag)
			{ SetMode(flag); }
		/**
			Gets the underline mode
			@return 	IDrawingStyle::UnderlineMode
		*/
		ValueType Get() const
			{ return GetMode(); }

		/**
			Sets the underline mode to the param passed in
			@param flag		IDrawingStyle::UnderlineMode
		*/
		virtual void SetMode(IDrawingStyle::UnderlineMode um) = 0;
		/**
			Gets the underline mode
			@return 	IDrawingStyle::UnderlineMode
		*/
		virtual IDrawingStyle::UnderlineMode GetMode() const = 0;
};

#endif
		// __ITextAttrUnderlineMode__

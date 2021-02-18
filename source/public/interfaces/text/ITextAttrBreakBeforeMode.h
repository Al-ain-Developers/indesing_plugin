//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrBreakBeforeMode.h $
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
#ifndef __ITextAttrBreakBeforeMode__
#define __ITextAttrBreakBeforeMode__

#include "CTextEnum.h"
#include "TextAttrID.h"


/** 
	ITextAttrBreakMode is a simple data interface that is used to hold the
	desired break mode which influences where the paragraph composes:
	Text::kNoForcedBreak, Text::kAtColumn, Text::kAtPage, Text::kAtFrameBox,
	Text::kAtOddPage and Text::kAtEvenPage.
	@ingroup text_attr
*/
class ITextAttrBreakBeforeMode : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRBREAKBEFOREMODE };
		
		typedef Text::StartBreakLocation	ValueType;

		/**
		Set the value
		@param flag specifies the break mode
		*/
		void Set(ValueType flag)
			{ SetBreakMode(flag); }

		/**
		Get the value
		@return the break mode
		*/
		ValueType Get() const
			{ return GetBreakMode(); }

		/**
		Set the value
		@param breakModel specifies the break mode
		*/
		virtual void SetBreakMode(ValueType breakMode) = 0;

		/**
		Get the value
		@return the break mode
		*/
		virtual ValueType GetBreakMode() const = 0;

};

#endif

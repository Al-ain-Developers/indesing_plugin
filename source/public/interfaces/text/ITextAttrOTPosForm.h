//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrOTPosForm.h $
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
#ifndef __ITextAttrOTPosForm__
#define __ITextAttrOTPosForm__

#include "IPMUnknown.h"
#include "IDrawingStyle.h"
#include "TextAttrID.h"


/**	ITextAttrOTPosForms is a simple data interface that is used to hold the
	desired opentype position form: Off, Auto, Initial, Medial, Final, Isolated.
	@ingroup text_attr
	@see IDrawingStyle
*/
class ITextAttrOTPosForm : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTROTPOSITIONFORM };

		typedef IDrawingStyle::OTPositioningForm		ValueType;

		/** Set the value.
			@param cm specifies the OpenType position forms mode.
		*/
		virtual void Set(IDrawingStyle::OTPositioningForm cm) = 0;

		/** Get the value.
			@return the OpenType position form.
		*/
		virtual IDrawingStyle::OTPositioningForm Get() const = 0;
};

#endif
		// __ITextAttrOTPosForm__


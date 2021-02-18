//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ITextAttrGlyphForm.h $
//  
//  Owner: hlynn
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
#ifndef __ITextAttrGlyphForm__
#define __ITextAttrGlyphForm__

#include "IPMUnknown.h"
#include "K2Vector.h"
#include "OTFeature.h"
#include "CJKID.h"


/** @see IGlyphUtils for utilities to convert between GlyphForm and OpenTypeFeature tags.
*/


class ITextAttrGlyphForm : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRGLYPHFORM };
		enum GlyphForm {
			kFirstForm,
			kNoForm = kFirstForm,
			kFirstValidForm,
			kTraditionalForm = kFirstValidForm,
			kExpertForm,
			kJIS78Form,
			kJIS83Form,
			kHalfWidthForm,
			kThirdWidthForm,
			kQuarterWidthForm,
			kNLCForm,
			kProportionalWidthForm,
			kFullWidthForm,
			kJIS04Form,
			kJIS90Form,
			kBeyondEndForm
		};

		typedef ITextAttrGlyphForm::GlyphForm		ValueType;

		/**	GlyphFormIsKnown
			@return	true if the glyph form is known (i.e., < ITextAttrGlyphForm::kBeyondEndForm)
		*/
			virtual
			bool
		IsKnown() const
			= 0;

			virtual
			int32
		ToFeatureInt() const
			= 0;

		/**	ToFeatureChars
			@return	The OpenType feature tag corresponding to this object, represented as characters.
		*/
			virtual
			const char *
		ToFeatureChars() const
			= 0;
			
		/**	GetDescriptiveString
			@return	The description string for the glyph form.
		*/
			virtual
			const char *
		GetDescriptiveString() const
			= 0;

		/**	SetGlyphForm
			@param	gf IN, the GlyphForm (enum)
		*/
		virtual void SetGlyphForm(GlyphForm gf) = 0;
		/** Set -- same as SetGlyphForm()
		@param val [IN] the glyph form
		*/
		virtual void Set(ValueType val)
			{ SetGlyphForm(val); }
		/** GetGlyphForm
			@return	the GlyphForm (enum)
		*/
		virtual GlyphForm GetGlyphForm() const = 0;
		/** Get -- same as GetGlyphForm()
			@return	the GlyphForm (enum)
		*/
		virtual ValueType Get() const
			{ return GetGlyphForm(); }
};


 #endif
		// __ITextAttrGlyphForm__

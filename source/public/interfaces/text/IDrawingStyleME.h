//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IDrawingStyleME.h $
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
//  ADOBE CONFIDENTIAL
//  
//  Usage rights licenced to Adobe Inc. 1993 - 2007.
//  
//========================================================================================

#pragma once
#ifndef __IDrawingStyleME__
#define __IDrawingStyleME__

#include "IPMUnknown.h"
#include "WorldReadyID.h"
#include "IHindiDigitsAttr.h"
#include "IDirOverrideAttr.h"

/**
	IDrawingStyleME is the primary interface of character attribute ME summary data.
	Text attributes can be summarized into a kComposeStyleBoss object, which is a non-persistent
	summary of every text attribute applied to some text. IDrawingStyleME lists most, but not all
	character attributes specific to the world ready composer: kashida preference, digit preference, etc.
	IDrawingStyleME should be considered a "read-only" interface because the set operations have no
	impact beyond this data interface. It does not apply through to the text that this interface derived from.
	The text attributes themselves are the primary setters of the data.
	@see IDrawingStyle
	@ingroup text_comp_style
*/
class IDrawingStyleME : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDRAWINGSTYLEME };

		/** Set the digits used by the world ready composer.
		@param val is the digit type.
		@see IDigitsAttr.
		*/
		virtual void SetDigits(IDigitsAttr::Digits digits) = 0;
		/** Get the digits used by the world ready composer.
		@return the digit type.
		@see IDigitsAttr.
		*/
		virtual IDigitsAttr::Digits GetDigits() const = 0;

		/** Set the kashida preference for the world ready composer.
		@param kashida is the kashida preference.
		@see IKashidaAttr.
		*/
		virtual void	SetKashida(int32 kashida) = 0;
		/** Get the kashida preference for the world ready composer.
		@return the kashida preference.
		@see IKashidaAttr.
		*/
		virtual int32	GetKashida() const = 0;

		/** Set the character direction override for the world ready composer.
		@param dir is the direction override.
		@see IDirOverrideAttr.
		*/
		virtual void	SetDirOverride(IDirOverrideAttr::DirOverride dir) = 0;
		/** Get the character direction override for the world ready composer.
		@return the direction override.
		@see IDirOverrideAttr.
		*/
		virtual IDirOverrideAttr::DirOverride	GetDirOverride() const = 0;

		/** GetNarrowHardSpaceWidth is used to override the space width for Farsi.
		@return the width of the non-breaking space.
		*/
		virtual PMReal	GetNarrowHardSpaceWidth(bool16 vertical) const = 0;

		/** Set the diacritic vertical position preference.
		@param vpos is the diacritic's vertical position preference.
		@see IDiacVPosAttr.
		*/
		virtual void	SetDiacVPos(int32 vpos) = 0;
		/** Get the diacritic vertical position preference.
		@return the diacritic's vertical position preference.
		@see IDiacVPosAttr.
		*/
		virtual int32	GetDiacVPos() const = 0;

		/** Set the diacritic x position offset from the default location.
		@param r is the x-offset for diacritics.
		*/
		virtual void	SetDiacXOffset(PMReal r) = 0;
		/** Get the diacritic x position offset from the default location.
		@return the x-offset for diacritics.
		*/
		virtual PMReal	GetDiacXOffset() const = 0;

		/** Set the diacritic y position offset from the default location.
		@param r the y-offset for diacritics.
		*/
		virtual void	SetDiacYOffset(PMReal r) = 0;
		/** Get the diacritic y position offset from the default location.
		@return the y-offset for diacritics.
		*/
		virtual PMReal	GetDiacYOffset() const = 0;

		/** the composer sets this when the base font of a complementary font
			is missing in the world ready composer. Should not be set otherwise.
		*/
		virtual void	SetBaseFontMissing(bool16 b) = 0;
		/** the composer sets this when the base font of a complementary font
			is missing in the world ready composer. Should not be set otherwise.
		*/
		virtual bool16	IsBaseFontMissing() const = 0;

		/** Set the keyboard direction (right-to-left or left-to-right).
		@param dir is the direction of the keyboard.
		@see IDirOverrideAttr.
		*/
		virtual void	SetKeyboardDir(IDirOverrideAttr::DirOverride dir) = 0;
		/** Get the keyboard direction (right-to-left or left-to-right).
		@return the direction of the keyboard.
		@see IDirOverrideAttr.
		*/
		virtual IDirOverrideAttr::DirOverride	GetKeyboardDir() const = 0;

		/** GetEffectiveCharDir consolidates the paragraph direction
		with the character direction override.
		@return the character's direction.
		*/
		virtual IDirOverrideAttr::DirOverride	GetEffectiveCharDir() const = 0;

#ifdef ID_DEPRECATED
		/** these don't appear to be used anywhere
		*/
		virtual void	SetGlyphScaleX(PMReal scale) = 0;
		/** these don't appear to be used anywhere
		*/
		virtual void	SetGlyphScaleY(PMReal scale) = 0;
#endif

};

#endif
	// __IDrawingStyleME__


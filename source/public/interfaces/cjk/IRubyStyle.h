//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IRubyStyle.h $
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
//========================================================================================

#pragma once
#ifndef __IRubyStyle__
#define __IRubyStyle__


#include "IPMUnknown.h"
#include "ICompositionStyle.h"
#include "PMPoint.h"
#include "CJKID.h"

#define kInvalidFontSize -1.0
class WideString;

/**
	IRubyStyle is the primary interface of character attributes for ruby summary data.
	@see IDrawingStyle
	@ingroup text_comp_style
*/
class IRubyStyle : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IRUBYSTYLE };


		//Ruby attributes

		/** RubyKind
		*/
		enum RubyKind {
				kRubyKind_Group = 0,			// Group ruby
				kRubyKind_Mono					// Mono ruby
			};

		/** RubyPosition
		*/
		enum RubyPosition {
				kRubyPosition_TopRight = 0,		// Horizontal: Top		Vertical: Right
				kRubyPosition_BottomLeft		// Horizontal: Bottom 	Vertical: Left
			};

		/** RubyOverHang
		*/
		enum RubyOverHang {
				kRubyOverHang_None = 0,		// None
				kRubyOverHang_OneRuby,		// One width of Ruby character
				kRubyOverHang_HalfRuby,		// Half width of Ruby character
				kRubyOverHang_OneChar,		// One width of Parent character
				kRubyOverHang_HalfChar,		// Half width of Parent character
				kRubyOverHang_NoLimit
			};

		/** RubyAdjustParent
		*/
		enum RubyAdjustParent {
				kRubyAdjustParent_None = 0,	// None
				kRubyAdjustParent_BothSide,	// Add space both side of parent characters.
				kRubyAdjustParent_Mojikumi,	// Add space 1:2:1 in parent characters.
				kRubyAdjustParent_EqualAki,	// Add space 1:1:1 in parent characters.
				kRubyAdjustParent_Justify	// Full Justify.
			};

		/** RubyAlign
		*/
		enum RubyAlign {
				kRubyAlign_Left = 0,		// Left alignment
				kRubyAlign_Center,			// Center alignment
				kRubyAlign_Right,			// Right alignment
				kRubyAlign_Justify,			// Full Justify
				kRubyAlign_JISRule,			// 1:2:1
				kRubyAlign_EqualSpace,		// 1:1:1
				kRubyAlign_EdgeOneRuby		// add one width of ruby character. (both side)
			};

		//
		// Composition section	-----------------------------------------------------------------------------------------------------------
		//

		/** Set whether Ruby is on/off
		@param the attribute.
		@note: obsolete.  Ruby on/off is now determined strictly by the RubyString attribute. (if the string is empty, it's off, otherwise on)
		*/
		virtual void SetRubyFlag(bool16	flag) = 0;
		/** Get whether Ruby is on/off
		@return the attribute.
		@note: obsolete.  Ruby on/off is now determined strictly by the RubyString attribute. (if the string is empty, it's off, otherwise on)
		*/
		virtual bool16 GetRubyFlag() const = 0;
		/** Set the Ruby string - this is the text that will appear as ruby
		@param the attribute.
		*/
		virtual void SetRubyString(const WideString& str) = 0;
		/** Get the Ruby string - this is the text that will appear as ruby
		@return the attribute.
		*/
		virtual const WideString& GetRubyString() const = 0;
		/** Set the Ruby kind
		@param the attribute.
		*/
		virtual void SetRubyKind(RubyKind kind) = 0;
		/** Get the Ruby kind
		@return the attribute.
		*/
		virtual RubyKind GetRubyKind() const = 0;
		/** Set the Ruby position
		@param the attribute.
		*/
		virtual void SetRubyPosition(RubyPosition flag) = 0;
		/** Get the Ruby position
		@return the attribute.
		*/
		virtual RubyPosition GetRubyPosition() const = 0;
		/** Set whether or not Ruby is continued. kTrue when style is not on the first base text character.
		@param the attribute.
		*/
		virtual void SetRubyContinued(bool16 flag) = 0;
		/** Get whether or not Ruby is continued. kTrue when style is not on the first base text character.
		@return the attribute.
		*/
		virtual bool16 GetRubyContinued() const = 0;

		// When ruby length exceeds base text length	-----------------------------------------------------------------------------------

		// Overhang	----------------------------------------------------------------------------------------------------------------------

		/** Set whether Ruby will overhang or not
		@param the attribute.
		*/
		virtual void SetRubyOverHangFlag(bool16 flag) = 0;
		/** Get whether Ruby will overhang or not
		@return the attribute.
		*/
		virtual bool16 GetRubyOverHangFlag() const = 0;
		/** Set whether Ruby will over hang and by how much
		@param the attribute.
		*/
		virtual void SetRubyOverHang(RubyOverHang hang) = 0;
		/** Get whether Ruby will over hang and by how much
		@return the attribute.
		*/
		virtual RubyOverHang GetRubyOverHang() const = 0;

		// Scaling	--------------------------------------------------------------------------------------------------------------------------

		/** Set whether Ruby text will scale or not
		@param the attribute.
		*/
		virtual void SetRubyAutoScaling(bool16 flag) = 0;
		/** Get whether Ruby text will scale or not
		@return the attribute.
		*/
		virtual bool16 GetRubyAutoScaling() const = 0;

		/** Set the minimum amount of scaling that will occur.
		@param the attribute.
		*/
		virtual void SetRubyAutoScaleMinimum(PMReal min) = 0;
		/** Get the minimum amount of scaling that will occur.
		@return the attribute.
		*/
		virtual PMReal GetRubyAutoScaleMinimum() const = 0;

		// Base text tracking	-----------------------------------------------------------------------------------------------------------

		/** Set whether Ruby will adjust spacing before/after and between parent characters and by how much.
		@param the attribute.
		*/
		virtual void SetRubyAdjustParent(RubyAdjustParent adjust) = 0;
		/** Get whether Ruby will adjust spacing before/after and between parent characters and by how much.
		@return the attribute.
		*/
		virtual RubyAdjustParent GetRubyAdjustParent() const = 0;
		/** Set whether Ruby will change the position of the base text when it's on the edge of a line or adjacent to some specific characters/attributes.
		@param the attribute.
		*/
		virtual void SetRubyEdgeAdjustment(bool16 flag) = 0;
		/** Get whether Ruby will change the position of the base text when it's on the edge of a line or adjacent to some specific characters/attributes.
		@return the attribute.
		*/
		virtual bool16 GetRubyEdgeAdjustment() const = 0;

		// When ruby length is shorter than base text.	-------------------------------------------------------------------------------

		/** Set the Ruby Alignment
		@param the attribute.
		*/
		virtual void SetRubyAlignment(RubyAlign align) = 0;
		/** Get the Ruby Alignment
		@return the attribute.
		*/
		virtual RubyAlign GetRubyAlignment() const = 0;

		// Ruby body position	--------------------------------------------------------------------------------------------------------------
		/** Set the offset of the ruby text in the X-direction
		@param the attribute.
		*/
		virtual void SetRubyXOffset(PMReal r) = 0;
		/** Get the offset of the ruby text in the X-direction
		@return the attribute.
		*/
		virtual PMReal GetRubyXOffset() const = 0;
		/** Set the offset of the ruby text in the Y-direction
		@param the attribute.
		*/
		virtual void SetRubyYOffset(PMReal r) = 0;
		/** Get the offset of the ruby text in the Y-direction
		@return the attribute.
		*/
		virtual PMReal GetRubyYOffset() const = 0;

		//
		// Drawing section	--------------------------------------------------------------------------------------------------------------
		//

		// Ruby Font family	--------------------------------------------------------------------------------------------------------------
		/** Set the font to be used for Ruby text.
		@param the attribute.
		*/
		virtual void SetRubyFontUID(UID u) = 0;
		/** Get the font to be used for Ruby text.
		@return the attribute.
		*/
		virtual UID GetRubyFontUID() const = 0;
		/** Set the Font Style name to be used for Ruby text
		@param the attribute.
		*/
		virtual void SetRubyFontStyleName(const PMString& name) = 0;
		/** Get the Font Style name to be used for Ruby text
		@return the attribute.
		*/
		virtual const PMString& GetRubyFontStyleName() const = 0;
		/** Set the size of the ruby text
		@param the attribute.
		*/
		virtual void SetRubyFontSize(PMReal p) = 0;
		/** Get the size of the ruby text
		@return the attribute.
		*/
		virtual PMReal GetRubyFontSize() const = 0;
		/** Set the relative size of the ruby text.
		@param the attribute.
		*/
		virtual void SetRubyRelativeSize(PMReal p) = 0;
		/** Get the relative size of the ruby text.
		@return the attribute.
		*/
		virtual PMReal GetRubyRelativeSize() const = 0;
		/** Set the scaling of the ruby text in the X-direction
		@param the attribute.
		*/
		virtual void SetRubyXScale(PMReal scale) = 0;
		/** Get the scaling of the ruby text in the X-direction
		@return the attribute.
		*/
		virtual PMReal GetRubyXScale() const = 0;
		/** Set the scaling of the ruby text in the Y-direction
		@param the attribute.
		*/
		virtual void SetRubyYScale(PMReal scale) = 0;
		/** Get the scaling of the ruby text in the Y-direction
		@return the attribute.
		*/
		virtual PMReal GetRubyYScale() const = 0;
		/** Set the color of the ruby text (the fill color).
		@param the attribute.
		*/
		virtual void SetRubyColorUID(UID u) = 0;
		/** Get the color of the ruby text (the fill color).
		@return the attribute.
		*/
		virtual UID GetRubyColorUID() const = 0;

		// Ruby color panel	--------------------------------------------------------------------------------------------------------------
		/** Get the color of the ruby text for the given stroke.
		@param stroke if kTrue, the stroke color, else the fill color.
		@return the attribute.
		*/
		virtual UID GetColorUID(bool16 stroke) const = 0;
		/** Set the color of the ruby text for the given stroke.
		@param stroke if kTrue, the stroke color, else the fill color.
		@param the attribute.
		*/
		virtual void SetColorUID(bool16 stroke, UID newColor) = 0;
		/** Set the tint of the ruby text.
		@param stroke if kTrue, the stroke color, else the fill color.
		@param the attribute.
		*/
		virtual void SetTint(bool16 stroke, PMReal tint) = 0;
		/** Get the tint of the ruby text.
		@param stroke if kTrue, the stroke color, else the fill color.
		@return the attribute.
		*/
		virtual PMReal GetTint(bool16 stroke) const = 0;
		/** Set whether or not the ruby text will overprint.
		@param stroke if kTrue, the stroke color, else the fill color.
		@param the attribute.
		*/
		virtual void SetOverprint(bool16 stroke, bool16 over) = 0;
		/** Get whether or not the ruby text will overprint.
		@param stroke if kTrue, the stroke color, else the fill color.
		@return the attribute.
		*/
		virtual bool16 GetOverprint(bool16 stroke) const = 0;

		/** Get whether or not the ruby text will outline.
		@return the attribute.
		*/
		virtual bool16 IsOutlined() const = 0;
		/** Set the outline width.
		@param the attribute.
		*/
		virtual void SetOutlineWidth(PMReal width) = 0;
		/** Get the outline width.
		@return the attribute.
		*/
		virtual PMReal GetOutlineWidth() const = 0;

		/** Set whether or not the ruby text will use OpenType glyphs.
		@param the attribute.
		*/
		virtual void SetUseOTRubyGlyphs(bool16 use) = 0;
		/** Get whether or not the ruby text will use OpenType glyphs.
		@return the attribute.
		*/
		virtual bool16 GetUseOTRubyGlyphs() const = 0;

		// AutoTCY	----------------------------------------------------------------------------------------------------------------------
		/** Set the maximum number of digits at which TCY will occur.
		@param the attribute.
		*/
		virtual void SetAutoTCYNumDigits(int16 num) = 0;
		/** Get the maximum number of digits at which TCY will occur.
		@return the attribute.
		*/
		virtual int16 GetAutoTCYNumDigits() const = 0;
		/** Set whether or not the TCY of ruby text should include non-digit roman characters.
		@param the attribute.
		*/
		virtual void SetAutoTCYIncludeRoman(bool16 b) = 0;
		/** Get whether or not the TCY of ruby text should include non-digit roman characters.
		@return the attribute.
		*/
		virtual bool16 GetAutoTCYIncludeRoman() const = 0;
		/** Set whether or not the TCY of ruby text will automatically be scaled.
		@param the attribute.
		*/
		virtual void SetAutoTCYAutoScale(bool16 b) = 0;
		/** Get whether or not the TCY of ruby text will automatically be scaled.
		@return the attribute.
		*/
		virtual bool16 GetAutoTCYAutoScale() const = 0;
};


#endif
		// __IRubyStyle__

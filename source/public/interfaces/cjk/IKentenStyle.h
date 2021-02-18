//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IKentenStyle.h $
//  
//  Owner: Shinji Hiramatsu
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
#ifndef __IKentenStyle__
#define __IKentenStyle__


#include "IPMUnknown.h"
#include "CTextEnum.h"
#include "CJKID.h"

 
/** 
	Interface for the kenten style text attribute. It is traditionally an accent mark above or below kanji characters.
*/
class IKentenStyle : public IPMUnknown
{
	public:
		
		/** interface ID enum */
		enum { kDefaultIID = IID_IKENTENSTYLE };

		/** Kenten kind	enum */
		enum KentenKind {
				Kenten_None = 0,
				
				Kenten_BlackSesameDot,
				Kenten_WhiteSesameDot,
				Kenten_Fisheye,
				Kenten_BlackCircle,
				Kenten_SmallBlackCircle,
				Kenten_Bullseye,
				Kenten_BlackTriangle,
				Kenten_WhiteTriangle,
				Kenten_WhiteCircle,
				Kenten_SmallWhiteCircle,

				/** user selected glyph */
                Kenten_Custom
			};

		/** Kenten alignment enum */
		enum AlignmentType { kLeft, kCenter, kRight };

		/** Kenten character set enum */
		enum  {
				kShiftJIS = 0,
				kJIS,
				kUnicode,
				kKuten
			};
			
		/** Kenten kind ascii enum (for Adobe Kenten font) */
		enum  {
				kBlackSesameAscii = 0x0030,
				kWhiteSesameAscii,
				kFisheyeAscii,
				kBlackCircleAscii,
				kSmallBlackCircleAscii,
				kBullseyeAscii,
				kBlackTriangleAscii,
				kWhiteTriangleAscii,
				kWhiteCircleAscii,
				kSmallWhiteCircleAscii
			};
	
		/** Set Kenten kind		
			@param flag		(should be of the KentenKind enumerated type specified above!) 
		*/
		virtual void SetKentenKind(IKentenStyle::KentenKind flag) = 0;
		/** Get Kenten Character kind */
		virtual IKentenStyle::KentenKind GetKentenKind() const = 0;
		

		/** Set Kenten point size
			@param p		point size
		*/
		virtual void SetKentenSize(PMReal p) = 0;
		/** Get Kenten point size
		@return Kenten point size  */
		virtual PMReal GetKentenSize() const = 0;
		

		/** Set Kenten related size
			@param p		related size
		*/
		virtual void SetKentenRelatedSize(PMReal p) = 0;
		/** Get Kenten related size
		@return Kenten related size  */
		virtual PMReal GetKentenRelatedSize() const = 0;
		

		/** Set Kenten Font family
			@param u	font UID
		*/
		virtual void SetKentenFontFamily(UID u) = 0;
		/** Get Kenten Font family
		@return Kenten Font family UID  */
		virtual UID GetKentenFontFamily() const = 0;
		

		/** Set Kenten Font style
			@param n	fontStyleName
		*/
		virtual void SetKentenFontStyle(const PMString& n) = 0;
		/** Get Kenten Font style
		@return Kenten Font family style name  */
		virtual const PMString& GetKentenFontStyle() const = 0;
		

		/** Set Kenten X Scale
			@param r	the x scale value
		*/
		virtual void SetKentenXScale(PMReal r) = 0;
		/** Get Kenten X Scale
		@return Kenten X Scale  */
		virtual PMReal GetKentenXScale() const = 0;
		

		/** Set Kenten Y Scale
			@param r	the y scale value
		*/
		virtual void SetKentenYScale(PMReal r) = 0;
		/** Get Kenten Y Scale
		@return Kenten Y Scale  */
		virtual PMReal GetKentenYScale() const = 0;


		/** Set Kenten X Offset
			@param r	the x offset value
		*/
		virtual void SetKentenXOffset(PMReal r) = 0;
		/** Get Kenten X Offset
		@return Kenten X Offset  */
		virtual PMReal GetKentenXOffset() const = 0;
		

		/** Set Kenten Y Offset
			@param r	the y offset value
		*/
		virtual void SetKentenYOffset(PMReal r) = 0;
		/** Get Kenten Y Offset
		@return Kenten Y Offset  */
		virtual PMReal GetKentenYOffset() const = 0;


		/** Set Kenten Color
			@param newColor	color UID
		*/
		virtual void SetKentenColor(UID newColor) = 0;
		/** Get Kenten Color
		@return Kenten Color UID  */
		virtual UID GetKentenColor() = 0;


		/** Set Kenten Color
			@param stroke	flag
			@param newColor	color uid
		*/
		virtual void SetColorUID(bool16 stroke, UID newColor) = 0;
		/** Get Kenten Color UID
		@return Kenten Color UID  */
		virtual UID GetColorUID(bool16 stroke) = 0;
		

		/** Set Kenten tint
			@param stroke	flag
			@param tint	value
		*/
		virtual void SetTint(bool16 stroke, PMReal tint) = 0;
		/** Get Kenten tint
		@return Kenten tint  */
		virtual PMReal GetTint(bool16 stroke) const = 0;
		

		/** Set Kenten Overprint
			@param stroke flag
			@param overprint value
		*/
		virtual void SetOverprint(bool16 stroke, int16 over) = 0;
		/** Get Kenten Overprint
		@return Kenten Overprint  */
		virtual int16 GetOverprint(bool16 stroke) const = 0;


		/** Set Kenten Outline Width
			@param width
		*/
		virtual void SetOutlineWidth(PMReal width) = 0;
		/** Get Kenten Outline Width
		@return Kenten Outline Width  */
		virtual PMReal GetOutlineWidth() const = 0;
		/** Get Kenten is outlined flag
		@return Kenten is outlined flag  */
		virtual bool16 IsOutlined() = 0;
		

		/** Set Kenten Alignment
			@param align
		*/
		virtual void SetKentenAlignment(IKentenStyle::AlignmentType align) = 0;
		/** Get Kenten Alignment
		@return Kenten Alignment  */
		virtual int16 GetKentenAlignment() const = 0;
		

		/** Set Kenten Character Set
			@param characterSet
		*/
		virtual void SetKentenCharacterSet(int16 characterSet) = 0;
		/** Get Kenten Character Set
		@return Kenten Character Set  */
		virtual int16 GetKentenCharacterSet() const = 0;
		

		/** Set Kenten Position	
			@param pos		0: above/right 1: below/left 
		*/
		virtual void SetKentenPosition(bool16 pos) = 0;
		/** Get Kenten Position
		@return Kenten Position  */
		virtual bool16 GetKentenPosition() const = 0;


		/** Set Kenten Character code of Kenten (Custom) 
			@param code		kenten textchar
		*/
		virtual void SetKentenCharacter(textchar code) = 0;
		/** Get Kenten Character code
		@return Kenten Character code  */
		virtual textchar GetKentenCharacter() const = 0;
};


#endif
		// __IKentenStyle__

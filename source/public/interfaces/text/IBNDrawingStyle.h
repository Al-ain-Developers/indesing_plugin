//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IBNDrawingStyle.h $
//  
//  Owner: Anurag Wahi
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
#ifndef __IBNDRAWINGSTYLE__
#define __IBNDRAWINGSTYLE__


#include "IPMUnknown.h"
#include "ITextAttrListType.h"
#include "ITextAttrBulletCharacter.h"
#include "BNTextAttrID.h"

/**
	IBNDrawingStyle is the collection of summary information for attributes related to
	Bullets and Numbering. The information in this collection is set by the actual
	text attributes themselves.
	@see IDrawingStyle
*/
class IBNDrawingStyle : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IBNDRAWINGSTYLE };

		/**
			List Alignment
		*/
		typedef enum {
						/** Left align */
						kAlignLeft,

						/** Center align */
						kAlignCenter,

						/** Right align */
						kAlignRight

		} ListAlignment;

		/**
		Set the list type to bullets, numbering or none.
		@param listType specifies the list type to set to. It may be ITextAttrListType::kNone for no list, ITextAttrListType::kBulletedList for bullets
		and ITextAttrListType::kNumberedList for numbering.
		*/
		virtual void SetListType(ITextAttrListType::ListType listType) = 0;

		/**
		Get the list type as bulleted, numbered or none.
		@return The actually used list type. It may be ITextAttrListType::kNone for no list, ITextAttrListType::kBulletedList for bullets
		and ITextAttrListType::kNumberedList for numbering.
		*/
		virtual ITextAttrListType::ListType GetListType() const = 0;

		/**
		Checks if bullets or numbering is on.
		@return true if bullet or numbering is on, false otherwise.
		*/
		virtual bool16 IsBulletOrNumberingApplied() const = 0;

		/**
		Sets the bullet font family UID.
		@param u is the bullet font family UID.
		*/
		virtual void SetBulletFontUID(UID u) = 0;

		/**
		Gets the bullet font family UID.
		@return The actually used bullet font family UID. The value may also be kInvalidUID.
		*/
		virtual UID GetBulletFontUID() const = 0;

		/**
		Sets the bullet font style name.
		@param name is the bullet font style name.
		*/
		virtual void SetBulletFontStyleName(const PMString& name) = 0;

		/**
		Gets the bullet font style name.
		@return The actually used bullet font style name.
		*/
		virtual const PMString& GetBulletFontStyleName() const = 0;

		/**
		Sets the character style for bullets and text after.
		@param u is the UID of an existing character style.
		*/
		virtual void SetBulletCharacterStyleUID(UID u) = 0;

		/**
		Gets the character style for bullets and text after.
		@return The actually applied character style.
		*/
		virtual UID GetBulletCharacterStyleUID() const = 0;

		/**
		Sets the alignment for bullets.
		@param val is the type of alignment.
		*/
		virtual void SetBulletAlignment(ListAlignment val) = 0;

		/**
		Gets the alignment for bullets.
		@return The actually applied alignment type.
		*/
		virtual ListAlignment GetBulletAlignment() const = 0;

		/**
		Sets the character style for numbers.
		@param u is the UID of an existing character style.
		*/
		virtual void SetNumberingCharacterStyleUID(UID u) = 0;

		/**
		Gets the character style for numbers.
		@return The actually applied character style.
		*/
		virtual UID GetNumberingCharacterStyleUID() const = 0;

		/**
		Sets the alignment for numbers.
		@param val is the type of alignment.
		*/
		virtual void SetNumberingAlignment(ListAlignment val) = 0;

		/**
		Gets the alignment for numbers.
		@return The actually applied alignment type.
		*/
		virtual ListAlignment GetNumberingAlignment() const = 0;

		/**
		Gets the UID for applied color to bullet or number.
		@return The actually applied color UID from the character style. The value may also be kInvalidUID.
		*/
		virtual UID GetUsedColorUID() const = 0;

		/**
		Gets the font family UID from applied character style to bullet or number.
		@return The font family UID. The value may also be kInvalidUID.
		*/
		virtual UID GetUsedFontUIDFromCharacterStyle() const = 0;

		/**
		Gets the font style name from applied character style to bullet or number.
		@return The font style name.
		*/
		virtual PMString GetUsedFontStyleNameFromCharacterStyle() const = 0;

		virtual void SetBulletCharacterType(ITextAttrBulletCharacter::BulletCharacterType bulType) = 0;
		virtual ITextAttrBulletCharacter::BulletCharacterType GetBulletCharacterType() const = 0;
		virtual void SetBulletCharacterValue(int32 value) = 0;
		virtual int32 GetBulletCharacterValue() const = 0;
		virtual void SetBulletFontMMAxes(int32 numAxes, const Fixed *axes) = 0;
		virtual int32 GetBulletFontMMAxes(Fixed *axes) const = 0;

		virtual void SetNumberingSeparator(int32 i) = 0;
		virtual int32 GetNumberingSeparator() const = 0;
		virtual void SetNumberingStyle(ClassID c) = 0;
		virtual ClassID GetNumberingStyle() const = 0;
		virtual void SetNumberStartAt(int32 i) = 0;
		virtual int32 GetNumberStartAt() const = 0;

};


#endif // __IBNDRAWINGSTYLE__

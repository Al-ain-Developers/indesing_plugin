//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrBulletCharacter.h $
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
#ifndef __ITextAttrBulletCharacter_h__
#define __ITextAttrBulletCharacter_h__

#include "IPMUnknown.h"
#include "BNTextAttrID.h"

/** Represents the bullet character text attribute.
	@ingroup text_attr
*/

class ITextAttrBulletCharacter : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRBULLETCHARACTER};

		/**
			Bullet Type
		*/
		typedef enum {
						/** Bullet represented by a unicode character */
						kUnicodeOnly, 

						/** Bullet represented by a unicode character from a specific font */
						kUnicodeWithFont, 

						/** Bullet represented by a glyph id from a specific font */
						kGlyphWithFont

		} BulletCharacterType;

		/**
			Set the bullet character type in this text attribute
			@param bcType	The bullet character type to set
		*/
		virtual void SetBulletCharacterType(const BulletCharacterType bcType) = 0;
		
		/**
			Set the bullet character value in this text attribute. For bullets of type
			kUnicodeOnly and kUnicodeWithFont, this is a unicode character value. For bullets of
			type kGlyphWithFont, this is a glyph id.
			@param bcValue	The bullet character value to set
		*/
		virtual void SetBulletCharacterValue(const int32 bcValue) = 0;

		/**
			Get the bullet character type from this text attribute
			@return 		BulletCharacterType
		*/
		virtual const BulletCharacterType GetBulletCharacterType() const = 0;

		/**
			Get the bullet character value from this text attribute. For bullets of type
			kUnicodeOnly and kUnicodeWithFont, this is a unicode character value. For bullets of
			type kGlyphWithFont, this is a glyph id.
			@return 		int32
		*/
		virtual const int32	GetBulletCharacterValue() const = 0;

};

#endif // __ITextAttrBulletCharacter_h__

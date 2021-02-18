//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IStyleInfo.h $
//  
//  Owner: EricK
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
#ifndef __ISTYLEINFOLIST__
#define __ISTYLEINFOLIST__

#include "IPMUnknown.h"
#include "TextID.h"
#include "VirtualKey.h"
#include "GlobalTime.h"

class PMString;

#define NORMALPARAGRAPHUNIQUEID "771888e2-944e-42ec-89d5-874cd945e62b"

/**
	Data interface for the non-attribute parts of a style. Usually, but not
	necessarily a text style. Necessary for anything listed by an IStyleNameTable.
	May be part of the style itself, or part of a command that operates on styles.
	@see KeyboardDefs.h
	@see IStyleNameTable
	@ingroup text_style
*/
class IStyleInfo : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISTYLEINFO };
		enum { kInvalidTimeStamp = 0, kPubConvertedTimeStamp = 1, kRefConvertedTimeStamp = 2 };
		enum StyleType { kCharacterStyle = 0, kParagraphStyle = 1, kTableStyle = 2, kCellStyle = 3 };

		/**
		Get the UID of the style this style is based on
		*/
		virtual UID GetBasedOn() const = 0;

		/**
		Get the UID of the next style.
		Only applicable to paragraph styles. Only applied after typing a <CR>
		*/
		virtual UID GetNextStyle() const = 0;

		/**
		Unsupported at this time. Do not use.
		*/
		virtual UID GetCharStyle() const = 0;

		/**
		Get the color UID to use for the style preview mode.
		*/
		virtual UID GetPreviewColor() const = 0;

		/**
		Get the name of this style.
		*/
		virtual const PMString& GetName() const = 0;

		/**
		Was this style imported? Usually during a <Place> operation.
		*/
		virtual bool16 IsStyleImported() const = 0;

		/**
		Set the UID of the style this style is based on. There may be restrictions.
		For example, you cannot create cycles and paragraph styles must be based
		on [No Paragraph Style].
		@param base is the UID of the style to base this one on.
		*/
		virtual void SetBasedOn(const UID& base) = 0;

		/**
		Set the UID of the next style.
		Only applicable to paragraph styles. Only applied after typing a <CR>
		@param base is the UID of the style that would follow this one.
		*/
		virtual void SetNextStyle(const UID& next) = 0;

		/**
		Unsupported at this time. Do not use.
		*/
		virtual void SetCharStyle(const UID& charStyle) = 0;

		/**
		Get the color UID to use for the style preview mode.
		*/
		virtual void SetPreviewColor(const UID& color) = 0;

		/**
		Set the name of this style.
		@param s is the style name.
		@param translatable would always be kFalse for user-specified names. [No Paragraph Style] is translated, for example.
		*/
		virtual void SetName(const PMString& s, bool16 translatable = kFalse) = 0;

		/**
		Is this style a paragraph style?
		@param isParaStyle
		DEPRECATED -- used SetStyleType since we now support other style types!
		*/
		// virtual void SetIsParagraphStyle(bool16 isParaStyle) = 0;

		/**
		Is this style imported?
		@param isStyleImported
		*/
		virtual void SetIsStyleImported(bool16 isStyleImported) = 0;

		/**
		Set the keyboard shortcut that triggers this style.
		@param virtualKey is the key code.
		@param modifiers are the modifier keys.
		@see KeyboardDefs.h
		*/
		virtual void SetKeyboardShortcut(VirtualKey virtualKey, int16 modifiers) = 0;

		/**
		Get the VirtualKey for the keyboard shortcut that triggers this style.
		@param modifiers MAY NOT BE NIL
		*/
		virtual VirtualKey GetKeyboardShortcut(int16 *modifiers) const = 0;

		/**
		Get the keyboard shortcut time stamp. If two styles share the same keyboard shortcut, the
		one with the newer time stamp is used.
		*/
		virtual GlobalTime GetKeyboardShortcutTimeStamp () const = 0;

		/**
		Set the keyboard shortcut time stamp. If two styles share the same keyboard shortcut, the
		one with the newer time stamp is used.
		@param gtime specifies the current time, used to compare conflicted shortcuts.
		*/
		virtual void SetKeyboardShortcutTimeStamp (GlobalTime gtime) = 0;

		/**
		Sets the type of the style see @StyleType
		@param styleType
		*/
		virtual void SetStyleType(IStyleInfo::StyleType styleType) = 0;

		/**
		Get the type of the style see @StyleType
		@return styleType
		*/
		virtual IStyleInfo::StyleType GetStyleType() const = 0;
	
		/**
		 Copy the style information from one IStyleInfo instance to this instance.
		 @param other the style information to copy. MAY NOT BE NIL.
		 */
		virtual void Copy(const IStyleInfo* other) = 0;

		/**
		FOR INTERNAL USE ONLY
		Sets the unique id for the style.
		*/
		virtual void SetUniqueID(const PMString& uniqueId) = 0;

		/**
		FOR INTERNAL USE ONLY
		Get the unique id of this style. Can return empty string if no unique id has been set.
		*/
		virtual const PMString& GetUniqueID() const = 0;

		/**
		FOR INTERNAL USE ONLY
		Generates a unique ID and sets it for the style.
		*/
		virtual void GenerateAndSetUniqueID() = 0;
};

#endif

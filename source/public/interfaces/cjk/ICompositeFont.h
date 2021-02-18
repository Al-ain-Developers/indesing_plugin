//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ICompositeFont.h $
//  
//  Owner: mjessett
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
#ifndef __ICompositeFont__
#define __ICompositeFont__


#include "IPMUnknown.h"
#include "CompositeFontMgrID.h"

#include "K2Vector.h"
#include "IPMStream.h"
#include "IDocument.h"
#include "UIDList.h"

class WideString;
//----------------------------------------------------------------------------------------
// character classes for Composite Font
//----------------------------------------------------------------------------------------
#define kCompFontString_Kanji			"Kanji"				// Kanji
#define kCompFontString_Kana			"Kana"				// Kana
#define kCompFontString_FullPunctuation	"Punctuation"		// Full width punctuation
#define kCompFontString_FullSymbols		"Symbols"			// Full symbols, alphabet and numbers
#define kCompFontString_HalfSymbols		"Alphabetic"		// Half symbols and aphabet
#define kCompFontString_HalfNumbers		"Numbers"			// Half numbers
#define kCompFontString_Hangul			"Hangul"			// Korean Hangul


/**
	CharacterRange. Used in CharRangeCollection.
	
	@see SetCharRanges
*/
class CharacterRange {
public:
	typedef base_type data_type;
	/**	Set range with unicode values.
		@param firstChar	Unicode value of first character in composite font.
		@param lastChar		Unicode value of last character in composite font.
		@param destChar		Unicode value that first character maps to in component font.
							In most cases destChar == firstChar. If you want to map a component font
							to a different area in the composite font you will want to use this value.
		@param script		OBSOLETE.
	 */
	void		SetRange(UTF32TextChar firstChar, UTF32TextChar lastChar, UTF32TextChar destChar, int32 script = -1)
					{ fFirstChar = firstChar; fLastChar = lastChar; fDestChar = destChar; }
	/**	Reset beginning of range. Call updates destchar to remapped value of new firstChar.
		@param firstChar	new Unicode value for first character in composite font.
		@return bool16		kFalse if firstchar is greater than lastchar.
	 */
	bool16		SetFirstAndDest(UTF32TextChar firstChar)
					{ if (firstChar > fLastChar) return kFalse;
						UTF32TextChar destChar = GetRemappedChar(firstChar);
						fDestChar = destChar;
						fFirstChar = firstChar;
						return kTrue; }
	/**	Reset end of range.
		@param lastChar		new Unicode value for last character in composite font.
		@return bool16		kFalse if lastchar is less than firstchar.
	 */
	bool16		SetLast(UTF32TextChar lastChar)
					{ if (lastChar < fFirstChar) return kFalse; fLastChar = lastChar; return kTrue; }
	/**	Reset destination of range.
		@param destChar		new Unicode value for what first character maps to in component font.
	 */
	void		SetDest(UTF32TextChar destChar)
					{ fDestChar = destChar; }
	/**	Get Unicode value of first character in composite font.
		@return UTF32TextChar	first character in composite font.
	 */
	UTF32TextChar	GetFirst() const
					{ return fFirstChar; }
	/**	Get Unicode value of last character in composite font.
		@return UTF32TextChar	last character in composite font.
	 */
	UTF32TextChar	GetLast() const
					{ return fLastChar; }
	/**	Get Unicode value that first character maps to in component font.
		@return UTF32TextChar	destination character in component font.
	 */
	UTF32TextChar	GetDest() const
					{ return fDestChar; }
	/**	Get Unicode value that input character maps to in composite font.
		@return UTF32TextChar	character in composite font.
	 */
	UTF32TextChar	GetRemappedChar(UTF32TextChar originalChar) const
					{ return fDestChar.GetValue()+originalChar.GetValue()-fFirstChar.GetValue(); }
					
	/**	Read or Write values.
		@param s	stream to read/write to.
	 */
	void		ReadWrite(IPMStream *s)
					{
						fFirstChar.ReadWriteUTF16(s);
						fLastChar.ReadWriteUTF16(s);
						fDestChar.ReadWriteUTF16(s);
					}

	// BP: comparison operators are required by K2Vector<CharacterRange>
	/**	comparison operator.
	 */
	inline bool16	operator==( const CharacterRange &charRange ) const 
				{
					return	fFirstChar == charRange.fFirstChar &&
							fLastChar == charRange.fLastChar &&
							fDestChar == charRange.fDestChar;
				}


	/**	OBSOLETE. Use SetRange(UTF32TextChar...
	 */
	void		SetRange(PlatformChar firstChar, PlatformChar lastChar, PlatformChar destChar, int32 script = -1)
					{ fFirstChar = firstChar.GetValue(); fLastChar = lastChar.GetValue(); fDestChar = destChar.GetValue(); }
	/**	OBSOLETE. do not use.
	 */
	int32		GetScript() const
					{ ASSERT_FAIL("GetScript - Obsolete"); return -1; }


private:
	UTF32TextChar	fFirstChar;
	UTF32TextChar	fLastChar;
	UTF32TextChar	fDestChar;
};


typedef K2Vector<CharacterRange>	CharRangeCollection;


/**
	ScaleAdjustment.
	
	@see GetScaleAdjustment
*/
class ScaleAdjustment {
public:
	uint16		GetHorizontalAdjustmentFlag()
					{ return fHorizontalFlags; };
	void		SetHorizontalAdjustmentFlag(uint16 horizontalFlag)
					{ fHorizontalFlags = horizontalFlag; };

	uint16		GetHorizontalGlyphCentering()
					{ return fHorizontalGlyphCentering; };
	void		SetHorizontalGlyphCentering(uint16 horizontalGlyphCentering)
					{ fHorizontalGlyphCentering = horizontalGlyphCentering; };

	uint16		GetVerticalAdjustmentFlag()
					{ return fVerticalFlags; };
	void		SetVerticalAdjustmentFlag(uint16 verticalFlag)
					{ fVerticalFlags = verticalFlag; };

	uint16		GetVerticalGlyphCentering()
					{ return fVerticalGlyphCentering; };
	void		SetVerticalGlyphCentering(uint16 verticalGlyphCentering)
					{ fVerticalGlyphCentering = verticalGlyphCentering; };

	void		ReadWrite(IPMStream *s)
					{
						s->XferInt16((short&)fHorizontalFlags);
						s->XferInt16((short&)fHorizontalGlyphCentering);
						s->XferInt16((short&)fVerticalFlags);
						s->XferInt16((short&)fVerticalGlyphCentering);
					}

private:
	uint16		fHorizontalFlags;						/*  */
	uint16		fHorizontalGlyphCentering;				/*  */
	uint16		fVerticalFlags;							/*  */
	uint16		fVerticalGlyphCentering;				/*  */


};


/** Settings in a ICompositeFont.
	@ingroup text_font
*/
class ICompFontDataSettings : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICOMPFONTDATASETTINGS };

		/**	Clear all character ranges.
		 */
		virtual void			ClearRanges() = 0;		

		/**	Set all values to default. This will also clear all ranges.
		 */
		virtual void			SetDefault() = 0;


		/**	Set name of setting.
			@param s	name of setting.
		 */
		virtual void			SetName(const PMString& s) = 0;

		/**	Set name of setting.
			@param s			name of setting.
			@param translatable	kTrue if name is translatable. Translatable names are usually only for
								the default settings like "Kanji", "Kana" ,,,
		 */
		virtual void			SetName(const PMString& s, bool16 translatable) = 0;

		/**	Get name of setting
			@return PMString	name of setting
		 */
		virtual const PMString	&GetName() const = 0;


		/**	Set UID of font family for this setting
			@param nUID			font family UID
		 */
		virtual void			SetFontUID( const UID& nUID ) = 0;

		/**	Get UID of font family for this setting
			@return		font family UID
		 */
		virtual UID 			GetFontUID() const = 0;


		/**	Set font style name for setting
			@param nFontStyle	font style name
		 */
		virtual void			SetFontStyle( const PMString& nFontStyle ) = 0;

		/**	Get font style name for setting
			@return				font style name
		 */
		virtual PMString		GetFontStyle() const = 0;


		/**	Set relative font size percentage. This is relative to base(Kanji) setting.
			@param nSize		percent of base font size
		 */
		virtual void			SetSizeValue( const PMReal nSize ) = 0;

		/**	Get relative font size percentage. This is relative to base(Kanji) setting.
			@return				percent of base font size
		 */
		virtual PMReal			GetSizeValue() const = 0;


		/**	Set relative base line shift percentage. This is relative to base(Kanji) setting.
			@param nBaseline		percent of base setting base line shift
		 */
		virtual void			SetBaselineValue( const PMReal nBaseline ) = 0;

		/**	Get relative base line shift percentage. This is relative to base(Kanji) setting.
			@return				percent of base setting base line shift
		 */
		virtual PMReal			GetBaselineValue() const = 0;


		/**	Set relative horizontal scale percentage. This is relative to base(Kanji) setting.
			@param nSize		percent of base font horizontal scale
		 */
		virtual void			SetHScaleValue( const PMReal nScale ) = 0;

		/**	Get relative horizontal scale percentage. This is relative to base(Kanji) setting.
			@return				percent of base font horizontal scale
		 */
		virtual PMReal			GetHScaleValue() const = 0;
	

		/**	Set relative vertical scale percentage. This is relative to base(Kanji) setting.
			@param nSize		percent of base font vertical scale
		 */
		virtual void			SetVScaleValue( const PMReal nScale ) = 0;

		/**	Get relative vertical scale percentage. This is relative to base(Kanji) setting.
			@return				percent of base font vertical scale
		 */
		virtual PMReal			GetVScaleValue() const = 0;

		/**
			Sets data setting so user cannot edit.
		
			@param	bool16					kTrue to set lock. kFalse to set unlocked
		*/
		virtual void			SetLocked( const bool16 locked ) = 0;
		
		/**
			Gets locked status of data setting.
		
			@return	bool16					kTrue if locked. kFalse if unlocked
		*/
		virtual bool16			IsLocked() const = 0;


		/**	Set character ranges. replaces does not append.
			@param ranges	new character ranges.
		 */
		virtual void SetCharRanges(const CharRangeCollection ranges) = 0;

		/**	Get character ranges
			@return CharRangeCollection		character ranges
		 */
		virtual CharRangeCollection GetCharRanges() const = 0;

		/**
			this is the ranges adjusted for sending to cooltype. this flattens ATC ranges
			when a component font is ATC
		
			@return	CharRangeCollection		adjusted character ranges
		*/
		virtual CharRangeCollection GetCharRangesAjustedForCoolType() = 0;

		/**
			This converts InDesign 1.0J composite fonts from platform encoding to unicode encoding
		
			@return	bool16					kTrue if success. kFalse if could not convert to unicode
		*/
		virtual bool16			ConvertToUnicode() = 0;

		/**
			Add unicode range to setting.
		
			@param	firstChar				first unicode value of range
			@param	lastChar				last unicode value of range
			@param	destChar				new unicode value to remap firstChar. If equal to firstChar no remapping is done.
			@param	script					Obsolete. Do not use.
		*/
		virtual void			AddRemapRange(UTF32TextChar firstChar, UTF32TextChar lastChar, UTF32TextChar destChar, int32 script = -1) = 0;

		/**
			Add unicode range to setting.
		
			@param	firstChar				first unicode value of range
			@param	lastChar				last unicode value of range
			@param	script					Obsolete. Do not use.
		*/
		virtual void			AddRange(UTF32TextChar firstChar, UTF32TextChar lastChar, int32 script = -1) = 0;
		

		/**	Range is returned as a Unicode string of characters.
			@return WideString	Unicode string of range characters.
		 */
		virtual WideString		GetRangeAsWideString() const = 0;

		/**	Range is returned as a PMString of characters
			@return PMString	string of range characters
		 */
		virtual PMString		GetRangeAsString() const = 0;

		/**	Set range from Unicode string
			@param setWString	string to use to set ranges
			@param script		OBSOLETE	
		 */
		virtual void			SetRangeFromWideString( WideString setWString, int32 script = -1 ) = 0;

		/**	Set range from PMString string
			@param setString	string to use to set ranges
		 */
		virtual void			SetRangeFromString( PMString setString ) = 0;
			

		/**	Returns what script the setting supports. Kanji supports all CJK scripts. This is used to determine
			what fonts are shown in composite font setting UI.
			@param script		script to test for support
			@return bool16		kTrue if setting supports the script.
		 */
		virtual bool16			SupportsScript( int32 script ) const = 0;
		

		/**	Copy composite font setting data
			@param from			data to copy
		 */
		virtual void			CopyCompFontSetting(ICompFontDataSettings *from) = 0;


		/**	Read/Write the setting data
			@param s			stream to read write
			@param id			not used
		 */
		virtual void			ReadWrite(IPMStream *s, ImplementationID id) = 0;

		/**	Given a character return kTrue if in range and return remapped character in remapChar
			@param findChar		character to find
			@param remapChar	remapped character value. Unless ranges are remapped this is same as findChar
			@return bool16		kTrue if character is in range.
		 */
		virtual bool16			FindCharInRange( UTF32TextChar findChar, UTF32TextChar &remapChar ) const = 0;


		/**	Set all scale adjustment values to 0.
		 */
		virtual void			ClearScaleAdjustment() = 0;

		/**	Get scale adjustment setting. Most of the time you just need the GetScaleOption value.
			@return ScaleAdjustment		scale adjustment setting
		 */
		virtual ScaleAdjustment GetScaleAdjustment() const = 0;

		/**
			Get the scale from center option.
		
			@return	bool16			kTrue if scaling from center. kFalse if scaling from baseline
		*/
		virtual bool16			GetScaleOption() = 0;

		/**
			Set the scale from center option.
			@param	scaleOption		kTrue if scaling from center. kFalse if scaling from baseline
		*/
		virtual void			SetScaleOption(bool16 scaleOption) = 0;

};


/** Composite Font. creates a new font composed of real fonts. Font switching is based on unicode value.
	Currently base font must be either Chinese, Japanese, or Korean font.
	@ingroup text_font
*/
class ICompositeFont : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICOMPOSITEFONT };


		/**	This value is set with SetBasedOn but not used internally
			@return UID		not used
		 */
		virtual UID GetBasedOn() const = 0;

		/**	Family name of composite font. This is set with SetName(). It is the same as GetFontFamilyName()
			except this is always roman encoded. So if there are non roman characters their unicode will be
			embedded.
			@return PMString	family name
		 */
		virtual PMString GetFontFamilyName() const = 0;

		/**	Native family name of composite font. This is set with SetName().
			@return PMString	native family name
		 */
		virtual const PMString &GetNativeFontFamilyName() const = 0;


		/**	Value is saved but not used internally
			@param base		not used
		 */
		virtual void SetBasedOn(const UID& base) = 0;

		/**	Set the composite font name. To get this name call GetNativeFontFamilyName
			@param s		composite font name
		 */
		virtual void SetName(const PMString& s) = 0;


		/**	This is usually an empty string.
			@return			composite font style name. 
		 */
		virtual const PMString& GetNameStyle() const = 0;

		/**	This is generally not called. The default of empty string is fine
			@param s	composite font style name.
		 */
		virtual void SetNameStyle(const PMString& s) = 0;


		/**	Postscript name for composite font. This is usually generated from name set with SetName.
			@return PMString postscript name for composite font
		 */
		virtual PMString GetPostScriptName() = 0;

		/**	Set postscript name for composite font.
			@param s	new postscript name
		 */
		virtual void SetPostScriptName(const PMString& s) = 0;


		/**	Get file name of composite font.
			@return		file name of composite font
		 */
		virtual const PMString& GetCMapFileName() const = 0;

		/**	Set file name of composite font.
			@param PMString		file name of composite font
		 */
		virtual void SetCMapFileName(const PMString& s) = 0;


		/**	Get number of ICompFontDataSetting interfaces for this composite font
			@return int32	number of settings for composite font
		 */
		virtual int32 GetCharClassLength() = 0;

		/**	Get setting at index.
			@param index					0 based index. must be < GetCharClassLength
			@return ICompFontDataSettings*	setting at index
		 */
		virtual ICompFontDataSettings* GetCharClass(int32 index) const = 0;

		/**
			find Class by name
		
			@param	nameString				name to find
			@return	ICompFontDataSettings	setting found. nil if not found
		*/
		virtual ICompFontDataSettings* GetCharClass(const PMString &nameString) const = 0;

		/**
			find class with findChar in its range. Search from end as the last item has precedence
		
			@param	findChar				unicode value to find
			@param	remapChar				OUT value of what find char is remapped to in found setting
			@return	ICompFontDataSettings	setting found. nil if not found
		*/
		virtual ICompFontDataSettings* GetCharClass(UTF32TextChar findChar, UTF32TextChar *remapChar = nil) const = 0;

		/**
			get Class UID by index. UID is a ICompFontDataSetting UID
		
			@param	nameString				index of class
			@return	UID						UID of setting found. kInvalidUID if not found
		*/
		virtual UID GetCharClassUID(int32 index) const = 0;

		/**
			find Class by name
		
			@param	nameString				name to find
			@return	int32					index of setting found. 0 if not found
		*/
		virtual int32 GetCharClassIndex(const PMString &nameString) const = 0;
		

		/**	Create a new setting. New setting is already appended to composite font
			@return ICompFontDataSettings*	new setting
		 */
		virtual ICompFontDataSettings* CreateCharClass() = 0;

		/**	Append setting to composite font
			@param newSetting	new settting to append.
		 */
		virtual void AppendCharClass(const UID newSetting) = 0;

		/**	Append setting to composite font
			@param newSetting	new settting to append.
		 */
		virtual void AppendCharClass(ICompFontDataSettings* newSetting) = 0;

		/**	Remove setting at index
			@param nIndex setting index to remove
		 */
		virtual void RemoveCharClass(int32 nIndex) = 0;

		/**	Undeletes UID and appends it to composite font.
			@param nUID	UID to unremove
		 */
		virtual void UnRemoveCharClass(UID nUID) = 0;


		/**	Copy composite font data
			@param from		composite font data to copy
		 */
		virtual void CopyCompositeFontData(ICompositeFont *from) = 0;

		/**	Copy composite font data. This will conver the font family UIDs from source DB to dest DB
			@param from		composite font data to cop
			@param sourceDB	database of from composite font data
			@param destDB	database of this composite font data
		 */
		virtual void CopyAndConvertCompositeFontData(ICompositeFont *from, IDataBase* sourceDB,
													IDataBase* destDB) = 0;

		/**	Get postscript font name of font assigned to nCharClass setting.
			@param nCharClass		setting to get postscript font name from
			@param fEncoding		encoding of setting is appended to postscriptname. For instance if
									script of base font is Japanese "-UniJIS-UTF16-H" will be appended
			@return PMString		postscript font name 
		 */
		virtual const PMString GetPSFontName(const int32 nCharClass, bool16 fEncoding = kTrue) const = 0;

		/**	Compare composite fonts and return kTrue if they are the same
			@param srcData	composite font to compare to
			@return bool16	kTrue if same
		 */
		virtual bool16 CompareCompositeFontData(ICompositeFont *srcData) = 0;

		/**	Delete all settings in composite font
		 */
		virtual void DeleteCompositeFontData() = 0;


		/**	OBSOLETE
			@return bool16	always returns kFalse
		 */
		virtual bool16 IsDirty() = 0;

		/**	Set dirty
		 */
		virtual boost::shared_ptr<CmdUtils::AutoUndoSequencePtr> DoDirty() = 0;

		/**
			Sets composite font so user cannot edit. this is the case for external ATC fonts becuase we
			cannot create the same font that ATC does (ATC fonts have extra data)
		
			@param	bool16					kTrue to set lock. kFalse to set unlocked
		*/
		virtual void		SetLocked( const bool16 locked ) = 0;

		/**
			Gets locked status of composite font.
		
			@return	bool16					kTrue if locked. kFalse if unlocked
		*/
		virtual bool16		IsLocked() const = 0;


		/**	OBSOLETE
			@param verticalBaselineShift
		 */
		virtual void SetFontMatrixAdjustment(const uint16 verticalBaselineShift) = 0;

		/**	OBSOLETE
			@return uint16	always returns 1
		 */
		virtual uint16 GetFontMatrixAdjustment() const = 0;


		/**	Read/Write the setting data
			@param s			stream to read write
			@param id			not used
		 */
		virtual void ReadWrite(IPMStream *s, ImplementationID id) = 0;

		/**	Read or write composite font out to a file that can be read as a font.
			@param s			stream to write to
			@return ErrorCode	kSuccess if no error.
		 */
		virtual ErrorCode ReadWriteRffFile(IPMStream *s) = 0;
		
		
		/**
			Should not use this. Only used in special cases where commands are used.
		
			@return	IDocument	document 
		*/
		virtual IDocument* GetDocument() const = 0;

		/**
			Should not use this. Only used in special cases where commands are used.
		
			@param	theDocWS	document 
		*/
		virtual void SetDocument(IDocument* theDocWS) = 0;
};

#endif	// __ICompositeFont__

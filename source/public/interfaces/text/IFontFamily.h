//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFontFamily.h $
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
#ifndef __IFontFamily__
#define __IFontFamily__

#include "IPMUnknown.h"
#include "IPMFont.h"
#include "IFontMgr.h"
#include "IFontGroup.h"

class IFontGroupId;
class PMString;

class FontEntry
{
    public:
        FontEntry()
            { 
				fFontType = IPMFont::kUnknownFontType;
				fWritingScript = -1;
			};
        FontEntry(const PMString &fontStyleName, const PMString &postScriptName,
			const PMString &fullName, const PMString &nativeStyleName,
			const PMString &nativeFullName,	IPMFont::FontType fontType,
			const WideString &version, int32 writingScript)
            { 
				fFontStyleName = fontStyleName;
				fPostScriptName = postScriptName;
				fFullName = fullName;
				fNativeStyleName = nativeStyleName;
				fNativeFullName = nativeFullName;
				fFontType = fontType;
				fVersion = version;
				fWritingScript = writingScript;
			};

		PMString			fFontStyleName;
		PMString			fPostScriptName;
		PMString			fFullName;
		PMString			fNativeStyleName;
		PMString			fNativeFullName;
		IPMFont::FontType	fFontType;
		WideString			fVersion;
		int32				fWritingScript;

};


/** This plus the style name is used to identify an IPMFont in the document. IFontFamily
	plus style name are saved as attributes in the document.
	@ingroup text_font
*/
class IFontFamily : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IFONTFAMILY };
		
		struct FontFaceMappingInfo
		{
			FontFaceMappingInfo() : fStyle(IFontMgr::kNormal), fScript(kDontKnowScript), fOS(IFontMgr::kOriginalUnknownOS) {};
			typedef object_type data_type;
			PMString 				fPlatformName;
			PMString 				fFontFaceName;			
			IFontMgr::FontStyleBits fStyle;
			int32 					fScript;
			IFontMgr::OriginalOS 	fOS;			
		};

		/**	Shouldn't be called by anything but the font management system
			@param familyName 
			@param familyNameNative 
			@param missing 
		 */
		virtual void SetFamilyName( const PMString& familyName, const PMString& familyNameNative, bool16 missing, const FontEntry *fontEntry = nil) = 0;

		/**	Gets the roman family name
			@return PMString&  Family Name
		 */
		virtual PMString GetFamilyName() const = 0;

		/**	Gets the native family name. This is the full font name for the writing
			script. So if the font is Japanese writing script the Native name will be Japanese. 
			@return PMString&  Native family name
		 */
		virtual PMString GetFamilyNameNative() const = 0;
			
		/** Call GetWritingScript if a font is missing and you want to find the 
			writingScript from the family. To get the writing script of a font
			your first choice should be to call IPMFont::GetWritingScript.
			@return int32  writing script. kCTRomanScript is returned for roman scripts.
		 */
		virtual int32 GetWritingScript() const = 0;
		

		/**	This will throw away all the font data and get the information again.
			Only should be called by the font management system when the font system
			has changed.
			@param *docFontList 
		 */
		virtual bool16 UpdateFontState(IUsedFontList *docFontList) = 0;
		

		/**	Count number of font styles in this font family
			WARNING: The count returned may not reflect all available faces. It merely returns
			one beyond the highest index usable in functions taking an index.

			@param getForDysfunctional	if true return count of faces in dysfunctional family
										if false return -1 for dysfunctional family
			@return int32 
		 */
		virtual int32 CountFontFaces(bool16 getForDysfunctional = kFalse) const = 0;

		/**	Appends the postscript name to string
			@param i  Index into font family. From 0 to < CountFontFaces
			@param s  String to append name to.
		 */
		virtual void AppendFontName(int32 i, PMString& s) const = 0;

		/**	Appends the full font name to string. Full name can be family
			name plus style name but it is not always.
			@param i  Index into font family. From 0 to < CountFontFaces
			@param s  String to append name to.
		 */
		virtual void AppendFullName(int32 i, PMString& s) const = 0;

		/**	Appends the roman font style name to string
			@param i  Index into font family. From 0 to < CountFontFaces
			@param s  String to append name to.
		 */
		virtual void AppendStyleName(int32 i, PMString& s) const = 0;

		/**	Appends the native font style name to string. This is the style
			name for the writing script. So if the font is Japanese writing
			script the Native name will be Japanese.
			@param i  Index into font family. From 0 to < CountFontFaces
			@param s  String to append name to. Be careful. s may have a different
				script than the writingscript of the font and the Append will not
				work correctly
		 */
		virtual void AppendStyleNameNative(int32 i, PMString& s) const = 0;

		/**	Appends the native full font name to string. Full name can be family
			name plus style name but it is not always. This is the full font
			name for the writing script. So if the font is Japanese writing
			script the Native name will be Japanese.
			@param i  Index into font family. From 0 to < CountFontFaces
			@param s  String to append name to. Be careful. s may have a different
				script than the writingscript of the font and the Append will not
				work correctly
		 */
		virtual void AppendFullNameNative(int32 i, PMString& s) const = 0;

		

		/**	This will give you an index into the font family for the face given.
			If you want only the plain or regular style and to fail otherwise call CorrectVariantIndex with "Regular".
			You will then get -1 if no regular style.
			Regular style is either - "R", "Roman", "Regular", "Book", "Plain", "Normal". Likewise if you want
			Italic style call with face = "Italic", for bold face = "Bold" for bold italic face = "Bold Italic". These
			will match against other names for italic, bold and bold italic. Then call AppendStyleName with index to
			find the actual name the family uses for italic, bold or bold italic.
			
			WARNING: In the face of Document-installed fonts, the index returned is problematic and deprecated.
			The face may be available yet this function may still return -1.

			@param face  Face to find. Do not pass native style names as they will
				not be found. -1 is returned if face name is not found.
			@return int32  Index into the font family.
		 */
		virtual int32 CorrectVariantIndex(const PMString& face) const = 0;

		/**
			Retrieve a font from this family using a non native style name
		
			@param	face			name of the font style. only works for non native style names
			@param	style			font style bits
			@param	smallcapscale	used when style bits are set to kSmallCaps to set small cap scale
			@return	IPMFont*		font found. check for nil and FontStatus() == IPMFont::kFontInstalled to see if the font is installed.
		*/
		virtual IPMFont* QueryFace(const PMString& face, 
					IFontMgr::FontStyleBits style = IFontMgr::kNormal,
					PMReal smallcapscale = 0.7) = 0;

		/**
			Attempt to auto activate the font. If a font is missing you can call this to see if the font can be activated.
		
			@param	face			name of the font style. only works for non native style names
			@param	style			font style bits
			@param	smallcapscale	used when style bits are set to kSmallCaps to set small cap scale
			@return	bool16			kTrue if font is now available
		*/
		virtual bool16 AttemptAutoActivation(const PMString& face,
					IFontMgr::FontStyleBits style = IFontMgr::kNormal, 
					PMReal smallcapscale = 0.7) = 0;

		/**
			Returns true if font face name is available in family.
			WARNING: A true result does NOT imply that GetVariantIndex or CorrectVariantIndex will return a non-negative integer.
			In the face of Document-installed fonts, such an index is problematic and deprecated.

			@param	face	face check if available in family
			@param	style	style bits
			@param	smallcapscale
			@param	oldTech	OBSOLETE. was used to change font type in family. Now
				family must always keep original font type.
			@param	newTech	OBSOLETE. was used to change font type in family. Now
				family must always keep original font type.
			@param	resetTechnology	OBSOLETE. was used to change font type in family. Now
				family must always keep original font type.
			@return	bool16	kTrue if face is available in family. kFalse if it is not.
		*/
		virtual bool16 IsFaceAvailable(const PMString& face, 
					IFontMgr::FontStyleBits style = IFontMgr::kNormal,
					PMReal smallcapscale = 0.7,
					int32 *oldTech = nil, int32 *newTech = nil, bool16 resetTechnology = kFalse) = 0;

		/**
			Dysfunctional fonts are a special kind of missing font.

			There are 2 reasons a family is dysfunctional.
			1. Family was converted from an old InDesign document and during conversion the family was missing so we mark
			the font as dysfunctional until the family is available.
			2.  Family was created while importing a document. For example, PageMaker or Word document. During
			the import the family could not be found so the font is marked as dysfunctional.
		
			@return	bool16	kTrue if font is dysfunctional
		*/
		virtual bool16 IsDysfunctional() const = 0;

		/**
			Get postscript font name for this font style name.
		
			@param	face				name of the font style. only works for non native style names
			@param	getOnlyRealPSName	if true only real name returned if not available kNullString is returned.
										false will return either the default postscript font name(for the family)
										or if that is not available(as in dysfunctional fonts) it returns the fontfamily name.

			@return	PMString&		postscript name of the font.
		*/
		virtual PMString GetFacePostscriptName(const PMString& face, bool16 getOnlyRealPSName = kFalse) const = 0;

		/**
			Returns a string containing the non native font style name that is the opposite of the face
			passed in. So passing in "Bold" with Bold toggle gives you "Regular".
		
			@param	face		font style to toggle
			@param	toggle		how to toggle the font style
			@return	PMString	result of font style toggle
		*/
		virtual PMString ToggleBoldItalic(const PMString& face, 
					IFontMgr::FontStyleBits toggle) = 0;		

		/**
			Gets the native font style name
		
			@param	face			name of the font style. only works for non native style names
			@param	style			font style bits
			@param	smallcapscale	used when style bits are set to kSmallCaps to set small cap scale
			@return	PMString&		native font style name
		*/
		virtual PMString GetFaceNativeName(const PMString& face,
					IFontMgr::FontStyleBits style = IFontMgr::kNormal,
					PMReal smallcapscale = 0.7) = 0;

		/** sets the best full name to fontString, returns fontString, sets translation and
			script; called i.e. by DocumentFontUsage and MissingFontsController.
			@param faceName 
			@param &fontString 
			@return const 
		 */
		virtual PMString GetDisplayFullName( const PMString& faceName, PMString &fontString ) = 0;
		
		/**
			Only used by dysfunctional fonts
		
			@param	FontFaceMappingInfo
		*/
		virtual void SetFontFaceMappingInfo(FontFaceMappingInfo& FontFaceMappingInfo) = 0;
		/**
			Only used by dysfunctional fonts
		
			@param	faceName
			@return	FontFaceMappingInfo&
		*/
		virtual const FontFaceMappingInfo& GetFontFaceMappingInfo(const PMString &faceName) const = 0;
		/**
			Only used by dysfunctional fonts
		
			@param	faceName
			@return	bool16
		*/
		virtual bool16 FontFaceMappingInfoIsSet(const PMString &faceName) const = 0;

		/**
			Only used by codependent fonts. All other return kInvalidUID
		
			@return	UID		UID of font family this family is related to
		*/
		virtual UID GetDependentFamily() const = 0;

		/**	Whether this font should be flattened in the font menu. This is true for non-OTF
			Japanese fonts.
			@return bool16  Font Family should have all styles shown as separate groups in the
				font menu.
		 */
		virtual bool16 IsFlattened() const = 0;


		/**	Get a unique identifier for this font family
			@return IFontGroupId 
		 */
		virtual IFontGroupId *QueryFontGroupUniqueID() const = 0;

		/**	Set a unique identifier for this font family
			@param fontGroupID 
		 */
		virtual void SetFamilyWithFontGroupID( const IFontGroupId *fontGroupIDPtr ) = 0;
		
		/**
			Given a style name reports if that font is bad and what is the file path to the bad font
		
			@param	styleName	font to evaluate
			@param	badFontPath	OUT if font is bad the file path is returned. Trying to QueryFont
								and using IPMFont->GetFullPath will not return the correct path for bad fonts.
			@return	bool16		kTrue if font is bad
		*/
		virtual bool16 IsBadFont(const PMString &styleName, PMString &badFontPath) const = 0;

		/**
			Get the name of the family to display in the ui. For families that have the same
			name as another family the font type is added. Ex. (TT) for TrueType
		
			@return	PMString&	display name for the family
		*/
		virtual const PMString GetDisplayFamilyName() const = 0;

		/** Get font type for index in family. dysfuntional and codependent will always return kUnknownFontType.
			This will return values for missing families for the font that used to be installed
			@param styleName	style name of font.
			@return IPMFont::FontType font type
		 */
		virtual IPMFont::FontType GetFontType(const PMString &styleName) const = 0;

		/**	This will give you an index into the font family for the default style. This will be the plain or
			regular style when available. If no plain or regular style it will be the first style. Regular style 
			is either - "R", "Roman", "Regular", "Book", "Plain", "Normal". If you want only the plain or regular
			style and to fail otherwise call CorrectVariantIndex with "Regular". You will then get -1 if no regular
			style.

			@return int32  Index into the font family for default style.
		 */
		virtual int32 GetDefaultStyleIndex() const = 0;
		
		/** Get font version for index in family. dysfuntional and codependent will always return empty string.
			This will return values for missing families for the font that used to be installed
			@param styleName	style name of font.
			@return WideString	font version
		 */
		virtual WideString GetFontVersion(const PMString &styleName) const = 0;

		/** Updates the font versions in family to currently installed fonts.
			These are the versions returned by GetFontVersion. We currently only update these when a
			font family is copied to a new database in ConvertReference. 
			missing families will not be reset as there is no installed font to get a version from.
		 */
		virtual void UpdateFontVersions() = 0;

		/**	This will give you an index into the font family for the face given.
			Regular style is either - "R", "Roman", "Regular", "Book", "Plain", "Normal". Likewise if you want
			Italic style call with face = "Italic", for bold face = "Bold" for bold italic face = "Bold Italic". These
			will match against other names for italic, bold and bold italic. Then call AppendStyleName with index to
			find the actual name the family uses for italic, bold or bold italic.

			This function differs from CorrectVariantIndex in that it returns an
			index even when the font is missing.
			
			WARNING: In the face of Document-installed fonts, the index returned is problematic and deprecated.
			The face may be available yet this function may still return -1.

			@param face  Face to find. Do not pass native style names as they will
				not be found. -1 is returned if face name is not found.
			@return int32  Index into the font family.
		 */
		virtual int32 GetVariantIndex(const PMString& face) const = 0;

		//----------DISCOURAGED ROUTINES---------------

		/** This is to be used only by internal font management code.
			@param &fontEntry
		 */
		virtual void AddMissingFontEntry( const FontEntry &fontEntry ) = 0;		

        /** Get the Typekit status of font for index in family. dysfuntional and codependent will always return kFalse.
         This will return values for missing families for the font that used to be installed
         @param styleName	style name of font.
         @return bool16		whether from typekit or not
         */
        virtual bool16 IsTypekitFont(const PMString &styleName) const = 0;

		/**
            Get the typekit ID of the font
         
            @return PMString  typekit font id, if it is a typekit subscribed font, else empty string.
        */
        virtual PMString GetTypekitFontID(const PMString &styleName) const = 0;
    
        /**
            Get Style name, given design axes of font instance. To be called only for custom instances of variable fonts having single dict.
         
            @return PMString Style name of font instance.
         */
        virtual PMString GetStyleNameFromDesignAxes(const Fixed* designAxes, int32 numAxes, PMString parentStyleName) = 0;
    
        /**
            Get design axes of font instance, given style name. To be called only for custom instances of variable fonts having single dict.
         
            @return Fixed* Design Axes of font instance.
         */
        virtual Fixed* GetDesignAxesFromStyleName(const PMString& styleName, int32& numAxes) = 0;
    
        /**
            Checks whether a given variant is a Named Instance or Custom Instance of variable font family.
            If called for non-variable font families, it always returns kFalse.
         
            @return bool16 kTrue if instance is a custom instance of variable font family, kFalse otherwise.
         */
        virtual bool16 IsCustomVariableFont(const PMString& variant) = 0;
};

#endif
		//__IFontFamily__

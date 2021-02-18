//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFontMgr.h $
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
//  
//  Purpose:
//  IFontMgr is the Interface used to retrieve Fonts, FontGroups, etc.
//  The Interfaces returned are not boss objects (as of 10/17/96) but are RefCounted objects
//  
//========================================================================================

#pragma once
#ifndef __IFontMgr__
#define __IFontMgr__

#include "FontMgrID.h"
#include "PMString.h"
#include "PMMatrix.h"

#include "BravoForwardDecl.h"

#include <string>		// for virtual std::string GetDefaultFontPSName()


class IPMFont;
class IFontInstance;
class IFontGroup;
class FontGroupIteratorCallBack;
class IUsedFontList;
class IFontFamily;
class IWRFontContext;
class IFontMenuData;

class IPMFont;
class UIDList;

//----------------------------------------------------------------------------------------
// Interface IFontMgr
//----------------------------------------------------------------------------------------

/** Manager for fonts. CoolType is for Adobe Internal use only. All PMStrings used in
	IFontMgr are expected to not be translatable. If you create a PMString to pass to
	IFontMgr you sould set it to no translate.
	@ingroup text_font
*/
class IFontMgr : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IFONTMGR };

		enum FontStyleBits{ kNormal		= 0x00, kItalic		= 0x01, kBold		= 0x02, kBoldItalic = 0x03,
					   kSmallCaps	= 0x04, kCapStyles	= 0x04
				} ;

		enum WritingDirection{ kWD_LeftToRight = 0, kWD_RightToLeft, kWD_TopToBottom
				} ;

		/** Types for what kind of font to get from QueryFont */
		enum InternalFake{
					/** Get the installed font if available */
					kInternalFake_Not		= 0x0000,
					/** Create the font as missing even if installed */
					kInternal_Substitution = 0x0001,
					/** Gets a fake small cap font */
					kInternalFake_Smallcap = 0x0004
				} ;

		// matches CTOriginatingOS enum from cooltype.
		enum OriginalOS{
			kOriginalMacOS,
			kOriginalWinOS,
			kOriginalUnknownOS
		} ;

		/**
			Used by QueryFontPlatform to send back information about font.
		*/
		struct FontNameInfo
		{
			public:
				typedef object_type data_type;
				PMString	fPostScriptName;
				PMString	fFamilyName;
				PMString	fStyleName;
				PMString	fFamilyNameNative;
				PMString	fStyleNameNative;
				/** Out parameter. Is kTrue if font info was set. */
				bool16		fFontInfoSet;
		} ;

		/**
			returns current seed -- use this to detect changes

			@param	fullCheck	causes cooltype to check the system for font changes.
			@param	cooltypeSeedOnly	returns only cooltype seed. cooltype seed only changes when the font
								list has changed. The other seed changes when opening a document with missing
								fonts that are now present.
			@return	int32		new seed
		*/
		virtual int32 CurrentFontSystemSeed(bool16 fullCheck = kFalse, bool16 cooltypeSeedOnly = kFalse) const = 0;

		/**
			Called on application quit to clean up.

		*/
		virtual void CoolTypeShuttingDown() = 0;

		/**
			Gets postscript name of default font

			@return	PMString&	postscript name of default font
		*/
		virtual const PMString& GetDefaultFontName() = 0;

		/**
			Sets default font name. This sets the text default font this font is used in many places. DO NOT CHANGE
			this unless you really know what you are doing. This code will only allow you to set a font that is available
			and not corrupt (a bad font).

			@param	s	postscript name of font to set as default
		*/
		virtual void SetDefaultFontName(const PMString& s) = 0;

		/**
			Returns whether a postscript font name is installed. checks that FontStatus() == IPMFont::kFontInstalled

			@param	fontname	postscript font name to check
			@param	writingscript	here for completeness and is passed into QueryFont but I think it has no purpose.
									Recommend to use default parameter of kDontKnowScript.
			@return	bool16	kTrue if font with postscript name is installed. kFalse if not.
		*/
		virtual bool16 IsFontAvailable(const PMString &fontname, int32 writingscript = kDontKnowScript) = 0;

		/**
			Returns whether an IPMFont is installed and suitable for general content display.

			@param	pmFont	font instance to check
			@return	bool16	kTrue if font is installed and suitable for general content display. kFalse if font is not
							installed or if it carries a truncated or otherwise unsuitable glyph complement.
		*/
		virtual bool16 IsSuitableUIFont(IPMFont* pmFont) = 0;

		/**
			Retrieve a font using a postscript name, may return nil for fonts not found

			@param	fontName		postscript font name
			@param	style			font style bits
			@param	writingscript	writing script will be used if font is not found to find an appropriate substitute.
									values for script can be found in SDKDef.h
			@param	smallcapscale	used when style bits are set to kSmallCaps to set small cap scale
			@param	fake			passing in kInternal_Substitution forces resulting IPMFont to be missing even if postscript
									name font is installed. Calling GetFontStatus on the IPMFont will return IPMFont::kFontSubstituted
			@return	IPMFont*		font found. check for nil and FontStatus() == IPMFont::kFontInstalled to see if the font is installed.
		*/
		virtual IPMFont* QueryFont(const std::string &fontName, FontStyleBits style = kNormal, int32 writingscript = kDontKnowScript,
								PMReal smallcapscale = 0.7, InternalFake fake = kInternalFake_Not) = 0;

		/**
			Retrieve a font using a postscript name, may return nil for fonts not found

			@param	fontName		postscript font name
			@param	style			font style bits
			@param	writingscript	writing script will be used if font is not found to find an appropriate substitute.
									values for script can be found in SDKDef.h
			@param	smallcapscale	used when style bits are set to kSmallCaps to set small cap scale
			@param	fake			passing in kInternal_Substitution forces resulting IPMFont to be missing even if postscript
									name font is installed. Calling GetFontStatus on the IPMFont will return IPMFont::kFontSubstituted
			@return	IPMFont*		font found. check for nil and FontStatus() == IPMFont::kFontInstalled to see if the font is installed.
		*/
		virtual IPMFont* QueryFont(const PMString &fontName, FontStyleBits style = kNormal, int32 writingscript = kDontKnowScript,
								PMReal smallcapscale = 0.7, InternalFake fake = kInternalFake_Not) = 0;

		/**
			Retrieve a font using IFontGroup and font style index, may return nil for fonts not found

			@param	fontGroup		font group
			@param	index			font style index
			@param	style			font style bits
			@param	smallcapscale	used when style bits are set to kSmallCaps to set small cap scale
			@param	fake			passing in kInternal_Substitution forces resulting IPMFont to be missing even if postscript
									name font is installed. Calling GetFontStatus on the IPMFont will return IPMFont::kFontSubstituted
			@return	IPMFont*		font found. check for nil and FontStatus() == IPMFont::kFontInstalled to see if the font is installed.
		*/
		virtual IPMFont* QueryFont(const IFontGroup *fontGroup, int32 index, FontStyleBits style = kNormal,
								PMReal smallcapscale = 0.7, InternalFake fake = kInternalFake_Not) = 0;

		/**
			this method useful for converting raw CoolType fonts into InDesign style fonts

			@param	rawFont			CoolType font dictionary
			@param	fake			passing in kInternal_Substitution forces resulting IPMFont to be missing even if postscript
									name font is installed. Calling GetFontStatus on the IPMFont will return IPMFont::kFontSubstituted
			@param  index			index of font style (Named Instance of variable font dict) in dictionary. Used in case of variable fonts as in variable fonts single dictionary 
									can contain multiple styles. otherwise use -1.
			@param	bIsEPSFont
			@param	bIsEmbeddedFont
			@param	encoding
			@return	IPMFont*		font found. check for nil and FontStatus() == IPMFont::kFontInstalled to see if the font is installed.
		*/
		virtual IPMFont* QueryFont(const CTFontDict* rawFont, InternalFake fake = kInternalFake_Not, int32 index = -1,
					bool16 bIsEPSFont = kFalse, bool16 bIsEmbeddedFont = kFalse, CCTEncoding *encoding = nil) = 0;

		/**
			this method useful for converting raw CoolType fonts into InDesign style fonts

			@param	rawFont			CoolType font dictionary
			@param  designAxes		design axis of required variable font in rawFont (CTFontDict). if nullptr passed then Default face of font is applied. 
			@param	fake			passing in kInternal_Substitution forces resulting IPMFont to be missing even if postscript
									name font is installed. Calling GetFontStatus on the IPMFont will return IPMFont::kFontSubstituted
			@param	bIsEPSFont
			@param	bIsEmbeddedFont
			@param	encoding
			@return	IPMFont*		font found. check for nil and FontStatus() == IPMFont::kFontInstalled to see if the font is installed.
									return font with given design axis, if given design axis is null then default font design axis used
		*/
		virtual IPMFont* QueryFont(const CTFontDict* rawFont, Fixed *designAxes, InternalFake fake = kInternalFake_Not,
			bool16 bIsEPSFont = kFalse, bool16 bIsEmbeddedFont = kFalse, CCTEncoding *encoding = nil) = 0;

		/**
			this method is for getting InDesign fonts from edge information. If nameInfo is non nil it will
			be filled with info on the font. In the case that the font is installed this info is obtained
			from the font. In the case that the font does not exist on the system then we try to obtain this
			info from the FontNames.db file. outNameInfo->fFontInfoSet is set to kTrue if this info was successfully
			filled out.

			@param	fontName		platform font name
			@param	style			font style bits
			@param	ctScript		Can be any of the writing scripts.  If kDontKnowScript is given, the first match for a
									given operating system is returned. values for script can be found in SDKDef.h
			@param	os				operating system the platform font name came from
			@param	outNameInfo		OUT font information for the platform name
			@return	IPMFont*		font found. check for nil and FontStatus() == IPMFont::kFontInstalled to see if the font is installed.
		*/
		virtual IPMFont* QueryFontPlatform(const PMString &fontName, FontStyleBits style,
			int32 ctScript = kDontKnowScript, OriginalOS os = kOriginalUnknownOS, FontNameInfo* outNameInfo = nil) = 0;

		/**
			retrieve an instance of a font, will return nil for non-existant fonts

			@param	fontName		postscript font name
			@param	matrix			This matrix describes the user space to device space transformation for the
									characters.  Note that: 1. Only the first 4 values of the matrix are used. The
									x and y translation are ignored (it is a 2 x 2 matrix). 2.  The matrix is treated as
									the entire user space to device space matrix (it will not be concatenated with any
									"current transformation matrix" before being used).
									matrix(12.0, 0.0, 0.0, 12.0, 0.0, 0.0) is a 12 point font instance
			@param	writingscript	writing script will be used if font is not found to find an appropriate substitute.
									values for script can be found in SDKDef.h
			@param	dir				writing direction
			@param	style			font style bits
			@param	designV			for multiple master font. Same as IPMFont GetNumDesignAxes
			@param	smallcapscale	used when style bits are set to kSmallCaps to set small cap scale
			@return	IFontInstance*	font instance for given parameters
		*/
		virtual IFontInstance *QueryFontInstance(const PMString &fontName, const PMMatrix &matrix, int32 writingscript = kDontKnowScript, WritingDirection dir = kWD_LeftToRight,
						 FontStyleBits style = kNormal, Fixed *designV = nil, PMReal smallcapscale = 0.7) = 0;
		/**
			retrieve an instance of a font, will return nil for non-existant fonts

			@param	font			font to get instance for
			@param	matrix			This matrix describes the user space to device space transformation for the
									characters.  Note that: 1. Only the first 4 values of the matrix are used. The
									x and y translation are ignored (it is a 2 x 2 matrix). 2.  The matrix is treated as
									the entire user space to device space matrix (it will not be concatenated with any
									"current transformation matrix" before being used).
									matrix(12.0, 0.0, 0.0, 12.0, 0.0, 0.0) is a 12 point font instance
			@param	dir				writing direction
			@return	IFontInstance*	font instance for given parameters
		*/
		virtual IFontInstance *QueryFontInstance(const IPMFont* font, const PMMatrix &matrix, WritingDirection dir = kWD_LeftToRight) = 0;

		/**
			retrieve a font group

			@param	groupName		known as group name or family name. can be either native or non native.	if more than
									one group with same name this returns the first one found. Calling IFontGroup->GetGroupsWithSameName
									will return other groups with same name.
			@return	IFontGroup*		font group found. nil if none found
		*/
		virtual IFontGroup *QueryFontGroup(const PMString &groupName) = 0;
		/**
			retrieve a font group

			@param	groupIndex		index of group. must be less than GetNumFontGroups
			@return	IFontGroup*		font group found. nil if not found
		*/
		virtual IFontGroup *QueryFontGroup(int32 groupIndex) = 0;

		/**
			Returns the number of font groups installed

			@return	int32	number of font groups installed
		*/
		virtual int32 GetNumFontGroups() = 0;

		/**
			Iterate over font groups, calling back into FontGroupIteratorCallBack...

			@param	callBack
		*/
		virtual void IterateFontGroups( FontGroupIteratorCallBack *callBack ) = 0;

		/**
			Forces an update and re-initializes the Font Manager

		*/
		virtual void ForceUpdateFontSystem() = 0;

		/**
			Given a base font, find a styled variant.

			@param	basefont		font to find variant of
			@param	stylebits		style bits
			@param	smallcapscale	used when style bits are set to kSmallCaps to set small cap scale
			@param	technology		use -1 for any technology
			@return	IPMFont*		variant font
		*/
		virtual IPMFont *FindVariant (IPMFont *basefont, FontStyleBits stylebits, PMReal smallCapScale, int32 technology) = 0;

		/**
			Mark a font dict as bad. Most likely because font dict has errors and could crash

			@param	badFontDict	cooltype dictionary to mark bad
		*/
		virtual void MarkBadFont (CTFontDict *badFontDict) = 0;

		/**
			Finds a font given a display family name and font style.

			@param	displayFamilyName	family name as it shows in the menu
			@param	fontStyle			style of font to find
			@return	IPMFont*			font found
		*/
		virtual IPMFont *QueryFontFromDisplayName(const PMString &displayFamilyName, PMString &fontStyle) = 0;

		/**
			Adds a font to the font set that this FontMgr manages. Each document has its own
			FontMgr now.
		*/

		virtual void AddFont (CTFontDict *dict) = 0;
		virtual void DeleteFont (CTFontDict *dict) = 0;

		/**
			Gets postscript name of default font.

			@param	ctScript		Can be any of the writing scripts.  If kDontKnowScript is given, the default script for the current
									locale is used. values for script can be found in SDKDef.h
			@return	std::string		postscript name of default font
		*/
		virtual std::string GetDefaultFontPSName(int32 script = kDontKnowScript) = 0;

		/**
			Gets world ready font context

			@return	IWRFontContext*		world ready font context
		*/
		virtual IWRFontContext* GetWRFontContext() const = 0;

		/** Internal Use only */
		virtual void AllowPurge() = 0;
		virtual void DisallowPurge() = 0;

		virtual void AddDirectory(IDFile fontsPath) = 0;
		virtual	void RemoveUnusedFontsFromCache() = 0;

		virtual ActionID IterateTypeQuestFonts(const ActionID lastLocalActionID, IFontMenuData* fontMenuData) = 0;
		virtual HarfbuzzCooltype* GetHarfbuzzFontAccess() = 0;
		virtual bool16 AddCustomOTVarInstance(IFontGroup *fontGroup, const Fixed *designAxis) = 0;
    
        /** Internal Use only */
    
        /**
         Returns True if a variable font dictionary has a default font instance,
         that is not the same as one of the named instances.
         For non-variable fonts, always returns False.
         */
        virtual bool16 HasExtraDefaultVariableFont(CTFontDict* dict) const = 0;
    
        /** Internal Use only */
    
        /**
         Given a variable font dict, returns the font name of the default font instance in fontName.
         */
        virtual void GetDefaultVariableFontName(PMString& fontName, CTFontDict* dict) const = 0;
};



//----------------------------------------------------------------------------------------
// Class FontGroupIteratorCallBack
//----------------------------------------------------------------------------------------

/** Parameter for IFontMgr::IterateFontGroups()
	@ingroup text_font
*/
class FontGroupIteratorCallBack
{
public:
	enum	MissingFonts { 	kSkip, 				// skip missing fonts.
							kBeforeFonts,		// iterate missing fonts before the other fonts.
							kAfterFonts,		// iterate missing fonts after the other fonts.
							kOnly				// iterate only over missing fonts, skip the other fonts.
						 };

	/**
		Called at the start of the iteration, first call

	*/
	virtual void	OnStart() = 0;

	/**
		Called at the end of the iteration, last call

	*/
	virtual void	OnEnd() = 0;

	/**
		Called before the fonts that use locale writing script are being colected.

	*/
	virtual void	OnLocaleScriptFontsStart() = 0;

	/**
		Called after the fonts that use locale writing script are being colected.

	*/
	virtual void	OnLocaleScriptFontsEnd() = 0;

	/**
		Called before multiple master fonts are being colected.

	*/
	virtual void	OnMMFontsStart() = 0;
	/**
		Called after multiple master fonts are being collected.

	*/
	virtual void	OnMMFontsEnd() = 0;
	/**
		Called for each multiple master instance

		@param	pFont		multiple master font
		@param	sourceAxes	axes
		@param	numAxes		number of axes
	*/
	virtual void	OnMMAxes( IPMFont *pFont, const Fixed *sourceAxes, int32 numAxes ) = 0;


	/**
		Called for each item

		@param	pFont		font to iterate
		@param	fontGroup	font group font belongs to
		@param	displayFamilyName	name for family as it shows in font menu
		@param	displayStyleName	name for font style as it shows in font menu
	*/
	virtual void	OnFont( IPMFont *pFont, IFontGroup *fontGroup, const PMString &displayFamilyName, const PMString &displayStyleName ) = 0;

	/**
		Called at the start of a font group

		@param	fontGroup	font group we are starting to iterate
	*/
	virtual void	OnFontGroupStart( IFontGroup *fontGroup ) = 0;
	/**
		Called at the end of a font group

		@param	fontGroup	font group we are done iterating
	*/
	virtual void	OnFontGroupEnd( IFontGroup *fontGroup ) = 0;

	/**
		Called on script change

	*/
	virtual void	OnFontsAddedForLastScript() = 0;


	/** Called by FontGroupIterator; drives the iterator to skip styles
		@return	kTrue skip styles. kFalse iterate styles.
	 */
	virtual	bool16	RunFamilyOnly() const = 0;

	/**	Determines the format of names returned in OnFont
		@return	Names flag value. See enum ITextUtils::DisplayNamesFlag.
	 */
	virtual	int16	GetNamesFlag() const = 0;

	/**	Called by FontGroupIterator; drives the iterator to flatten MM Fonts.
		@return  kTrue iterate MM axes. kFalse only show Regular Style for MM fonts.
	 */
	virtual	bool16	RunMMFonts() const = 0;

	/**	Called by FontGroupIterator; drives the iterator to skip a font entirely.
		@param *font	font to choose to skip
		@return bool16	kTrue skip this font. kFalse iterate this font.
	 */
	virtual bool16  SkipThisFont( IPMFont *font ) const = 0;

	// missing fonts
	/**
		Called by FontGroupIterator. drives the iterator to flatten the menu to "Times Bold".

		@return	MissingFonts
	*/
	virtual	MissingFonts	RunMissingFonts() const = 0;
	/**
		Called before missing fonts are being colected

	*/
	virtual void			OnMissingFontsStart() = 0;
	/**
		Called after missing fonts are being colected.

	*/
	virtual void			OnMissingFontsEnd() = 0;
	/**
		Called by FontGroupIterator for missing fonts, usually front doc's IUsedFontList.

		@return	IUsedFontList*
	*/
	virtual IUsedFontList *	QueryUsedFontList() = 0;
	/**
		Called for each missing font

		@param	fontFamily
		@param	faceIndex
		@param	displayFamilyName
		@param	displayStyleName
	*/
	virtual void			OnMissingFont( IFontFamily *fontFamily, int32 faceIndex, const PMString &displayFamilyName, const PMString &displayStyleName ) = 0;

	/**
		Called by FontGroupIterator. drives the iterator to use the returned UIDList instead of the FontMgr.

		@return	UIDList*
	*/
	virtual	const UIDList *	UseFontUIDList() const = 0;
	/**
		Called by FontGroupIterator. drives the iterator to allow duplicate font names.

		@return	bool16
	*/
	virtual	bool16 			RunDuplicateFonts() const = 0;
};

#endif

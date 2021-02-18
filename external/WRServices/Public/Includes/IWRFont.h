//========================================================================================
//  
//  File: IWRFont.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __IWRFont__
#define __IWRFont__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRClass.h"
#include "IWRExtensionAttributeList.h"

#ifdef WR_WIN_ENV
#pragma warning(disable:4250)
#endif

/// Interface to internal font objects
/** this interface is used to access Lipika internal font structures, enabling a
minimal support for some basic functionality which are difficult to mimic accurately
**/

class WRSERVICES_DECL IWRFont : public WRClass
{
public:
	typedef enum { 
		kNotSupported =  0, 
		kSupportedThroughUnicode = 1, 
		kSupportedThroughOpenType = 2,
		kSupportThroughPlatformEncoding = 3
	}ScriptSupportTechnology;

	/// probing selector
	/** 
	these constants are use to identify specific traits in order to ask the font object 
	if and how they're supported. 
	Some of them are related only some scripts or script categories.
	**/
	typedef enum { 
		kCursivitySupport,				///< init / medi / fina shape selection
		kLigaturesSupport,				///< normal ligatures, usually expected (e.g. final beh-noon) (liga)
		kRequiredLigaturesSupport,		///< required ligatures (e.g. lam-alif) (rlig)
		kDiscLigaturesSupport,			///< ligatures those are usually not made by default (dlig)
		kDiacPositioningSupport,		///< combining mark positioning (mark)
		kLongKafSupport,				///< support for the elongated kaf variant (Arabic specific)
		kStretchSupport,				///< support for connection strecthing (Arabic specific) (strl-strr)
		kCanonSupport,					///< canonical decomposing support (ccmp)
		kAllCapsSupport,				///< support for all full size caps 
		kCapsToSmallCapsSupport,		///< support of replacing upper case glyphs by small capitals
		kLowercaseToSmallCapsSupport, 	///< support of replacing lower case glyphs by small capitals
		kCursivityPosSupport,			///< support for base letter cursive attachement (curs)
		kSanahSupport,					///< support of the sanah (Arabic year traditional layout)
		kEndOfAyahSupport				///< support of the end-of-ayah (Kuranic end of verse)
	} ScriptSupportSelector;

	virtual ~IWRFont() {}

	/// Get the font dictionary
	/**
	@return a IWRFontDict pointer representing the client concept of a font dictionary (font without a pt size)
	**/
	virtual WRFontDict* GetDict()= 0;

	virtual WRInt32		GetGlyphID(WRUnichar32 c, WRGlyphID32* glyphs, WRInt32 avail) = 0;
	virtual WRFloat		GetSpaceGlyphWidth() const = 0;
	virtual WRBool		IsMark(WRGlyphID32 id) = 0;
	virtual IWRExtensionAttributeList* GetExtensionAttributeList(void) = 0;

	virtual ScriptSupportTechnology ProbeBasicSupport(WRScriptID script,ScriptSupportSelector selector) = 0;

};

#endif

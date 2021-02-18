//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightArtworkTextInfo.h $
//  
//  Owner: Matt Phillips
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

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "GraphicTypes.h"
#include "IPreflightArtworkImage.h"

class IPreflightArtworkPaintInfo;

/**	This interface provides text and font information for a marking operation. This is broken
	out from IPreflightArtworkMarkInfo to avoid overwhelming that interface with text APIs.

	@see IPreflightArtworkMarkInfo
*/

class IPreflightArtworkTextInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTARTWORKTEXTINFO };

	/** Types returned by GetFontType. */
	typedef enum
	{
		kFontType_Invalid,
		kFontType_Type1,	
		kFontType_TrueType,
		kFontType_CID,	
		kFontType_ATC,	
		kFontType_Bitmap,	
		kFontType_OpenTypeCFF,	
		kFontType_OpenTypeCID,	
		kFontType_OpenTypeTT,	
		kFontType_Type3,
		kFontType_SVG
	} FontType;

	/** Types returned by GetFontTechnology. These are a slightly different way to slice
		the categorization and may differentiate between some of the above cases.
	*/
	typedef enum
	{
		kFontTech_Invalid,
		kFontTech_Type1,
		kFontTech_TrueType,
		kFontTech_CID,
		kFontTech_Bitmap,
		kFontTech_ATC,
		kFontTech_Type3,
	} FontTechnology;

public:
	/** Get the character matrix for a text marking operation. This is generally used to determine
		the 'native' point size of the text.

		@return The character matrix.
	*/
	virtual PMMatrix GetCharMatrix() const = 0;

	/** Get the text matrix for a text marking operation. This is a matrix that is applied at this
		marking operation's level to the text itself. This can be combined with GetAbsoluteMatrix
		from the marking operation to determine the overall matrix.

		@return The text matrix.
	*/
	virtual PMMatrix GetTextMatrix() const = 0;

		/** Get the number of glyphs for a text marking operation.
		@return Number of glyphs.
	*/
	virtual uint32 GetNumGlyphs() const = 0;

	/** Get the Nth glyph and associated information.
		@param n IN The index (0 to GetNumGlyphs() - 1) you're interested in.
		@param pWhere OUT If not nil, receives the XY location of the glyph.
		@param pIsValid OUT If not nil, recieves a boolean indicating whether this is a defined glyphID.
			(Note that this returns kFalse if the glyph is the font's not-defined glyph.)
		@return The glyph ID.
	*/
	virtual int32 GetNthGlyph(uint32 n, PMPoint* pWhere, bool* pIsValid) const = 0;

	/** Get the type of font used for a text marking operation.
		@return The font type.
	*/
	virtual FontType GetFontType() const = 0;

	/** Get the type of font technology used for a text marking operation.
		@return The font technology type.
	*/
	virtual FontTechnology GetFontTechnology() const = 0;

	/** Get whether the font is protected.
		@return True if protected; false otherwise.
	*/
	virtual bool GetFontIsProtected() const = 0;

	/** Get whether the font is real, as opposed to a substituted or fauxed font because the
		original font is not available.
		@return True if real; false otherwise.
	*/
	virtual bool GetFontIsReal() const = 0;

	/** Get the name of the font used for a text marking operation. Note that there is a specific
		hierarchy for determining this name:

		- If the font is a substitute for another font, returns the name of the font it was 
			substituted for.
		- Else, if a "full name" for the font is available, that's returned.
		- Else the postscript name of the font is returned.

		@return The name of the font.
	*/
	virtual PMString GetFontName() const = 0;

	/** @return true iff the font is CFF.
	*/
	virtual bool GetFontIsCFF() const = 0;

	/** @return true iff the font is a SING glyphlet.
	*/
	virtual bool GetFontIsSING() const = 0;

	/** @return true iff the font has outlines; if not, it's a bitmap.
	*/
	virtual bool GetFontHasOutlines() const = 0;

	/** @return true iff the font source was an embedded in EPS or PDF.
	*/
	virtual bool GetFontIsEmbedded() const = 0;

	/** @return true iff the font is a multiple master font.
	*/
	virtual bool GetFontIsMultipleMaster() const = 0;

};

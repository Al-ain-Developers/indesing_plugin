//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/utils/IFindChangeUtils.h $
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
#ifndef __IFindChangeUtils__
#define __IFindChangeUtils__

#include "IPMUnknown.h"

#include "WideString.h"
#include "K2Vector.h"
#include "CTextEnum.h"
#include "TextWalkerServiceProviderID.h"

class IFindChangeOptions;
class ITextModel;
class AttributeBossList;
class PMString;

/** ID to use to search for not def glyph. GetNotDefinedGlyph is different across different fonts.
    @see SearchForGlyph 
    @see IPMFont::GetNotDefinedGlyph 
*/ 
const Text::GlyphID kAnyNotDefGlyphID = -2;

class IFindChangeUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFINDCHANGEUTILS };

	virtual void		FindThisItem(const ITextModel* pModel, const WideString& findString,
										TextIndex nPosition, TextIndex nEnd,
										TextIndex& nFoundStart, TextIndex& nFoundEnd,
										const IFindChangeOptions* pFindChangeOptions,
										int32 allWildCardCount ) const = 0;


	/** Search text for glyph id. Font is assumed to have compatiable glyph ids for the range from findStart to findEnd.
			If glyph id is kAnyNotDefGlyphID or the not def glyph id for the font the wax is searched so overset text is not
			searched. Otherwise the text is searched and overset text can be returned. If kAnyNotDefGlyphID is used findStart
			and findEnd can cross fonts with different not def glyph ids and the not defs for each wax run will still be found.
			
		@param model		model to search in 
		@param option		not used
		@param value		glyph to search for. If kAnyNotDefGlyphID is used then IPMFont::GetNotDefinedGlyph is looked
								for in the wax.
		@param findStart	in: where to start searching
		@param findEnd		in: where to stop searching
		@param nFoundStart	out: found start
		@param nFoundEnd	out: found end
		@return				kTrue if glyph was found 
	*/ 
	virtual bool16 		SearchForGlyph(const ITextModel *pModel,
										const IFindChangeOptions* option,
										Text::GlyphID value,
										TextIndex findStart,
										TextIndex findEnd,
										TextIndex& nFoundStart,
										TextIndex& nFoundEnd) const = 0;

	virtual bool16		SearchForGrepText(const ITextModel *pModel,
											bool16 caseSensitive,
											bool16 widthSensitive,
											bool16 kanaSensitive,
											bool16 getEntireWord,
											const WideString &findString,
											TextIndex nPosition,
											TextIndex nEnd,
											TextIndex& nFoundStart,
											TextIndex& nFoundEnd,
											bool16 nestedStyles = kFalse,
											bool16 searchBackwards = kFalse) const = 0;

	virtual bool16		SearchForRawText(const ITextModel *pModel,
											bool16 caseSensitive,
											bool16 widthSensitive,
											bool16 kanaSensitive,
											bool16 getEntireWord,
											const WideString &findString,
											TextIndex nPosition,
											TextIndex nEnd,
											TextIndex& nFoundStart,
											TextIndex& nFoundEnd,
											const bool16 diacritics = kFalse,
											const bool16 kashidas = kFalse,
											bool16 searchBackwards = kFalse) const = 0;

	virtual bool16		SearchForCharStyle(const ITextModel* pModel, const UID& charStyleUID,
											TextIndex nFindStart, TextIndex nFindEnd,
											TextIndex& nFoundStart, TextIndex& nFoundEnd,
											bool16 searchBackwards = kFalse) const = 0;
	virtual bool16		SearchForParaStyle(const ITextModel* pModel, const UID& paraStyleUID,
											TextIndex nFindStart, TextIndex nFindEnd,
											TextIndex& nFoundStart, TextIndex& nFoundEnd,
											bool16 searchBackwards = kFalse) const = 0;
	virtual bool16		SearchForAttributes(const ITextModel* pModel, const AttributeBossList* list,
											TextIndex nFindStart, TextIndex nFindEnd,
											TextIndex& nFoundStart, TextIndex& nFoundEnd,
											bool16 searchBackwards = kFalse) const = 0;

	virtual bool16		SearchForROSFontGroup(const ITextModel* pModel, const AttributeBossList* list,
											const PMString& registry, const PMString& ordering,
											TextIndex nFindStart, TextIndex nFindEnd,
											TextIndex& nFoundStart, TextIndex& nFoundEnd,
											bool16 searchBackwards = kFalse) const = 0;

	virtual int32		SearchForAccessPath(const ITextModel *model,
											K2Vector<WideString>& accessPaths,
											TextIndex nFindStart,
											TextIndex nFindEnd,
											TextIndex& nFoundStart,
											TextIndex& nFoundEnd,
											bool16 searchBackwards = kFalse) const = 0;

	virtual void		UnescapeGrepFindString(const WideString& inStr, WideString& out, bool16 ignoreWidth = kFalse) const = 0;

};


#endif
		// __IFindChangeUtils__

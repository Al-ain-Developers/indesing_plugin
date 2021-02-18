//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/XRefBuildingBlock.h $
//  
//  Owner: Jianlan Song
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

// ----- Interfaces -----
#include "IPMStream.h"
#include "ITextModel.h"

// ----- Includes -----
#include <map>
#include "EscapeTable.h"

#ifdef PUBLIC_BUILD
#pragma export on
#endif

/** This class represents the building block object for cross reference format. 
	Cross reference formats contain one or more building block object(s) which 
	are used to construct the source content of the cross reference source referencing
	the format.
*/
class PUBLIC_DECL XRefBuildingBlock
{
public:	
   	typedef object_type data_type;

	/** Building block type enum
	*/
	enum XRefBuildingBlockType
	{
		kInvalidXRefBBType = -1,
		kXRefBBCustomString = 0,
		kXRefBBFileName,
		kXRefBBChapterNumber,
		kXRefBBPageNumber,
		kXRefBBFullParagraph,
		kXRefBBParagraphNumber,
		kXRefBBParagraphText,
		kXRefBBBookmarkName,
		kMaxXRefBBType,
	} ;
		
	XRefBuildingBlock() : fType(kInvalidXRefBBType), fCharStyleUID(kInvalidUID), fCustomText(), fIncludeDelim(kFalse) {}
	
	XRefBuildingBlock(XRefBuildingBlockType type) : fType(type), fCharStyleUID(kInvalidUID), fIncludeDelim(kFalse) {}
	XRefBuildingBlock(XRefBuildingBlockType type, UID charStyle) : fType(type), fCharStyleUID(charStyle), fIncludeDelim(kFalse) {}
	XRefBuildingBlock(const XRefBuildingBlock& block);

	~XRefBuildingBlock() {}

	XRefBuildingBlock& operator = (const XRefBuildingBlock &copy);
	bool16 operator==(const XRefBuildingBlock &other) const;
	bool16 operator != (const XRefBuildingBlock &other) const
		{ return !(*this == other); }
	
	/** Gets the type of the building block.
		@return XRefBuildingBlockType - type of the building block.
	*/
	XRefBuildingBlockType GetType() const { return fType; }
	/** Sets the type of the building block.
		@param type - type of the building block to be set to.
	*/
	void SetType(XRefBuildingBlockType type);

	/** Gets the character style applied to the building block.
		@return UID - UID of character style of the building block.
	*/
	UID GetCharacterStyle() const { return fCharStyleUID; }
	/** Sets the character style of the building block.
		@param charStyle - UID of character style to apply to the building block.
	*/
	void SetCharacterStyle(UID charStyle);

	/** Sets the custom text of the building block. Currently custom text is only
		applicable for custom string building block. It is ignored for other building
		blocks.
		@param customText - custom text for the building block.
	*/
	void SetCustomText(const PMString& customText);
	/** Gets the custom text of the building block. 
		@return PMString - custom text for the building block.
	*/
	PMString GetCustomText() const { return fCustomText; }

	/** Sets the delimiter character of the building block. 
		@param delim - delimiter character on the building block.
		@param includeDelim - kTrue if the delimiter should be included 
							in the generated source text. kFalse otherwise.
	*/
	void SetDelimiter(const UTF32TextChar& delim, bool16 includeDelim);
	void SetDelimiter(const UTF32TextChar& delim) { fDelim = delim; }
	void SetIncludeDelim(bool16 includeDelim) { fIncludeDelim = includeDelim; }
	/** Gets the delimiter character of the building block. 
		@return UTF32TextChar - delimiter character of the building block.
	*/
	UTF32TextChar GetDelimiter() const { return fDelim; }
	/** Gets the flag whether or not delimiter character should be included in
		the generated source content. 
		@return bool16 - kTrue if delimiter character is included in the source
						content. kFalse otherwise.
	*/
	bool16 IncludeDelimiter() const { return fIncludeDelim; }
	
	/** Generates the string to be inserted into format string for editing in UI. 
		@return PMString - generated string for UI editing.
	*/
	PMString GenerateElementString() const;
	/** Generates the source content string. 
		@param textModel - destination story of the cross reference.
		@param destIndex - text index of the destination marker.
		@param externDest - kTrue if the destination is in external document. kFalse otherwise.
		@param variableLocations - [OUT] List of text variables and their offset index in the source content.
		@param inlineLocations - [OUT] List of inline object offset index in the source content and the index in the destination story.
		@return PMString - generated source content.
	*/
	PMString GenerateSourceString(const ITextModel* textModel, TextIndex destIndex, bool16 externDest, 
		std::map<TextIndex, WideString>* variableLocations, std::map<TextIndex, TextIndex>* inlineLocations) const;
		
	void ReadWrite(IPMStream *s);

	static bool NeedToStripForParaNum(const UTF32TextChar& c);
	
private:	
	XRefBuildingBlockType fType;
	UID fCharStyleUID;
	PMString fCustomText;
	UTF32TextChar fDelim;
	bool16 fIncludeDelim;
};


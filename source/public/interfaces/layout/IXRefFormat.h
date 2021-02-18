//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IXRefFormat.h $
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

#include "IPMUnknown.h"
#include "IOwnedItem.h"

#include "HyperlinkID.h"

#include "XRefBuildingBlock.h"

#define kDefaultXRefFormatCount		9

/** Structure to cache sub ranges which need to apply character style in generated cross reference source string.
	@see IXRefFormat::GenerateSourceString
*/
typedef struct CharStyleRange
{
	typedef base_type data_type;
	
	CharStyleRange() : charStyle(kInvalidUID), startOffset(0), length(0) {}
	bool16 operator==(const CharStyleRange& s) const 
		{ return ( charStyle == s.charStyle && startOffset == s.startOffset && length == s.length); }
	
	UID charStyle;
	TextIndex startOffset;
	int32 length;
} CharStyleRange;

/** Abstract interface to cross reference format. Cross reference format is referenced 
	by cross reference source object. The format is used by the source to generate
	proper content string in the document. 
	@see kXRefBuildingBlockBoss 
*/
class IXRefFormat : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IXREFFORMAT };

	virtual void CopyData(const IXRefFormat* other) = 0;
	
	/**	Set the name of the format
		@param formatName - The new name to use
	 */
	virtual void			SetName(const PMString & formatName) = 0;
	/**	Get the name of the format (This name will be marked as translated)
		@return PMString - The name of the format
	 */
	virtual PMString		GetName() const = 0;

	/** Set/Get character style for the entire format
	*/
	virtual void SetCharacterStyle(UID charStyle) = 0;
	virtual UID GetCharacterStyle() const = 0;
	
	/**	Set the building blocks list to the format
		@param buildingBlocks - building blocks list used to initialize the internal structure private to the object.
	 */
	virtual void SetBuildingBlocks(const K2Vector<XRefBuildingBlock>& buildingBlocks) = 0;

	/**	Get the building blocks list of the format
		@param K2Vector<XRefBuildingblock>* - [OUT]list of building blocks.
	*/
	virtual void GetBuildingBlocks(K2Vector<XRefBuildingBlock>& buildingBlocks) const = 0;
	
	/**	Get the building blocks count.
		@return int32 - total count of building blocks 
	 */
	virtual int32 GetBuildingBlockCount() const = 0;

	/**	Get the n'th building block of the format.
		@param index - index of the building block
		@param buildingBlock - [OUT] building block returned
		@return bool16 - kTrue if we successfully retrieve the building block, kFalse otherwise. 
	 */
	virtual bool16 GetNthBuildingBlock(int32 index, XRefBuildingBlock& buildingBlock) const = 0;

	/** Checks if the format contains full paragraph or paragraph text building block.
		@return bool16 - kTrue if format contains paragraph text or full paragraph building block. kFalse otherwise.
	*/
	virtual bool16 HasParagraphBlock() const = 0;
	
	/**	Get the string representation of the building blocks in the format. 
		The string is used in the UI for editing building blocks.
		
		@return PMString - The string value of the building blocks
	 */
	virtual PMString GenerateBlocksString() const = 0;
	
	/**	Get the source string of the format for the specified destination marker
		@param destMarker - destination marker owned item
		@param isParagraphDest - kTrue if the destination is a paragraph destination
		@param charStyleRanges - contains ranges where to apply character styles
		@param pageNumLocations - offset of page numbers in the source string
		@param chapterNumLocations - offset of chapter numbers in the source string
		@param variableLoations - [OUT] text variables and their index offset in the source content
		@param inlineLocations - [OUT] inline objects index offset in the source content and corresponding index in destination story.
		@return PMString - The source string generated for the destination
		
	 */
	virtual PMString GenerateSourceString(const IOwnedItem* destMarker, bool16 isParagraphDest, K2Vector<CharStyleRange>& charStyleRanges,
	K2Vector<uint32>& pageNumLocations, K2Vector<uint32>& chapterNumLocations, std::map<TextIndex, WideString>* variableLocations,
	std::map<TextIndex, TextIndex>* inlineLocations) const = 0;
};



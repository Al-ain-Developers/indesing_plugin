//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/MetaChar.h $
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
#ifndef __METACHAR__
#define __METACHAR__

const char kMetaChar_AnyDoubleQuote[2] = 		{ '"', 0 };
const char kMetaChar_AnySingleQuote[2] = 			{ '\'', 0 };

//const char kMetaChar_xxxxxxx[3] = 				{ '^', '!', 0 };		// ! = Lines in nested styles

const char kMetaChar_StraightDoubleQuote[3] = 	{ '^', '"', 0 };
const char kMetaChar_PageNumber[3] =			{ '^', '#', 0 };
//const char kMetaChar_AnyPageNumber[3] = 			{ '^', '#', 0 };
const char kMetaChar_AnyLetter[3] =				{ '^', '$', 0 };
const char kMetaChar_SixthSpace[3] =				{ '^', '%', 0 };
const char kMetaChar_IdeographicSpace[3] = 		{ '^', '(', 0 };
const char kMetaChar_NonRomanSpecialGlyph[3] =	{ '^', '+', 0 };
const char kMetaChar_DiscretionaryHyphen[3] =		{ '^', '-', 0 };
const char kMetaChar_PunctuationSpace[3] =		{ '^', '.', 0 };
const char kMetaChar_FigureSpace[3] =				{ '^', '/', 0 };

const char kMetaChar_CopyrightSign[3] =			{ '^', '2', 0 };
const char kMetaChar_ThirdSpace[3] =				{ '^', '3', 0 };
const char kMetaChar_QuarterSpace[3] =			{ '^', '4', 0 };
const char kMetaChar_KatakanaMiddleDot[3] =		{ '^', '5', 0 };
const char kMetaChar_SectionSign[3] =				{ '^', '6', 0 };
const char kMetaChar_PilchrowSign[3] =			{ '^', '7', 0 };
const char kMetaChar_Bullet[3] =					{ '^', '8', 0 };
const char kMetaChar_AnyDigit[3] =				{ '^', '9', 0 };

const char kMetaChar_SpecialGlyph[3] =			{ '^', ';', 0 };
const char kMetaChar_EnDash[3] =					{ '^', '=', 0 };
const char kMetaChar_AnyCharacter[3] =			{ '^', '?', 0 };
const char kMetaChar_EnSpace[3] =				{ '^', '>', 0 };
const char kMetaChar_ThinSpace[3] =				{ '^', '<', 0 };

const char kMetaChar_LeftSingleQuotationMark[3] = { '^', '[', 0 };
const char kMetaChar_RightSingleQuotationMark[3] = { '^', ']', 0 };
//const char kMetaChar_SingleLeftQuote[3] = 			{ '^', '[', 0 };
//const char kMetaChar_SingleRightQuote[3] = 			{ '^', ']', 0 };
const char kMetaChar_StraightSingleQuote[3] = 		{ '^', '\'', 0 };
const char kMetaChar_CircumflexAccent[3] =		{ '^', '^', 0 };
const char kMetaChar_EmDash[3] =					{ '^', '_', 0 };

const char kMetaChar_LeftDoubleQuotationMark[3] = { '^', '{', 0 };
const char kMetaChar_RightDoubleQuotationMark[3] = { '^', '}', 0 };
//const char kMetaChar_DoubleLeftQuote[3] = 			{ '^', '{', 0 };
//const char kMetaChar_DoubleRightQuote[3] = 		{ '^', '}', 0 };
const char kMetaChar_HairSpace[3] =				{ '^', '|', 0 };
const char kMetaChar_NoBreakHyphen[3] =			{ '^', '~', 0 };



const char kMetaChar_Inline[3] =					{ '^', 'a', 0 };
const char kMetaChar_Gershayim[3] =				{ '^', 'A', 0 };
const char kMetaChar_AnyBreak[3] = 				{ '^', 'b', 0 };
const char kMetaChar_CBContentsFormatted[3] = 	{ '^', 'c', 0 };		// dropcap in nested styles
const char kMetaChar_CBContentsUnformatted[3] =	{ '^', 'C', 0 };
const char kMetaChar_OutputDateVariable[3] =		{ '^', 'D', 0 };
const char kMetaChar_TrademarkSign[3] =			{ '^', 'd', 0 };
const char kMetaChar_EvenPageBreak[3] = 			{ '^', 'E', 0 };
const char kMetaChar_Ellipsis[3] =					{ '^', 'e', 0 };
const char kMetaChar_FootnoteMarker[3] =			{ '^', 'F', 0 };
const char kMetaChar_FlushSpace[3] =				{ '^', 'f', 0 };
const char kMetaChar_FindInlineGraphic[3] =		{ '^', 'g', 0 };
const char kMetaChar_Geresh[3] =					{ '^', 'G', 0 };
const char kMetaChar_BreakRunInStyle[3] =			{ '^', 'h', 0 };
//const char kMetaChar_EndNestedStyle[3] = 			{ '^', 'h', 0 };
const char kMetaChar_ChapterNumberVariable[3] =	{ '^', 'H', 0 };
const char kMetaChar_IndexMarker[3] = 			{ '^', 'I', 0 };
const char kMetaChar_IndentToHere[3] =			{ '^', 'i', 0 };
const char kMetaChar_ZeroWidthNonJoiner[3] =		{ '^', 'j', 0 };
const char kMetaChar_MetadataCaptionVariable[3] =	{ '^', 'J', 0 };
const char kMetaChar_DiscretionaryLineBreak[3] =	{ '^', 'k', 0 };
const char kMetaChar_AnyKanji[3] =				{ '^', 'K', 0 };
const char kMetaChar_OddPageBreak[3] = 			{ '^', 'L', 0 };
const char kMetaChar_FileNameVariable[3] =		{ '^', 'l', 0 };
const char kMetaChar_ColumnBreak[3] = 			{ '^', 'M', 0 };
const char kMetaChar_EmSpace[3] =				{ '^', 'm', 0 };
const char kMetaChar_CurrentPageNumber[3] =	 	{ '^', 'N', 0 };
const char kMetaChar_LF[3] =						{ '^', 'n', 0 };
//const char kMetaChar_ForcedLineBreak[3] = 			{ '^', 'n', 0 };
const char kMetaChar_ModificationDateVariable[3] = { '^', 'o', 0 };
const char kMetaChar_CreationDateVariable[3] =	{ '^', 'O', 0 };
const char kMetaChar_CR[3] =						{ '^', 'p', 0 };
//const char kMetaChar_EndOfParagraph[3] = 			{ '^', 'p', 0 };
const char kMetaChar_PageBreak[3] = 				{ '^', 'P', 0 };
const char kMetaChar_Maqaf[3] =					{ '^', 'Q', 0 };
const char kMetaChar_FrameBreak[3] = 			{ '^', 'R', 0 };
const char kMetaChar_RegisteredSign[3] =			{ '^', 'r', 0 };
const char kMetaChar_HardSpace[3] =				{ '^', 'S', 0 };		// Sentence in nested styles
const char kMetaChar_NarrowNoBreakSpace[3] =	{ '^', 's', 0 };
const char kMetaChar_Tab[3] =						{ '^', 't', 0 };
const char kMetaChar_PageCountVariable[3] =		{ '^', 'T', 0 };
const char kMetaChar_CustomTextVariable[3] =		{ '^', 'u', 0 };
const char kMetaChar_EndnoteMarker[3] =			{ '^', 'U', 0 };
const char kMetaChar_PrevPageNumber[3] = 		{ '^', 'V', 0 };
const char kMetaChar_AnyVariable[3] =				{ '^', 'v', 0 };
const char kMetaChar_WhiteSpace[3] =				{ '^', 'w', 0 };		// Word in nested styles
const char kMetaChar_Kashida[3] =					{ '^', 'W', 0 };
const char kMetaChar_SectionName[3] =			{ '^', 'x', 0 };
//const char kMetaChar_SectionMarker[3] = 			{ '^', 'x', 0 };
const char kMetaChar_NextPageNumber[3] = 		{ '^', 'X', 0 };
const char kMetaChar_RightAlignedTab[3] =			{ '^', 'y', 0 };
const char kMetaChar_RunningHeaderPSVariable[3] =	{ '^', 'Y', 0 };
const char kMetaChar_RunningHeaderCSVariable[3] =	{ '^', 'Z', 0 };


#pragma export off

#endif	// __METACHAR__

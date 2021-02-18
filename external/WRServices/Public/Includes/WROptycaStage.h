//========================================================================================
//  
//  File: WROptycaStage.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WROPTYCASTAGE__
#define __WROPTYCASTAGE__

enum OptycaStage
{
	kStage_Char = 0,

	kGlyphStage_Nominal = 0x100,
	kGlyphStage_Canonical = 0x200,
	kGlyphStage_Cursive = 0x300,
	kGlyphStage_Ligatures = 0x400,
	kGlyphStage_JustificationAlternates = 0x500,
	kGlyphStage_JustificationStretches = 0x600,
	kGlyphStage_Final = kGlyphStage_JustificationStretches,
	kGlyphStage_Mask = 0x0000FF00,

	kPosStage_Basic = 0x1,
	kPosStage_Cursive = 0x2,
	kPosStage_Kerning = 0x3,
	kPosStage_InterKerning = 0x4,
	kPosStage_Mark = 0x5,
	kPosStage_UserOffsets = 0x6,
	kPosStage_Final = kPosStage_UserOffsets,
	kPosStage_Mask = 0x000000FF
};

#endif

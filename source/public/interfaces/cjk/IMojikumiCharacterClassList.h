//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IMojikumiCharacterClassList.h $
//  
//  Owner: Shinji Hiramatsu
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
#ifndef __IMojikumiCharacterClassList__
#define __IMojikumiCharacterClassList__


#include "IPMUnknown.h"
#include "CTextEnum.h"

class MojikumiCharacterClass;

enum {
	kMojikumi_DoubleByteCharacter = 0,
	kMojikumi_SingleByteCharacter,
	kMojikumi_BeginParagraph,
	kMojikumi_EdgeOfLine,
	
	kMojikumi_NumOfDefaultClass
};

class IMojikumiCharacterClassList : public IPMUnknown
{
	public:
		virtual void	Clear() = 0;
		virtual void	AddCharacterClass(MojikumiCharacterClass* charClass) = 0;
		virtual void	RemoveCharacterClass(MojikumiCharacterClass* charClass) = 0;
		virtual MojikumiCharacterClass*	GetCharacterClass(textchar code) = 0;
		virtual int32	GetCharacterClassIndex(textchar code) = 0;

		virtual MojikumiCharacterClass*	GetGlyphClass(Text::GlyphID glyph) = 0;
		virtual int32	GetGlyphClassIndex(Text::GlyphID glyph) = 0;

		virtual int32	GetNumOfCharacterClasses() const = 0;
		
		virtual int32	GetNumOfCharacters(int32 index) = 0;
		virtual PMString	GetCharacterClassName(int32 index) = 0;
		virtual void		SetCharacterClassName(int32 index, PMString& name) = 0;
		
		virtual int32	GetDefaultCharacterClassIndex(int16 defClass) const = 0;
};

#endif	// __IMojikumiCharacterClassList__

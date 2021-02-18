//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/WorldReadyScriptID.h $
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
//  
//  Usage rights licenced to Adobe Inc. 1993 - 2008.
//  
//  Contains script info IDs used by the text engine.
//  
//========================================================================================

#ifndef _H_WorldReadyScriptID
#define _H_WorldReadyScriptID

#include "IDFactory.h"

#include "WorldReadyID.h"

//Suites

//Objects

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kParagraphDirectionPropertyScriptElement,				kWorldReadyPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kParagraphJustificationPropertyScriptElement,			kWorldReadyPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kCharacterDirectionPropertyScriptElement,				kWorldReadyPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kDigitsPropertyScriptElement,							kWorldReadyPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kKashidasPropertyScriptElement,						kWorldReadyPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kDiacriticVPosPropertyScriptElement,					kWorldReadyPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kDiacriticXOffsetPropertyScriptElement,				kWorldReadyPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kDiacriticYOffsetPropertyScriptElement,				kWorldReadyPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kTableDirectionPropertyScriptElement,					kWorldReadyPrefix + 9)
DECLARE_PMID(kScriptInfoIDSpace, kOTFOverlapSwashPropertyScriptElement,					kWorldReadyPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kOTFStylistAltPropertyScriptElement,					kWorldReadyPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kOTFJustificationAltPropertyScriptElement,				kWorldReadyPrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kOTFStretchedAltPropertyScriptElement,					kWorldReadyPrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kKeyboardDirectionPropertyScriptElement,				kWorldReadyPrefix + 15)
DECLARE_PMID(kScriptInfoIDSpace, kIgnoreKashidasPropertyScriptElement,					kWorldReadyPrefix + 16)
DECLARE_PMID(kScriptInfoIDSpace, kIgnoreDiacriticsPropertyScriptElement,				kWorldReadyPrefix + 17)
DECLARE_PMID(kScriptInfoIDSpace, kChangeComposerScriptElement,				kWorldReadyPrefix + 18)
DECLARE_PMID(kScriptInfoIDSpace, kParagraphKashidaWidthPropertyScriptElement,			kWorldReadyPrefix + 19)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kParagraphDirectionEnumScriptElement,					kWorldReadyPrefix + 51)
DECLARE_PMID(kScriptInfoIDSpace, kParagraphJustificationEnumScriptElement,				kWorldReadyPrefix + 52)
DECLARE_PMID(kScriptInfoIDSpace, kCharacterDirectionEnumScriptElement,					kWorldReadyPrefix + 53)
DECLARE_PMID(kScriptInfoIDSpace, kDigitsEnumScriptElement,								kWorldReadyPrefix + 54)
DECLARE_PMID(kScriptInfoIDSpace, kKashidasEnumScriptElement,							kWorldReadyPrefix + 55)
DECLARE_PMID(kScriptInfoIDSpace, kDiacriticVPosEnumScriptElement,						kWorldReadyPrefix + 56)
DECLARE_PMID(kScriptInfoIDSpace, kTableDirectionEnumScriptElement,						kWorldReadyPrefix + 57)

#endif /* _H_WorldReadyScriptID */

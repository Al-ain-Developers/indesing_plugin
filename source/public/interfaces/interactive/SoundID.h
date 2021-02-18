//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/SoundID.h $
//  
//  Owner: xdx
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

#ifndef __SoundID__
#define __SoundID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kSoundPrefix 				RezLong( 0x14F00 )

//----------------------------------------------------------------------------------------
//
// PluginID
//

#define kSoundPluginName 			"Sound"
#define kSoundPluginID 				kSoundPrefix + 1

// Anna
#define kSoundAnnaRemoveImpls		kAnnaInitialMinorFormatNumber

// Add one of these for each product version.
#define kSoundLastAnnaMinorFormat	kSoundAnnaRemoveImpls

// Overall
#define kSoundLastFormatChg			kSoundLastAnnaMinorFormat


//----------------------------------------------------------------------------------------
//
// <Class ID>
//
DECLARE_PMID(kClassIDSpace, kSoundPageItemBoss, kSoundPrefix + 1)
DECLARE_PMID(kClassIDSpace, kSoundPlaceProviderBoss, kSoundPrefix + 2)
DECLARE_PMID(kClassIDSpace, kSetSoundFramePrefsCmdBoss, kSoundPrefix + 3)
DECLARE_PMID(kClassIDSpace, kSoundItemScriptProviderBoss, kSoundPrefix + 4)
DECLARE_PMID(kClassIDSpace, kTopSoundFrameAdornmentBoss, kSoundPrefix + 5)
//available
DECLARE_PMID(kClassIDSpace, kSoundInfoBoss, kSoundPrefix + 7)
DECLARE_PMID(kClassIDSpace, kSoundErrorStringServiceBoss, kSoundPrefix + 8)

//----------------------------------------------------------------------------------------
//
// <Interface ID>
//

DECLARE_PMID(kInterfaceIDSpace, IID_ISOUNDIMPORT, kSoundPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISOUNDSUITE, kSoundPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISOUNDATTRIBUTES, kSoundPrefix + 3)


//----------------------------------------------------------------------------------------
//
// <Implementation ID>
//

DECLARE_PMID(kImplementationIDSpace, kSoundStringRegisterImpl, kSoundPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSoundShapeImpl, kSoundPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kSoundPageItemScriptImpl, kSoundPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kSoundItemScriptProviderImpl, kSoundPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kSoundOLEAutoStubImpl,	kSoundPrefix + 5)
// gap
DECLARE_PMID(kImplementationIDSpace, kSoundAdornmentInfoImpl, kSoundPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kSoundInfoImpl, kSoundPrefix + 8)
// available
DECLARE_PMID(kImplementationIDSpace, kSoundSuiteAbstractImpl, kSoundPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kSoundSuiteASBSelExtImpl, kSoundPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kSoundSuiteDefaultImpl, kSoundPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kSoundSuiteLayoutImpl, kSoundPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kSoundSuiteLayoutSelExtImpl, kSoundPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kSoundAttributesImpl, kSoundPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kSoundErrorStringServiceImpl, kSoundPrefix + 17)

// Error
DECLARE_PMID(kErrorIDSpace, kSetSoundAttrFailedError,		kSoundPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kSoundAttrNotAvailableError,	kSoundPrefix + 2)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kSoundObjectScriptElement,						kSoundPrefix + 20)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kDoNotPrintPosterPropertyScriptElement,		kSoundPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kSoundPosterTypePropertyScriptElement,			kSoundPrefix + 161) // WHT: added 7/14/2003 [Vantive 616739]
DECLARE_PMID(kScriptInfoIDSpace, kSoundStopOnPageTurnPropertyScriptElement,		kSoundPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kSoundLoopForeverPropertyScriptElement,		kSoundPrefix + 163)
  
 //Enums
DECLARE_PMID(kScriptInfoIDSpace, kSoundPosterTypeEnumScriptElement,				kSoundPrefix + 240) // WHT: added 7/14/2003 [Vantive 616739]


#endif // __SoundID__

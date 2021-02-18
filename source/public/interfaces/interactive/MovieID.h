//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/MovieID.h $
//  
//  Owner: wtislar
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

#ifndef __MovieID__
#define __MovieID__


#include "CrossPlatformTypes.h"
#include "IDFactory.h"


#define kMoviePrefix 				RezLong( 0x14800 )


//----------------------------------------------------------------------------------------
//
// PluginID
//


#define kMoviePluginName 			"Movie"
#define kMoviePluginID 				kMoviePrefix + 1


// Anna
#define kMovieAnnaRemoveImpls		kAnnaInitialMinorFormatNumber


// Add one of these for each product version.
#define kMovieLastAnnaMinorFormat	kMovieAnnaRemoveImpls


// Overall
#define kMovieLastFormatChg			kMovieLastAnnaMinorFormat




//----------------------------------------------------------------------------------------
//
// <Class ID>
//

DECLARE_PMID(kClassIDSpace, kMoviePageItemBoss, kMoviePrefix + 1)
DECLARE_PMID(kClassIDSpace, kSetMovieAttrCmdBoss, kMoviePrefix + 2)
DECLARE_PMID(kClassIDSpace, kMoviePlaceProviderBoss, kMoviePrefix + 3)
// gap
DECLARE_PMID(kClassIDSpace, kMovieInfoBoss, kMoviePrefix + 5)
DECLARE_PMID(kClassIDSpace, kTopMovieFrameAdornmentBoss, kMoviePrefix + 6)
// gap
DECLARE_PMID(kClassIDSpace, kMovieItemScriptProviderBoss, kMoviePrefix + 8)
// gap
// available
//DECLARE_PMID(kClassIDSpace, kObsoleteMovieCloneBlobBoss, kMoviePrefix + 11)
//DECLARE_PMID(kClassIDSpace, kObsoleteCopySurrogateCmdMgrObsBoss, kMoviePrefix + 12)
DECLARE_PMID(kClassIDSpace, kNavigationPointScriptProviderBoss, kMoviePrefix + 13)
DECLARE_PMID(kClassIDSpace, kNavigationPointScriptObjectBoss, kMoviePrefix + 14)


//----------------------------------------------------------------------------------------
//
// <Interface ID>
//

DECLARE_PMID(kInterfaceIDSpace, IID_IMOVIEIMPORT, kMoviePrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTMOVIEATTRCMDDATA, kMoviePrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IMOVIEATTRIBUTES, kMoviePrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETMOVIEATTRCMDDATA, kMoviePrefix + 4)
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_IMOVIESUITE, kMoviePrefix + 8)

//----------------------------------------------------------------------------------------
//
// <Implementation ID>
//

DECLARE_PMID(kImplementationIDSpace, kMovieAttributesImpl, kMoviePrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kMovieStringRegisterImpl, kMoviePrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kMovieShapeImpl, kMoviePrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kSetMovieAttrCmdImpl, kMoviePrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kSetMovieAttrCmdDataImpl, kMoviePrefix + 5)
// gap
DECLARE_PMID(kImplementationIDSpace, kMoviePageItemScriptImpl, kMoviePrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kMovieItemScriptProviderImpl, kMoviePrefix + 13)
// gap 
DECLARE_PMID(kImplementationIDSpace, kMovieAdornmentInfoImpl, kMoviePrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kMovieInfoImpl, kMoviePrefix + 19)
// available
DECLARE_PMID(kImplementationIDSpace, kMovieSuiteLayoutImpl, kMoviePrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kMovieSuiteLayoutSelExtImpl, kMoviePrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kMovieSuiteDefaultImpl, kMoviePrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kMovieSuiteAbstractImpl, kMoviePrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kMovieSuiteASBSelExtImpl, kMoviePrefix + 26)
// available
DECLARE_PMID(kImplementationIDSpace, kNavigationPointScriptImpl, kMoviePrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kNavigationPointScriptProviderImpl, kMoviePrefix + 31)


// Error ID
DECLARE_PMID(kErrorIDSpace, kSetMovieAttrFailedError, kMoviePrefix + 1)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kMovieObjectScriptElement,						kMoviePrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kNavigationPointObjectScriptElement,			kMoviePrefix + 21)
//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kFloatingWindowPropertyScriptElement,			kMoviePrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kFloatingWindowPositionPropertyScriptElement,	kMoviePrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kFloatingWindowSizePropertyScriptElement,		kMoviePrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kPlayModePropertyScriptElement,				kMoviePrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kShowControlsPropertyScriptElement,			kMoviePrefix + 164)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kCustomPosterPropertyScriptElement,			kMoviePrefix + 166)
DECLARE_PMID(kScriptInfoIDSpace, kIntrinsicMovieBoundsPropertyScriptElement,	kMoviePrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kPosterIsAvailablePropertyScriptElement,		kMoviePrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kCanChoosePostersPropertyScriptElement,		kMoviePrefix + 169)
DECLARE_PMID(kScriptInfoIDSpace, kMoviePosterTypePropertyScriptElement,			kMoviePrefix + 170)
DECLARE_PMID(kScriptInfoIDSpace, kNavigationPointTimePropertyScriptElement,		kMoviePrefix + 171)
DECLARE_PMID(kScriptInfoIDSpace, kNavigationPointUniqueIDPropertyScriptElement,	kMoviePrefix + 172)
DECLARE_PMID(kScriptInfoIDSpace, kNavigationPointDisplayNamePropertyScriptElement,kMoviePrefix + 173)
DECLARE_PMID(kScriptInfoIDSpace, kControllerSkinPropertyScriptElement,			kMoviePrefix + 174)
DECLARE_PMID(kScriptInfoIDSpace, kShowControllerOnRolloverPropertyScriptElement,kMoviePrefix + 175)
DECLARE_PMID(kScriptInfoIDSpace, kMovieLoopPropertyScriptElement,				kMoviePrefix + 176)
DECLARE_PMID(kScriptInfoIDSpace, kMovieOperationPropertyScriptElement,			kMoviePrefix + 177)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kFloatingWindowPositionEnumScriptElement,		kMoviePrefix + 240)
DECLARE_PMID(kScriptInfoIDSpace, kFloatingWindowSizeEnumScriptElement,			kMoviePrefix + 241)
DECLARE_PMID(kScriptInfoIDSpace, kPlayModeEnumScriptElement,					kMoviePrefix + 242)
DECLARE_PMID(kScriptInfoIDSpace, kMoviePosterTypeEnumScriptElement,				kMoviePrefix + 243) // WHT: added 7/14/2003 [Vantive 616739]
DECLARE_PMID(kScriptInfoIDSpace, kMoviePlayOperationsEnumScriptElement,			kMoviePrefix + 244)
#endif // __MovieID__

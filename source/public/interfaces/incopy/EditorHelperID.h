//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/EditorHelperID.h $
//  
//  Owner: Matt Ramme
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#ifndef __EditorHelperID__
#define __EditorHelperID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
//#include "FormatNumber.h"

#define kEditorHelperPrefix	 RezLong(0xfb00)

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------

//PlugInID
#define kEditorHelperPlugInName				"EditorHelper"
DECLARE_PMID(kPlugInIDSpace, kEditorHelperPlugInID, kEditorHelperPrefix + 1)

//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------

//gap 

DECLARE_PMID(kClassIDSpace,		kEditorHelperRegisterBoss, 				kEditorHelperPrefix + 2)
DECLARE_PMID(kClassIDSpace,		kEditorHelperStringRegisterBoss, 		kEditorHelperPrefix + 3)
DECLARE_PMID(kClassIDSpace,		kEditorHelperMenuRegisterBoss, 			kEditorHelperPrefix + 4)
DECLARE_PMID(kClassIDSpace,		kEditorHelperActionRegisterBoss, 		kEditorHelperPrefix + 5)
DECLARE_PMID(kClassIDSpace,		kEditorHelperTipsRegisterBoss, 			kEditorHelperPrefix + 6)
DECLARE_PMID(kClassIDSpace,		kEditorHelperConversionProviderBoss,	kEditorHelperPrefix + 7)
//gap 
DECLARE_PMID(kClassIDSpace,		kAddTextMacroCmdBoss, 					kEditorHelperPrefix + 17)
DECLARE_PMID(kClassIDSpace,		kDeleteTextMacroCmdBoss, 				kEditorHelperPrefix + 18)
DECLARE_PMID(kClassIDSpace,		kMacroDocBoss, 							kEditorHelperPrefix + 19)
DECLARE_PMID(kClassIDSpace,		kMacroDataBoss, 						kEditorHelperPrefix + 20)
//gap 
DECLARE_PMID(kClassIDSpace,		kTextMacroStartupShutdownBoss, 			kEditorHelperPrefix + 22)
//gap 
DECLARE_PMID(kClassIDSpace,		kSetMacroActionCmdBoss, 				kEditorHelperPrefix + 24)
//gap 
DECLARE_PMID(kClassIDSpace,		kReplaceTextMacroCmdBoss, 				kEditorHelperPrefix + 26)
DECLARE_PMID(kClassIDSpace,		kMacroStartupIdleTaskBoss, 				kEditorHelperPrefix + 27)
//gap 
DECLARE_PMID(kClassIDSpace,		kStyledMacroClusterPanelBoss, 			kEditorHelperPrefix + 37)
DECLARE_PMID(kClassIDSpace,		kAutoFrameNewDocResponderBoss, 			kEditorHelperPrefix + 38)
DECLARE_PMID(kClassIDSpace,		kAutoFrameOpenDocResponderBoss, 		kEditorHelperPrefix + 39)
DECLARE_PMID(kClassIDSpace,		kAutoFrameIdleTaskBoss,					kEditorHelperPrefix + 40)
//gap 
DECLARE_PMID(kClassIDSpace,		kPositionMarkerPreProcessorBoss,		kEditorHelperPrefix + 42)
DECLARE_PMID(kClassIDSpace,		kTextMacroScriptProviderBoss,			kEditorHelperPrefix + 43)
//gap 
DECLARE_PMID(kClassIDSpace,		kPositionMarkerPostProcessorBoss,		kEditorHelperPrefix + 45)
DECLARE_PMID(kClassIDSpace,		kSetPositionMarkerCmdBoss, 				kEditorHelperPrefix + 46)
DECLARE_PMID(kClassIDSpace,		kClearPositionMarkerCmdBoss, 			kEditorHelperPrefix + 47)
DECLARE_PMID(kClassIDSpace,		kPositionMarkerLayoutAdornmentBoss,		kEditorHelperPrefix + 48)
DECLARE_PMID(kClassIDSpace,		kAutoTextMacroCmdBoss,					kEditorHelperPrefix + 49)
//gap 
DECLARE_PMID(kClassIDSpace,		kPositionMarkerLinksChangedResponderBoss,kEditorHelperPrefix + 51)
DECLARE_PMID(kClassIDSpace,		kEditorHelperErrorStringServiceBoss,	kEditorHelperPrefix + 52)
DECLARE_PMID(kClassIDSpace,		kTextMacrosSettingsMigrationServiceProviderBoss,	kEditorHelperPrefix + 53)


//----------------------------------------------------------------------------------------
// Interface identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace,		IID_ITEXTMACROLIST, 				kEditorHelperPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace,		IID_ITEXTMACROCMDDATA, 				kEditorHelperPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace,		IID_ITEXTMACROUTILS, 				kEditorHelperPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace,		IID_ITEXTMACROSUITE, 				kEditorHelperPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace,		IID_ISTYLEDMACROINSERT, 			kEditorHelperPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace,		IID_ISTYLEDCLUSTEROBSERVER,			kEditorHelperPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace,		IID_IAUTOFRAMEDOCOBSERVER,			kEditorHelperPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace,		IID_IPOSITIONMARKERDATA,			kEditorHelperPrefix + 8)
//gap 
DECLARE_PMID(kInterfaceIDSpace,		IID_IPOSITIONMARKERGALLEYADORNMENT,	kEditorHelperPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace,		IID_IAUTOTEXTMACRORANGEDATA,		kEditorHelperPrefix + 11)
//gap 
DECLARE_PMID(kInterfaceIDSpace,		IID_IAUTOTEXTMACROLIST, 			kEditorHelperPrefix + 13)


//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------

//gap 
DECLARE_PMID(kImplementationIDSpace,		kTextMacroListImpl, 				kEditorHelperPrefix + 3)
// gap
DECLARE_PMID(kImplementationIDSpace,		kAddTextMacroCmdImpl,				kEditorHelperPrefix + 12)
DECLARE_PMID(kImplementationIDSpace,		kDeleteTextMacroCmdImpl,			kEditorHelperPrefix + 13)
DECLARE_PMID(kImplementationIDSpace,		kTextMacroCmdDataImpl,				kEditorHelperPrefix + 14)
DECLARE_PMID(kImplementationIDSpace,		kPrivateTextMacroListImpl, 			kEditorHelperPrefix + 15)
DECLARE_PMID(kImplementationIDSpace,		kMacroDataStoryThreadImpl, 			kEditorHelperPrefix + 16)
DECLARE_PMID(kImplementationIDSpace,		kMacroDataStoryThreadDictImpl, 		kEditorHelperPrefix + 17)
// gap
DECLARE_PMID(kImplementationIDSpace,		kTextMacroStartupShutdownImpl, 		kEditorHelperPrefix + 19)
//gap 
DECLARE_PMID(kImplementationIDSpace,		kMacroActionWidgetViewImpl,			kEditorHelperPrefix + 21)
DECLARE_PMID(kImplementationIDSpace,		kTextMacroUtilsImpl, 				kEditorHelperPrefix + 22)
DECLARE_PMID(kImplementationIDSpace,		kSetMacroActionCmdImpl, 			kEditorHelperPrefix + 23)
//gap 
DECLARE_PMID(kImplementationIDSpace,		kReplaceTextMacroCmdImpl,			kEditorHelperPrefix + 25)
DECLARE_PMID(kImplementationIDSpace,		kMacroStartupIdleTaskImpl,			kEditorHelperPrefix + 26)
//gap 
DECLARE_PMID(kImplementationIDSpace,		kTextMacroSuiteASBImpl,				kEditorHelperPrefix + 32)
DECLARE_PMID(kImplementationIDSpace,		kTextMacroSuiteTextCSBImpl,			kEditorHelperPrefix + 33)
//gap 
DECLARE_PMID(kImplementationIDSpace,		kStyledMacroButtonObserverImpl,		kEditorHelperPrefix + 52)
DECLARE_PMID(kImplementationIDSpace,		kAutoFrameDocObserverImpl,			kEditorHelperPrefix + 53)
DECLARE_PMID(kImplementationIDSpace,		kAutoFrameNewDocResponderImpl,		kEditorHelperPrefix + 54)
DECLARE_PMID(kImplementationIDSpace,		kAutoFrameIdleTaskImpl,				kEditorHelperPrefix + 55)
//gap
DECLARE_PMID(kImplementationIDSpace,		kTextMacroScriptProviderImpl,		kEditorHelperPrefix + 57)
//gap 
DECLARE_PMID(kImplementationIDSpace,		kAutoFrameOpenDocResponderImpl,		kEditorHelperPrefix + 60)
DECLARE_PMID(kImplementationIDSpace,		kPositionMarkerDataImpl,			kEditorHelperPrefix + 61)
//gap 
DECLARE_PMID(kImplementationIDSpace,		kPositionMarkerPostProcessorImpl,	kEditorHelperPrefix + 65)
DECLARE_PMID(kImplementationIDSpace,		kSetPositionMarkerCmdImpl,			kEditorHelperPrefix + 66)
DECLARE_PMID(kImplementationIDSpace,		kClearPositionMarkerCmdImpl,		kEditorHelperPrefix + 67)
DECLARE_PMID(kImplementationIDSpace,		kPositionMarkerLayoutAdornmentImpl,	kEditorHelperPrefix + 68)
DECLARE_PMID(kImplementationIDSpace,		kPositionMarkerGalleyAdornmentImpl,	kEditorHelperPrefix + 69)
DECLARE_PMID(kImplementationIDSpace,		kAutoTextMacroCmdImpl,				kEditorHelperPrefix + 70)
DECLARE_PMID(kImplementationIDSpace,		kAutoTextMacroObserverImpl,			kEditorHelperPrefix + 71)
DECLARE_PMID(kImplementationIDSpace,		kAutoTextMacroKeyEventWatcherImpl,	kEditorHelperPrefix + 72)
//gap 
DECLARE_PMID(kImplementationIDSpace,		kPositionMarkerLinksChangedResponderImpl,kEditorHelperPrefix + 75)
DECLARE_PMID(kImplementationIDSpace,		kPositionMarkerPreProcessorImpl,	kEditorHelperPrefix + 76)
DECLARE_PMID(kImplementationIDSpace,		kEditorHelperErrorStringServiceImpl, kEditorHelperPrefix + 77)
DECLARE_PMID(kImplementationIDSpace,		kTextMacrosSettingsMigrationImpl, kEditorHelperPrefix + 78)



//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------



// <Ignore>
//========================================================================================
// ----- Tree Node ID types -----
//========================================================================================
//#define kMacroNodeID					kEditorHelperPrefix + 1

//----------------------------------------------------------------------------------------
// Action identifiers
//----------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
// Scripting
//----------------------------------------------------------------------------------------

DECLARE_PMID(kScriptInfoIDSpace, kTextMacroObjectScriptElement,			kEditorHelperPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kExpansionPropertyScriptElement,		kEditorHelperPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kTextMacroCreateMethodScriptElement,	kEditorHelperPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kAutoExpandMacrosPropertyScriptElement,kEditorHelperPrefix + 4)
//DECLARE_PMID(kScriptInfoIDSpace, kYourNewSuiteScriptElement,			kEditorHelperPrefix + 1)

//GUIDS
// {1D8C91B4-A1BE-4fa8-9324-2D97E82DDD1A}
#define kTextMacro_CLSID { 0x1d8c91b4, 0xa1be, 0x4fa8, { 0x93, 0x24, 0x2d, 0x97, 0xe8, 0x2d, 0xdd, 0x1a } }
// {BC69C660-538B-49db-9910-141B19A63A9C}
#define kTextMacros_CLSID { 0xbc69c660, 0x538b, 0x49db, { 0x99, 0x10, 0x14, 0x1b, 0x19, 0xa6, 0x3a, 0x9c } }

// <Message ID>
//---------------------------------------------------------------
//	MessageIDs
//---------------------------------------------------------------

DECLARE_PMID(kMessageIDSpace,	kPositionMarkerOversetMsgID,			kEditorHelperPrefix + 1)
DECLARE_PMID(kMessageIDSpace,	kPositionMarkerStoryCollapsedMsgID,		kEditorHelperPrefix + 2)
DECLARE_PMID(kMessageIDSpace,	kPositionMarkerStoryUnavailableMsgID,	kEditorHelperPrefix + 3)
DECLARE_PMID(kMessageIDSpace,	kAutoFrameMsgID,						kEditorHelperPrefix + 4)

// <Error ID>
//---------------------------------------------------------------
//	ErrorIDs
//---------------------------------------------------------------
DECLARE_PMID(kErrorIDSpace, kMacroExists,			kEditorHelperPrefix + 1)

// ---------------------------------------------------------------------------------------
// Schema Changes
// ---------------------------------------------------------------------------------------
#define kEditorHelperInCopy2Format	(kAnnaInitialMinorFormatNumber + 1)
#define kEditorHelperInCopy3Format	(kDragontailInitialMinorFormatNumber + 1)
#define kEditorHelperInCopy4Format	(kFiredrakeInitialMinorFormatNumber + 1)
#define kEditorHelperLastFormatChange		kEditorHelperInCopy4Format

// Overall
#define kEditorHelperLastMajorFormatChange			kFiredrakeMajorFormatNumber
#define kEditorHelperLastMinorFormatChange			kEditorHelperLastFormatChange

#define kEditorHelperErrorRsrcID 	5000

#endif // __AlignPanelID__


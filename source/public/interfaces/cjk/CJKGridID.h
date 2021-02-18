//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/CJKGridID.h $
//  
//  Owner: Heath Lynn
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

#ifndef __CJKGridID__
#define __CJKGridID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kCJKGridPrefix	RezLong(0xcd00)

// <Start IDC>
// PluginID
#define kCJKGridPluginName 		"CJKGrid"
DECLARE_PMID(kPlugInIDSpace, kCJKGridPluginID, kCJKGridPrefix + 1)

// <Class ID>
//--------------------------------------------------------------
// class IDs
//--------------------------------------------------------------
//gap
DECLARE_PMID(kClassIDSpace, kDefaultCJKGridDrawBoss, kCJKGridPrefix + 2)
DECLARE_PMID(kClassIDSpace, kSetCJKGridDataCmdBoss, kCJKGridPrefix + 3 )
DECLARE_PMID(kClassIDSpace, kCJKFrameGridAdornmentBoss, kCJKGridPrefix + 4)
DECLARE_PMID(kClassIDSpace, kSetCJKGridPainterCmdBoss, kCJKGridPrefix + 5)
DECLARE_PMID(kClassIDSpace, kSetCJKLayoutGridDataCmdBoss, kCJKGridPrefix + 6)
DECLARE_PMID(kClassIDSpace, kCJKGridNewDocResponderBoss, kCJKGridPrefix + 7)
DECLARE_PMID(kClassIDSpace, kCJKGridOpenDocResponderBoss, kCJKGridPrefix + 8)
DECLARE_PMID(kClassIDSpace, kCJKLayoutGridDrawServicesBoss, kCJKGridPrefix + 9)
DECLARE_PMID(kClassIDSpace, kDupSpreadCJKGridResponderBoss, kCJKGridPrefix + 11)
DECLARE_PMID(kClassIDSpace, kApplyMasterCJKGridRespBoss, kCJKGridPrefix + 12)
DECLARE_PMID(kClassIDSpace, kSetCJKGridPrefsCmdBoss, kCJKGridPrefix + 13)
DECLARE_PMID(kClassIDSpace, kZNAdornmentBoss, kCJKGridPrefix + 14)
DECLARE_PMID(kClassIDSpace, kCharCountAdornmentBoss, kCJKGridPrefix + 15)
DECLARE_PMID(kClassIDSpace, kAlignmentAdornmentBoss, kCJKGridPrefix + 16)
DECLARE_PMID(kClassIDSpace, kSetAdornmentVisibilityCmdBoss, kCJKGridPrefix + 17)
DECLARE_PMID(kClassIDSpace, kNamedGridBoss, kCJKGridPrefix + 18)
DECLARE_PMID(kClassIDSpace, kCreateNamedGridCmdBoss, kCJKGridPrefix + 19)
DECLARE_PMID(kClassIDSpace, kDeleteNamedGridCmdBoss, kCJKGridPrefix + 20)
DECLARE_PMID(kClassIDSpace, kCopyOneNamedGridCmdBoss, kCJKGridPrefix + 21)
DECLARE_PMID(kClassIDSpace, kReplaceNamedGridCmdBoss, kCJKGridPrefix + 22)
DECLARE_PMID(kClassIDSpace, kEditNamedGridCmdBoss, kCJKGridPrefix + 23)
DECLARE_PMID(kClassIDSpace, kSetCJKFrameGridDefaultsCmdBoss, kCJKGridPrefix + 24)
DECLARE_PMID(kClassIDSpace, kSetCJKLayoutGridDefaultsCmdBoss, kCJKGridPrefix + 25)
DECLARE_PMID(kClassIDSpace, kLoadNamedGridsCmdBoss, kCJKGridPrefix + 26)
DECLARE_PMID(kClassIDSpace, kActivateCJKGridCmdBoss, kCJKGridPrefix + 27)
DECLARE_PMID(kClassIDSpace, kCJKGridNewStoryResponderBoss, kCJKGridPrefix + 28)
DECLARE_PMID(kClassIDSpace, kApplyCJKGridFormatCmdBoss, kCJKGridPrefix + 29)
 // Moved to FrameGridDialog plug-in
 //DECLARE_PMID(kClassIDSpace, kApplyCJKGridComponentBoss, kCJKGridPrefix + 30)
 //DECLARE_PMID(kClassIDSpace, kPasteWithoutCJKGridComponentBoss, kCJKGridPrefix + 31)
DECLARE_PMID(kClassIDSpace, kCJKGridPrintingDrawServicesBoss, kCJKGridPrefix + 32)
DECLARE_PMID(kClassIDSpace, kNamedGridRefConverterBoss, kCJKGridPrefix + 33)
DECLARE_PMID(kClassIDSpace, kCJKGridNewWSResponderBoss, kCJKGridPrefix + 35)
DECLARE_PMID(kClassIDSpace, kCJKGridConversionProviderBoss, kCJKGridPrefix + 36)
DECLARE_PMID(kClassIDSpace, kSetPrintContentPrefsCmdBoss, kCJKGridPrefix + 37)
DECLARE_PMID(kClassIDSpace, kPrintContentPrefsBoss, kCJKGridPrefix + 38)
DECLARE_PMID(kClassIDSpace, kCJKGridPhase2ConverterBoss, kCJKGridPrefix + 39)
DECLARE_PMID(kClassIDSpace, kNamedGridSyncBoss, kCJKGridPrefix + 40)
DECLARE_PMID(kClassIDSpace, kSetDefaultFrameGridViewCmdBoss, kCJKGridPrefix + 41)
DECLARE_PMID(kClassIDSpace, kCJKGridContentIteratorRegBoss, kCJKGridPrefix + 42)
DECLARE_PMID(kClassIDSpace, kMCFCharCountAdornmentBoss, kCJKGridPrefix + 43)
DECLARE_PMID(kClassIDSpace, kJBXNamedGridsResTypeBoss, kCJKGridPrefix + 44)
//gap

//Scripting
DECLARE_PMID(kClassIDSpace, kCJKLayoutGridDataScriptProviderBoss, kCJKGridPrefix + 76)
//gap
DECLARE_PMID(kClassIDSpace, kCJKStoryGridDataScriptProviderBoss, kCJKGridPrefix + 78)
//gap
DECLARE_PMID(kClassIDSpace, kCJKGridDataScriptProviderBoss, kCJKGridPrefix + 84)
//gap
DECLARE_PMID(kClassIDSpace, kCJKGridPrefsScriptProviderBoss, kCJKGridPrefix + 86)
//gap
DECLARE_PMID(kClassIDSpace, kPrintGridPrefsScriptProviderBoss, kCJKGridPrefix + 88)

DECLARE_PMID(kClassIDSpace, kFilteredCJKGridDataBoss, kCJKGridPrefix + 90)

DECLARE_PMID(kClassIDSpace, kNamedGridsScriptProviderBoss, kCJKGridPrefix + 91)
DECLARE_PMID(kClassIDSpace, kNamedGridsScriptObjectBoss, kCJKGridPrefix + 92)
DECLARE_PMID(kClassIDSpace, kLayoutGridScriptProviderBoss, kCJKGridPrefix + 93)
DECLARE_PMID(kClassIDSpace, kSetCJKCharCountOptionsCmdBoss, kCJKGridPrefix + 94)


// <Interface ID>
//--------------------------------------------------------------
// IIDs
//--------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKGRIDDATA, kCJKGridPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKGRIDSHOWLAYOUTGRIDSPREF, kCJKGridPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKLAYOUTGRIDDATA, kCJKGridPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKGRIDMANAGER, kCJKGridPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKGRIDPAINTER, kCJKGridPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAWCJKGRID, kCJKGridPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKFRAMEGRIDOBSERVER, kCJKGridPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKGRIDPREFS, kCJKGridPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKMARGINOBSERVER, kCJKGridPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKGRIDSNAPTOLAYOUTGRIDPREF, kCJKGridPrefix + 10)
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_IADORNMENTVISIBILITY, kCJKGridPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKGRIDVISIBILITY, kCJKGridPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKALIGNVISIBILITY, kCJKGridPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKGRIDSHOWFRAMEGRIDSPREF, kCJKGridPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKZNVISIBILITY, kCJKGridPrefix + 16)
//DECLARE_PMID(kInterfaceIDSpace, IID_MYFANCYNEWIID, kCJKGridPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_INAMEDGRIDSNAMETABLE, kCJKGridPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_INAMEDGRIDINFO, kCJKGridPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKGRIDSHOWCHARACTERCOUNTPREF, kCJKGridPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IFILTEREDCJKGRIDCMDDATA, kCJKGridPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKFRAMEGRIDDEFAULTS, kCJKGridPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKLAYOUTGRIDDEFAULTS, kCJKGridPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_INAMEDGRIDUID, kCJKGridPrefix + 24)

DECLARE_PMID(kInterfaceIDSpace, IID_ISKIPNEWDOCLAYOUTGRIDDEFAULTS, kCJKGridPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_ISKIPNEWDOCFRAMEGRIDDEFAULTS, kCJKGridPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_ISKIPNEWDOCCJKGRIDPREFS, kCJKGridPrefix + 27)

DECLARE_PMID(kInterfaceIDSpace, IID_ICHARCOUNTBOUNDSDATA, kCJKGridPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKGRIDSTORYOBSERVER, kCJKGridPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKGRIDSTORYLISTOBSERVER, kCJKGridPrefix + 30)

DECLARE_PMID(kInterfaceIDSpace, IID_INONPERSISTCJKGRIDDATA, kCJKGridPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKINGCJKGRIDDATA, kCJKGridPrefix + 32)  // Used by place and frame grid tool trackers
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKWITHCJKGRID, kCJKGridPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKWITHVERTICALGRID, kCJKGridPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_APPLYGRIDATTRIBUTESBOOL, kCJKGridPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLYCJKGRIDDIRECTION, kCJKGridPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKGRIDUTILS, kCJKGridPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKGRIDBOOLDATA, kCJKGridPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKGRIDSUITE, kCJKGridPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_IPASTEWITOUTCJKGRID, kCJKGridPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKCHARCOUNTOPTIONS, kCJKGridPrefix + 41)

DECLARE_PMID(kInterfaceIDSpace, IID_ICJKGRIDDEBUGFLAGS, kCJKGridPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKGRIDICFDATA, kCJKGridPrefix + 43)

// <Implementation ID>
//--------------------------------------------------------------
// Implementation IDs
//--------------------------------------------------------------

//gap
DECLARE_PMID(kImplementationIDSpace, kCJKGridDataImpl, kCJKGridPrefix + 2)
//gap
DECLARE_PMID(kImplementationIDSpace, kCJKLayoutGridDataImpl, kCJKGridPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCJKFrameGridManagerImpl_Obsolete, kCJKGridPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kCJKLayoutGridManagerImpl, kCJKGridPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kCJKGridPainterImpl, kCJKGridPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kFrameItemCJKGridDataImpl, kCJKGridPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kDefaultCJKGridDrawImpl, kCJKGridPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kSetCJKGridDataCmdImpl, kCJKGridPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kCJKFrameGridAdornmentImpl, kCJKGridPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kSetCJKGridPainterCmdImpl, kCJKGridPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kSetCJKLayoutGridDataCmdImpl, kCJKGridPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kCJKFrameGridObserverImpl, kCJKGridPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kCJKGridNewDocResponderImpl, kCJKGridPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kCJKGridOpenDocResponderImpl, kCJKGridPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kCJKLayoutGridDrawServiceImpl, kCJKGridPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kCJKLayoutGridDrawHandlerImpl, kCJKGridPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kCJKGridPrefsImpl, kCJKGridPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kCJKGridDocSnapToLayoutGridDataImpl, kCJKGridPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kCJKMarginObserverImpl, kCJKGridPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kDupSpreadCJKGridResponderImpl, kCJKGridPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kApplyMasterCJKGridRespImpl, kCJKGridPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kSetCJKGridPrefsCmdImpl, kCJKGridPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kZNAdornmentImpl, kCJKGridPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kCharCountAdornmentImpl, kCJKGridPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kAlignmentAdornmentImpl, kCJKGridPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kCJKGridDocShowAllLayoutGridsDataImpl, kCJKGridPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kCJKGridDocShowAllFrameGridsDataImpl, kCJKGridPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kCJKGridDocShowCharacterCountDataImpl, kCJKGridPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kCJKGridVisibilityImpl, kCJKGridPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kCJKAlignVisibilityImpl, kCJKGridPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kCJKCharCountVisibilityImpl_obsolete, kCJKGridPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kCJKZNVisibilityImpl, kCJKGridPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kSetAdornmentVisibilityCmdImpl, kCJKGridPrefix + 35)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kCJKGridPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kNamedGridsNameTableImpl, kCJKGridPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kFilteredCJKGridCmdDataImpl, kCJKGridPrefix + 38)

DECLARE_PMID(kImplementationIDSpace, kNamedGridInfoImpl, kCJKGridPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kCreateNamedGridCmdImpl, kCJKGridPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kDeleteNamedGridCmdImpl, kCJKGridPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kCopyOneNamedGridCmdImpl, kCJKGridPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kEditNamedGridCmdImpl, kCJKGridPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kReplaceNamedGridCmdImpl, kCJKGridPrefix + 45)

DECLARE_PMID(kImplementationIDSpace, kCJKFrameGridDefaultsImpl, kCJKGridPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kCJKLayoutGridDefaultsImpl, kCJKGridPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kSetCJKFrameGridDefaultsCmdImpl, kCJKGridPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kSetCJKLayoutGridDefaultsCmdImpl, kCJKGridPrefix + 49)

DECLARE_PMID(kImplementationIDSpace, kNamedGridUIDImpl, kCJKGridPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kFrameItemNamedGridUIDImpl, kCJKGridPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kLoadNamedGridsCmdImpl, kCJKGridPrefix + 52)

DECLARE_PMID(kImplementationIDSpace, kActivateCJKGridCmdImpl, kCJKGridPrefix + 53)

DECLARE_PMID(kImplementationIDSpace, kCJKGridNewStoryResponderImpl, kCJKGridPrefix + 54)

DECLARE_PMID(kImplementationIDSpace, kApplyCJKGridFormatCmdImpl, kCJKGridPrefix + 55)
// Moved to FrameGridDialog plug-in
//DECLARE_PMID(kImplementationIDSpace, kApplyCJKGridComponentImpl, kCJKGridPrefix + 56)
//DECLARE_PMID(kImplementationIDSpace, kPasteWithoutCJKGridComponentImpl, kCJKGridPrefix + 57)

DECLARE_PMID(kImplementationIDSpace, kCJKGridPrintingDrawServiceImpl, kCJKGridPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kCJKGridPrintingDrawHandlerImpl, kCJKGridPrefix + 59)

DECLARE_PMID(kImplementationIDSpace, kCharCountBoundsDataImpl, kCJKGridPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kCJKGridStoryObserverImpl, kCJKGridPrefix + 61)

DECLARE_PMID(kImplementationIDSpace, kNamedGridRefConverterImpl, kCJKGridPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kCJKGridStoryListObserverImpl, kCJKGridPrefix + 63	 )
DECLARE_PMID(kImplementationIDSpace, kNonPersistCJKGridDataImpl, kCJKGridPrefix + 64   )
DECLARE_PMID(kImplementationIDSpace, kCJKMCFFrameGridManagerImpl, kCJKGridPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kCJKGridNewWSResponderImpl, kCJKGridPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kCJKGridConversionProviderImpl, kCJKGridPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kSetPrintContentPrefsCmdImpl, kCJKGridPrefix + 68)

DECLARE_PMID(kImplementationIDSpace, kNamedGridSyncProviderImpl, kCJKGridPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kApplyCJKGridDirectionImpl, kCJKGridPrefix + 70)
// bumped from 70 5/Jan/01 %brycem%
//DECLARE_PMID(kImplementationIDSpace, kNamedGridSyncServiceImpl, kCJKGridPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kAliasPersistPrintContentPrefsImpl, kCJKGridPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kCJKGridPhase2ConverterImpl, kCJKGridPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kNamedGridSyncServiceImpl, kCJKGridPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kCJKGridConversionHookImpl, kCJKGridPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kCJKGridInkResourcesImpl, kCJKGridPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kSetDefaultFrameGridViewCmdImpl, kCJKGridPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kCJKGridContentIteratorRegImpl, kCJKGridPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kCharCountInkResourcesImpl, kCJKGridPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kCJKGridUtilsImpl, kCJKGridPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kMCFCharCountAdornmentImpl, kCJKGridPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kCJKGridSessionSnapToLayoutGridDataImpl, kCJKGridPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kCJKGridSessionShowAllLayoutGridsDataImpl, kCJKGridPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kCJKGridSessionShowAllFrameGridsDataImpl, kCJKGridPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kCJKGridSessionShowCharacterCountDataImpl, kCJKGridPrefix + 84)
//gap

//Scripting
DECLARE_PMID(kImplementationIDSpace, kCJKGridPrefsScriptProviderImpl, kCJKGridPrefix + 90)
//gap
DECLARE_PMID(kImplementationIDSpace, kCJKGridDataScriptProviderImpl, kCJKGridPrefix + 92)
//gap
DECLARE_PMID(kImplementationIDSpace, kPrintGridPrefsScriptProviderImpl, kCJKGridPrefix + 94)
//gap
DECLARE_PMID(kImplementationIDSpace, kCJKLayoutGridDataScriptProviderImpl, kCJKGridPrefix + 96)
//gap
DECLARE_PMID(kImplementationIDSpace, kCJKStoryGridDataScriptProviderImpl, kCJKGridPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kCJKGridFacadeImpl, kCJKGridPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kCJKGridSuiteASBImpl, kCJKGridPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kCJKGridSuiteDefaultsCSBImpl, kCJKGridPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kCJKGridSuiteLayoutCSBImpl, kCJKGridPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kCJKGridSuiteTextCSBImpl, kCJKGridPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kNamedGridsScriptProviderImpl, kCJKGridPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kNamedGridScriptImpl, kCJKGridPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kCJKGridSuiteDefaultsCSBSelectionExtImpl, kCJKGridPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kCJKGridSuiteLayoutCSBSelectionExtImpl, kCJKGridPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kCJKGridSuiteTextCSBSelectionExtImpl, kCJKGridPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kLayoutGridScriptProviderImpl, kCJKGridPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kCJKGridSuiteGalleyTextCSBImpl, kCJKGridPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kCJKGridSuiteGalleyTextCSBSelectionExtImpl, kCJKGridPrefix + 111)

DECLARE_PMID(kImplementationIDSpace, kCJKCharCountOptionsImpl, kCJKGridPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kSetCJKCharCountOptionsCmdImpl, kCJKGridPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kCJKGridDebugFlagsImpl, kCJKGridPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kCJKGridICFDataImpl, kCJKGridPrefix + 115)

// Some special values the user won't likely enter
#define kMixedValue								-1834
#define kCustomNumColumns						-1835

//
//Script Element IDs
//

//Suites
//DECLARE_PMID(kScriptInfoIDSpace, ,					kCJKGridPrefix + 0)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kGridDataObjectScriptElement,				kCJKGridPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kLayoutGridDataObjectScriptElement,		kCJKGridPrefix + 41)
DECLARE_PMID(kScriptInfoIDSpace, kStoryGridDataObjectScriptElement,			kCJKGridPrefix + 42)
DECLARE_PMID(kScriptInfoIDSpace, kCJKGridPreferencesObjectScriptElement,	kCJKGridPrefix + 43)
DECLARE_PMID(kScriptInfoIDSpace, kGridPrintingPreferencesObjectScriptElement, kCJKGridPrefix + 44)
DECLARE_PMID(kScriptInfoIDSpace, kNamedGridObjectScriptElement, kCJKGridPrefix + 45)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kCreateNamedGridMethodScriptElement,		kCJKGridPrefix + 80)
//DECLARE_PMID(kScriptInfoIDSpace, ,			kCJKGridPrefix + 80)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kLineAlignmentEnumScriptElement,			kCJKGridPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kGridStartingPointEnumScriptElement,			kCJKGridPrefix + 101)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kCharacterAkiPropertyScriptElement,		kCJKGridPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kLineAkiPropertyScriptElement,				kCJKGridPrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kLayoutGridDataPropertyScriptElement,		kCJKGridPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kStoryGridDataPropertyScriptElement,		kCJKGridPrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kGridDataPropertyScriptElement,			kCJKGridPrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kShowAllLayoutGridsPropertyScriptElement,	kCJKGridPrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kShowAllFrameGridsPropertyScriptElement,	kCJKGridPrefix + 166)
DECLARE_PMID(kScriptInfoIDSpace, kMinimumScalePropertyScriptElement,		kCJKGridPrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kSnapToLayoutGridPropertyScriptElement,	kCJKGridPrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kLayoutGridColorIndexPropertyScriptElement, kCJKGridPrefix + 169)
DECLARE_PMID(kScriptInfoIDSpace, kColorEveryNthCellPropertyScriptElement,	kCJKGridPrefix + 170)
DECLARE_PMID(kScriptInfoIDSpace, kSingleLineColorModePropertyScriptElement,	kCJKGridPrefix + 171)
DECLARE_PMID(kScriptInfoIDSpace, kICFModePropertyScriptElement,				kCJKGridPrefix + 172)
DECLARE_PMID(kScriptInfoIDSpace, kUseCircularCellsPropertyScriptElement,	kCJKGridPrefix + 173)
DECLARE_PMID(kScriptInfoIDSpace, kShowCharacterCountPropertyScriptElement,	kCJKGridPrefix + 174)
DECLARE_PMID(kScriptInfoIDSpace, kGridPreferencesPropertyScriptElement,		kCJKGridPrefix + 175)
DECLARE_PMID(kScriptInfoIDSpace, kLayoutGridPrintingPropertyScriptElement,	kCJKGridPrefix + 176)
DECLARE_PMID(kScriptInfoIDSpace, kFrameGridPrintingPropertyScriptElement,	kCJKGridPrefix + 177)
DECLARE_PMID(kScriptInfoIDSpace, kTextPrintingPropertyScriptElement,		kCJKGridPrefix + 178)
DECLARE_PMID(kScriptInfoIDSpace, kPageItemPrintingPropertyScriptElement,	 kCJKGridPrefix + 179)
DECLARE_PMID(kScriptInfoIDSpace, kLayoutGridStrokeWeightPropertyScriptElement,	kCJKGridPrefix + 180)
DECLARE_PMID(kScriptInfoIDSpace, kFrameGridStrokeWeightPropertyScriptElement,	kCJKGridPrefix + 181)
DECLARE_PMID(kScriptInfoIDSpace, kGridPrintingPreferencesPropertyScriptElement,	kCJKGridPrefix + 182)
DECLARE_PMID(kScriptInfoIDSpace, kAppliedNamedGridPropertyScriptElement,	kCJKGridPrefix + 183)
DECLARE_PMID(kScriptInfoIDSpace, kLineAlignmentPropertyScriptElement,		kCJKGridPrefix + 184)
DECLARE_PMID(kScriptInfoIDSpace, kGridStartingPointPropertyScriptElement,		kCJKGridPrefix + 185)
DECLARE_PMID(kScriptInfoIDSpace, kUseMasterGridPropertyScriptElement,		kCJKGridPrefix + 186)
DECLARE_PMID(kScriptInfoIDSpace, kGridViewEnumScriptElement,				kCJKGridPrefix + 187)
DECLARE_PMID(kScriptInfoIDSpace, kGridViewPropertyScriptElement,			kCJKGridPrefix + 188)
DECLARE_PMID(kScriptInfoIDSpace, kGridLineCountPropertyScriptElement,			kCJKGridPrefix + 189)
DECLARE_PMID(kScriptInfoIDSpace, kCharCountLocationEnumScriptElement,			kCJKGridPrefix + 190)
DECLARE_PMID(kScriptInfoIDSpace, kCharCountLocationPropertyScriptElement,			kCJKGridPrefix + 191)
DECLARE_PMID(kScriptInfoIDSpace, kCharCountSizePropertyScriptElement,			kCJKGridPrefix + 192)


//GUIDS
// {45F9BC51-E026-11d3-9D01-00C04F99131A),
#define kCJKGridPreferences_CLSID {0x45f9bc51, 0xe026, 0x11d3, { 0x9D, 0x01, 0x00, 0xC0, 0x4F, 0x99, 0x13, 0x1A } }
// {45F9BC50-E026-11d3-9D01-00C04F99131A},
#define kCJKGridData_CLSID {0x45f9bc50, 0xe026, 0x11d3, { 0x9D, 0x01, 0x00, 0xC0, 0x4F, 0x99, 0x13, 0x1A } }
// {FDB0E9E4-ABBF-470a-B75C-4ADA759069C7}
#define kNamedGrid_CLSID { 0xfdb0e9e4, 0xabbf, 0x470a, { 0xb7, 0x5c, 0x4a, 0xda, 0x75, 0x90, 0x69, 0xc7 } }
// {7A0A1153-32E2-42ed-9043-40841ED6433A}
#define kNamedGrids_CLSID { 0x7a0a1153, 0x32e2, 0x42ed, { 0x90, 0x43, 0x40, 0x84, 0x1e, 0xd6, 0x43, 0x3a } }
// {7666516E-3AE1-437b-B6FA-9F66D91D1622}
#define kCJKLayoutGridData_CLSID { 0x7666516e, 0x3ae1, 0x437b, { 0xb6, 0xfa, 0x9f, 0x66, 0xd9, 0x1d, 0x16, 0x22 } }
// {1DFEAFFB-A275-49c2-B03E-6394112F2CD7}
#define kCJKStoryGridData_CLSID { 0x1dfeaffb, 0xa275, 0x49c2, { 0xb0, 0x3e, 0x63, 0x94, 0x11, 0x2f, 0x2c, 0xd7 } }
// {496f0bdc-7834-11d2-aaf0-00c04fa37726}
#define kCJKPrintGridPreferences_CLSID { 0x496f0bdc, 0x7834, 0x11d2, { 0xaa, 0xf0, 0x0, 0xc0, 0x4f, 0xa3, 0x77, 0x26 } }

#endif // __CJKGridID__


//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/StandOffID.h $
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
//  Contains IDs used by the standoff of the generic page item plug-in
//  
//========================================================================================

#ifndef __StandOffID__
#define __StandOffID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define kStandOffIDPrefix	RezLong(0x3700)



// PluginID
#define kStandOffPluginName 				"Text Wrap"
DECLARE_PMID(kPlugInIDSpace, kStandOffPluginID, kStandOffIDPrefix + 1)

//---------------------------------------------------------------
// ClassIDs
//---------------------------------------------------------------
// OBSOLETE: DECLARE_PMID(kClassIDSpace, kStandOffBoss, kStandOffIDPrefix + 1)	// the widget
DECLARE_PMID(kClassIDSpace, kStandOffPageItemBoss, kStandOffIDPrefix + 2	)

DECLARE_PMID(kClassIDSpace, kStandOffModeCmdBoss, kStandOffIDPrefix + 4	)
DECLARE_PMID(kClassIDSpace, kStandOffFormCmdBoss, kStandOffIDPrefix + 5)
DECLARE_PMID(kClassIDSpace, kStandOffMarginCmdBoss, kStandOffIDPrefix + 6		)
DECLARE_PMID(kClassIDSpace, kNewStandOffItemCmdBoss, kStandOffIDPrefix + 7)		// Commands
DECLARE_PMID(kClassIDSpace, kDeleteStandOffItemCmdBoss, kStandOffIDPrefix + 8)		// Commands
DECLARE_PMID(kClassIDSpace, kChangeStandOffItemCmdBoss, kStandOffIDPrefix + 9)		// Commands
// gap
DECLARE_PMID(kClassIDSpace, kStandOffPolygonBoss, kStandOffIDPrefix + 11	)
DECLARE_PMID(kClassIDSpace, kSetStandOffWorkspaceCmdBoss, kStandOffIDPrefix + 12	)
//gap
DECLARE_PMID(kClassIDSpace, kSetTextInsetCmdBoss, kStandOffIDPrefix + 14)
DECLARE_PMID(kClassIDSpace, kDeleteInsetPageItemCmdBoss, kStandOffIDPrefix + 15)
DECLARE_PMID(kClassIDSpace, kTextInsetPageItemBoss, kStandOffIDPrefix + 16)
// gap
DECLARE_PMID(kClassIDSpace, kSetIgnoreWrapCmdBoss, kStandOffIDPrefix + 22)
DECLARE_PMID(kClassIDSpace, kSetUserStandOffCmdBoss, kStandOffIDPrefix + 23)
DECLARE_PMID(kClassIDSpace, kStandOffNewPIResponderBoss, kStandOffIDPrefix + 24)
// gap
DECLARE_PMID(kClassIDSpace, kNewInsetPageItemCmdBoss, kStandOffIDPrefix + 28)
// gap
DECLARE_PMID(kClassIDSpace, kPrivateConnectItemsCmdBoss, kStandOffIDPrefix + 30)
DECLARE_PMID(kClassIDSpace, kPrivateDisconnectItemsCmdBoss, kStandOffIDPrefix + 31)
DECLARE_PMID(kClassIDSpace, kZOrderWrapOptimizerBoss, kStandOffIDPrefix + 32)
DECLARE_PMID(kClassIDSpace, kSetContourWrapCmdBoss, kStandOffIDPrefix + 33)
DECLARE_PMID(kClassIDSpace, kStandOffCodeConversionProviderBoss, kStandOffIDPrefix + 34)
DECLARE_PMID(kClassIDSpace, kStandOffConversionProviderBoss, kStandOffIDPrefix + 35)
DECLARE_PMID(kClassIDSpace, kSetZOrderTextWrapCmdBoss, kStandOffIDPrefix + 36)
DECLARE_PMID(kClassIDSpace, kSetSkipByLineHeightCmdBoss, kStandOffIDPrefix + 37)
DECLARE_PMID(kClassIDSpace, kTextWrapScriptProviderBoss, kStandOffIDPrefix + 38)
DECLARE_PMID(kClassIDSpace, kTextWrapScriptObjectBoss, kStandOffIDPrefix + 39)
DECLARE_PMID(kClassIDSpace, kContourOptionsScriptProviderBoss, kStandOffIDPrefix + 40)
DECLARE_PMID(kClassIDSpace, kContourOptionsScriptObjectBoss, kStandOffIDPrefix + 41)
DECLARE_PMID(kClassIDSpace, kContourOptionsScriptProvider40Boss, kStandOffIDPrefix + 42)
DECLARE_PMID(kClassIDSpace, kTextWrapObjStylesHandlerBoss, kStandOffIDPrefix + 43)
DECLARE_PMID(kClassIDSpace, kStandOffActiveFromMasterCmdBoss, kStandOffIDPrefix + 44)
DECLARE_PMID(kClassIDSpace, kStandOffSideCmdBoss, kStandOffIDPrefix + 45)
DECLARE_PMID(kClassIDSpace, kTextWrapAdornmentBoss, kStandOffIDPrefix + 46 )
DECLARE_PMID(kClassIDSpace, kTextInsetAdornmentBoss, kStandOffIDPrefix + 47 )

// rmadala: The following attributes are for find/change.
//Textwrap Attributes
DECLARE_PMID(kClassIDSpace, kObjectFCTWTypeAttrBoss, kStandOffIDPrefix + 50)
DECLARE_PMID(kClassIDSpace, kObjectFCTWInvertAttrBoss, kStandOffIDPrefix + 51)
DECLARE_PMID(kClassIDSpace, kObjectFCTWTopOffsetAttrBoss, kStandOffIDPrefix + 52)
DECLARE_PMID(kClassIDSpace, kObjectFCTWBottomOffsetAttrBoss, kStandOffIDPrefix + 53)
DECLARE_PMID(kClassIDSpace, kObjectFCTWLeftOffsetAttrBoss, kStandOffIDPrefix + 54)
DECLARE_PMID(kClassIDSpace, kObjectFCTWRightOffsetAttrBoss, kStandOffIDPrefix + 55)
DECLARE_PMID(kClassIDSpace, kObjectFCTWContourTypeAttrBoss, kStandOffIDPrefix + 56)
DECLARE_PMID(kClassIDSpace, kObjectFCTWIncludeInsideEdgesAttrBoss, kStandOffIDPrefix + 57)
DECLARE_PMID(kClassIDSpace, kObjectFCTWNonPrintingAttrBoss, kStandOffIDPrefix + 58)
DECLARE_PMID(kClassIDSpace, kObjectFCTWActiveFromMasterAttrBoss, kStandOffIDPrefix + 59)
// Anchored Object Attributes
DECLARE_PMID(kClassIDSpace, kObjectFCAOPositionAttrBoss, kStandOffIDPrefix + 60)
DECLARE_PMID(kClassIDSpace, kObjectFCAOInlineAttrBoss_Obsolete, kStandOffIDPrefix + 61)
DECLARE_PMID(kClassIDSpace, kObjectFCAOInlineYOffsetAttrBoss, kStandOffIDPrefix + 62)
DECLARE_PMID(kClassIDSpace, kObjectFCAOAbovelineAttrBoss_Obsolete, kStandOffIDPrefix + 63)
DECLARE_PMID(kClassIDSpace, kObjectFCAOAbovelineAlignmentAttrBoss, kStandOffIDPrefix + 64)
DECLARE_PMID(kClassIDSpace, kObjectFCAOAbovelineSpaceBeforeAttrBoss, kStandOffIDPrefix + 65)
DECLARE_PMID(kClassIDSpace, kObjectFCAOAbovelineSpaceAfterAttrBoss, kStandOffIDPrefix + 66)
DECLARE_PMID(kClassIDSpace, kObjectFCAOPreventManualPositioningAttrBoss, kStandOffIDPrefix + 67)
DECLARE_PMID(kClassIDSpace, kObjectFCAOCustomRelativeToSplineAttrBoss, kStandOffIDPrefix + 68)
DECLARE_PMID(kClassIDSpace, kObjectFCAOCustomObjectReferencePointAttrBoss, kStandOffIDPrefix + 69)
DECLARE_PMID(kClassIDSpace, kObjectFCAOCustomPositionReferencePointAttrBoss, kStandOffIDPrefix + 70)
DECLARE_PMID(kClassIDSpace, kObjectFCAOCustomXRelativeToAttrBoss, kStandOffIDPrefix + 71)
DECLARE_PMID(kClassIDSpace, kObjectFCAOCustomXOffsetAttrBoss, kStandOffIDPrefix + 72)
DECLARE_PMID(kClassIDSpace, kObjectFCAOCustomYRelativeToAttrBoss, kStandOffIDPrefix + 73)
DECLARE_PMID(kClassIDSpace, kObjectFCAOCustomYOffsetAttrBoss, kStandOffIDPrefix + 74)
DECLARE_PMID(kClassIDSpace, kObjectFCAOCustomKeepWithBoundariesAttrBoss, kStandOffIDPrefix + 75)
DECLARE_PMID(kClassIDSpace, kObjectFCTWSideAttrBoss, kStandOffIDPrefix + 76)
DECLARE_PMID(kClassIDSpace, kStandOffRefConverterBoss, kStandOffIDPrefix + 77)
DECLARE_PMID(kClassIDSpace, kStandOffM2MListenerServiceBoss, kStandOffIDPrefix + 78)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kStandOffIDPrefix + 79)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kStandOffIDPrefix + 80)
DECLARE_PMID(kClassIDSpace, kTextWrapForwarderM2MListenerServiceBoss, kStandOffIDPrefix + 81)

// Categories for Object Style Attriubtes
DECLARE_PMID(kClassIDSpace, kTextWrapDataAttributeCategory, kStandOffIDPrefix + 200)
DECLARE_PMID(kClassIDSpace, kContourWrapDataAttributeCategory, kStandOffIDPrefix + 201)


//---------------------------------------------------------------
// IIDs
//---------------------------------------------------------------

DECLARE_PMID(kInterfaceIDSpace, IID_IPOLYGONCONVERTER, kStandOffIDPrefix + 1	)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTANDOFF, kStandOffIDPrefix + 2)	// GenericPageItem's StandOff
DECLARE_PMID(kInterfaceIDSpace, IID_ISTANDOFFDATA, kStandOffIDPrefix + 3)	// for GenericPageItem's StandOff
DECLARE_PMID(kInterfaceIDSpace, IID_ISTANDOFFITEMDATA, kStandOffIDPrefix + 4)	// for StandOffPageItem
DECLARE_PMID(kInterfaceIDSpace, IID_ISTANDOFFMODECMDDATA, kStandOffIDPrefix + 5		)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTANDOFFFORMCMDDATA, kStandOffIDPrefix + 6		)

DECLARE_PMID(kInterfaceIDSpace, IID_ISTANDOFFMARGINCMDDATA, kStandOffIDPrefix + 8		)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTANDOFFITEMCMDDATA, kStandOffIDPrefix + 9		)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMTOPOLYGON, kStandOffIDPrefix + 10)	// used as IID_IPOLYGONCONVERTER2 in Rect2
DECLARE_PMID(kInterfaceIDSpace, IID_IOLDSTANDOFFDATA, kStandOffIDPrefix + 11)	// used as IID_ISTANDOFFDATA2 in kSetStandOffWorkspaceCmdBoss
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTINSET, kStandOffIDPrefix + 12	)
DECLARE_PMID(kInterfaceIDSpace, IID_IIGNOREWRAP, kStandOffIDPrefix + 13)	// used as kBoolDataImpl in MultiColumnPageItem, ignoreWrap.
DECLARE_PMID(kInterfaceIDSpace, IID_ISAVEDBOOLDATA, kStandOffIDPrefix + 14)	// used as kBoolDataImpl in kSetUserStandOffCmdBoss.
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTOURWRAPSETTINGS, kStandOffIDPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETCONTOURWRAPCMDDATA, kStandOffIDPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEMPINSET_DOCUMENT, kStandOffIDPrefix + 17)

// DragonTail IIDs
//DECLARE_PMID(kInterfaceIDSpace, IID_ISTANDOFFDATASUITE, kStandOffIDPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTWRAPFACADE, kStandOffIDPrefix + 52)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTWRAP_ISUITE, kStandOffIDPrefix + 53)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTWRAPOPTIONS, kStandOffIDPrefix + 54)
//DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTWRAPDEBUGFLAGS, kStandOffIDPrefix + 55)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTANDOFFPARCELUSEDLIST, kStandOffIDPrefix + 56)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPREADSTANDOFFS, kStandOffIDPrefix + 57)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPREADMULTICOLUMNFRAMES, kStandOffIDPrefix + 58)

DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTWRAPTARGET, kStandOffIDPrefix + 59)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTWRAPTARGETMANAGER, kStandOffIDPrefix + 60)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPREADMSPREADTEXTWRAPMANAGER, kStandOffIDPrefix + 61)
DECLARE_PMID(kInterfaceIDSpace, IID_IMSPREADDEPENDENTSPREADLIST, kStandOffIDPrefix + 62)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTANDOFFSIDECMDDATA, kStandOffIDPrefix + 63)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTANDOFFDATA_MODE, kStandOffIDPrefix + 64)	// M2M Message - turning wrap off

//---------------------------------------------------------------
// ImplementationIIDs
//---------------------------------------------------------------

DECLARE_PMID(kImplementationIDSpace, kPageItemStandOffImpl, kStandOffIDPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPageItemToPolygonImpl, kStandOffIDPrefix + 2	)
DECLARE_PMID(kImplementationIDSpace, kStandOffDataImpl, kStandOffIDPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kTextWrapAdornmentImpl, kStandOffIDPrefix + 4 )
DECLARE_PMID(kImplementationIDSpace, kTextInsetAdornmentImpl, kStandOffIDPrefix + 5 )

// Widget
// OBSOLETE: DECLARE_PMID(kImplementationIDSpace, kStandOffControlViewImpl, kStandOffIDPrefix + 4	)
// OBSOLETE: DECLARE_PMID(kImplementationIDSpace, kStandOffEventHandlerImpl, kStandOffIDPrefix + 5	)
// OBSOLETE: DECLARE_PMID(kImplementationIDSpace, kStandOffWidgetCreatorImpl, kStandOffIDPrefix + 6	)
// OBSOLETE: DECLARE_PMID(kImplementationIDSpace, kStandOffFocusImpl, kStandOffIDPrefix + 7	)
// OBSOLETE: DECLARE_PMID(kImplementationIDSpace, kStandOffSelectionObserverImpl, kStandOffIDPrefix + 8	)

DECLARE_PMID(kImplementationIDSpace, kStandOffItemDataImpl, kStandOffIDPrefix + 9	)

// PageItem
DECLARE_PMID(kImplementationIDSpace, kStandOffShapeImpl, kStandOffIDPrefix + 10	)

// Commands
DECLARE_PMID(kImplementationIDSpace, kStandOffModeCmdImpl, kStandOffIDPrefix + 13		)
DECLARE_PMID(kImplementationIDSpace, kStandOffFormCmdImpl, kStandOffIDPrefix + 14		)
DECLARE_PMID(kImplementationIDSpace, kStandOffModeCmdDataImpl, kStandOffIDPrefix + 15		)
DECLARE_PMID(kImplementationIDSpace, kStandOffFormCmdDataImpl, kStandOffIDPrefix + 16		)

// and the rest...
DECLARE_PMID(kImplementationIDSpace, kStandOffControlDataImpl, kStandOffIDPrefix + 17)		// Widget
DECLARE_PMID(kImplementationIDSpace, kStandOffM2MListenerImpl, kStandOffIDPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kDynamicStandOffImpl, kStandOffIDPrefix + 19)		// Widget
DECLARE_PMID(kImplementationIDSpace, kStandOffTransformImpl, kStandOffIDPrefix + 20)		// PageItem
DECLARE_PMID(kImplementationIDSpace, kLocalStandOffsImpl, kStandOffIDPrefix + 21)		// PageItem
DECLARE_PMID(kImplementationIDSpace, kSetTextInsetCmdImpl, kStandOffIDPrefix + 22)		// Commands
DECLARE_PMID(kImplementationIDSpace, kStandOffMarginCmdImpl, kStandOffIDPrefix + 23)		// Commands
DECLARE_PMID(kImplementationIDSpace, kStandOffMarginCmdDataImpl, kStandOffIDPrefix + 24)		// Commands
DECLARE_PMID(kImplementationIDSpace, kStandOffScrapImpl, kStandOffIDPrefix + 25)		// PageItem
DECLARE_PMID(kImplementationIDSpace, kNewStandOffItemCmdImpl, kStandOffIDPrefix + 26)		// Commands
DECLARE_PMID(kImplementationIDSpace, kDeleteStandOffItemCmdImpl, kStandOffIDPrefix + 27)		// Commands
DECLARE_PMID(kImplementationIDSpace, kChangeStandOffItemCmdImpl, kStandOffIDPrefix + 28)		// Commands
DECLARE_PMID(kImplementationIDSpace, kStandOffItemCmdDataImpl, kStandOffIDPrefix + 29)		// Commands
DECLARE_PMID(kImplementationIDSpace, kTextWrapForwarderM2MListenerImpl, kStandOffIDPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kStandOffHierarchyImpl, kStandOffIDPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kStandOffWorkspaceDataImpl, kStandOffIDPrefix + 32)		// IID_ISTANDOFFDATA
DECLARE_PMID(kImplementationIDSpace, kSetStandOffWorkspaceCmdImpl, kStandOffIDPrefix + 33)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kStandOffIDPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kTextInsetImpl, kStandOffIDPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kTextInsetScrapImpl, kStandOffIDPrefix + 36)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kStandOffIDPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kDeleteInsetPageItemCmdImpl, kStandOffIDPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kTextInsetShapeImpl, kStandOffIDPrefix + 39)
// gap
DECLARE_PMID(kImplementationIDSpace, kStandOffGeometryImpl, kStandOffIDPrefix + 41)
// gap
DECLARE_PMID(kImplementationIDSpace, kStandOffSubjectImpl, kStandOffIDPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kStandOffConversionProviderImpl, kStandOffIDPrefix + 45)
// gap
DECLARE_PMID(kImplementationIDSpace, kIgnoreWrapImpl, kStandOffIDPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kSetIgnoreWrapCmdImpl, kStandOffIDPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kSetUserStandOffCmdImpl, kStandOffIDPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kPrivateConnectItemsCmdImpl, kStandOffIDPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kStandOffNewPIResponderImpl, kStandOffIDPrefix + 52)
//DECLARE_PMID(kImplementationIDSpace, kSelectStandOffCmdImpl, kStandOffIDPrefix + 53)		// SelectStandOffCmd.cpp
//DECLARE_PMID(kImplementationIDSpace, kDeselectStandOffCmdImpl, kStandOffIDPrefix + 54)		// SelectStandOffCmd.cpp
// gap
DECLARE_PMID(kImplementationIDSpace, kNewInsetPageItemCmdImpl, kStandOffIDPrefix + 56		)
// gap
DECLARE_PMID(kImplementationIDSpace, kStandOffWorkspaceDataImpl2, kStandOffIDPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kPrivateDisconnectItemsCmdImpl, kStandOffIDPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kZOrderWrapOptimizerImpl, kStandOffIDPrefix + 60)

DECLARE_PMID(kImplementationIDSpace, kContourWrapSettingsImpl, kStandOffIDPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kSessionContourWrapSettingsImpl, kStandOffIDPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kDocumentContourWrapSettingsImpl, kStandOffIDPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kSetContourWrapCmdDataImpl, kStandOffIDPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kSetContourWrapCmdImpl, kStandOffIDPrefix + 65)

DECLARE_PMID(kImplementationIDSpace, kSOGraphicFrameDataImpl, kStandOffIDPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kUpdateStandOffCmdImpl, kStandOffIDPrefix + 67)

// New to DragonTail
//DECLARE_PMID(kImplementationIDSpace, kStandOffDataSuiteASBImpl, kStandOffIDPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kTextWrapFacadeImpl, kStandOffIDPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kTextWrapSuiteImpl, kStandOffIDPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kTextWrapSuiteLayoutImpl, kStandOffIDPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kDocTextWrapOptionsImpl, kStandOffIDPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kSessionTextWrapOptionsImpl, kStandOffIDPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kSetZOrderTextWrapCmdImpl, kStandOffIDPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kSetSkipByLineHeightCmdImpl, kStandOffIDPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kTextWrapScriptProviderImpl, kStandOffIDPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kTextWrapScriptImpl, kStandOffIDPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kContourOptionsScriptProviderImpl, kStandOffIDPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kContourOptionsScriptImpl, kStandOffIDPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kTextWrapSuiteDefaultImpl, kStandOffIDPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kTextWrapSuiteDefaultSelExtImpl, kStandOffIDPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kTextWrapSuiteLayoutSelExtImpl, kStandOffIDPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kContourOptionsScriptProvider40Impl, kStandOffIDPrefix + 115)

//DECLARE_PMID(kImplementationIDSpace, kTextWrapDebugFlagsImpl, kStandOffIDPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kTextWrapObjStylesHandlerImpl, kStandOffIDPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kObjStylesStandOffDataImpl, kStandOffIDPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kOObjStylesContourWrapDataImpl, kStandOffIDPrefix + 119)
//DECLARE_PMID(kImplementationIDSpace, kUnusedImpl, kStandOffIDPrefix + 120)
//DECLARE_PMID(kImplementationIDSpace, kUnusedImpl, kStandOffIDPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kStandOffParcelUsedListImpl, kStandOffIDPrefix + 122)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kStandOffIDPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kSpreadMultiColumnFramesImpl, kStandOffIDPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kSpreadStandOffsImpl, kStandOffIDPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kTextWrapTargetManagerImpl, kStandOffIDPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kSpreadMSpreadTextWrapManagerImpl, kStandOffIDPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kMSpreadDependentSpreadListImpl, kStandOffIDPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kStandOffActiveFromMasterCmdImpl, kStandOffIDPrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kStandOffSideCmdImpl, kStandOffIDPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kStandOffSideCmdDataImpl, kStandOffIDPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kObjectFCTextWrapAttrInfoImpl, kStandOffIDPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kObjectFCAnchoredFrameAttrInfoImpl, kStandOffIDPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kStandOffRefConverterImpl, kStandOffIDPrefix + 134)


// ActionID
DECLARE_PMID(kActionIDSpace, kStandOffModeNoneActionID, kStandOffIDPrefix + 1)
DECLARE_PMID(kActionIDSpace, kStandOffModeBandActionID, kStandOffIDPrefix + 2)
DECLARE_PMID(kActionIDSpace, kStandOffModeBothSidesActionID, kStandOffIDPrefix + 3)
DECLARE_PMID(kActionIDSpace, kStandOffModeNextFrameActionID, kStandOffIDPrefix + 4)
DECLARE_PMID(kActionIDSpace, kStandOffModeAutoContourActionID, kStandOffIDPrefix + 5)
DECLARE_PMID(kActionIDSpace, kStandOffModeManualContourActionID, kStandOffIDPrefix + 6)
DECLARE_PMID(kActionIDSpace, kStandOffFormInvertOnActionID, kStandOffIDPrefix + 7)
DECLARE_PMID(kActionIDSpace, kStandOffFormInvertOffActionID, kStandOffIDPrefix +  8)
DECLARE_PMID(kActionIDSpace, kStandOffModeLeftContourActionID, kStandOffIDPrefix + 9)
DECLARE_PMID(kActionIDSpace, kStandOffModeRightContourActionID, kStandOffIDPrefix + 10)
DECLARE_PMID(kActionIDSpace, kStandOffModeActionID, kStandOffIDPrefix + 11)
DECLARE_PMID(kActionIDSpace, kStandOffFormActionID, kStandOffIDPrefix + 12)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kTextWrapObjectScriptElement,					kStandOffIDPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kContourOptionsObjectScriptElement,			kStandOffIDPrefix + 23)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kZOrderTextWrapsPropertyScriptElement,			kStandOffIDPrefix + 170)
DECLARE_PMID(kScriptInfoIDSpace, kAbutTextToTextWrapsPropertyScriptElement,		kStandOffIDPrefix + 171)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kTextWrapPropertyScriptElement,				kStandOffIDPrefix + 178)
DECLARE_PMID(kScriptInfoIDSpace, kTextWrapTypePropertyScriptElement,			kStandOffIDPrefix + 179)
DECLARE_PMID(kScriptInfoIDSpace, kTextWrapOffsetPropertyScriptElement,			kStandOffIDPrefix + 180)
DECLARE_PMID(kScriptInfoIDSpace, kTextWrapInversePropertyScriptElement,			kStandOffIDPrefix + 181)
DECLARE_PMID(kScriptInfoIDSpace, kFCTextWrapOffsetPropertyScriptElement,		kStandOffIDPrefix + 182)
DECLARE_PMID(kScriptInfoIDSpace, kContourOptionsPropertyScriptElement,			kStandOffIDPrefix + 183)
DECLARE_PMID(kScriptInfoIDSpace, kContourOptionsTypePropertyScriptElement,		kStandOffIDPrefix + 184)
DECLARE_PMID(kScriptInfoIDSpace, kContourNamePropertyScriptElement,				kStandOffIDPrefix + 185)
DECLARE_PMID(kScriptInfoIDSpace, kTextWrapApplyToMasterPageOnlyPropertyScriptElement,kStandOffIDPrefix + 186)
DECLARE_PMID(kScriptInfoIDSpace, kTextWrapSidePropertyScriptElement,			kStandOffIDPrefix + 187)
DECLARE_PMID(kScriptInfoIDSpace, kTextWrapModePropertyScriptElement,			kStandOffIDPrefix + 188)
DECLARE_PMID(kScriptInfoIDSpace, kTextWrapUserModifiedPropertyScriptElement,	kStandOffIDPrefix + 189)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kTextWrapTypeEnumScriptElement,				kStandOffIDPrefix + 222)
DECLARE_PMID(kScriptInfoIDSpace, kContourOptionsTypeEnumScriptElement,			kStandOffIDPrefix + 223)
DECLARE_PMID(kScriptInfoIDSpace, kTextWrapSideEnumScriptElement,				kStandOffIDPrefix + 224)
DECLARE_PMID(kScriptInfoIDSpace, kTextWrapModeEnumScriptElement,				kStandOffIDPrefix + 225)


//GUIDS
// {E76DB095-D513-4e19-9DEC-42DC06B44592}
#define kTextWrap_CLSID { 0xe76db095, 0xd513, 0x4e19, { 0x9d, 0xec, 0x42, 0xdc, 0x6, 0xb4, 0x45, 0x92 } }
// {8AB9A718-3241-4bef-B959-60F5DC071350}
#define kContourOptions_CLSID { 0x8ab9a718, 0x3241, 0x4bef, { 0xb9, 0x59, 0x60, 0xf5, 0xdc, 0x7, 0x13, 0x50 } }

#endif // __StandOffID__





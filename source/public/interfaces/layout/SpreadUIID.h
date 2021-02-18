//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/SpreadUIID.h $
//  
//  Owner: Robin_Briggs
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
//  Contains IDs used by the spreadUI plug-in
//  
//========================================================================================

#ifndef __SpreadUIID__
#define __SpreadUIID__

// Must be first to set flags before other includes (So I get the DEBUG define)
#include "GeneralBuildFlags.h"

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kSpreadUIPrefix	 RezLong(0x5F00)

// <Start IDC>
// PluginID
#define kSpreadUIPluginName			"Spread UI"
DECLARE_PMID(kPlugInIDSpace, kSpreadUIPluginID, kSpreadUIPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kSpreadUIMenuActionBoss, kSpreadUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kPrefsMenuActionBoss, kSpreadUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kViewPrefsMenuActionBoss, kSpreadUIPrefix + 3)
DECLARE_PMID(kClassIDSpace, kGridPrefsDialogBoss, kSpreadUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kGuidePrefsDialogBoss, kSpreadUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kPageToolBoss, kSpreadUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kUnitsPrefsDialogBoss, kSpreadUIPrefix + 7)

DECLARE_PMID(kClassIDSpace, kColumnGuideTrackerBoss, kSpreadUIPrefix + 8)
DECLARE_PMID(kClassIDSpace, kColumnGuideTrackerRegisterBoss, kSpreadUIPrefix + 9)
DECLARE_PMID(kClassIDSpace, kFitPageInViewCmdBoss, kSpreadUIPrefix + 10)
DECLARE_PMID(kClassIDSpace, kSpreadTestMenuBoss, kSpreadUIPrefix + 11)
DECLARE_PMID(kClassIDSpace, kSpreadKBSCMenuActionBoss, kSpreadUIPrefix + 12)
DECLARE_PMID(kClassIDSpace, kColumnMarginLayoutActionBoss, kSpreadUIPrefix + 13)
DECLARE_PMID(kClassIDSpace, kSpreadWorkspaceLayoutActionBoss, kSpreadUIPrefix + 14)
DECLARE_PMID(kClassIDSpace, kSpreadListLayoutActionBoss, kSpreadUIPrefix + 15)
DECLARE_PMID(kClassIDSpace, kColumnGuideHitTestServicesBoss, kSpreadUIPrefix + 16)

DECLARE_PMID(kClassIDSpace, kSnapToBaselineGridServiceBoss, kSpreadUIPrefix + 17)
DECLARE_PMID(kClassIDSpace, kSnapToColumnGuidesServiceBoss, kSpreadUIPrefix + 18)
DECLARE_PMID(kClassIDSpace, kSnapToGridServiceBoss, kSpreadUIPrefix + 19)
DECLARE_PMID(kClassIDSpace, kSnapToMarginGuidesServiceBoss, kSpreadUIPrefix + 20)
DECLARE_PMID(kClassIDSpace, kSnapToPageServiceBoss, kSpreadUIPrefix + 21)
DECLARE_PMID(kClassIDSpace, kSnapToRulerGuidesServiceBoss, kSpreadUIPrefix + 22)
DECLARE_PMID(kClassIDSpace, kSnapToRulerTickmarksServiceBoss, kSpreadUIPrefix + 23)
DECLARE_PMID(kClassIDSpace, kSnapToSelectionServiceBoss, kSpreadUIPrefix + 24)

DECLARE_PMID(kClassIDSpace, kColumnGuideSelectFilterBoss, kSpreadUIPrefix + 25)
DECLARE_PMID(kClassIDSpace, kPointsPerInchObserverBoss, kSpreadUIPrefix + 26)

DECLARE_PMID(kClassIDSpace, kMainItemNewDocResponderBoss, kSpreadUIPrefix + 27)
DECLARE_PMID(kClassIDSpace, kMainItemOpenDocResponderBoss, kSpreadUIPrefix + 28)
DECLARE_PMID(kClassIDSpace, kSnapToSmartGuideServiceBoss, kSpreadUIPrefix + 29)
DECLARE_PMID(kClassIDSpace, kSetSmartGuidePrefsCmdBoss, kSpreadUIPrefix + 30)
DECLARE_PMID(kClassIDSpace, kSmartGuidePrefsScriptProviderBoss, kSpreadUIPrefix + 31)
DECLARE_PMID(kClassIDSpace, kPageToolTrackerBoss, kSpreadUIPrefix + 32)
DECLARE_PMID(kClassIDSpace, kSpreadUITrackerRegisterBoss, kSpreadUIPrefix + 33)
DECLARE_PMID(kClassIDSpace, kPrimaryTextFlowTrackerBoss, kSpreadUIPrefix + 34)
DECLARE_PMID(kClassIDSpace, kPrimaryTextFlowToolBoss, kSpreadUIPrefix + 35)	// Just for registering the tracker, there isn't an actual Primary Text Flow Tool
DECLARE_PMID(kClassIDSpace, kPrimaryTextFlowHandleAdornmentBoss, kSpreadUIPrefix + 36)
DECLARE_PMID(kClassIDSpace, kGuideHandleAdornmentTrackerBoss, kSpreadUIPrefix + 37)
DECLARE_PMID(kClassIDSpace, kGuideToolBoss, kSpreadUIPrefix + 38)	// Just for registering the tracker, there isn't an actual Guide Tool
DECLARE_PMID(kClassIDSpace, kGuideHandleAdornmentBoss, kSpreadUIPrefix + 39)
DECLARE_PMID(kClassIDSpace, kPageHandleAdornmentBoss, kSpreadUIPrefix + 40)
DECLARE_PMID(kClassIDSpace, kPageHandleAdornmentTrackerBoss, kSpreadUIPrefix + 41)
DECLARE_PMID(kClassIDSpace, kPageHandleToolBoss, kSpreadUIPrefix + 42)	// Just for registering the tracker, there isn't an actual Page Handle Tool
DECLARE_PMID(kClassIDSpace, kTouchContextMenuHandleAdornmentBoss, kSpreadUIPrefix + 43)
DECLARE_PMID(kClassIDSpace, kTouchContextMenuHandleAdornmentTrackerBoss, kSpreadUIPrefix + 44)
DECLARE_PMID(kClassIDSpace, kTouchContextMenuDialogPopupWindowBoss, kSpreadUIPrefix + 45)

DECLARE_PMID(kClassIDSpace, kRulersGridsPrefsDialogBoss, kSpreadUIPrefix + 46)

// <Interface ID>
// IIDs

DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTCOLUMNMARGINOBSERVER, kSpreadUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTPREFSOBSERVER, kSpreadUIPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTSPREADLISTOBSERVER, kSpreadUIPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNAPTOSERVICE, kSpreadUIPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNAPTOSELECTIONSUITE, kSpreadUIPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IMAINITEMOBSERVER, kSpreadUIPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ISMARTGUIDES, kSpreadUIPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ISMARTGUIDEPREFS, kSpreadUIPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IGUIDESFACADE, kSpreadUIPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ISMARTDIMENSIONS, kSpreadUIPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IGUIDEPREFERENCESFACADE, kSpreadUIPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ISMARTDIMENSIONSALLOWABLECONTAINER, kSpreadUIPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIMARYTEXTFLOWUIDDATA, kSpreadUIPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IHANDLEINDEXDATA, kSpreadUIPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGERESIZETRACKERBEGIN, kSpreadUIPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGERESIZETRACKEREND, kSpreadUIPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEUIUTILS, kSpreadUIPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOUCHCONTEXTMENUADORNMENTINFO, kSpreadUIPrefix + 18)

// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kSpreadUIMenuActionImpl, kSpreadUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPrefsMenuActionImpl, kSpreadUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kViewPrefsMenuActionImpl, kSpreadUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kGridPrefsDialogControllerImpl, kSpreadUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kGuidePrefsDialogControllerImpl, kSpreadUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kGridPrefsPanelCreatorImpl, kSpreadUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kGuidePrefsPanelCreatorImpl, kSpreadUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kPointsPerInchObserverImpl, kSpreadUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kUnitsPrefsDialogObserverImpl, kSpreadUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kUnitsPrefsDialogControllerImpl, kSpreadUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kUnitsPrefsPanelCreatorImpl, kSpreadUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kColumnGuideTrackerImpl, kSpreadUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kColumnGuideTrackerRegisterImpl, kSpreadUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kFitPageInViewCmdImpl, kSpreadUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kSpreadTestMenuImpl, kSpreadUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kSpreadKBSCMenuActionImpl, kSpreadUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kColumnMarginLayoutActionImpl, kSpreadUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kLayoutColumnMarginObserverImpl, kSpreadUIPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kLayoutPrefsObserverImpl, kSpreadUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kSpreadWorkspaceLayoutActionImpl, kSpreadUIPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kCLayoutSpreadListObserverImpl, kSpreadUIPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kSpreadListLayoutActionImpl, kSpreadUIPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kColumnGuideHitTestServiceImpl, kSpreadUIPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kColumnGuideHitTestHandlerImpl, kSpreadUIPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kCSnapToImpl, kSpreadUIPrefix + 25)

DECLARE_PMID(kImplementationIDSpace, kSnapToServiceProviderImpl, kSpreadUIPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kSnapToBaselineGridServiceImpl, kSpreadUIPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kSnapToColumnGuidesServiceImpl, kSpreadUIPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kSnapToGridServiceImpl, kSpreadUIPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kSnapToMarginGuidesServiceImpl, kSpreadUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kSnapToPageServiceImpl, kSpreadUIPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kSnapToRulerGuidesServiceImpl, kSpreadUIPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kSnapToRulerTickmarksServiceImpl, kSpreadUIPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kSnapToSelectionServiceImpl, kSpreadUIPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kSnapToSelectionSuiteLayoutCSBImpl, kSpreadUIPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kSnapToSelectionSuiteASBImpl, kSpreadUIPrefix + 36)

DECLARE_PMID(kImplementationIDSpace, kColumnGuideSelectFilterImpl, kSpreadUIPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kPointsPerInchCalculatedValueImpl, kSpreadUIPrefix + 38)

DECLARE_PMID(kImplementationIDSpace, kMainItemObserverImpl, kSpreadUIPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kMainItemNewDocResponderImpl, kSpreadUIPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kMainItemOpenDocResponderImpl, kSpreadUIPrefix + 41)

DECLARE_PMID(kImplementationIDSpace, kSnapToSmartGuideServiceImpl, kSpreadUIPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kSmartGuidesImpl, kSpreadUIPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kGuidesFacadeImpl, kSpreadUIPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kSmartGuidePrefsImpl, kSpreadUIPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kSetSmartGuidePrefsCmdImpl, kSpreadUIPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kSmartDimensionsImpl, kSpreadUIPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kGuidePreferencesFacadeImpl, kSpreadUIPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kSmartGuidePrefsScriptProviderImpl, kSpreadUIPrefix + 49)

DECLARE_PMID(kImplementationIDSpace, kPageToolImpl, kSpreadUIPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kPageToolCursorProviderImpl, kSpreadUIPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kPageToolTrackerImpl, kSpreadUIPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kSpreadUITrackerRegisterImpl, kSpreadUIPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kGuidePrefsDialogObserverImpl, kSpreadUIPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kPrimaryTextFlowTrackerImpl, kSpreadUIPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kPrimaryTextFlowHandleAdornmentImpl, kSpreadUIPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kPrimaryTextFlowHandleTipImpl, kSpreadUIPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kGuideHandleAdornmentTrackerImpl, kSpreadUIPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kGuideHandleAdornmentImpl, kSpreadUIPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kGuideHandleAdornmentTipImpl, kSpreadUIPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kPageHandleShapeImpl, kSpreadUIPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kPageHandleAdornmentImpl, kSpreadUIPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kPageHandleAdornmentTipImpl, kSpreadUIPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kPageHandleAdornmentTrackerImpl, kSpreadUIPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kPageUIUtilsImpl, kSpreadUIPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kTouchContextMenuHandleAdornmentImpl, kSpreadUIPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kTouchContextMenuHandleAdornmentTrackerImpl, kSpreadUIPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kTouchContextMenuAdornmentInfoImpl, kSpreadUIPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kTouchContextMenuDialogPositioningHelperImpl, kSpreadUIPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kTouchContextMenuDialogPopupWindowImpl, kSpreadUIPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kEraseViewImpl, kSpreadUIPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kTouchContextMenuPopupWindowEHImpl, kSpreadUIPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kRulersGridsPrefsDialogObserverImpl, kSpreadUIPrefix + 73)

// <Widget ID>
// Widget IDs for Grids Prefs dialog - Baseline Grids section
DECLARE_PMID(kWidgetIDSpace, kBaselineGridStartWidgetID, kSpreadUIPrefix + 1 )
DECLARE_PMID(kWidgetIDSpace, kBaselineGridDivisionWidgetID, kSpreadUIPrefix + 2 )
DECLARE_PMID(kWidgetIDSpace, kBaselineGridViewLimitWidgetID, kSpreadUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kBaselineGridTitleTextWidgetID, kSpreadUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kBaselineGridRelativeToWidgetID, kSpreadUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kBaselineGridStartTextWidgetID, kSpreadUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kBaselineGridDivisionTextWidgetID, kSpreadUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kBaselineGridViewLimitTextWidgetID, kSpreadUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kBaselineGridPercentageTextWidgetID, kSpreadUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kBaselineGridColorTextWidgetID, kSpreadUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kBaselineGridColorDropDownWidgetID, kSpreadUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kBaselineGridRelativeToDropDownWidgetID, kSpreadUIPrefix + 12)

DECLARE_PMID(kWidgetIDSpace, kBaselinePrefsPanelWidgetId, kSpreadUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kBaselineGenericPanellWidgetId, kSpreadUIPrefix + 14)

// Widget IDs for Grids Prefs dialog - Grids section
DECLARE_PMID(kWidgetIDSpace, kGridHDivisionWidgetID, kSpreadUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kGridVDivisionWidgetID, kSpreadUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kGridHSubDivisionsWidgetID, kSpreadUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kGridVSubDivisionsWidgetID, kSpreadUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kGridTitleTextWidgetID, kSpreadUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kGridHTitleTextWidgetID, kSpreadUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kGridVTitleTextWidgetID, kSpreadUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kGridHDivisionTextWidgetID, kSpreadUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kGridHSubDivisionsTextWidgetID, kSpreadUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kGridVDivisionTextWidgetID, kSpreadUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kGridVSubDivisionsTextWidgetID, kSpreadUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kGridColorTextWidgetID, kSpreadUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kLayoutGridColorDropDownWidgetID, kSpreadUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kSnapToZonePixelsWidgetID, kSpreadUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kGridsInBackCheckboxWidgetID, kSpreadUIPrefix + 29)

// Widget IDs for Guide Prefs dialog - Snap-to section
DECLARE_PMID(kWidgetIDSpace, kSnapToWidgetID, kSpreadUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kSnapToTitleTextWidgetID, kSpreadUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kSnapToTextWidgetID, kSpreadUIPrefix + 32)

// Widget IDs for Guide Prefs dialog - Margin and Column Guides section
DECLARE_PMID(kWidgetIDSpace, kMarginColorTextWidgetID, kSpreadUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kColumnColorTextWidgetID, kSpreadUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kMarginColorDropDownWidgetID, kSpreadUIPrefix + 35)
//DECLARE_PMID(kWidgetIDSpace, kChangeMarginColorSwatchWidgetID, kSpreadUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kColumnColorDropDownWidgetID, kSpreadUIPrefix + 37)
//DECLARE_PMID(kWidgetIDSpace, kChangeColumnColorSwatchWidgetID, kSpreadUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kGuidesBackCheckboxWidgetID, kSpreadUIPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kMarginTitleTextWidgetID, kSpreadUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kColumnTitleTextWidgetID, kSpreadUIPrefix + 41)

// Widget IDs for Units Prefs dialog - Measurement system and keyboard increments section
DECLARE_PMID(kWidgetIDSpace, kHorizontalTextWidgetID, kSpreadUIPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kHorizontalUnitsDropDownWidgetID, kSpreadUIPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kVerticalTextWidgetID, kSpreadUIPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kVerticalUnitsDropDownWidgetID, kSpreadUIPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kMeasurementTitleTextWidgetID, kSpreadUIPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kCustomHRulerEditboxWidgetID, kSpreadUIPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kCustomVRulerEditboxWidgetID, kSpreadUIPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kKeyboardIncreTitleTextWidgetID, kSpreadUIPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kCursorKeyTextWidgetID, kSpreadUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kCursorKeyEditboxWidgetID, kSpreadUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kSizeLeadingTextWidgetID, kSpreadUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kSizeLeadingEditboxWidgetID, kSpreadUIPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kBaselineShiftTextWidgetID, kSpreadUIPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kBaselineShiftEditboxWidgetID, kSpreadUIPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kTrackingTextWidgetID, kSpreadUIPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kTrackingEditboxWidgetID, kSpreadUIPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kRulerCoordinateTextWidgetID, kSpreadUIPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kRulerCoordinateDropDownWidgetID, kSpreadUIPrefix + 59	)

// Dialog Panel IDs
DECLARE_PMID(kWidgetIDSpace, kGridPrefsDialogPanelWidgetID, kSpreadUIPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kGuidePrefsDialogPanelWidgetID, kSpreadUIPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kUnitsPrefsDialogPanelWidgetID, kSpreadUIPrefix + 62)

DECLARE_PMID(kWidgetIDSpace, kGuidePrefsGroupWidgetId, kSpreadUIPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kGuidePrefsGroup2WidgetId, kSpreadUIPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kGuidePrefsGroup3WidgetId, kSpreadUIPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kGuidePrefsGroup4WidgetId, kSpreadUIPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kGuidePrefsGroup5WidgetId, kSpreadUIPrefix + 67)

DECLARE_PMID(kWidgetIDSpace, kpointsLabelWidgetId, kSpreadUIPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kpointsLabel2WidgetId, kSpreadUIPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kemLabelWidgetId, kSpreadUIPrefix + 70)

DECLARE_PMID(kWidgetIDSpace, kGridHPanelWidgetID, kSpreadUIPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kGridVPanelWidgetID, kSpreadUIPrefix + 72)

DECLARE_PMID(kWidgetIDSpace, kTextTextWidgetID, kSpreadUIPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kTextUnitsDropDownWidgetID, kSpreadUIPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kTextSizeTextWidgetID, kSpreadUIPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kTextSizeUnitsDropDownWidgetID, kSpreadUIPrefix + 76)

DECLARE_PMID(kWidgetIDSpace, kPointPicaSizeGroupWidgetId, kSpreadUIPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kPointPicaSizeTextWidgetID, kSpreadUIPrefix + 78)

DECLARE_PMID(kWidgetIDSpace, kLineUnitsTextWidgetID, kSpreadUIPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kLineUnitsDropDownWidgetID, kSpreadUIPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kOtherUnitsTitleTextWidgetID, kSpreadUIPrefix + 81)

DECLARE_PMID(kWidgetIDSpace, kPageToolWidgetId, kSpreadUIPrefix + 82)

// Pasteboard preferences panel:
//DECLARE_PMID(kWidgetIDSpace, kPasteboardPrefsDialogPanelWidgetID, kSpreadUIPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kPasteboardPrefsPanelWidgetId, kSpreadUIPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kPasteboardTitleTextWidgetID, kSpreadUIPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kPasteboardColorTextWidgetID, kSpreadUIPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kPasteboardColorDropDownWidgetID, kSpreadUIPrefix + 86)
//DECLARE_PMID(kWidgetIDSpace, kPasteboardGenericPanellWidgetId, kSpreadUIPrefix + 87)
//DECLARE_PMID(kWidgetIDSpace, kChangePasteboardColorSwatchWidgetID, kSpreadUIPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kPasteboardMinExtraHeightTextWidgetID, kSpreadUIPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kPasteboardMinExtraHeightWidgetID, kSpreadUIPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kPasteboardMinExtraWidthTextWidgetID, kSpreadUIPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kPasteboardMinExtraWidthWidgetID, kSpreadUIPrefix + 92)

// New widgets for color & pasteboard prefs (some older ones still in use)
DECLARE_PMID(kWidgetIDSpace, kGuideColorsGroupWidgetId, kSpreadUIPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kColorTitleTextWidgetID, kSpreadUIPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kBleedColorTextWidgetID, kSpreadUIPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kBleedColorDropDownWidgetID, kSpreadUIPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kSlugColorTextWidgetID, kSpreadUIPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kSlugColorDropDownWidgetID, kSpreadUIPrefix + 105)

DECLARE_PMID(kWidgetIDSpace, kPointsPerInchStaticTextWidgetId, kSpreadUIPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kPointsPerInchDropDownWidgetID, kSpreadUIPrefix + 107)

// Smart/Wise Guide prefs
DECLARE_PMID(kWidgetIDSpace, kSmartGuidesColorTextWidgetID, kSpreadUIPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kSmartGuidesColorDropDownWidgetID, kSpreadUIPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kSmartGuidesPrefsPanelWidgetId, kSpreadUIPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kSmartGuidesTitleTextWidgetID, kSpreadUIPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kSmartGuidesCenterCheckboxWidgetID, kSpreadUIPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kSmartGuidesEdgesCheckboxWidgetID, kSpreadUIPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kSmartDimensionsCheckboxWidgetID, kSpreadUIPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kSmartSpacingCheckboxWidgetID, kSpreadUIPrefix + 115)

DECLARE_PMID(kWidgetIDSpace, kPageTransitionAlertWarningID, kSpreadUIPrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kPreviewColorMatchThemeCheckBoxWID, kSpreadUIPrefix + 117)

// Rulers and Grids Kit: Properties Panel
DECLARE_PMID(kWidgetIDSpace, kRulersGridsPanelWidgetID, kSpreadUIPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kRulersGridsIconButtonHolderWidgetID, kSpreadUIPrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kRulersGridsButtonFocusWidgetId, kSpreadUIPrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kShowBaselineGridButtonWidgetID, kSpreadUIPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kShowGridButtonWidgetID, kSpreadUIPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kShowRulersButtonWidgetID, kSpreadUIPrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kShowLayoutGridButtonWidgetID, kSpreadUIPrefix + 124)

// <Action ID>
DECLARE_PMID(kActionIDSpace, kGridPrefsActionID, kSpreadUIPrefix +1)
DECLARE_PMID(kActionIDSpace, kGuidePrefsActionID, kSpreadUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kUnitsPrefsActionID, kSpreadUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kViewPrefsActionID, kSpreadUIPrefix + 4 )

DECLARE_PMID(kActionIDSpace, kShowGuidesActionID, kSpreadUIPrefix +5)
DECLARE_PMID(kActionIDSpace, kLockGuidesActionID, kSpreadUIPrefix +6)
DECLARE_PMID(kActionIDSpace, kShowBaselineGridActionID, kSpreadUIPrefix +7)
DECLARE_PMID(kActionIDSpace, kSnapToGuideActionID, kSpreadUIPrefix +8)

DECLARE_PMID(kActionIDSpace, kShowGridActionID, kSpreadUIPrefix +9)
DECLARE_PMID(kActionIDSpace, kSnapToGridActionID, kSpreadUIPrefix +10)

DECLARE_PMID(kActionIDSpace, kShowFrameEdgeActionID, kSpreadUIPrefix + 11)
DECLARE_PMID(kActionIDSpace, kShowFrameThreadsActionID, kSpreadUIPrefix + 12)
DECLARE_PMID(kActionIDSpace, kFirstPageActionID, kSpreadUIPrefix + 13)
DECLARE_PMID(kActionIDSpace, kLastPageActionID, kSpreadUIPrefix + 14)
DECLARE_PMID(kActionIDSpace, kNextPageActionID, kSpreadUIPrefix + 15)
DECLARE_PMID(kActionIDSpace, kPreviousPageActionID, kSpreadUIPrefix + 16)
// gap
DECLARE_PMID(kActionIDSpace, kShowGuideSepActionID, kSpreadUIPrefix + 18)
DECLARE_PMID(kActionIDSpace, kShowBaselineSepActionID, kSpreadUIPrefix + 19)
DECLARE_PMID(kActionIDSpace, kNothingShowGridSepActionID, kSpreadUIPrefix + 20)
DECLARE_PMID(kActionIDSpace, kGuideLockSepActionID, kSpreadUIPrefix + 21)
DECLARE_PMID(kActionIDSpace, kGuidesInBackActionID, kSpreadUIPrefix + 22)
DECLARE_PMID(kActionIDSpace, kGridsInBackActionID, kSpreadUIPrefix + 23)
DECLARE_PMID(kActionIDSpace, kGridsSepActionID, kSpreadUIPrefix + 24)
DECLARE_PMID(kActionIDSpace, kGuidesSepActionID, kSpreadUIPrefix + 25)
DECLARE_PMID(kActionIDSpace, kAddNewPageActionID, kSpreadUIPrefix + 26)
DECLARE_PMID(kActionIDSpace, kLockColumnGuidesActionID, kSpreadUIPrefix + 27)

DECLARE_PMID(kActionIDSpace, kGuidePrefsSepActionID, kSpreadUIPrefix + 28)
DECLARE_PMID(kActionIDSpace, kShowSmartGuidesActionID, kSpreadUIPrefix + 29)
DECLARE_PMID(kActionIDSpace, kPageToolActionID, kSpreadUIPrefix + 30)

DECLARE_PMID(kActionIDSpace, kSetLayoutPolicyUseMasterActionID, kSpreadUIPrefix + 31)
DECLARE_PMID(kActionIDSpace, kSetLayoutPolicyRecenterActionID, kSpreadUIPrefix + 32)
DECLARE_PMID(kActionIDSpace, kSetLayoutPolicyRepositionActionID, kSpreadUIPrefix + 33)
DECLARE_PMID(kActionIDSpace, kSetLayoutPolicyScaleActionID, kSpreadUIPrefix + 34)
DECLARE_PMID(kActionIDSpace, kSetLayoutPolicyGuideSliceActionID, kSpreadUIPrefix + 35)
DECLARE_PMID(kActionIDSpace, kSetLayoutPolicyOffActionID, kSpreadUIPrefix + 36)
DECLARE_PMID(kActionIDSpace, kLayoutPolicySep1ActionID, kSpreadUIPrefix + 37)
DECLARE_PMID(kActionIDSpace, kLayoutPolicySep2ActionID, kSpreadUIPrefix + 38)
DECLARE_PMID(kActionIDSpace, kLayoutPolicySep3ActionID, kSpreadUIPrefix + 39)
DECLARE_PMID(kActionIDSpace, kObjectConstraintPinLeftActionID, kSpreadUIPrefix + 40)
DECLARE_PMID(kActionIDSpace, kObjectConstraintPinRightActionID, kSpreadUIPrefix + 41)
DECLARE_PMID(kActionIDSpace, kObjectConstraintCenterHorizontallyActionID, kSpreadUIPrefix + 42)
DECLARE_PMID(kActionIDSpace, kObjectConstraintSepActionID, kSpreadUIPrefix + 43)
DECLARE_PMID(kActionIDSpace, kObjectConstraintPinTopActionID, kSpreadUIPrefix + 44)
DECLARE_PMID(kActionIDSpace, kObjectConstraintPinBottomActionID, kSpreadUIPrefix + 45)
DECLARE_PMID(kActionIDSpace, kObjectConstraintCenterVerticallyActionID, kSpreadUIPrefix + 46)
DECLARE_PMID(kActionIDSpace, kObjectConstraintResizeHorizontallyActionID, kSpreadUIPrefix + 47)
DECLARE_PMID(kActionIDSpace, kObjectConstraintResizeVerticallyActionID, kSpreadUIPrefix + 48)

DECLARE_PMID(kServiceIDSpace, kSnapToService, kSpreadUIPrefix + 1)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kSmartGuidePrefsObjectScriptElement,        kSpreadUIPrefix + 20)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kSmartGuidePrefsPropertyScriptElement,			kSpreadUIPrefix + 120)
DECLARE_PMID(kScriptInfoIDSpace, kShowSmartGuidesPropertyScriptElement,			kSpreadUIPrefix + 121)
DECLARE_PMID(kScriptInfoIDSpace, kSmartAlignEdgeGuidesPropertyScriptElement,    kSpreadUIPrefix + 122)
DECLARE_PMID(kScriptInfoIDSpace, kSmartAlignCenterGuidesPropertyScriptElement,  kSpreadUIPrefix + 123)
DECLARE_PMID(kScriptInfoIDSpace, kSmartDimensionsPropertyScriptElement,			kSpreadUIPrefix + 124)
DECLARE_PMID(kScriptInfoIDSpace, kSmartSpacingPropertyScriptElement,			kSpreadUIPrefix + 125)

//Enums

//GUIDS
// {41F6CD3B-D5B2-405c-A899-9FBCE2DD9B8A}
#define kSmartGuidePref_CLSID {0x41f6cd3b, 0xd5b2, 0x405c, {0xa8, 0x99, 0x9f, 0xbc, 0xe2, 0xdd, 0x9b, 0x8a}}

#endif // __SpreadUIID__





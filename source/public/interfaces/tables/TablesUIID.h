//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/TablesUIID.h $
//  
//  Owner: Danielle Bessette
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
//  Purpose: Contains IDs for the TablesUI plug-in.
//  
//========================================================================================

#ifndef __TablesUIID__
#define __TablesUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

// These two prefixes extend from 0x105 through 0x106
#define kTablesUIPrefix		 RezLong(0x10500)			
#define kTablesUIPrefix2	 RezLong(0x10600)			
#define kTablesUIPrefix3	 RezLong(0x1fe00)			

// This is a temp fix until this attribute name is fixed
// #define kCellRightInsetAttrBoss			kCellRigthtInsetAttrBoss

//---------------------------------------------------------------
//	Plugin IDs
//---------------------------------------------------------------
#define kTablesUIPluginName						"TablesUI"
DECLARE_PMID(kPlugInIDSpace, kTablesUIPluginID, kTablesUIPrefix + 1)

//---------------------------------------------------------------
//  Interface IDs
//---------------------------------------------------------------
// Moved IID_ISTROKESELECTATTRIBUTES to widgetBin
DECLARE_PMID(kInterfaceIDSpace, IID_IRULESDATA, kTablesUIPrefix + 2)
// Moved IID_ISTORKEWIDGET_OBSERVER to widgetBin
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKE_UTILITIES, kTablesUIPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKEATTR_ACCESSOR, kTablesUIPrefix + 5)
//DECLARE_PMID(kInterfaceIDSpace, IID_ITABLESLINESTYLEDDCONTROL, kTablesUIPrefix + 6)
//DECLARE_PMID(kInterfaceIDSpace, IID_ITABLESLINECOLORDDCONTROL, kTablesUIPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLECURSORPROVIDER, kTablesUIPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_TABLERESIZESPRITEDATA, kTablesUIPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_TABLESGRAPHICSPANLSUITE, kTablesUIPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLEPANELWIDGETOBSERVER, kTablesUIPrefix + 11)

// All used by TablesUIChangeTableDimCmd
DECLARE_PMID(kInterfaceIDSpace, IID_IROWINTDATA, kTablesUIPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLINTDATA, kTablesUIPrefix + 13)
// REMOVED IID_IROWSTARTVALUEINTDATA -- 14
// REMOVED IID_ICOLSTARTVALUEINTDATA -- 15
DECLARE_PMID(kInterfaceIDSpace, IID_ISHADERULEPANELAPPYATTRDATA, kTablesUIPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IABORTTRACKINGDATA, kTablesUIPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLYTABLEBORDERCMDDATA, kTablesUIPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLESTROKEFILLPANEL, kTablesUIPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IRULINGPANELAPPYATTRDATA, kTablesUIPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLESUIRESIZECELLCMDDATA, kTablesUIPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIALOGWASINITIALIZED, kTablesUIPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_ICELLSELECTTRACKERINITDATA, kTablesUIPrefix + 23)

// Control Strip
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLSTRIPTABLESUISUITE, kTablesUIPrefix + 24)

DECLARE_PMID(kInterfaceIDSpace, IID_ISINGLECHARTEXTDATAVALIDATION, kTablesUIPrefix + 25) // custom combobox for TextToFromTableDlg
DECLARE_PMID(kInterfaceIDSpace, IID_REAL_ILASTVALIDTEXTCONTROLDATA, kTablesUIPrefix + 26)

DECLARE_PMID(kInterfaceIDSpace, IID_ITABLEDIMENSIONINFO, kTablesUIPrefix + 27)
// DECLARE_PMID(kInterfaceIDSpace, IID_MYFANCYNEWIMPL, kTablesUIPrefix + 28)
	
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLESUICMDSUITE, kTablesUIPrefix + 29)

// TableTool
DECLARE_PMID(kInterfaceIDSpace, IID_TABLETOOLRESIZESPRITEDATA,	kTablesUIPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_TABLETOOLROWINTDATA,		kTablesUIPrefix + 31) // to diff. btw IIntData's on Col/RowSeg trackers
DECLARE_PMID(kInterfaceIDSpace, IID_TABLETOOLCOLINTDATA,		kTablesUIPrefix + 32) // to diff. btw IIntData's on Col/RowSeg trackers
DECLARE_PMID(kInterfaceIDSpace, IID_TABLETOOLPENCILSPRITEDATA,	kTablesUIPrefix + 33)

// ---- Moved from TableModel plug-in
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLESELECTIONCOMMANDS, 	kTablesUIPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTCELLRANGECMDDATA, 	kTablesUIPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_ICELLSTROKESIDESDATA, 		kTablesUIPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLENAVIGATOR_SUITE, 		kTablesUIPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLESHORCUTSUITE,			kTablesUIPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLESTROKEPANELSUITE, 	kTablesUIPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLESELECTION_SUITE, 		kTablesUIPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLETEXTSELECTION,		kTablesUIPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLEHIGHLIGHTUTILS,		kTablesUIPrefix + 48)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLEHIGHLIGHTER,			kTablesUIPrefix + 49)

// ---- end move.

DECLARE_PMID(kInterfaceIDSpace, IID_IMOVEROWCOLUMNSPRITEDATA, kTablesUIPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLETOOLMGR, kTablesUIPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATETABLEOPTIONSDATA, kTablesUIPrefix + 52)



//---------------------------------------------------------------
//	ClassIDs
//---------------------------------------------------------------

// TablesUI
DECLARE_PMID(kClassIDSpace, kTablesUIDialogBoss, kTablesUIPrefix + 1)
//gap
DECLARE_PMID(kClassIDSpace, kTablesUIMenuActionBoss, kTablesUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kTableRolloverButtonObserverBoss, kTablesUIPrefix + 5)

//gap
// Table Row and Column Dimensions Panel
DECLARE_PMID(kClassIDSpace, kTableRowColDimPanelBoss, kTablesUIPrefix + 7)

// Table Alternating Fill Panel
DECLARE_PMID(kClassIDSpace, kTableAltFillPanelBoss, kTablesUIPrefix + 8)

// Table Alternating Stroke Panel
DECLARE_PMID(kClassIDSpace, kTableAltColStrokePanelBoss, kTablesUIPrefix + 9)

// Table Diagnol Lines Panel
DECLARE_PMID(kClassIDSpace, kTableDiagLinesPanelBoss, kTablesUIPrefix + 10)

// Table (Selection) Stroke Fill Panel 
DECLARE_PMID(kClassIDSpace, kTableStrokeFillPanelBoss, kTablesUIPrefix + 11)

// Insert Table Dialog
DECLARE_PMID(kClassIDSpace, kInsertTableDlgBoss, kTablesUIPrefix + 12)
DECLARE_PMID(kClassIDSpace, kPropertiesButtonWidgetBoss, kTablesUIPrefix + 13)

// SHortcut Boss
DECLARE_PMID(kClassIDSpace, kTablesUIShortcutBoss, kTablesUIPrefix + 14)

// Table Setup
DECLARE_PMID(kClassIDSpace, kTableSetupPanelBoss, kTablesUIPrefix + 15)

// Table Alternating Stroke Panel
DECLARE_PMID(kClassIDSpace, kTableAltRowStrokePanelBoss, kTablesUIPrefix + 16)

// Control Strip
DECLARE_PMID(kClassIDSpace, kControlStripTablesUIRegisterBoss, kTablesUIPrefix + 17)
DECLARE_PMID(kClassIDSpace, kTablesUIControlSetBoss, kTablesUIPrefix + 18)

// Insert Row/Column Dialog
DECLARE_PMID(kClassIDSpace, kInsertRowDlgBoss, kTablesUIPrefix + 19)
DECLARE_PMID(kClassIDSpace, kInsertColDlgBoss, kTablesUIPrefix + 20)

// Gap (2)

// Line Style Drop Downs
DECLARE_PMID(kClassIDSpace, kTablesLineStyleDropDownBoss, kTablesUIPrefix + 23)
//DECLARE_PMID(kClassIDSpace, kTablesLineColorDropDownBoss, kTablesUIPrefix + 24)

// Moved kCellStrokeSelectionBoss to widgetBin

DECLARE_PMID(kClassIDSpace, kCellSelectTrackerBoss, kTablesUIPrefix + 34)
DECLARE_PMID(kClassIDSpace, kColResizeTrackerBoss, kTablesUIPrefix + 36)
DECLARE_PMID(kClassIDSpace, kRowResizeTrackerBoss, kTablesUIPrefix + 37)
DECLARE_PMID(kClassIDSpace, kTableResizeTrackerBoss, kTablesUIPrefix + 38			)
DECLARE_PMID(kClassIDSpace, kVerticalTableResizeTrackerBoss, kTablesUIPrefix + 39)
DECLARE_PMID(kClassIDSpace, kHorizontalTableResizeTrackerBoss, kTablesUIPrefix + 40)
DECLARE_PMID(kClassIDSpace, kRowSelectTrackerBoss, kTablesUIPrefix + 41)
DECLARE_PMID(kClassIDSpace, kColSelectTrackerBoss, kTablesUIPrefix + 42)
DECLARE_PMID(kClassIDSpace, kTablesUIShortcutContextBoss, kTablesUIPrefix + 43)
DECLARE_PMID(kClassIDSpace, kDoNothingTrackerBoss, kTablesUIPrefix + 44)
DECLARE_PMID(kClassIDSpace, kBodyColSelectTrackerBoss, kTablesUIPrefix + 45)
DECLARE_PMID(kClassIDSpace, kTablePanelBoss, kTablesUIPrefix + 46)
DECLARE_PMID(kClassIDSpace, kTableTextAttrPanelBoss, kTablesUIPrefix + 47)
DECLARE_PMID(kClassIDSpace, kCellTrackerHandlerBoss, kTablesUIPrefix + 48)
DECLARE_PMID(kClassIDSpace, kTableGoToRowDlgBoss, kTablesUIPrefix + 49)
// used for AddDependency						kTablesUIPrefix + 50
// used for AddDependency						kTablesUIPrefix + 51
DECLARE_PMID(kClassIDSpace, kNoOpCommandBoss, kTablesUIPrefix + 52)
DECLARE_PMID(kClassIDSpace, kTablesDDTargetSwatchHelperBoss, kTablesUIPrefix + 53)

// Commands
DECLARE_PMID(kClassIDSpace, kTablesUIApplyCellAttrCmdBoss, kTablesUIPrefix + 54)
DECLARE_PMID(kClassIDSpace, kTablesUIApplyRowAttrCmdBoss, kTablesUIPrefix + 55)
DECLARE_PMID(kClassIDSpace, kTablesUIApplyTableAttrCmdBoss, kTablesUIPrefix + 56)
DECLARE_PMID(kClassIDSpace, kTablesUIChangeTableDimCmdBoss, kTablesUIPrefix + 57)
DECLARE_PMID(kClassIDSpace, kTablesUISelectionDialogBoss, kTablesUIPrefix + 58)

DECLARE_PMID(kClassIDSpace, kTablesUISuiteRegisterBoss, kTablesUIPrefix + 60)
DECLARE_PMID(kClassIDSpace, kTableSelectTrackerBoss, kTablesUIPrefix + 61)
DECLARE_PMID(kClassIDSpace, kBodyTableSelectTrackerBoss, kTablesUIPrefix + 62)
DECLARE_PMID(kClassIDSpace, kShadeRulePanelApplyAttrCmdBoss, kTablesUIPrefix + 63)
DECLARE_PMID(kClassIDSpace, kTextCellSelectTrackerBoss, kTablesUIPrefix + 64)
DECLARE_PMID(kClassIDSpace, kTextCellTextSelectTrackerBoss, kTablesUIPrefix + 65)

DECLARE_PMID(kClassIDSpace, kTablesUIApplyCellStrokeCmdBoss, kTablesUIPrefix + 66)
DECLARE_PMID(kClassIDSpace, kApplyTableBorderCmdBoss, kTablesUIPrefix + 67)
DECLARE_PMID(kClassIDSpace, kRulingPanelApplyAttrCmdBoss, kTablesUIPrefix + 68)
DECLARE_PMID(kClassIDSpace, kTablesUIResizeCellCmdBoss, kTablesUIPrefix + 69)
DECLARE_PMID(kClassIDSpace, kTableGraphicAttrPanelBoss, kTablesUIPrefix + 70)
DECLARE_PMID(kClassIDSpace, kTextToTableDlgBoss, kTablesUIPrefix + 71)
DECLARE_PMID(kClassIDSpace, kTableToTextDlgBoss, kTablesUIPrefix + 72)
DECLARE_PMID(kClassIDSpace, kSingleCharTextComboBoxWidgetBoss, kTablesUIPrefix + 73)
DECLARE_PMID(kClassIDSpace, kSelectOnClickEditBoxBoss, kTablesUIPrefix + 74)
DECLARE_PMID(kClassIDSpace, kHideOnDisableIntEditBoxWidgetBoss, kTablesUIPrefix + 75)

// Table Header and Footer Panel
DECLARE_PMID(kClassIDSpace, kTableHeaderFooterPanelBoss, kTablesUIPrefix + 76)

// TableTool
DECLARE_PMID(kClassIDSpace, kTableToolBoss,					kTablesUIPrefix + 77)
DECLARE_PMID(kClassIDSpace, kTableToolTrackerBoss,			kTablesUIPrefix + 78)
DECLARE_PMID(kClassIDSpace, kTableToolTrackerRegisterBoss,	kTablesUIPrefix + 79)
DECLARE_PMID(kClassIDSpace, kTableToolRegisterBoss,			kTablesUIPrefix + 80)
DECLARE_PMID(kClassIDSpace, kColSegmentResizeTrackerBoss,	kTablesUIPrefix + 81)
DECLARE_PMID(kClassIDSpace, kRowSegmentResizeTrackerBoss,	kTablesUIPrefix + 82)
DECLARE_PMID(kClassIDSpace, kPencilTrackerBoss,				kTablesUIPrefix + 83)
DECLARE_PMID(kClassIDSpace, kTableCreationTrackerBoss,		kTablesUIPrefix + 84)
DECLARE_PMID(kClassIDSpace, kTableCreationToolBoss,			kTablesUIPrefix + 85)

// ---- Moved from TableModel plug-in
DECLARE_PMID(kClassIDSpace, kTableSelectionBoss,					kTablesUIPrefix + 90)
DECLARE_PMID(kClassIDSpace, kSelectCellRangeCmdBoss,				kTablesUIPrefix + 91)
DECLARE_PMID(kClassIDSpace, kTableScrapSuiteDefaultPasteHelperBoss,	kTablesUIPrefix + 93)
DECLARE_PMID(kClassIDSpace, kTextScrapSuiteTablePasteHelperBoss,	kTablesUIPrefix + 94)
DECLARE_PMID(kClassIDSpace, kPageItemScrapSuiteTablePasteHelperBoss,kTablesUIPrefix + 95)
// ---- end move.
DECLARE_PMID(kClassIDSpace, kTableStyleDropDownListBoss,                  kTablesUIPrefix + 96)
DECLARE_PMID(kClassIDSpace, kMoveRowsTrackerBoss, kTablesUIPrefix + 97)
DECLARE_PMID(kClassIDSpace, kMoveColumnsTrackerBoss, kTablesUIPrefix + 98)

DECLARE_PMID(kClassIDSpace, kTablesPIShortcutContextBoss, kTablesUIPrefix + 99)


//---------------------------------------------------------------
//	Implementation IDs
//---------------------------------------------------------------

// TablesUI
DECLARE_PMID(kImplementationIDSpace, kTablesUIDialogCreatorImpl, kTablesUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kTablesUIMenuActionImpl, kTablesUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kTablesUIWidgetImpl, kTablesUIPrefix + 3)

// Table Text Attributes Panel
DECLARE_PMID(kImplementationIDSpace, kTableTextAttrPanelCreatorImpl, kTablesUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kTableTextAttrPanelControllerImpl, kTablesUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kTableTextAttrPanelObserverImpl, kTablesUIPrefix + 6)

DECLARE_PMID(kImplementationIDSpace, kTablesUIDialogControllerImpl, kTablesUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kTablesUISelectionDialogControllerImpl, kTablesUIPrefix + 8)

DECLARE_PMID(kImplementationIDSpace, kTableGraphicAttrPanelObserverImpl, kTablesUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kTableGraphicAttrPanelControllerImpl, kTablesUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kTableGraphicAttrPanelCreatorImpl, kTablesUIPrefix + 11)

// Stroke Widget
// Moved kCellStrokeSelectionWidgetImpll to WidgetBin	
// Moved kStrokeSelectAttributesImpll to WidgetBin
// Moved kCellStrokeWidgetObserverImpl to WidgetBin
// Moved kStrokeWidgetPanelSelectionObsImpl to WidgetBin
// Table Row and Column Dimensions Panel
DECLARE_PMID(kImplementationIDSpace, kTableRowColDimPanelCreatorImpl, kTablesUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kTableRowColDimPanelControllerImpl, kTablesUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kTableRowColDimPanelObserverImpl, kTablesUIPrefix + 15)

// Table Alternating Fill Panel
DECLARE_PMID(kImplementationIDSpace, kTableAltFillPanelCreatorImpl, kTablesUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kTableAltFillPanelControllerImpl, kTablesUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kTableAltFillPanelObserverImpl, kTablesUIPrefix + 18)

// Table Alternation Stroke Panel
DECLARE_PMID(kImplementationIDSpace, kTableAltColStrokePanelCreatorImpl, kTablesUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kTableAltStrokePanelControllerImpl, kTablesUIPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kTableAltStrokePanelObserverImpl, kTablesUIPrefix + 21	)

// Shading
DECLARE_PMID(kImplementationIDSpace, kTableDiagLinesPanelCreatorImpl, kTablesUIPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kTableDiagLinesPanelControllerImpl, kTablesUIPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kTableDiagLinesPanelObserverImpl, kTablesUIPrefix + 24)

// Ruling
DECLARE_PMID(kImplementationIDSpace, kTableStrokeFillPanelCreatorImpl, kTablesUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kTableStrokeFillPanelControllerImpl, kTablesUIPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kTableStrokeFillPanelObserverImpl, kTablesUIPrefix + 27)

// Insert Table Properties
DECLARE_PMID(kImplementationIDSpace, kInsertTableDlgCreatorImpl, kTablesUIPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kInsertTableDlgControllerImpl, kTablesUIPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kInsertTableDlgObserverImpl, kTablesUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kPropertiesButtonObserverImpl, kTablesUIPrefix + 31)

// Shortcut
DECLARE_PMID(kImplementationIDSpace, kTablesUIShortcutActionImpl, kTablesUIPrefix + 32)

// Tabel Setup Penl
DECLARE_PMID(kImplementationIDSpace, kTableSetupPanelCreatorImpl, kTablesUIPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kTableSetupPanelControllerImpl, kTablesUIPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kTableSetupPanelObserverImpl, kTablesUIPrefix + 35)

// Control Strip
DECLARE_PMID(kImplementationIDSpace, kControlStripTablesUIRegisterImpl, kTablesUIPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kControlStripTablesUISuiteImpl, kTablesUIPrefix + 37)

// Insert Row/Column 
DECLARE_PMID(kImplementationIDSpace, kInsertRowDlgCreatorImpl, kTablesUIPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kInsertRowDlgControllerImpl, kTablesUIPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kInsertColDlgCreatorImpl, kTablesUIPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kInsertColDlgControllerImpl, kTablesUIPrefix + 41)

// Line Style Drop Down
//DECLARE_PMID(kImplementationIDSpace, kLineStyleDDWidgetViewImpl, kTablesUIPrefix + 45)
//DECLARE_PMID(kImplementationIDSpace, kLineStyleDDWidgetDataValueImpl, kTablesUIPrefix + 46)
//DECLARE_PMID(kImplementationIDSpace, kLineColorDDWidgetViewImpl, kTablesUIPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kStrokeWidgetUtilitiesImpl, kTablesUIPrefix + 48)

DECLARE_PMID(kImplementationIDSpace, kCellStrokeAttributeAccessorImpl, kTablesUIPrefix + 49)

//DECLARE_PMID(kImplementationIDSpace, kLineStyleDDControllerImpl, kTablesUIPrefix + 52)
//DECLARE_PMID(kImplementationIDSpace, kLineColorDDControllerImpl, kTablesUIPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kStrokeFillPanelTargetImpl, kTablesUIPrefix + 54)

// Trackers
//DECLARE_PMID(kImplementationIDSpace, kTableToolTrackerImpl, kTablesUIPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kCellSelectTrackerImpl, kTablesUIPrefix + 56)
//DECLARE_PMID(kImplementationIDSpace, kCreateTableTrackerImpl, kTablesUIPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kColResizeTrackerImpl, kTablesUIPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kRowResizeTrackerImpl, kTablesUIPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kFrameAnchorTrackerImpl, kTablesUIPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kTableResizeTrackerImpl, kTablesUIPrefix + 61)

// available 					kTablesUIPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kCellTextSelectTrackerImpl, kTablesUIPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kTextCellTrackerImpl, kTablesUIPrefix + 64)

DECLARE_PMID(kImplementationIDSpace, kVerticalTableResizeTrackerImpl, kTablesUIPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kHorizontalTableResizeTrackerImpl, kTablesUIPrefix + 66)

DECLARE_PMID(kImplementationIDSpace, kTableResizeSpriteImpl, kTablesUIPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kTableResizeSpriteDataImpl, kTablesUIPrefix + 68)

DECLARE_PMID(kImplementationIDSpace, kRowSelectTrackerImpl, kTablesUIPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kColSelectTrackerImpl, kTablesUIPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kTablesUIShortcutContextImpl, kTablesUIPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kBodyColSelectTrackerImpl, kTablesUIPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kDoNothingTrackerImpl, kTablesUIPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kStrokePanelSelectionObsImpl, kTablesUIPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kTableFrameOwnedItemIBeamDataImpl, kTablesUIPrefix + 75)
// Gap
DECLARE_PMID(kImplementationIDSpace, kTablePanelSelectionObserverImpl, kTablesUIPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kTablePanelWidgetObserverImpl, kTablesUIPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kCellTrackerHandlerImpl, kTablesUIPrefix + 79)

DECLARE_PMID(kImplementationIDSpace, kTableGoToRowDlgControllerImpl, kTablesUIPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kTableGoToRowDlgCreatorImpl, kTablesUIPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kNoOpCommandImpl, kTablesUIPrefix + 82)

//DECLARE_PMID(kImplementationIDSpace, kTablesDDTargetHelperProviderImpl, kTablesUIPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kTablesDDTargetSwatchFlavorHelperImpl, kTablesUIPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kTablesDDTargetImpl, kTablesUIPrefix + 85)

// Commands
DECLARE_PMID(kImplementationIDSpace, kTablesUIApplyCellAttrCmdImpl, kTablesUIPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kTablesUIApplyRowAttrCmdImpl, kTablesUIPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kTablesUIApplyTableAttrCmdImpl, kTablesUIPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kTablesUIChangeTableDimCmdImpl, kTablesUIPrefix + 89)

DECLARE_PMID(kImplementationIDSpace, kTableAltRowStrokePanelCreatorImpl, kTablesUIPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kTablesUISelectionDialogCreatorImpl, kTablesUIPrefix + 91)

DECLARE_PMID(kImplementationIDSpace, kTableSelectTrackerImpl, kTablesUIPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kShadeRulePanelApplyAttrCmdImpl, kTablesUIPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kShadeRulePanelApplyAttrDataImpl, kTablesUIPrefix + 94)

DECLARE_PMID(kImplementationIDSpace, kTextCellSelectTrackerImpl, kTablesUIPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kAbortTrackingDataImpl, kTablesUIPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kTextCellTextSelectTrackerImpl, kTablesUIPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kBodyTableSelectTrackerImpl, kTablesUIPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kCreateTableOptionsDataImpl, kTablesUIPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kTablesUIApplyCellStrokeCmdImpl, kTablesUIPrefix + 100)

DECLARE_PMID(kImplementationIDSpace, kApplyTableBorderCmdImpl, kTablesUIPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kApplyTableBorderCmdDataImpl, kTablesUIPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kTablePanelTipImpl, kTablesUIPrefix + 103)

DECLARE_PMID(kImplementationIDSpace, kRulingPanelApplyAttrCmdImpl, kTablesUIPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kRulingPanelApplyAttrDataImpl, kTablesUIPrefix + 105)
//gap

DECLARE_PMID(kImplementationIDSpace, kTablesUIResizeCellCmdImpl, kTablesUIPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kTablesUIResizeCellCmdDataImpl, kTablesUIPrefix + 108)

DECLARE_PMID(kImplementationIDSpace, kCellSelectTrackerInitDataImpl, kTablesUIPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kTableGoToRowDlgObserverImpl, kTablesUIPrefix + 110)

DECLARE_PMID(kImplementationIDSpace, kTextToTableDlgCreatorImpl, kTablesUIPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kTextToTableDlgControllerImpl, kTablesUIPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kTextToTableDlgObserverImpl, kTablesUIPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kTableToTextDlgCreatorImpl, kTablesUIPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kTableToTextDlgControllerImpl, kTablesUIPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kSingleCharTextValidationImpl, kTablesUIPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kSelectOnClickCBAttributesImpl, kTablesUIPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kSelectOnClickEditBoxEHImpl, kTablesUIPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kRealLastValidCTextControlDataImpl, kTablesUIPrefix + 119)

DECLARE_PMID(kImplementationIDSpace, kTableHeaderFooterPanelCreatorImpl, kTablesUIPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kTableHeaderFooterPanelControllerImpl, kTablesUIPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kTableHeaderFooterPanelObserverImpl, kTablesUIPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kTableDimensionInfoImpl, kTablesUIPrefix + 123)

DECLARE_PMID(kImplementationIDSpace, kTablesUICmdSuiteImpl, kTablesUIPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kTablesUICmdSuiteASBImpl, kTablesUIPrefix + 125)

// TableTool
DECLARE_PMID(kImplementationIDSpace, kTableToolImpl,					kTablesUIPrefix + 126)					// TableTool
DECLARE_PMID(kImplementationIDSpace, kTableToolTrackerImpl,				kTablesUIPrefix + 127)			// Sample Tracker
DECLARE_PMID(kImplementationIDSpace, kTableToolTrackerRegisterImpl,		kTablesUIPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kTableToolCursorProviderImpl,		kTablesUIPrefix + 129)	// CursorProvider
DECLARE_PMID(kImplementationIDSpace, kTableToolResizeSpriteImpl,		kTablesUIPrefix + 130)		// Trackers/Sprites
DECLARE_PMID(kImplementationIDSpace, kTableToolResizeSpriteDataImpl,	kTablesUIPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kColSegmentResizeTrackerImpl,		kTablesUIPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kRowSegmentResizeTrackerImpl,		kTablesUIPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kPencilTrackerImpl,				kTablesUIPrefix + 134)
DECLARE_PMID(kImplementationIDSpace, kTableToolPencilSpriteImpl,		kTablesUIPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kTableToolPencilSpriteDataImpl,	kTablesUIPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kTableCreationTrackerImpl,			kTablesUIPrefix + 137)
DECLARE_PMID(kImplementationIDSpace, kTableToolObserverImpl,			kTablesUIPrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kTableToolMgrImpl,					kTablesUIPrefix + 139)
// ---- Moved from TableModel plug-in
DECLARE_PMID(kImplementationIDSpace, kTableSelectionHighlighterImpl,	kTablesUIPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kTableSelectionCommandsImpl,		kTablesUIPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kSelectCellRangeCmdImpl,			kTablesUIPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kSelectCellRangeCmdDataImpl,		kTablesUIPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kCellStrokeSidesDataImpl, 			kTablesUIPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kTableNavigatorSuiteTableCSBImpl,	kTablesUIPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kTableNavigatorSuiteTableCSBExtImpl,kTablesUIPrefix + 146)
DECLARE_PMID(kImplementationIDSpace, kScrapSuiteTablesCSBImpl,			kTablesUIPrefix + 147)
DECLARE_PMID(kImplementationIDSpace, kToolChangeSuiteTableCSBImpl,		kTablesUIPrefix + 148) 
DECLARE_PMID(kImplementationIDSpace, kContextMenuSuiteTableCSBImpl,		kTablesUIPrefix + 149)
DECLARE_PMID(kImplementationIDSpace, kSelectionDataSuiteTableCSBImpl,	kTablesUIPrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kTableSelectionSnapshotSuiteImpl,	kTablesUIPrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperSuiteTableImpl, 		kTablesUIPrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kTypeToolSuiteTableCSBImpl,		kTablesUIPrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kDummyTableShortcutSuiteImpl,		kTablesUIPrefix + 154)
DECLARE_PMID(kImplementationIDSpace, kTableStrokePanelSuiteImpl,		kTablesUIPrefix + 155)
DECLARE_PMID(kImplementationIDSpace, kTableMiscellanySuiteCSBImpl,		kTablesUIPrefix + 156)
DECLARE_PMID(kImplementationIDSpace, kTableSelectionSuiteImpl,			kTablesUIPrefix + 157)
DECLARE_PMID(kImplementationIDSpace, kTableNavigatorSuiteTextCSBImpl,	kTablesUIPrefix + 158)
DECLARE_PMID(kImplementationIDSpace, kTableNavigatorSuiteTextCSBExtImpl,kTablesUIPrefix + 159)
DECLARE_PMID(kImplementationIDSpace, kCellFocusTextCSBImpl,				kTablesUIPrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kCellFocusTextCSBSelectionExtImpl,	kTablesUIPrefix + 161)
DECLARE_PMID(kImplementationIDSpace, kTableTextSelectionImpl, 			kTablesUIPrefix + 162)
DECLARE_PMID(kImplementationIDSpace, kTableHightlightUtilsImpl,			kTablesUIPrefix + 163)
DECLARE_PMID(kImplementationIDSpace, kTableShortcutIntegratorSuiteImpl,	kTablesUIPrefix + 164)
DECLARE_PMID(kImplementationIDSpace, kTableStrokePanelSuiteASBImpl,		kTablesUIPrefix + 165)
DECLARE_PMID(kImplementationIDSpace, kTableSelectionFactoryImpl,		kTablesUIPrefix + 166)
DECLARE_PMID(kImplementationIDSpace, kTableScrapSuitePasteHelperProviderImpl,	kTablesUIPrefix + 167)
DECLARE_PMID(kImplementationIDSpace, kTableScrapSuiteDefaultPasteHelperImpl,	kTablesUIPrefix + 168)
DECLARE_PMID(kImplementationIDSpace, kTextScrapSuiteTablePasteHelperImpl,		kTablesUIPrefix + 169)
DECLARE_PMID(kImplementationIDSpace, kPageItemScrapSuiteTablePasteHelperImpl,	kTablesUIPrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kTableFrameEventActionImpl,				kTablesUIPrefix + 171)
DECLARE_PMID(kImplementationIDSpace, kConcreteTableSelectionImpl, 		kTablesUIPrefix + 172)
DECLARE_PMID(kImplementationIDSpace, kTableToTextDlgObserverImpl, 		kTablesUIPrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kTablesUIDialogObserverImpl, 		kTablesUIPrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kTableHighlighterImpl, 			kTablesUIPrefix + 175)
DECLARE_PMID(kImplementationIDSpace, kTableHighlighterASBImpl, 			kTablesUIPrefix + 176)
DECLARE_PMID(kImplementationIDSpace, kMoveRowsTrackerImpl, kTablesUIPrefix + 177)
DECLARE_PMID(kImplementationIDSpace, kMoveColumnsTrackerImpl, kTablesUIPrefix + 178)
DECLARE_PMID(kImplementationIDSpace, kMoveRowsSpriteImpl, kTablesUIPrefix + 179)
DECLARE_PMID(kImplementationIDSpace, kMoveColumnsSpriteImpl, kTablesUIPrefix + 180)
DECLARE_PMID(kImplementationIDSpace, kMoveRowColumnSpriteDataImpl, kTablesUIPrefix + 181)

DECLARE_PMID(kImplementationIDSpace, kColorThemeDropperSuiteTableImpl, kTablesUIPrefix + 182)


DECLARE_PMID(kImplementationIDSpace, kTableNavigatorSuiteObjectCSBImpl, kTablesUIPrefix + 183)
DECLARE_PMID(kImplementationIDSpace, kTableNavigatorSuiteObjectCSBExtImpl,kTablesUIPrefix + 184)
DECLARE_PMID(kImplementationIDSpace, kLayoutShortcutContextImpl, kTablesUIPrefix + 185 )
// ---- end move.
DECLARE_PMID(kImplementationIDSpace, kTableNavigatorSuiteGalleyCSBImpl,	kTablesUIPrefix + 186)
DECLARE_PMID(kImplementationIDSpace, kTableNavigatorSuiteGalleyCSBExtImpl,kTablesUIPrefix + 187)
DECLARE_PMID(kImplementationIDSpace, kTablesUIPIShortcutContextImpl, kTablesUIPrefix + 188)

//---------------------------------------------------------------
//	Widget IDs
//---------------------------------------------------------------

// Tables UI
DECLARE_PMID(kWidgetIDSpace, kTablesUIWidgetID, kTablesUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kTablesUIPopupGroupWidgetID, kTablesUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kTablePanelMergeIconWidgetID, kTablesUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kTablePanelUnmergeIconWidgetID, kTablesUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kTSFSpace1WidgetID, kTablesUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kTSFSpace2WidgetID, kTablesUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kTSFSpace3WidgetID, kTablesUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kTSFSpace4WidgetID, kTablesUIPrefix + 8)

// Table Alternating Fill Panel
DECLARE_PMID(kWidgetIDSpace, kRowColSelectGroupWidgetID, kTablesUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kTableAltFillPanelWidgetID, kTablesUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kColumnsRadioButtonWidgetID, kTablesUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kShadingGrpBorderWidgetID, kTablesUIPrefix + 12)

DECLARE_PMID(kWidgetIDSpace, kRowsRadioButtonWidgetID, kTablesUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kShadingSkipWidgetID, kTablesUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kShadingSkipFirstTextWidgetID, kTablesUIPrefix + 15)

DECLARE_PMID(kWidgetIDSpace, kShadingSkipFirstWidgetID, kTablesUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kShadingSkipLastTextWidgetID, kTablesUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kShadingSkipLastWidgetID, kTablesUIPrefix + 18)

DECLARE_PMID(kWidgetIDSpace, kShadingFirstGroupWidgetID, kTablesUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kShadingFirstGroupBorderTextWidgetID, kTablesUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kShadingFirstContainsWidgetTextID, kTablesUIPrefix + 21)

DECLARE_PMID(kWidgetIDSpace, kShadingFirstContainsWidgetID, kTablesUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kShadingFirstWidgetRowTextID, kTablesUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kShadingFirstCellFillGroupWidgetID, kTablesUIPrefix + 24)

DECLARE_PMID(kWidgetIDSpace, kShadingFirstCellFillGroupWidgetTextID, kTablesUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kShadingFirstColorDDTextWidgetID, kTablesUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kShadingFirstColorDDWidgetID, kTablesUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kShadingFirstTintTextWidgetID, kTablesUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kShadingFirstTintWidgetID, kTablesUIPrefix + 29)
//DECLARE_PMID(kWidgetIDSpace, kTDLCenteredButtonsPanelsWidgetID, kTablesUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kShadingFirstOverprintCheckBoxWidgetID, kTablesUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kShadingSecondGroupWidgetID, kTablesUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kShadingSecondGroupBorderTextWidgetID, kTablesUIPrefix + 33)

DECLARE_PMID(kWidgetIDSpace, kShadingSecondContainsWidgetTextID, kTablesUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kShadingSecondContainsWidgetID, kTablesUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kShadingSecondWidgetRowTextID, kTablesUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kShadingSecondCellFillGroupWidgetID, kTablesUIPrefix + 37)

DECLARE_PMID(kWidgetIDSpace, kShadingSecondCellFillGroupWidgetTextID, kTablesUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kShadingSecondColorDDTextWidgetID, kTablesUIPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kShadingSecondColorDDWidgetID, kTablesUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kShadingSecondTintTextWidgetID, kTablesUIPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kShadingSecondTintWidgetID, kTablesUIPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kTDLSpace1WidgetID, kTablesUIPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kShadingSecondOverprintCheckBoxWidgetID, kTablesUIPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kTDLSpace2WidgetID, kTablesUIPrefix + 45)

DECLARE_PMID(kWidgetIDSpace, kTDLSpace3WidgetID, kTablesUIPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kTDLSpace4WidgetID, kTablesUIPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kTDLSpace5WidgetID, kTablesUIPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kTDLSpace6WidgetID, kTablesUIPrefix + 49)

// Cell Stroke  Selection
DECLARE_PMID(kWidgetIDSpace, kCellStrokeSelectionWidgetID, kTablesUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kCellStrokeStaticWidgetID, kTablesUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kCellStrokeEditBoxID, kTablesUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kCellStrokeStaticTextID, kTablesUIPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kCellStrokeNudgeWidget, kTablesUIPrefix + 54)
//DECLARE_PMID(kWidgetIDSpace, AVAILABLE, kTablesUIPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kStrokeSelectionWidgetID, kTablesUIPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kSWPanelParentWidgetID, kTablesUIPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kClearSelectionOverridesButtonWidgetID, kTablesUIPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kInsertColsNudgeWidgetID, kTablesUIPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kInsertRowsNudgeWidgetID, kTablesUIPrefix + 60)
// Alternating Row Stroke Panel Properties
DECLARE_PMID(kWidgetIDSpace, kRowStrokeGrpBorderWidgetID, kTablesUIPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kFillPreserveOverridesWidgetID, kTablesUIPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kRowStrokePreserveOverridesWidgetID, kTablesUIPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kShadingSkipFirstStaticRowTextWidgetID, kTablesUIPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kShadingSkipLastStaticRowTextWidgetID, kTablesUIPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSkipFirstStaticTextWidgetID, kTablesUIPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSkipLastStaticTextWidgetID, kTablesUIPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstWeightComboNudgeWidgetID, kTablesUIPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondWeightComboNudgeWidgetID, kTablesUIPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kTableAltRowStrokePanelWidgetID, kTablesUIPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kRulingRowGroupWidgetID, kTablesUIPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kRulingRowShadeByDDWidgetID, kTablesUIPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSkipWidgetID, kTablesUIPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSkipFirstTextWidgetID, kTablesUIPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSkipFirstWidgetID, kTablesUIPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSkipLastTextWidgetID, kTablesUIPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSkipLastWidgetID, kTablesUIPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstGroupWidgetID, kTablesUIPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstGroupBorderTextWidgetID, kTablesUIPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstContainsWidgetTextID, kTablesUIPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstContainsWidgetID, kTablesUIPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstWidgetTextID, kTablesUIPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstCellStrokeGroupWidgetID, kTablesUIPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstCellStrokeGroupWidgetTextID, kTablesUIPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstWeightTextWidgetID, kTablesUIPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstWeightComboWidgetID, kTablesUIPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstLineStyleDDTextWidgetID, kTablesUIPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstLineStyleDDWidgetID, kTablesUIPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstColorDDTextWidgetID, kTablesUIPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstColorDDWidgetID, kTablesUIPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstTintTextWidgetID, kTablesUIPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstTintWidgetID, kTablesUIPrefix + 92)
//DECLARE_PMID(kWidgetIDSpace, AVAILABLE, kTablesUIPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstOverprintCheckBoxWidgetID, kTablesUIPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondGroupWidgetID, kTablesUIPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondGroupBorderTextWidgetID, kTablesUIPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondContainsWidgetTextID, kTablesUIPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondContainsWidgetID, kTablesUIPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondWidgetTextID, kTablesUIPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondCellStrokeGroupWidgetID, kTablesUIPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondCellStrokeGroupWidgetTextID, kTablesUIPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondWeightTextWidgetID, kTablesUIPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondWeightComboWidgetID, kTablesUIPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondLineStyleDDTextWidgetID, kTablesUIPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondLineStyleDDWidgetID, kTablesUIPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondColorDDTextWidgetID, kTablesUIPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondColorDDWidgetID, kTablesUIPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondTintTextWidgetID, kTablesUIPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondTintWidgetID, kTablesUIPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kTSFStrokeSelectionWidgetID, kTablesUIPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondOverprintCheckBoxWidgetID, kTablesUIPrefix + 111)

// Table Stroke Fill
DECLARE_PMID(kWidgetIDSpace, kTableStrokeFillWidgetID, kTablesUIPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeGroupWidgetID, kTablesUIPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeBorderWidgetID, kTablesUIPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeStaticTextID, kTablesUIPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeWeightComboWidgetId, kTablesUIPrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeWeightNudgeWidgetId, kTablesUIPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeSelectionWidgetID, kTablesUIPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeLineDDWidgetID, kTablesUIPrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeTypeTextWidgetID, kTablesUIPrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeColorDDWidgetID, kTablesUIPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeColorDDTextWidgetID, kTablesUIPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeTintTextWidgetID, kTablesUIPrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeTintWidgetID, kTablesUIPrefix + 124)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeSelectionSpace1WidgetID, kTablesUIPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeOverprintCheckBoxWidgetID, kTablesUIPrefix + 126)
DECLARE_PMID(kWidgetIDSpace, kTableFillGroupWidgetID, kTablesUIPrefix + 127)
DECLARE_PMID(kWidgetIDSpace, kTableFillGrpBorderWidgetID, kTablesUIPrefix + 128)
DECLARE_PMID(kWidgetIDSpace, kTableFillColorDDWidgetID, kTablesUIPrefix + 129)
DECLARE_PMID(kWidgetIDSpace, kTableFillStaticWidgetID, kTablesUIPrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kTableFillTintTextWidgetID, kTablesUIPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kTableFillTintWidgetID, kTablesUIPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeSelectionSpace2WidgetID, kTablesUIPrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kTableFillOverprintCheckBoxWidgetID, kTablesUIPrefix + 134)

// Table Text Attributes
DECLARE_PMID(kWidgetIDSpace, kTableTextAttrPanelWidgetID, kTablesUIPrefix + 135)
DECLARE_PMID(kWidgetIDSpace, kCellInsetsGroupWidgetId, kTablesUIPrefix + 136)
DECLARE_PMID(kWidgetIDSpace, kCellInsetsBorderWidgetID, kTablesUIPrefix + 137)
DECLARE_PMID(kWidgetIDSpace, kTablesTopInsetTextWidgetID, kTablesUIPrefix + 138)
DECLARE_PMID(kWidgetIDSpace, kTopInsetEditBoxWidgetID, kTablesUIPrefix + 139)
DECLARE_PMID(kWidgetIDSpace, kTopInsetNudgeWidget, kTablesUIPrefix + 140)
DECLARE_PMID(kWidgetIDSpace, kTablesBottomInsetTextWidgetID, kTablesUIPrefix + 141)
DECLARE_PMID(kWidgetIDSpace, kBottomInsetEditBoxWidgetID, kTablesUIPrefix + 142)
DECLARE_PMID(kWidgetIDSpace, kBottomInsetNudgeWidget, kTablesUIPrefix + 143)
DECLARE_PMID(kWidgetIDSpace, kTablesLeftInsetTextWidgetID, kTablesUIPrefix + 144)
DECLARE_PMID(kWidgetIDSpace, kLeftInsetEditBoxWidgetID, kTablesUIPrefix + 145)
DECLARE_PMID(kWidgetIDSpace, kLeftInsetNudgeWidget, kTablesUIPrefix + 146)
DECLARE_PMID(kWidgetIDSpace, kTablesRightInsetTextWidgetID, kTablesUIPrefix + 147)
DECLARE_PMID(kWidgetIDSpace, kRightInsetEditBoxWidgetID, kTablesUIPrefix + 148)
DECLARE_PMID(kWidgetIDSpace, kRightInsetNudgeWidget, kTablesUIPrefix + 149)
DECLARE_PMID(kWidgetIDSpace, kTablesTextRotationGroupWidgetId, kTablesUIPrefix + 150)
DECLARE_PMID(kWidgetIDSpace, kTablesTextRotationTitleWidgetId, kTablesUIPrefix + 151)
DECLARE_PMID(kWidgetIDSpace, kTablesTextRotationDropdownWidgetId, kTablesUIPrefix + 152)
DECLARE_PMID(kWidgetIDSpace, kTablesTextRotationWidgetID, kTablesUIPrefix + 153)
DECLARE_PMID(kWidgetIDSpace, kTablesVerticalTextGroupWidgetId, kTablesUIPrefix + 154)
DECLARE_PMID(kWidgetIDSpace, kTablesVerticalTextTitleWidgetId, kTablesUIPrefix + 155)
DECLARE_PMID(kWidgetIDSpace, kTablesVerticalTextDropdownWidgetId, kTablesUIPrefix + 156)
DECLARE_PMID(kWidgetIDSpace, kTablesVerticalTextWidgetID, kTablesUIPrefix + 157)
DECLARE_PMID(kWidgetIDSpace, kTablesParagraphSpacingTextWidgetId, kTablesUIPrefix + 158)
DECLARE_PMID(kWidgetIDSpace, kTablesParagraphSpacingWidgetId, kTablesUIPrefix + 159)
DECLARE_PMID(kWidgetIDSpace, kTablesParagraphSpacingNudgeWidget, kTablesUIPrefix + 160)
DECLARE_PMID(kWidgetIDSpace, kTablesFirstBaselineGroupWidgetId, kTablesUIPrefix + 161)
DECLARE_PMID(kWidgetIDSpace, kTablesFirstBaselineTitleTextWidgetID, kTablesUIPrefix + 162)
DECLARE_PMID(kWidgetIDSpace, kTablesOffsetDropdownWidgetID, kTablesUIPrefix + 163)
DECLARE_PMID(kWidgetIDSpace, kTablesOffsetWidgetID, kTablesUIPrefix + 164)
DECLARE_PMID(kWidgetIDSpace, kTablesOffsetEditWidgetID, kTablesUIPrefix + 165)
DECLARE_PMID(kWidgetIDSpace, kTablesMinOffsetWidgetID, kTablesUIPrefix + 166)
DECLARE_PMID(kWidgetIDSpace, kTableCellClippingGroupWidgetId, kTablesUIPrefix + 167)
DECLARE_PMID(kWidgetIDSpace, kTableCellClippingTitleWidgetId, kTablesUIPrefix + 168)
DECLARE_PMID(kWidgetIDSpace, kTableCellClippingCheckBoxWidgetID, kTablesUIPrefix + 169)
DECLARE_PMID(kWidgetIDSpace, kTablesTextOrientationDropdownWidgetId, kTablesUIPrefix + 170)
DECLARE_PMID(kWidgetIDSpace, kTablesTextOrientationTextWidgetID, kTablesUIPrefix + 171)
DECLARE_PMID(kWidgetIDSpace, kTablesInsetChainWidgetID, kTablesUIPrefix + 172)
DECLARE_PMID(kWidgetIDSpace, kTTAChainControlsWidgetID, kTablesUIPrefix + 173)
DECLARE_PMID(kWidgetIDSpace, kTablesPanelInsetChainWidgetID, kTablesUIPrefix + 174)
//gap

// Insert Table Dialog Widgets
DECLARE_PMID(kWidgetIDSpace, kInsertDlgWidgetID, kTablesUIPrefix + 180)
DECLARE_PMID(kWidgetIDSpace, kInsertRowsEditBoxWidgetID, kTablesUIPrefix + 181)
DECLARE_PMID(kWidgetIDSpace, kInsertColsEditBoxWidgetID, kTablesUIPrefix + 182)
DECLARE_PMID(kWidgetIDSpace, kInsertStrokeEditBoxWidgetID, kTablesUIPrefix + 183)
DECLARE_PMID(kWidgetIDSpace, kRowsStaticTextWidgetID, kTablesUIPrefix + 184)
DECLARE_PMID(kWidgetIDSpace, kColsStaticTextWidgetID, kTablesUIPrefix + 185)
DECLARE_PMID(kWidgetIDSpace, kStrokeStaticTextWidgetID, kTablesUIPrefix + 186)
DECLARE_PMID(kWidgetIDSpace, kStrokeNudgeWidget, kTablesUIPrefix + 187)
DECLARE_PMID(kWidgetIDSpace, kPropertiesButtonWidgetID, kTablesUIPrefix + 188)
DECLARE_PMID(kWidgetIDSpace, kTableDimGroupWidgetID, kTablesUIPrefix + 189)
DECLARE_PMID(kWidgetIDSpace, kTableDimBorderWidgetID, kTablesUIPrefix + 190)
DECLARE_PMID(kWidgetIDSpace, kITRowHeigthStaticWidgetID, kTablesUIPrefix + 191)
DECLARE_PMID(kWidgetIDSpace, kITRowHeightEditBoxWidgetID, kTablesUIPrefix + 192)
DECLARE_PMID(kWidgetIDSpace, kITColumnWidthStaticWidgetID, kTablesUIPrefix + 193)
DECLARE_PMID(kWidgetIDSpace, kITColumnWidthEditBoxWidgetID, kTablesUIPrefix + 194)
DECLARE_PMID(kWidgetIDSpace, kVAlignGroupWidgetID, kTablesUIPrefix + 195			)
DECLARE_PMID(kWidgetIDSpace, kVAlignBorderWidgetID, kTablesUIPrefix + 196		)
DECLARE_PMID(kWidgetIDSpace, kITCellInsetGroupWidgetID, kTablesUIPrefix + 197		)
DECLARE_PMID(kWidgetIDSpace, kITCellInsetBorderWidgetID, kTablesUIPrefix + 198	)
DECLARE_PMID(kWidgetIDSpace, kITCARightEditBoxIconID, kTablesUIPrefix + 199)
DECLARE_PMID(kWidgetIDSpace, kITRightEditBoxWidgetID, kTablesUIPrefix + 200)
DECLARE_PMID(kWidgetIDSpace, kITCARightNudgeWidgetID, kTablesUIPrefix + 201)
DECLARE_PMID(kWidgetIDSpace, kITCALeftEditBoxIconID, kTablesUIPrefix + 202)
DECLARE_PMID(kWidgetIDSpace, kITCALeftEditBoxWidgetID, kTablesUIPrefix + 203	)
DECLARE_PMID(kWidgetIDSpace, kITCALeftNudgeWidgetID, kTablesUIPrefix + 204)
DECLARE_PMID(kWidgetIDSpace, kITCATopEditBoxIconID, kTablesUIPrefix + 205)
DECLARE_PMID(kWidgetIDSpace, kITCATopEditBoxWidgetID, kTablesUIPrefix + 206)
DECLARE_PMID(kWidgetIDSpace, kITCATopNudgeWidgetID, kTablesUIPrefix + 207)
DECLARE_PMID(kWidgetIDSpace, kITCABottomEditBoxIconID, kTablesUIPrefix + 208)
DECLARE_PMID(kWidgetIDSpace, kITCABottomEditBoxWidgetID, kTablesUIPrefix + 209)
DECLARE_PMID(kWidgetIDSpace, kITCABottomNudgeWidgetID, kTablesUIPrefix + 210)
DECLARE_PMID(kWidgetIDSpace, kITOSCheckBoxWID, kTablesUIPrefix + 211)
DECLARE_PMID(kWidgetIDSpace, kTSFCellFillControls1WidgetID, kTablesUIPrefix + 212)

DECLARE_PMID(kWidgetIDSpace, kTableGraphicAttrPanelWidgetID, kTablesUIPrefix + 213)

// Gap

// Row Column Dimensions Panel
DECLARE_PMID(kWidgetIDSpace, kRowKeepWithNextCheckBoxWidgetID, kTablesUIPrefix + 215)
DECLARE_PMID(kWidgetIDSpace, kColumnWidthNudgeWidget, kTablesUIPrefix + 216)
DECLARE_PMID(kWidgetIDSpace, kRowKeepsGroupWidgetID, kTablesUIPrefix + 217)
DECLARE_PMID(kWidgetIDSpace, kTableRowColDimPanelWidgetID, kTablesUIPrefix + 218)
DECLARE_PMID(kWidgetIDSpace, kRowGroupWidgetID, kTablesUIPrefix + 219)
DECLARE_PMID(kWidgetIDSpace, kRowGroupBorderWidgetID, kTablesUIPrefix + 220)
DECLARE_PMID(kWidgetIDSpace, kMinRowHeigthStaticWidgetID, kTablesUIPrefix + 221)
DECLARE_PMID(kWidgetIDSpace, kRowHeigthDDWidgetID, kTablesUIPrefix + 222)
DECLARE_PMID(kWidgetIDSpace, kStartOnStaticTextWidgetID, kTablesUIPrefix + 223)
DECLARE_PMID(kWidgetIDSpace, kMaxRowHeightNudgeWidget, kTablesUIPrefix + 224)
DECLARE_PMID(kWidgetIDSpace, kMinRowHeightEditBoxWidgetID, kTablesUIPrefix + 225)
DECLARE_PMID(kWidgetIDSpace, kMinRowHeightNudgeWidget, kTablesUIPrefix + 226 )
DECLARE_PMID(kWidgetIDSpace, kMaxRowHeigthStaticWidgetID, kTablesUIPrefix + 227)
DECLARE_PMID(kWidgetIDSpace, kMaxRowHeightEditBoxWidgetID, kTablesUIPrefix + 228)
DECLARE_PMID(kWidgetIDSpace, kRowKeepsGroupBorderWidgetID, kTablesUIPrefix + 229)
DECLARE_PMID(kWidgetIDSpace, kColumnGroupWidgetID, kTablesUIPrefix + 230)
DECLARE_PMID(kWidgetIDSpace, kColumnGroupBorderWidgetID, kTablesUIPrefix + 231)
DECLARE_PMID(kWidgetIDSpace, kColumnWidthStaticWidgetID, kTablesUIPrefix + 232)
DECLARE_PMID(kWidgetIDSpace, kColumnWidthEditBoxWidgetID, kTablesUIPrefix + 233)
DECLARE_PMID(kWidgetIDSpace, kStartOnNextDDWidgetID, kTablesUIPrefix + 234)

// Diagonal Lines
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesPanelWidgetID, kTablesUIPrefix + 235)
DECLARE_PMID(kWidgetIDSpace, kTDLIconTypeSelectGroupWidgetID, kTablesUIPrefix + 236)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesDrawInFrontWidgetID, kTablesUIPrefix + 237)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeGroupWidgetID, kTablesUIPrefix + 238)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesGroupBorderWidgetID, kTablesUIPrefix + 239)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeStaticTextID, kTablesUIPrefix + 240)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeWeightComboWidgetId, kTablesUIPrefix + 241)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeWeightNudgeWidgetId, kTablesUIPrefix + 242)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeLineDDWidgetID, kTablesUIPrefix + 243)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeTypeTextWidgetID, kTablesUIPrefix + 244)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeColorDDWidgetID, kTablesUIPrefix + 245)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeColorDDTextWidgetID, kTablesUIPrefix + 246)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeTintTextWidgetID, kTablesUIPrefix + 247)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeTintWidgetID, kTablesUIPrefix + 248)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeDrawDDTextWidgetID, kTablesUIPrefix + 249)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeOverprintCheckBoxWidgetID, kTablesUIPrefix + 250)

DECLARE_PMID(kWidgetIDSpace, kTRCRowColumnDimControlsWidgetID, kTablesUIPrefix + 251)
DECLARE_PMID(kWidgetIDSpace, kTRCRowHeightControlsWidgetID, kTablesUIPrefix + 252)
DECLARE_PMID(kWidgetIDSpace, kTDLNoneIconWidgetID, kTablesUIPrefix + 253)
DECLARE_PMID(kWidgetIDSpace, kTDLULeftToLRightIconWidgetID, kTablesUIPrefix + 254)
DECLARE_PMID(kWidgetIDSpace, kTDLLLeftToURightIconWidgetID, kTablesUIPrefix + 255)
/***********************************************************************
   IMPORTANT NOTE:
   This is the end of the line for kTablesUIPrefix1 (0x105).
   From here on, either use a gap above, or use kTablesUIPrefix2 (0x106).
 ***********************************************************************/
DECLARE_PMID(kWidgetIDSpace, kTDLBothIconWidgetID, kTablesUIPrefix2 + 0)

// Row Column Dimensions Panel (cont)

DECLARE_PMID(kWidgetIDSpace, kTableSetupSpaceGroupWidgetID, kTablesUIPrefix2 + 1)
DECLARE_PMID(kWidgetIDSpace, kTableSetupSpaceBorderWidgetID, kTablesUIPrefix2 + 2)
DECLARE_PMID(kWidgetIDSpace, kTableSpaceBeforeStaticTextID, kTablesUIPrefix2 + 3)
DECLARE_PMID(kWidgetIDSpace, kTableSpaceBeforeEditWidgetId, kTablesUIPrefix2 + 4)
DECLARE_PMID(kWidgetIDSpace, kTableSpaceBeforeNudgeWidgetId, kTablesUIPrefix2 + 5)
DECLARE_PMID(kWidgetIDSpace, kTableSpaceAfterStaticTextID, kTablesUIPrefix2 + 6)
DECLARE_PMID(kWidgetIDSpace, kTableSpaceAfterEditWidgetId, kTablesUIPrefix2 + 7)
DECLARE_PMID(kWidgetIDSpace, kTableSpaceAfterNudgeWidgetId, kTablesUIPrefix2 + 8)

DECLARE_PMID(kWidgetIDSpace, kTablesVerticalAlignmentControlSetWidgetID, kTablesUIPrefix2 + 9)

// Insert Row Dialog
DECLARE_PMID(kWidgetIDSpace, kInsertRowDlgWidgetID, kTablesUIPrefix2 + 10)
DECLARE_PMID(kWidgetIDSpace, kInsertRowGroupBorderWidgetID, kTablesUIPrefix2 + 11)
DECLARE_PMID(kWidgetIDSpace, kInsertRowGroupWidgetID, kTablesUIPrefix2 + 12)
DECLARE_PMID(kWidgetIDSpace, kNumRowStaticTextWidgetID, kTablesUIPrefix2 + 13)
DECLARE_PMID(kWidgetIDSpace, kInsertRowNumRowsEditBoxWidgetID, kTablesUIPrefix2 + 14)
DECLARE_PMID(kWidgetIDSpace, kNumRowsNudgeWidget, kTablesUIPrefix2 + 15)
DECLARE_PMID(kWidgetIDSpace, kBeforeRowRBWidgetID, kTablesUIPrefix2 + 16)
DECLARE_PMID(kWidgetIDSpace, kAfterRowRBWidgetID, kTablesUIPrefix2 + 17)
DECLARE_PMID(kWidgetIDSpace, kInsertRowNumEditBoxWidgetID, kTablesUIPrefix2 + 18)
DECLARE_PMID(kWidgetIDSpace, kRowWhereGroupWidgetID, kTablesUIPrefix2 + 19)

// InsertColumn Dialog
DECLARE_PMID(kWidgetIDSpace, kInsertColDlgWidgetID, kTablesUIPrefix2 + 20)
DECLARE_PMID(kWidgetIDSpace, kInsertColGroupBorderWidgetID, kTablesUIPrefix2 + 21)
DECLARE_PMID(kWidgetIDSpace, kInsertColGroupWidgetID, kTablesUIPrefix2 + 22)
DECLARE_PMID(kWidgetIDSpace, kNumColStaticTextWidgetID, kTablesUIPrefix2 + 23)
DECLARE_PMID(kWidgetIDSpace, kInsertColNumRowsEditBoxWidgetID, kTablesUIPrefix2 + 24)
DECLARE_PMID(kWidgetIDSpace, kNumColsNudgeWidget, kTablesUIPrefix2 + 25)
DECLARE_PMID(kWidgetIDSpace, kLeftColRBWidgetID, kTablesUIPrefix2 + 26)
DECLARE_PMID(kWidgetIDSpace, kRightColRBWidgetID, kTablesUIPrefix2 + 27)
DECLARE_PMID(kWidgetIDSpace, kInsertColNumEditBoxWidgetID, kTablesUIPrefix2 + 28)
DECLARE_PMID(kWidgetIDSpace, kColWhereGroupWidgetID, kTablesUIPrefix2 + 29)

// Table Setup Dialog
DECLARE_PMID(kWidgetIDSpace, kTableDimRowStaticTextID, kTablesUIPrefix2 + 30)
DECLARE_PMID(kWidgetIDSpace, kTableDimRowEditWidgetId, kTablesUIPrefix2 + 31)
DECLARE_PMID(kWidgetIDSpace, kTableDimRowNudgeWidgetId, kTablesUIPrefix2 + 32)
DECLARE_PMID(kWidgetIDSpace, kTableColDimStaticTextID, kTablesUIPrefix2 + 33)
DECLARE_PMID(kWidgetIDSpace, kTableDimColEditWidgetId, kTablesUIPrefix2 + 34)
DECLARE_PMID(kWidgetIDSpace, kTableDimColNudgeWidgetId, kTablesUIPrefix2 + 35)
DECLARE_PMID(kWidgetIDSpace, kTableBorderGroupWidgetID, kTablesUIPrefix2 + 36)
DECLARE_PMID(kWidgetIDSpace, kTableBorderBorderWidgetID, kTablesUIPrefix2 + 37)
DECLARE_PMID(kWidgetIDSpace, kTableBorderWeightStaticTextID, kTablesUIPrefix2 + 38)
DECLARE_PMID(kWidgetIDSpace, kTableBorderWeightComboWidgetId, kTablesUIPrefix2 + 39)
DECLARE_PMID(kWidgetIDSpace, kTableBorderWeightNudgeWidgetId, kTablesUIPrefix2 + 40)
DECLARE_PMID(kWidgetIDSpace, kTableBorderLineDDWidgetID, kTablesUIPrefix2 + 41)
DECLARE_PMID(kWidgetIDSpace, kTableBorderTypeTextWidgetID, kTablesUIPrefix2 + 42)
DECLARE_PMID(kWidgetIDSpace, kTableBorderColorDDWidgetID, kTablesUIPrefix2 + 43)
DECLARE_PMID(kWidgetIDSpace, kTableBorderColorDDTextWidgetID, kTablesUIPrefix2 + 44)
DECLARE_PMID(kWidgetIDSpace, kTableBorderTintTextWidgetID, kTablesUIPrefix2 + 45)
DECLARE_PMID(kWidgetIDSpace, kTableBorderTintWidgetID, kTablesUIPrefix2 + 46)
DECLARE_PMID(kWidgetIDSpace, kTRCRowColSizePanel2WidgetID, kTablesUIPrefix2 + 47)
DECLARE_PMID(kWidgetIDSpace, kTableBorderOverprintCheckBoxWidgetID, kTablesUIPrefix2 + 48)
DECLARE_PMID(kWidgetIDSpace, kTableSetupDimGroupWidgetID, kTablesUIPrefix2 + 49)
DECLARE_PMID(kWidgetIDSpace, kTableSetupDimBorderWidgetID, kTablesUIPrefix2 + 50)
DECLARE_PMID(kWidgetIDSpace, kTableSetupWidgetPanelID, kTablesUIPrefix2 + 51)


DECLARE_PMID(kWidgetIDSpace, kTableUISepActionID, kTablesUIPrefix2 + 52)

// Table Panel
DECLARE_PMID(kWidgetIDSpace, kTablePanelWidgetID, kTablesUIPrefix2 + 53)
DECLARE_PMID(kWidgetIDSpace, kTableSubPanel1Id, kTablesUIPrefix2 + 54)
DECLARE_PMID(kWidgetIDSpace, kTablePanelRowNumIconWidgetID, kTablesUIPrefix2 + 55)
DECLARE_PMID(kWidgetIDSpace, kTablePanelRowNumWidgetID, kTablesUIPrefix2 + 56)
DECLARE_PMID(kWidgetIDSpace, kTablePanelRowNumNugdeWidgetID, kTablesUIPrefix2 + 57)
DECLARE_PMID(kWidgetIDSpace, kTablePanelColNumIconWidgetID, kTablesUIPrefix2 + 58)
DECLARE_PMID(kWidgetIDSpace, kTablePanelColNumWidgetID, kTablesUIPrefix2 + 59)
DECLARE_PMID(kWidgetIDSpace, kTablePanelColNumNudgeWidgetID, kTablesUIPrefix2 + 60)
DECLARE_PMID(kWidgetIDSpace, kTablePanelRowHeightIconWidgetID, kTablesUIPrefix2 + 61)
DECLARE_PMID(kWidgetIDSpace, kTablePanelRowHeigthDDWidgetID, kTablesUIPrefix2 + 62)
DECLARE_PMID(kWidgetIDSpace, kTablePanelRowHeightEditBoxWidgetID, kTablesUIPrefix2 + 63)
DECLARE_PMID(kWidgetIDSpace, kTablePanelRowHeightNudgeWidgetID, kTablesUIPrefix2 + 64)
DECLARE_PMID(kWidgetIDSpace, kTablePanelColWidthIconWidgetID, kTablesUIPrefix2 + 65)
DECLARE_PMID(kWidgetIDSpace, kTablePanelColumnWidthEditBoxWidgetID, kTablesUIPrefix2 + 66)
DECLARE_PMID(kWidgetIDSpace, kTablePanelColWidthNudgeWidgetID, kTablesUIPrefix2 + 67)
DECLARE_PMID(kWidgetIDSpace, kTableSubPanel2Id, kTablesUIPrefix2 + 68)
DECLARE_PMID(kWidgetIDSpace, kTablePanelSeparatorWidgetId, kTablesUIPrefix2 + 69)
DECLARE_PMID(kWidgetIDSpace, kTablePanelTopAlignIconWidgetID, kTablesUIPrefix2 + 70)
DECLARE_PMID(kWidgetIDSpace, kTablePanelCenterAlignIconWidgetID, kTablesUIPrefix2 + 71)
DECLARE_PMID(kWidgetIDSpace, kTablePanelBottomAlignIconWidgetID, kTablesUIPrefix2 + 72)
DECLARE_PMID(kWidgetIDSpace, kTablePanelJustifyAlignIconWidgetID, kTablesUIPrefix2 + 73)
DECLARE_PMID(kWidgetIDSpace, kTablePanel0RotateIconWidgetID, kTablesUIPrefix2 + 74)
DECLARE_PMID(kWidgetIDSpace, kTablePanel90RotateIconWidgetID, kTablesUIPrefix2 + 75)
DECLARE_PMID(kWidgetIDSpace, kTablePanel180RotateAlignIconWidgetID, kTablesUIPrefix2 + 76)
DECLARE_PMID(kWidgetIDSpace, kTablePanel270RotateIconWidgetID, kTablesUIPrefix2 + 77)
DECLARE_PMID(kWidgetIDSpace, kTablePanelTopInsetIconWidgetID, kTablesUIPrefix2 + 78)
DECLARE_PMID(kWidgetIDSpace, kTablePanelTopInsetEditBoxWidgetID, kTablesUIPrefix2 + 79)
DECLARE_PMID(kWidgetIDSpace, kTablePanelTopInsetNudgeWidget, kTablesUIPrefix2 + 80)
DECLARE_PMID(kWidgetIDSpace, kTablePanelLeftInsetIconWidgetID, kTablesUIPrefix2 + 81)
DECLARE_PMID(kWidgetIDSpace, kTablePanelLeftInsetEditBoxWidgetID, kTablesUIPrefix2 + 82)

// Extra Nudge IDs
DECLARE_PMID(kWidgetIDSpace, kAltFillSkipFirstNudgeWidgetId, kTablesUIPrefix2 + 83)
DECLARE_PMID(kWidgetIDSpace, kAltFillSkipLastNudgeWidgetId, kTablesUIPrefix2 + 84)
DECLARE_PMID(kWidgetIDSpace, kShadingFirstContainsNudgeWidgetID, kTablesUIPrefix2 + 85)
DECLARE_PMID(kWidgetIDSpace, kShadingFirstTintNudgeWidgetID, kTablesUIPrefix2 + 86)
DECLARE_PMID(kWidgetIDSpace, kShadingSecondContainsNudgeWidgetID, kTablesUIPrefix2 + 87)
DECLARE_PMID(kWidgetIDSpace, kShadingSecondTintNudgeWidgetID, kTablesUIPrefix2 + 88)
DECLARE_PMID(kWidgetIDSpace, kTableBorderTintNudgeWidgetID, kTablesUIPrefix2 + 89)

DECLARE_PMID(kWidgetIDSpace, kRulingRowSkipFirstNudgeWidgetID, kTablesUIPrefix2 + 90)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSkipLastNudgeWidgetID, kTablesUIPrefix2 + 91)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstContainsNudgeWidgetID, kTablesUIPrefix2 + 92)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstTintNudgeWidgetID, kTablesUIPrefix2 + 93)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondContainsNudgeWidgetID, kTablesUIPrefix2 + 94)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondTintNudgeWidgetID, kTablesUIPrefix2 + 95)

DECLARE_PMID(kWidgetIDSpace, kTableStrokeTintNudgeWidgetID, kTablesUIPrefix2 + 96)
DECLARE_PMID(kWidgetIDSpace, kTableFillTintNudgeWidgetID, kTablesUIPrefix2 + 97)

DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeTintNudgeWidgetID, kTablesUIPrefix2 + 98)
DECLARE_PMID(kWidgetIDSpace, kTablesOffsetEditNudgeWidgetID, kTablesUIPrefix2 + 99)

// Go To Row Dialog
DECLARE_PMID(kWidgetIDSpace, kTableGoToRowDlgWidgetID, kTablesUIPrefix2 + 100)
DECLARE_PMID(kWidgetIDSpace, kRowTypeDropDownWidgetID, kTablesUIPrefix2 + 101)
DECLARE_PMID(kWidgetIDSpace, kRowNumEditBoxWidgetID, kTablesUIPrefix2 + 102)
DECLARE_PMID(kWidgetIDSpace, kRowNumEditBoxNudgeWidgetID, kTablesUIPrefix2 + 103)

// Alternating Column Stroke Panel Properties
DECLARE_PMID(kWidgetIDSpace, kColumnStrokePreserveOverridesWidgetID, kTablesUIPrefix2 + 104)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSkipFirstStaticTextWidgetID, kTablesUIPrefix2 + 105)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSkipLastStaticTextWidgetID, kTablesUIPrefix2 + 106)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstWeightComboNudgeWidgetID, kTablesUIPrefix2 + 107)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondWeightComboNudgeWidgetID, kTablesUIPrefix2 + 108)
DECLARE_PMID(kWidgetIDSpace, kTableAltColumnStrokePanelWidgetID, kTablesUIPrefix2 + 109)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnGroupWidgetID, kTablesUIPrefix2 + 110)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnShadeByDDWidgetID, kTablesUIPrefix2 + 111)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSkipWidgetID, kTablesUIPrefix2 + 112)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSkipFirstTextWidgetID, kTablesUIPrefix2 + 113)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSkipFirstWidgetID, kTablesUIPrefix2 + 114)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSkipLastTextWidgetID, kTablesUIPrefix2 + 115)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSkipLastWidgetID, kTablesUIPrefix2 + 116)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstGroupWidgetID, kTablesUIPrefix2 + 117)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstGroupBorderTextWidgetID, kTablesUIPrefix2 + 118)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstContainsWidgetTextID, kTablesUIPrefix2 + 119)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstContainsWidgetID, kTablesUIPrefix2 + 120)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstWidgetTextID, kTablesUIPrefix2 + 121)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstCellStrokeGroupWidgetID, kTablesUIPrefix2 + 122)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstCellStrokeGroupWidgetTextID, kTablesUIPrefix2 + 123)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstWeightTextWidgetID, kTablesUIPrefix2 + 124)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstWeightComboWidgetID, kTablesUIPrefix2 + 125)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstLineStyleDDTextWidgetID, kTablesUIPrefix2 + 126)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstLineStyleDDWidgetID, kTablesUIPrefix2 + 127)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstColorDDTextWidgetID, kTablesUIPrefix2 + 128)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstColorDDWidgetID, kTablesUIPrefix2 + 129)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstTintTextWidgetID, kTablesUIPrefix2 + 130)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstTintWidgetID, kTablesUIPrefix2 + 131)
DECLARE_PMID(kWidgetIDSpace, kTSFStrokeLabels2WidgetID, kTablesUIPrefix2 + 132)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstOverprintCheckBoxWidgetID, kTablesUIPrefix2 + 133)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondGroupWidgetID, kTablesUIPrefix2 + 134)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondGroupBorderTextWidgetID, kTablesUIPrefix2 + 135)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondContainsWidgetTextID, kTablesUIPrefix2 + 136)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondContainsWidgetID, kTablesUIPrefix2 + 137)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondWidgetTextID, kTablesUIPrefix2 + 138)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondCellStrokeGroupWidgetID, kTablesUIPrefix2 + 139)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondCellStrokeGroupWidgetTextID, kTablesUIPrefix2 + 140)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondWeightTextWidgetID, kTablesUIPrefix2 + 141)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondWeightComboWidgetID, kTablesUIPrefix2 + 142)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondLineStyleDDTextWidgetID, kTablesUIPrefix2 + 143)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondLineStyleDDWidgetID, kTablesUIPrefix2 + 144)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondColorDDTextWidgetID, kTablesUIPrefix2 + 145)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondColorDDWidgetID, kTablesUIPrefix2 + 146)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondTintTextWidgetID, kTablesUIPrefix2 + 147)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondTintWidgetID, kTablesUIPrefix2 + 148)
DECLARE_PMID(kWidgetIDSpace, kTSFStrokeControls2WidgetID, kTablesUIPrefix2 + 149)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondOverprintCheckBoxWidgetID, kTablesUIPrefix2 + 150)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSkipFirstNudgeWidgetID, kTablesUIPrefix2 + 151)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSkipLastNudgeWidgetID, kTablesUIPrefix2 + 152)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstContainsNudgeWidgetID, kTablesUIPrefix2 + 153)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstTintNudgeWidgetID, kTablesUIPrefix2 + 154)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondContainsNudgeWidgetID, kTablesUIPrefix2 + 155)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondTintNudgeWidgetID, kTablesUIPrefix2 + 156)

DECLARE_PMID(kWidgetIDSpace, kTablesUISelectWidgetID, kTablesUIPrefix2 + 157)

// More Table panel
DECLARE_PMID(kWidgetIDSpace, kTablePanelLeftInsetNudgeWidget, kTablesUIPrefix2 + 158)
DECLARE_PMID(kWidgetIDSpace, kTablePanelBottomInsetIconWidgetID, kTablesUIPrefix2 + 159)
DECLARE_PMID(kWidgetIDSpace, kTablePanelBottomInsetEditBoxWidgetID, kTablesUIPrefix2 + 160)
DECLARE_PMID(kWidgetIDSpace, kTablePanelBottomInsetNudgeWidget, kTablesUIPrefix2 + 161)
DECLARE_PMID(kWidgetIDSpace, kTablePanelRightInsetIconWidgetID, kTablesUIPrefix2 + 162)
DECLARE_PMID(kWidgetIDSpace, kTablePanelRightInsetEditBoxWidgetID, kTablesUIPrefix2 + 163)
DECLARE_PMID(kWidgetIDSpace, kTablePanelRightInsetNudgeWidget, kTablesUIPrefix2 + 164)
DECLARE_PMID(kWidgetIDSpace, kRotationSelectGroupWidgetID, kTablesUIPrefix2 + 165)
DECLARE_PMID(kWidgetIDSpace, kVerticalAlignmentSelectGroupWidgetID, kTablesUIPrefix2 + 166)

DECLARE_PMID(kWidgetIDSpace, kRulingRowAlternatingPatternDDWidgetID, kTablesUIPrefix2 + 167)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnAlternatingPatternDDWidgetID, kTablesUIPrefix2 + 168)
DECLARE_PMID(kWidgetIDSpace, kShadingAlternatingPatternDDWidgetID, kTablesUIPrefix2 + 169)
DECLARE_PMID(kWidgetIDSpace, kTableSetupPreserveOverridesWidgetID, kTablesUIPrefix2 + 170)

DECLARE_PMID(kWidgetIDSpace, kColumnStrokeGrpBorderWidgetID, kTablesUIPrefix2 + 171)

DECLARE_PMID(kWidgetIDSpace, kTablePanelTextOrientationDropdownWidgetId, kTablesUIPrefix2 + 172)
DECLARE_PMID(kWidgetIDSpace, kTablePanelTextOrientationTextWidgetID, kTablesUIPrefix2 + 173)

// TextToTable Dialog
DECLARE_PMID(kWidgetIDSpace, kTextToTableDlgWidgetID, kTablesUIPrefix2 + 174)
DECLARE_PMID(kWidgetIDSpace, kTextToTableColStaticTextWidgetID, kTablesUIPrefix2 + 175)
DECLARE_PMID(kWidgetIDSpace, kTextToTableColComboBoxWidgetID, kTablesUIPrefix2 + 176)
DECLARE_PMID(kWidgetIDSpace, kTextToTableRowStaticTextWidgetID, kTablesUIPrefix2 + 177)
DECLARE_PMID(kWidgetIDSpace, kTextToTableRowComboBoxWidgetID, kTablesUIPrefix2 + 178)
DECLARE_PMID(kWidgetIDSpace, kTextToTableNumColStaticTextWidgetID, kTablesUIPrefix2 + 179)
DECLARE_PMID(kWidgetIDSpace, kTextToTableNumColEditBoxNudgeWidgetID, kTablesUIPrefix2 + 180)
DECLARE_PMID(kWidgetIDSpace, kTextToTableNumColEditBoxWidgetID, kTablesUIPrefix2 + 181)

// TableToText Dialog
DECLARE_PMID(kWidgetIDSpace, kTableToTextDlgWidgetID, kTablesUIPrefix2 + 182)
DECLARE_PMID(kWidgetIDSpace, kTableToTextColStaticTextWidgetID, kTablesUIPrefix2 + 183)
DECLARE_PMID(kWidgetIDSpace, kTableToTextColComboBoxWidgetID, kTablesUIPrefix2 + 184)
DECLARE_PMID(kWidgetIDSpace, kTableToTextRowStaticTextWidgetID, kTablesUIPrefix2 + 185)
DECLARE_PMID(kWidgetIDSpace, kTableToTextRowComboBoxWidgetID, kTablesUIPrefix2 + 186)

DECLARE_PMID(kWidgetIDSpace, kTableSelectButtonsPanelWidgetID, kTablesUIPrefix2 + 187)
DECLARE_PMID(kWidgetIDSpace, kTDLButtonPanelsWidgetID, kTablesUIPrefix2 + 188)
DECLARE_PMID(kWidgetIDSpace, kTDLLabelsPanelsWidgetID, kTablesUIPrefix2 + 189)
DECLARE_PMID(kWidgetIDSpace, kTDLControlsPanelsWidgetID, kTablesUIPrefix2 + 190)
DECLARE_PMID(kWidgetIDSpace, kTTATopBottomLabelsWidgetID, kTablesUIPrefix2 + 191)
DECLARE_PMID(kWidgetIDSpace, kTTATopBottomControlsWidgetID, kTablesUIPrefix2 + 192)
DECLARE_PMID(kWidgetIDSpace, kTTATopControlWidgetID, kTablesUIPrefix2 + 193)
DECLARE_PMID(kWidgetIDSpace, kTTABottomControlWidgetID, kTablesUIPrefix2 + 194)
DECLARE_PMID(kWidgetIDSpace, kTTALeftRightLabelsWidgetID, kTablesUIPrefix2 + 195)
DECLARE_PMID(kWidgetIDSpace, kTTALeftControlWidgetID, kTablesUIPrefix2 + 196)
DECLARE_PMID(kWidgetIDSpace, kTTARightControlWidgetID, kTablesUIPrefix2 + 197)
DECLARE_PMID(kWidgetIDSpace, kTTALowestPanelWidgetID, kTablesUIPrefix2 + 198)
DECLARE_PMID(kWidgetIDSpace, kTTALeftRightControlsWidgetID, kTablesUIPrefix2 + 199)
DECLARE_PMID(kWidgetIDSpace, kTRCCol1WidgetID, kTablesUIPrefix2 + 200)
DECLARE_PMID(kWidgetIDSpace, kTRCCol2WidgetID, kTablesUIPrefix2 + 201)
DECLARE_PMID(kWidgetIDSpace, kTRCCol3WidgetID, kTablesUIPrefix2 + 202)
DECLARE_PMID(kWidgetIDSpace, kTRCStartRowPanelWidgetID, kTablesUIPrefix2 + 203)
DECLARE_PMID(kWidgetIDSpace, kTSFCellStrokePanellWidgetID, kTablesUIPrefix2 + 204)
DECLARE_PMID(kWidgetIDSpace, kTSFStrokeControlsWidgetID, kTablesUIPrefix2 + 205)
DECLARE_PMID(kWidgetIDSpace, kTSFStrokeLabelslWidgetID, kTablesUIPrefix2 + 206)
DECLARE_PMID(kWidgetIDSpace, kTSFStrokeWtControlsWidgetID, kTablesUIPrefix2 + 207)
DECLARE_PMID(kWidgetIDSpace, kTDLLabelsPanels2WidgetID, kTablesUIPrefix2 + 208)
DECLARE_PMID(kWidgetIDSpace, kTSFCellFillControlRowWidgetID, kTablesUIPrefix2 + 209)
DECLARE_PMID(kWidgetIDSpace, kTDLControlsPanels2WidgetID, kTablesUIPrefix2 + 210)
DECLARE_PMID(kWidgetIDSpace, kTDLWeightControlWidgetID, kTablesUIPrefix2 + 211)
DECLARE_PMID(kWidgetIDSpace, kTDLTintControlWidgetID, kTablesUIPrefix2 + 212)
DECLARE_PMID(kWidgetIDSpace, kTSFStrokeTintControlsWidgetID, kTablesUIPrefix2 + 213)
DECLARE_PMID(kWidgetIDSpace, kTRCRowColSizePanelWidgetID, kTablesUIPrefix2 + 214)
DECLARE_PMID(kWidgetIDSpace, kDummyRowStaticWidgetID, kTablesUIPrefix2 + 215)
DECLARE_PMID(kWidgetIDSpace, kTRCColWidthControlsWidgetID, kTablesUIPrefix2 + 216)
DECLARE_PMID(kWidgetIDSpace, kTRCMaxRowHeightControlsWidgetID, kTablesUIPrefix2 + 217)
DECLARE_PMID(kWidgetIDSpace, kTRCMinRowHeightControlsWidgetID, kTablesUIPrefix2 + 218)
DECLARE_PMID(kWidgetIDSpace, kTableSelectOnlyButtonsPanelWidgetID, kTablesUIPrefix2 + 219)

DECLARE_PMID(kWidgetIDSpace, kTableHeaderFooterWidgetPanelID, kTablesUIPrefix2 + 220)
DECLARE_PMID(kWidgetIDSpace, kTableHeadersGroupWidgetID, kTablesUIPrefix2 + 221)
DECLARE_PMID(kWidgetIDSpace, kTableHeadersBorderWidgetID, kTablesUIPrefix2 + 222)
DECLARE_PMID(kWidgetIDSpace, kTableHeadersShowinTextID, kTablesUIPrefix2 + 223)
DECLARE_PMID(kWidgetIDSpace, kTableHeadersShowinDDWidgetID, kTablesUIPrefix2 + 224)
DECLARE_PMID(kWidgetIDSpace, kTableHeadersSkipWidgetID, kTablesUIPrefix2 + 225)
DECLARE_PMID(kWidgetIDSpace, kTableFootersBorderGroupWidgetID, kTablesUIPrefix2 + 226)
DECLARE_PMID(kWidgetIDSpace, kTableFootersBorderWidgetID, kTablesUIPrefix2 + 227)
DECLARE_PMID(kWidgetIDSpace, kTableFootersShowinTextID, kTablesUIPrefix2 + 228)
DECLARE_PMID(kWidgetIDSpace, kTableFootersShowinDDWidgetID, kTablesUIPrefix2 + 229)
DECLARE_PMID(kWidgetIDSpace, kTableFootersSkipWidgetID, kTablesUIPrefix2 + 230)

// Kit Stuff
DECLARE_PMID(kWidgetIDSpace, kTableFloaterViewWidgetId, kTablesUIPrefix2 + 231)
DECLARE_PMID(kWidgetIDSpace, kTablePanelCellsCtrlSetWidgetID, kTablesUIPrefix2 + 232)
DECLARE_PMID(kWidgetIDSpace, kTablePanelAlignmentCtrlSetWidgetID, kTablesUIPrefix2 + 233)

DECLARE_PMID(kWidgetIDSpace, kHeadersRowsStaticTextWidgetID, kTablesUIPrefix2 + 234)
DECLARE_PMID(kWidgetIDSpace, kInsertHeaderRowsEditBoxWidgetID, kTablesUIPrefix2 + 235)
DECLARE_PMID(kWidgetIDSpace, kInsertHeaderRowsNudgeWidgetID, kTablesUIPrefix2 + 236)
DECLARE_PMID(kWidgetIDSpace, kFooterRowsStaticTextWidgetID, kTablesUIPrefix2 + 237)
DECLARE_PMID(kWidgetIDSpace, kInsertFooterRowsEditBoxWidgetID, kTablesUIPrefix2 + 238)
DECLARE_PMID(kWidgetIDSpace, kInsertFooterRowsNudgeWidgetID, kTablesUIPrefix2 + 239)

DECLARE_PMID(kWidgetIDSpace, kTableDimHeaderRowStaticTextID, kTablesUIPrefix2 + 240)
DECLARE_PMID(kWidgetIDSpace, kTableDimHeaderRowEditWidgetId, kTablesUIPrefix2 + 241)
DECLARE_PMID(kWidgetIDSpace, kTableDimHeaderRowNudgeWidgetId, kTablesUIPrefix2 + 242)
DECLARE_PMID(kWidgetIDSpace, kTableFooterRowDimStaticTextID, kTablesUIPrefix2 + 243)
DECLARE_PMID(kWidgetIDSpace, kTableDimFooterRowEditWidgetId, kTablesUIPrefix2 + 244)
DECLARE_PMID(kWidgetIDSpace, kTableDimFooterRowNudgeWidgetId, kTablesUIPrefix2 + 245)

DECLARE_PMID(kWidgetIDSpace, kTableStrokeOrderGroupWidgetID, kTablesUIPrefix2 + 246)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeOrderBorderWidgetID, kTablesUIPrefix2 + 247)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeOrderDDWidgetID, kTablesUIPrefix2 + 248)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeOrderDDTextWidgetID, kTablesUIPrefix2 + 249)

DECLARE_PMID(kWidgetIDSpace, kTableBorderGapColorDDWidgetID,				kTablesUIPrefix2 + 250)
DECLARE_PMID(kWidgetIDSpace, kTableBorderGapColorDDTextWidgetID,			kTablesUIPrefix2 + 251)
DECLARE_PMID(kWidgetIDSpace, kTableBorderGapTintTextWidgetID,				kTablesUIPrefix2 + 252)
DECLARE_PMID(kWidgetIDSpace, kTableBorderGapTintWidgetID,					kTablesUIPrefix2 + 253)
DECLARE_PMID(kWidgetIDSpace, kTableBorderGapTintNudgeWidgetID,				kTablesUIPrefix2 + 254)
DECLARE_PMID(kWidgetIDSpace, kTableBorderGapOverprintCheckBoxWidgetID,		kTablesUIPrefix2 + 255)
/***********************************************************************
   IMPORTANT NOTE:
   This is the end of the line for kTablesUIPrefix2 (0x106).
   From here on, either use a gap above, or use kTablesUIPrefix3 (0x107).
 ***********************************************************************/
DECLARE_PMID(kWidgetIDSpace, kTableStrokeGapColorDDWidgetID,					kTablesUIPrefix3 + 0)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeGapColorDDTextWidgetID,				kTablesUIPrefix3 + 1)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeGapTintTextWidgetID,					kTablesUIPrefix3 + 2)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeGapTintWidgetID,						kTablesUIPrefix3 + 3)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeGapTintNudgeWidgetID,					kTablesUIPrefix3 + 4)
DECLARE_PMID(kWidgetIDSpace, kTableStrokeGapOverprintCheckBoxWidgetID,			kTablesUIPrefix3 + 5)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeGapColorDDWidgetID,			kTablesUIPrefix3 + 6)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeGapColorDDTextWidgetID,		kTablesUIPrefix3 + 7)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeGapTintTextWidgetID,			kTablesUIPrefix3 + 8)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeGapTintWidgetID,				kTablesUIPrefix3 + 9)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeGapTintNudgeWidgetID,			kTablesUIPrefix3 + 10)
DECLARE_PMID(kWidgetIDSpace, kTableDiagLinesStrokeGapOverprintCheckBoxWidgetID,	kTablesUIPrefix3 + 11)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstGapColorDDTextWidgetID,				kTablesUIPrefix3 + 12)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstGapColorDDWidgetID,					kTablesUIPrefix3 + 13)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstGapTintTextWidgetID,				kTablesUIPrefix3 + 14)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstGapTintWidgetID,					kTablesUIPrefix3 + 15)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstGapTintNudgeWidgetID,				kTablesUIPrefix3 + 16)
DECLARE_PMID(kWidgetIDSpace, kRulingRowFirstGapOverprintCheckBoxWidgetID,		kTablesUIPrefix3 + 17)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondGapColorDDTextWidgetID,			kTablesUIPrefix3 + 18)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondGapColorDDWidgetID,				kTablesUIPrefix3 + 19)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondGapTintTextWidgetID,				kTablesUIPrefix3 + 20)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondGapTintWidgetID,					kTablesUIPrefix3 + 21)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondGapTintNudgeWidgetID,				kTablesUIPrefix3 + 22)
DECLARE_PMID(kWidgetIDSpace, kRulingRowSecondGapOverprintCheckBoxWidgetID,		kTablesUIPrefix3 + 23)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstGapColorDDTextWidgetID,			kTablesUIPrefix3 + 24)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstGapColorDDWidgetID,				kTablesUIPrefix3 + 25)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstGapTintTextWidgetID,				kTablesUIPrefix3 + 26)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstGapTintWidgetID,					kTablesUIPrefix3 + 27)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstGapTintNudgeWidgetID,			kTablesUIPrefix3 + 28)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnFirstGapOverprintCheckBoxWidgetID,	kTablesUIPrefix3 + 29)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondGapColorDDTextWidgetID,			kTablesUIPrefix3 + 30)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondGapColorDDWidgetID,				kTablesUIPrefix3 + 40)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondGapTintTextWidgetID,			kTablesUIPrefix3 + 41)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondGapTintWidgetID,				kTablesUIPrefix3 + 42)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondGapTintNudgeWidgetID,			kTablesUIPrefix3 + 43)
DECLARE_PMID(kWidgetIDSpace, kRulingColumnSecondGapOverprintCheckBoxWidgetID,	kTablesUIPrefix3 + 44)
DECLARE_PMID(kWidgetIDSpace, kTDLGapTintControlWidgetID,						kTablesUIPrefix3 + 45)
DECLARE_PMID(kWidgetIDSpace, kTSFStrokeGapTintControlsWidgetID,					kTablesUIPrefix3 + 46)

DECLARE_PMID(kWidgetIDSpace, kTableHeadersFootersDimGroupWidgetID,				kTablesUIPrefix3 + 47)
DECLARE_PMID(kWidgetIDSpace, kTableHeadersFootersDimBorderWidgetID,				kTablesUIPrefix3 + 48)
DECLARE_PMID(kWidgetIDSpace, kTableHeadersFootersHDimStaticTextID,				kTablesUIPrefix3 + 49)
DECLARE_PMID(kWidgetIDSpace, kTableHeadersFootersHDimEditWidgetId,				kTablesUIPrefix3 + 50)
DECLARE_PMID(kWidgetIDSpace, kTableHeadersFootersDimHNudgeWidgetId,				kTablesUIPrefix3 + 51)
DECLARE_PMID(kWidgetIDSpace, kTableHeadersFootersFDimStaticTextID,				kTablesUIPrefix3 + 52)
DECLARE_PMID(kWidgetIDSpace, kTableHeadersFootersFDimEditWidgetId,				kTablesUIPrefix3 + 53)
DECLARE_PMID(kWidgetIDSpace, kTableHeadersFootersDimFNudgeWidgetId,				kTablesUIPrefix3 + 54)

// TableTool
DECLARE_PMID(kWidgetIDSpace, kTableToolWidgetId,								kTablesUIPrefix3 + 55)

DECLARE_PMID(kWidgetIDSpace, kTableMergeGroupPanelWidgetId,					kTablesUIPrefix3 + 56)

DECLARE_PMID(kWidgetIDSpace, kTablesRowsColumnsControlSetWidgetID, kTablesUIPrefix3 + 57)
DECLARE_PMID(kWidgetIDSpace, kTablesCellOptionsControlSetWidgetID, kTablesUIPrefix3 + 58)
DECLARE_PMID(kWidgetIDSpace, kTablesInsetsControlSetWidgetID, kTablesUIPrefix3 + 59)

DECLARE_PMID(kWidgetIDSpace, kInsertTableStyleDDListWidgetID, kTablesUIPrefix3 + 60)
DECLARE_PMID(kWidgetIDSpace, kTextToTableStyleDDListWidgetID, kTablesUIPrefix3 + 61)
DECLARE_PMID(kWidgetIDSpace, kTablesMergeUnmergeControlSetWidgetID, kTablesUIPrefix3 + 62)
DECLARE_PMID(kWidgetIDSpace, kTablePanelMergeUnmergeCtrlSetWidgetID, kTablesUIPrefix3 + 63)
DECLARE_PMID(kWidgetIDSpace, kShadingFirstWidgetColumnTextID, kTablesUIPrefix3 + 64)
DECLARE_PMID(kWidgetIDSpace, kShadingSecondWidgetColumnTextID, kTablesUIPrefix3 + 65)
DECLARE_PMID(kWidgetIDSpace, kShadingSkipFirstStaticColumnTextWidgetID, kTablesUIPrefix3 + 66)
DECLARE_PMID(kWidgetIDSpace, kShadingSkipLastStaticColumnTextWidgetID, kTablesUIPrefix3 + 67)
DECLARE_PMID(kWidgetIDSpace, kDummyOverprintCheckBoxWidgetID, kTablesUIPrefix3 + 68)
DECLARE_PMID(kWidgetIDSpace, kDummyOverprintCheckBox2WidgetID, kTablesUIPrefix3 + 69)
//For Properties Panel 
DECLARE_PMID(kWidgetIDSpace, kPropertiesPanelSplitHorizontalWidgetID, kTablesUIPrefix3 + 70)
DECLARE_PMID(kWidgetIDSpace, kPropertiesPanelSplitVerticalWidgetID, kTablesUIPrefix3 + 71)
DECLARE_PMID(kWidgetIDSpace, kTableDimHeaderRowIconWidgetId, kTablesUIPrefix3 + 72)
DECLARE_PMID(kWidgetIDSpace, kTableDimFooterRowIconWidgetId, kTablesUIPrefix3 + 73)



//---------------------------------------------------------------
//	Action IDs
//---------------------------------------------------------------
DECLARE_PMID(kActionIDSpace, kTableAltFillPanelMenuActionID, kTablesUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kTableAltRowStrokePanelMenuActionID, kTablesUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kTableStrokeFillPanelMenuActionID, kTablesUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kTableTextAttrPanelMenuActionID, kTablesUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kTableRowColDimPanelMenuActionID, kTablesUIPrefix + 5)

DECLARE_PMID(kActionIDSpace, kInsertTableMenuActionID, kTablesUIPrefix + 6)

DECLARE_PMID(kActionIDSpace, kInsertRowsActionID, kTablesUIPrefix + 7)
DECLARE_PMID(kActionIDSpace, kInsertColsActionID, kTablesUIPrefix + 8)
DECLARE_PMID(kActionIDSpace, kSelectRowsActionID, kTablesUIPrefix + 9)
DECLARE_PMID(kActionIDSpace, kSelectColsActionID, kTablesUIPrefix + 10)
DECLARE_PMID(kActionIDSpace, kSelectTableActionID, kTablesUIPrefix + 11)
DECLARE_PMID(kActionIDSpace, kDeleteRowsActionID, kTablesUIPrefix + 12)
DECLARE_PMID(kActionIDSpace, kDeleteColsActionID, kTablesUIPrefix + 13)
DECLARE_PMID(kActionIDSpace, kDeleteTableActionID, kTablesUIPrefix + 14)

DECLARE_PMID(kActionIDSpace, kTableDiagLinesPanelMenuActionID, kTablesUIPrefix + 15)
DECLARE_PMID(kActionIDSpace, kConvertTextActionID, kTablesUIPrefix + 16)
DECLARE_PMID(kActionIDSpace, kTableSep1ActionID, kTablesUIPrefix + 17)
DECLARE_PMID(kActionIDSpace, kTableSep2ActionID, kTablesUIPrefix + 18)
DECLARE_PMID(kActionIDSpace, kTableSep3ActionID, kTablesUIPrefix + 19)
DECLARE_PMID(kActionIDSpace, kTableSep4ActionID, kTablesUIPrefix + 20)
DECLARE_PMID(kActionIDSpace, kMergeCellsActionID, kTablesUIPrefix + 21)
DECLARE_PMID(kActionIDSpace, kUnmergeCellsActionID, kTablesUIPrefix + 22)
DECLARE_PMID(kActionIDSpace, kRulingMenuActionID, kTablesUIPrefix + 23)
DECLARE_PMID(kActionIDSpace, kTableSep5ActionID, kTablesUIPrefix + 24)
DECLARE_PMID(kActionIDSpace, kRedistributeRowsActionID, kTablesUIPrefix + 25)
DECLARE_PMID(kActionIDSpace, kRedistributeColsActionID, kTablesUIPrefix + 26)
DECLARE_PMID(kActionIDSpace, kAutoGrowActionID,	 kTablesUIPrefix + 27)

// Shortcuts
DECLARE_PMID(kActionIDSpace, kSelectCellActionID, kTablesUIPrefix + 28)
DECLARE_PMID(kActionIDSpace, kInsertRowAboveActionID, kTablesUIPrefix + 29)
DECLARE_PMID(kActionIDSpace, kInsertColAboveActionID, kTablesUIPrefix + 30)

DECLARE_PMID(kActionIDSpace, kMoveToStartColCellActionID, kTablesUIPrefix + 31)
DECLARE_PMID(kActionIDSpace, kMoveToLastColCellActionID, kTablesUIPrefix + 32)
DECLARE_PMID(kActionIDSpace, kMoveToStartRowCellActionID, kTablesUIPrefix + 33)
DECLARE_PMID(kActionIDSpace, kMoveToLastRowCellActionID, kTablesUIPrefix + 34)
DECLARE_PMID(kActionIDSpace, kMoveToFirstRowInFrameActionID, kTablesUIPrefix + 35)
DECLARE_PMID(kActionIDSpace, kMoveToLastRowInFrameActionID, kTablesUIPrefix + 36)
DECLARE_PMID(kActionIDSpace, kEditHeaderActionID, kTablesUIPrefix + 37)
DECLARE_PMID(kActionIDSpace, kEditFooterActionID, kTablesUIPrefix + 38)
DECLARE_PMID(kActionIDSpace, kTextSelectCellActionID, kTablesUIPrefix + 39)	
DECLARE_PMID(kActionIDSpace, kMoveToNextCellActionID, kTablesUIPrefix + 40)	
DECLARE_PMID(kActionIDSpace, kMoveToPrevCellActionID, kTablesUIPrefix + 41)	

// Arrows Keys in Table
DECLARE_PMID(kActionIDSpace, kTablesMoveDownActionID, kTablesUIPrefix + 42)	
DECLARE_PMID(kActionIDSpace, kTablesMoveUpActionID, kTablesUIPrefix + 43)	
DECLARE_PMID(kActionIDSpace, kTablesMoveLeftActionID, kTablesUIPrefix + 44)	
DECLARE_PMID(kActionIDSpace, kTablesMoveRightActionID, kTablesUIPrefix + 45)	

DECLARE_PMID(kActionIDSpace, kSelectCellBelowActionID, kTablesUIPrefix + 46)
DECLARE_PMID(kActionIDSpace, kSelectCellAboveActionID, kTablesUIPrefix + 47)
DECLARE_PMID(kActionIDSpace, kSelectLeftCellActionID,	kTablesUIPrefix + 48)
DECLARE_PMID(kActionIDSpace, kSelectRightCellActionID, kTablesUIPrefix + 49)
DECLARE_PMID(kActionIDSpace, kTableSep0ActionID, kTablesUIPrefix + 50)
// Gap
DECLARE_PMID(kActionIDSpace, kConvertToTextCellActionID,		kTablesUIPrefix + 52)
DECLARE_PMID(kActionIDSpace, kConvertToImageCellActionID,		kTablesUIPrefix + 53)
DECLARE_PMID(kActionIDSpace, kSplitCellHorizontallyActionID, kTablesUIPrefix + 54)
DECLARE_PMID(kActionIDSpace, kSplitCellVerticallyActionID,	 kTablesUIPrefix + 55)
DECLARE_PMID(kActionIDSpace, kTableKeepRowsActionID, 		kTablesUIPrefix + 56)
DECLARE_PMID(kActionIDSpace, kTableKeepRowColActionID, 		kTablesUIPrefix + 57)
DECLARE_PMID(kActionIDSpace, kTableKeepRowFrameActionID, 	kTablesUIPrefix + 58)
// Gap
DECLARE_PMID(kActionIDSpace, kTableSetupPanelMenuActionID, kTablesUIPrefix + 60)
DECLARE_PMID(kActionIDSpace, kConvertTableToTextActionID, kTablesUIPrefix + 61)

DECLARE_PMID(kActionIDSpace, kTablePanelActionID, kTablesUIPrefix + 62)
DECLARE_PMID(kActionIDSpace, kShowTablePanelOptionsActionID, kTablesUIPrefix + 63)

DECLARE_PMID(kActionIDSpace, kTableRotate0ActionID, kTablesUIPrefix + 64)
DECLARE_PMID(kActionIDSpace, kTableRotate90ActionID, kTablesUIPrefix + 65)
DECLARE_PMID(kActionIDSpace, kTableRotate180ActionID, kTablesUIPrefix + 66)
DECLARE_PMID(kActionIDSpace, kTableRotate270ActionID, kTablesUIPrefix + 67)
DECLARE_PMID(kActionIDSpace, kTablesRotateContextMenuSepActionID, kTablesUIPrefix + 68)

DECLARE_PMID(kActionIDSpace, kTableGoToRowActionID, kTablesUIPrefix + 69)
DECLARE_PMID(kActionIDSpace, kTableAltColumnStrokePanelMenuActionID, kTablesUIPrefix + 70)
DECLARE_PMID(kActionIDSpace, kTablesClearActionID, kTablesUIPrefix + 71)
DECLARE_PMID(kActionIDSpace, kTablesDeleteActionID, kTablesUIPrefix + 72)

DECLARE_PMID(kActionIDSpace, kTablesConvertToHeaderActionID, kTablesUIPrefix + 73)
DECLARE_PMID(kActionIDSpace, kTablesConvertToFooterActionID, kTablesUIPrefix + 74)
DECLARE_PMID(kActionIDSpace, kTablesConvertToBodyActionID, kTablesUIPrefix + 75)
DECLARE_PMID(kActionIDSpace, kTableSep6ActionID, kTablesUIPrefix + 76)

// TABLE_STYLES_PROTO
DECLARE_PMID(kActionIDSpace, kNewTableStyleFromSelectionActionID, kTablesUIPrefix + 77)
DECLARE_PMID(kActionIDSpace, kApplyTableStyleS0ActionID, kTablesUIPrefix + 78)
DECLARE_PMID(kActionIDSpace, kApplyTableStyleS1ActionID, kTablesUIPrefix + 79)
DECLARE_PMID(kActionIDSpace, kApplyTableStyleS2ActionID, kTablesUIPrefix + 80)
DECLARE_PMID(kActionIDSpace, kApplyTableStyleS3ActionID, kTablesUIPrefix + 81)
DECLARE_PMID(kActionIDSpace, kApplyTableStyleS4ActionID, kTablesUIPrefix + 82)
DECLARE_PMID(kActionIDSpace, kTableHeaderFooterPanelMenuActionID, kTablesUIPrefix + 83)

DECLARE_PMID(kActionIDSpace, kSelectBodyRowsActionID, kTablesUIPrefix + 84)
DECLARE_PMID(kActionIDSpace, kSelectHeaderRowsActionID, kTablesUIPrefix + 85)
DECLARE_PMID(kActionIDSpace, kSelectFooterRowsActionID, kTablesUIPrefix + 86)

DECLARE_PMID(kActionIDSpace, kTablesConvertToHeaderNoSubMenuActionID, kTablesUIPrefix + 87)
DECLARE_PMID(kActionIDSpace, kTablesConvertToFooterNoSubMenuActionID, kTablesUIPrefix + 88)
DECLARE_PMID(kActionIDSpace, kTablesConvertToBodyNoSubMenuActionID, kTablesUIPrefix + 89)

DECLARE_PMID(kActionIDSpace, kTablesHorizontalWritingActionID, kTablesUIPrefix + 90)
DECLARE_PMID(kActionIDSpace, kTablesVerticalWritingActionID, kTablesUIPrefix + 91)

// TableTool
DECLARE_PMID(kActionIDSpace, kTablesTableToolActionID,			kTablesUIPrefix + 92)

// Table Cell Stroke context menu
DECLARE_PMID(kActionIDSpace, kTableStrokeSelectBorderActionID, kTablesUIPrefix + 93)
DECLARE_PMID(kActionIDSpace, kTableStrokeSelectInnerActionID, kTablesUIPrefix + 94)
DECLARE_PMID(kActionIDSpace, kTableStrokeSelectAllActionID, kTablesUIPrefix + 95)
DECLARE_PMID(kActionIDSpace, kTableStrokeClearBorderActionID, kTablesUIPrefix + 96)
DECLARE_PMID(kActionIDSpace, kTableStrokeClearInnerActionID, kTablesUIPrefix + 97)
DECLARE_PMID(kActionIDSpace, kTableStrokeClearAllActionID, kTablesUIPrefix + 98)

DECLARE_PMID(kActionIDSpace, kTablesRotateContextMenuSep2ActionID, kTablesUIPrefix + 99)

DECLARE_PMID(kActionIDSpace, kPasteAfterActionID,		kTablesUIPrefix + 100)
DECLARE_PMID(kActionIDSpace, kPasteBeforeActionID,		kTablesUIPrefix + 101)
DECLARE_PMID(kActionIDSpace, kTablesMenuPasteAfterActionID, kTablesUIPrefix + 102)
DECLARE_PMID(kActionIDSpace, kTablesMenuPasteBeforeActionID, kTablesUIPrefix + 103)

DECLARE_PMID(kActionIDSpace, kTablesPIMoveRightActionID, kTablesUIPrefix + 104)
DECLARE_PMID(kActionIDSpace, kTablesPIMoveLeftActionID,	 kTablesUIPrefix + 105)
DECLARE_PMID(kActionIDSpace, kTablesPIMoveUpActionID,	 kTablesUIPrefix + 106)
DECLARE_PMID(kActionIDSpace, kTablesPIMoveDownActionID,	 kTablesUIPrefix + 107)
DECLARE_PMID(kActionIDSpace, kTablesPIEscActionID,		 kTablesUIPrefix + 108)
DECLARE_PMID(kActionIDSpace, kPIMoveToNextCellActionID,	 kTablesUIPrefix + 109)
DECLARE_PMID(kActionIDSpace, kPIMoveToPrevCellActionID,	 kTablesUIPrefix + 110)

DECLARE_PMID(kActionIDSpace, kTableGraphicAttrPanelMenuActionID, kTablesUIPrefix + 111)

DECLARE_PMID(kActionIDSpace, kIncreaseCellWidthActionID, kTablesUIPrefix + 112)
DECLARE_PMID(kActionIDSpace, kDecreaseCellWidthActionID, kTablesUIPrefix + 113)
DECLARE_PMID(kActionIDSpace, kIncreaseCellHeightActionID, kTablesUIPrefix + 114)
DECLARE_PMID(kActionIDSpace, kDecreaseCellHeightActionID, kTablesUIPrefix + 115)

//---------------------------------------------------------------
//	Messages
//---------------------------------------------------------------
DECLARE_PMID(kMessageIDSpace, kStrokeAttrChangedMessage, kTablesUIPrefix + 1)


//---------------------------------------------------------------
//	Service IDS
//---------------------------------------------------------------
DECLARE_PMID(kServiceIDSpace, kTablesDDTargetFlavorHelperService, kTablesUIPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kTablesSelectableDialog1Service, kTablesUIPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kTablesSelectableDialog2Service, kTablesUIPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kTableScrapSuitePasteHelperService, kTablesUIPrefix +4)

#endif // 




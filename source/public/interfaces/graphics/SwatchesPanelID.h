//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/SwatchesPanelID.h $
//  
//  Owner: Michael Burbidge
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

#ifndef __SwatchesPanelID__
#define __SwatchesPanelID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kSwatchesPanelPrefix	 RezLong(0x4000)

// <Start IDC>
// PluginID
#define kSwatchesPanelPluginName			"Swatches Panel"
DECLARE_PMID(kPlugInIDSpace, kSwatchesPanelPluginID, kSwatchesPanelPrefix + 1)

// Resource IDs
#define kSwatchesPanelRsrcID				1000			// Resource ID of Swatches panel
#define kSwatchesPanelGridViewRsrcID		1050			// Resource ID of Swatch grid panel
#define kSwatchesPanelListViewRsrcID		1100			// Resource ID of List view panel
#define kSwatchesOptionsDialogRsrcID		1150			// Resource ID of Swatches option dialog: moved to SwatchesPanelID.h
#define kColorOptionPanelRsrcID				1200			// Resource ID of Color option dialog
#define kColorOptionPanelCreatorRsrcID		1250			// Resource ID of Color option dialog creator

#define kDeleteSwatchDialogRsrcID			1350			// Resource for the delete swatch dialog
#define kNewSwatchesOptionsDialogRsrcID		1360			// Resource ID of New Swatches option dialog.
#define kColorGroupOptionsDialogRsrcID		1370
#define kNewColorGroupDialogRsrcID			1380

#define kSwatchesPanelStringsRsrcID			1400
#define kSwatchesPanelStringsNoTransRsrcID	1450

#define kSwatchesPanelActionResID			1550

#define kSwatchesPanelListRsrcID			1700

#define kSwatchesPanelControlStripRsrcID	1750			// Resource ID of Swatches panel in popup panel view in control strip

#define kSwatchesCreateHLUIGroupRsrcID		1800
#define kSwatchesCreateHLUIWidgetSetRsrcID	1801

#define kSwatchesDeleteHLUIGroupRsrcID		1820
#define kSwatchesDeleteHLUIWidgetSetRsrcID	1821

//	For ink set swatches
#define kNewMixedInkGroupDialogRsrcID			1800		// Resource ID for New ink set dialog
#define kNewInkGroupPickerPanelRsrcID			1810		// Resource ID for defining ink set
#define kNewMixedInkSwatchPanelRsrcID			1820		// Resource ID for defining one ink set swatch
#define kMixedInkGroupInkListElementRsrcID		1850		// Resource ID for ink set panel's ink list element
															// when defining a set.
#define kMixedInkSwatchInkListElementRsrcID		1860		// Resource ID for ink set panel's ink list element
															// when defining one single swatch.
#define kPreviewInkGroupInkListElementRsrcID	1870		// Resource ID for ink set panel's preview list element.
#define	kInkGroupPickerListWidgetCreatorRsrcID	1900
#define	kMixedInkSliderListWidgetCreatorRsrcID	1910
#define	kMixedInkGroupOptionDialogRsrcID		1920
#define	kInkGroupOptionInkListElementRsrcID		1930

#define kSwatchesPanelMenuResID					2000

#define kSwatchesLargeTreeNodeRsrcID			3000
#define kSwatchesSmallTreeNodeRsrcID			3010
#define kAnySwatchSmallTreeNodeRsrcID			3020
#define kAnySwatchLargeTreeNodeRsrcID			3030
#define kColorGroupSmallTreeNodeRsrcID			3040
#define kColorGroupLargeTreeNodeRsrcID			3050
#define kSwatchesTouchTreeNodeRsrcID		3060
#define kColorGroupTouchTreeNodeRsrcID		3070
#define kAnySwatchTouchTreeNodeRsrcID			3080
#define kPropertiesPanelSwatchesLargeTreeNodeRsrcID		3090
#define kPropertiesPanelColorGroupLargeTreeNodeRsrcID		3100

#define kSwatchGridViewTouchWidgetRsrcID		4000
#define kSwatchGridViewTouchRsrcID				4010
#define kSwatchListViewTouchWidgetRsrcID		4020
#define kSwatchListViewTouchRsrcID				4030

#define kPropertiesPanelSwatchesPopupRsrcID			5000
#define kSwatchesPanelMenusWithIconRsrcID			5500
#define kFindThisColorOnBoardingIconResID			5501



// <Class ID>
//---------------------------------------------------------------
// ----- Class IDs -----
//---------------------------------------------------------------
//gap
DECLARE_PMID(kClassIDSpace, kSwatchesFilterMenuButtonBoss, kSwatchesPanelPrefix + 2)
DECLARE_PMID(kClassIDSpace, kDeleteSwatchButtonBoss, kSwatchesPanelPrefix + 3)
DECLARE_PMID(kClassIDSpace, kNewSwatchButtonBoss, kSwatchesPanelPrefix + 4)
DECLARE_PMID(kClassIDSpace, kSwatchViewBoss, kSwatchesPanelPrefix + 5)
DECLARE_PMID(kClassIDSpace, kSwatchesGridBoss, kSwatchesPanelPrefix + 6)
DECLARE_PMID(kClassIDSpace, kSwatchesPanelControlStripIconPopUpBoss, kSwatchesPanelPrefix + 7)
DECLARE_PMID(kClassIDSpace, kSwatchesPanelMenuComponentBoss, kSwatchesPanelPrefix + 8)

DECLARE_PMID(kClassIDSpace, kSwatchesPanelBasicBoss, kSwatchesPanelPrefix + 9)
DECLARE_PMID(kClassIDSpace, kSwatchesPanelBoss, kSwatchesPanelPrefix + 10)

DECLARE_PMID(kClassIDSpace, kRenderListBoxBasicBoss, kSwatchesPanelPrefix + 11)
DECLARE_PMID(kClassIDSpace, kRenderListBoxBoss, kSwatchesPanelPrefix + 12)
DECLARE_PMID(kClassIDSpace, kRenderListViewBoss, kSwatchesPanelPrefix + 13)
DECLARE_PMID(kClassIDSpace, kRenderListViewBasicBoss, kSwatchesPanelPrefix + 14)



DECLARE_PMID(kClassIDSpace, kShowSwatchesButtonBoss, kSwatchesPanelPrefix + 16)

DECLARE_PMID(kClassIDSpace, kSwatchOptionsDialogBoss, kSwatchesPanelPrefix + 17)
DECLARE_PMID(kClassIDSpace, kSwatchOptionsDialogPanelBoss, kSwatchesPanelPrefix + 18)
DECLARE_PMID(kClassIDSpace, kColorOptionMenuActionBoss, kSwatchesPanelPrefix + 19)
DECLARE_PMID(kClassIDSpace, kColorOptionDialogBoss, kSwatchesPanelPrefix + 20)
DECLARE_PMID(kClassIDSpace, kColorPickerPopupWidgetBoss, kSwatchesPanelPrefix + 21)

DECLARE_PMID(kClassIDSpace, kSwatchesGridPanelBoss, kSwatchesPanelPrefix + 22)
DECLARE_PMID(kClassIDSpace, kSwatchesListPanelBoss, kSwatchesPanelPrefix + 23)

DECLARE_PMID(kClassIDSpace, kSwatchesZOrderDEHandlerBoss, kSwatchesPanelPrefix + 24)

DECLARE_PMID(kClassIDSpace, kTintOptionPanelBoss, kSwatchesPanelPrefix + 25)

DECLARE_PMID(kClassIDSpace, kDeleteSwatchDialogBoss, kSwatchesPanelPrefix + 26)
DECLARE_PMID(kClassIDSpace, kSwatchNameEditBoxWidgetBoss, kSwatchesPanelPrefix + 27)
DECLARE_PMID(kClassIDSpace, kSwatchesDEHandlerBoss, kSwatchesPanelPrefix + 28)

DECLARE_PMID(kClassIDSpace, kNameWithColorCheckBoxWidgetBoss, kSwatchesPanelPrefix + 29)

DECLARE_PMID(kClassIDSpace, kSwatchesExportToCCLibrariesButtonBoss, kSwatchesPanelPrefix + 30)
//gap

DECLARE_PMID(kClassIDSpace, kColorGroupOptionsDialogBoss, kSwatchesPanelPrefix + 41)
DECLARE_PMID(kClassIDSpace, kColorGroupNameEditBoxWidgetBoss, kSwatchesPanelPrefix + 42)
DECLARE_PMID(kClassIDSpace, kNewColorGroupDialogBoss, kSwatchesPanelPrefix + 43)

//gap
DECLARE_PMID(kClassIDSpace, kGridPanelBoss, kSwatchesPanelPrefix + 50)
DECLARE_PMID(kClassIDSpace, kGridCellWidgetBoss, kSwatchesPanelPrefix + 51)
DECLARE_PMID(kClassIDSpace, kGridScrollBarWidgetBoss, kSwatchesPanelPrefix + 52)
DECLARE_PMID(kClassIDSpace, kAutoSwatchListTreeWidgetBoss, kSwatchesPanelPrefix + 53)
DECLARE_PMID(kClassIDSpace, kAutoSwatchRenderingObjectBoss, kSwatchesPanelPrefix + 54)
//gap
DECLARE_PMID(kClassIDSpace, kStrokeFillStripWidgetBoss, kSwatchesPanelPrefix + 57)
DECLARE_PMID(kClassIDSpace, kStrokeFillTintWidgetBoss, kSwatchesPanelPrefix + 58)

DECLARE_PMID(kClassIDSpace, kColorOptionDDListWidgetBoss, kSwatchesPanelPrefix + 59)
DECLARE_PMID(kClassIDSpace, kSwatchColorNameStaticTextWidgetBoss, kSwatchesPanelPrefix + 60)


DECLARE_PMID(kClassIDSpace, kNewMixedInkGroupDialogBoss, kSwatchesPanelPrefix + 61)
DECLARE_PMID(kClassIDSpace, kNewInkGroupPickerPanelBoss, kSwatchesPanelPrefix + 62)
DECLARE_PMID(kClassIDSpace, kNewInkGroupTreeViewWidgetBoss, kSwatchesPanelPrefix + 63)
DECLARE_PMID(kClassIDSpace, kNewInkGroupInkListElementBoss, kSwatchesPanelPrefix + 64)

DECLARE_PMID(kClassIDSpace, kPreviewInkGroupInkListBoxWidgetBoss, kSwatchesPanelPrefix + 65)
DECLARE_PMID(kClassIDSpace, kPreviewInkGroupInkListElementBoss, kSwatchesPanelPrefix + 66)
DECLARE_PMID(kClassIDSpace, kPreviewElementInfoStaticTextWidgetBoss, kSwatchesPanelPrefix + 67)

DECLARE_PMID(kClassIDSpace, kInkValuePopupSliderWidgetBoss, kSwatchesPanelPrefix + 68)
DECLARE_PMID(kClassIDSpace, kInkGroupItemEnableWidgetBoss, kSwatchesPanelPrefix + 69)
DECLARE_PMID(kClassIDSpace, kInkGroupItemTintPanelWidgetBoss, kSwatchesPanelPrefix + 70)
DECLARE_PMID(kClassIDSpace, kNewMixedInkSwatchPanelBoss, kSwatchesPanelPrefix + 71)
DECLARE_PMID(kClassIDSpace, kNewMixedInkSwatchTreeViewWidgetBoss, kSwatchesPanelPrefix + 72)
DECLARE_PMID(kClassIDSpace, kNewMixedInkSwatchInkListElementBoss, kSwatchesPanelPrefix + 73)
DECLARE_PMID(kClassIDSpace, kSwatchesDetailControlSetWidgetBoss, kSwatchesPanelPrefix + 74)

// Dock bar stuff
DECLARE_PMID(kClassIDSpace, kSwatchesDDListBoss, kSwatchesPanelPrefix + 75)
DECLARE_PMID(kClassIDSpace, kNewSwatchDBarButtonBoss, kSwatchesPanelPrefix + 76)
DECLARE_PMID(kClassIDSpace, kDeleteSwatchDBarButtonBoss, kSwatchesPanelPrefix + 77)
DECLARE_PMID(kClassIDSpace, kShowSwatchesDBarButtonBoss, kSwatchesPanelPrefix + 78)

//	InkGroup option
DECLARE_PMID(kClassIDSpace, kMixedInkGroupOptionDialogBoss, kSwatchesPanelPrefix + 79)
DECLARE_PMID(kClassIDSpace, kInkGroupOptionTreeViewWidgetBoss, kSwatchesPanelPrefix + 80)
DECLARE_PMID(kClassIDSpace, kInkGroupOptionInkListElementBoss, kSwatchesPanelPrefix + 81)
DECLARE_PMID(kClassIDSpace, kInkListDropDownWidgetBoss, kSwatchesPanelPrefix + 82)
DECLARE_PMID(kClassIDSpace, kRepeatCountPopupSliderWidgetBoss, kSwatchesPanelPrefix + 83)
DECLARE_PMID(kClassIDSpace, kRepeatCountEditBoxWidgetBoss, kSwatchesPanelPrefix + 84)
DECLARE_PMID(kClassIDSpace, kInitialInkValuePopupSliderWidgetBoss, kSwatchesPanelPrefix + 85)
DECLARE_PMID(kClassIDSpace, kInitialInkValuePSEditBoxWidgetBoss, kSwatchesPanelPrefix + 86)

//	Mixed ink color proxy that doesn't have event handling
DECLARE_PMID(kClassIDSpace, kNewMixedInkSwatchColorProxyWidgetBoss, kSwatchesPanelPrefix + 87)

DECLARE_PMID(kClassIDSpace, kAnySwatchWidgetBoss, kSwatchesPanelPrefix + 88)
DECLARE_PMID(kClassIDSpace, kNewSwatchOptionsDialogBoss, kSwatchesPanelPrefix + 89)

//	Swatch List Tree view widget
DECLARE_PMID(kClassIDSpace, kSwatchListTreeWidgetBoss, kSwatchesPanelPrefix + 90)
DECLARE_PMID(kClassIDSpace, kSwatchNodeWidgetBoss, kSwatchesPanelPrefix + 91)
DECLARE_PMID(kClassIDSpace, kSwatchNodeProxyWidgetBoss, kSwatchesPanelPrefix + 92)
DECLARE_PMID(kClassIDSpace, kEditableSwatchNameWidgetBoss, kSwatchesPanelPrefix + 93)
DECLARE_PMID(kClassIDSpace, kSwatchNodeIconPanelWidgetBoss, kSwatchesPanelPrefix + 94)
//gap
DECLARE_PMID(kClassIDSpace, kSwatchStaticNameWidgetBoss, kSwatchesPanelPrefix + 95)
DECLARE_PMID(kClassIDSpace, kSwatchListTreeNoDDWidgetBoss, kSwatchesPanelPrefix + 96)
DECLARE_PMID(kClassIDSpace, kSwatchTreeNoDDNoPanelPrefWidgetBoss, kSwatchesPanelPrefix + 97)
DECLARE_PMID(kClassIDSpace, kEditableSwatchChildEditBoxWidgetBoss, kSwatchesPanelPrefix + 98)
DECLARE_PMID(kClassIDSpace, kColorGroupNodeWidgetBoss, kSwatchesPanelPrefix + 99)
DECLARE_PMID(kClassIDSpace, kNewColorGroupButtonBoss, kSwatchesPanelPrefix + 100)
DECLARE_PMID(kClassIDSpace, kEditableColorGroupNameWidgetBoss, kSwatchesPanelPrefix + 101)
DECLARE_PMID(kClassIDSpace, kColorGroupGridNodeWidgetBoss, kSwatchesPanelPrefix + 102)
DECLARE_PMID(kClassIDSpace, kSwatchTouchGridViewBoss, kSwatchesPanelPrefix + 103)
DECLARE_PMID(kClassIDSpace, kSwatchTouchListViewBoss, kSwatchesPanelPrefix + 104)
DECLARE_PMID(kClassIDSpace, kSortSwatchesCommandBoss, kSwatchesPanelPrefix + 105)
DECLARE_PMID(kClassIDSpace, kPropertiesPanelSwatchesPopupBoss, kSwatchesPanelPrefix + 106)
DECLARE_PMID(kClassIDSpace, kInfoEditableSwatchNameWidgetBoss, kSwatchesPanelPrefix + 107)
DECLARE_PMID(kClassIDSpace, kInfoEditableColorGroupNameWidgetBoss, kSwatchesPanelPrefix + 108)


// <Interface ID>
//---------------------------------------------------------------
// ----- Interface IDs -----
//---------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHESOBSERVER, kSwatchesPanelPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHESPANELPREFS, kSwatchesPanelPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOPUPOBSERVER, kSwatchesPanelPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHESUIDLIST, kSwatchesPanelPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHESDIALOGINTDATA, kSwatchesPanelPrefix + 5)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHESOPTIONCOMMANDHELPER, kSwatchesPanelPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATESWATCHESPANELVIEW, kSwatchesPanelPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHESDIALOGKBSCOPTIONDATA, kSwatchesPanelPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHESPANELDRAGDROPHELPER, kSwatchesPanelPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRIDLISTCONTROLLER, kSwatchesPanelPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IPARENTCOLORSWATCH, kSwatchesPanelPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKETINTCOMBOBOXOBSERVER, kSwatchesPanelPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHESPANELOBSERVER, kSwatchesPanelPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IPANTONEUIDDATA, kSwatchesPanelPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHUIUTILS, kSwatchesPanelPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IINKGROUPPANELOBSERVER, kSwatchesPanelPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWINKGROUPLISTPANEL_ATTACHOBSERVER, kSwatchesPanelPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWINKSETDIALOGDATA, kSwatchesPanelPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHESOPTIONPENDINGCHANGES, kSwatchesPanelPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IPANTONEUIDLISTDATA, kSwatchesPanelPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOCOLORUIDDATA, kSwatchesPanelPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHESTREEVIEWOBSERVER, kSwatchesPanelPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHESTREENODEOBSERVER, kSwatchesPanelPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTATICSWATCHESUIDLISTDATA, kSwatchesPanelPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTEDARTWORKBOOLDATA, kSwatchesPanelPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPENEDCOLORGROUPLISTDATA, kSwatchesPanelPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_ISORTSELECTEDBOOLDATA, kSwatchesPanelPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_ISORTVISUALLYBOOLDATA, kSwatchesPanelPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROPERTIESPANELSWATCHESPREFS, kSwatchesPanelPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOPYSWATCHESPREFS, kSwatchesPanelPrefix + 31)

DECLARE_PMID(kInterfaceIDSpace, IID_ILOCATECOLORTABACTIONIDONBOARDINGICON, kSwatchesPanelPrefix + 32)

// <Implementation ID>
//---------------------------------------------------------------
// ---- Implementation IDs -----
//---------------------------------------------------------------
//gap
DECLARE_PMID(kImplementationIDSpace, kSwatchViewImpl, kSwatchesPanelPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kSwatchesPanelImpl, kSwatchesPanelPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kGridPanelObserverImpl, kSwatchesPanelPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kSwatchUIUtilsImpl, kSwatchesPanelPrefix + 5)

// gap

DECLARE_PMID(kImplementationIDSpace, kRenderListObserverImpl, kSwatchesPanelPrefix + 7	)
DECLARE_PMID(kImplementationIDSpace, kRenderListBoxObserverImpl, kSwatchesPanelPrefix + 8	)
DECLARE_PMID(kImplementationIDSpace, kRenderListViewImpl, kSwatchesPanelPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kShowSwatchesButtonObserverImpl, kSwatchesPanelPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kSPNewButtonObserverImpl, kSwatchesPanelPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kSPDeleteButtonObserverImpl, kSwatchesPanelPrefix + 14)

DECLARE_PMID(kImplementationIDSpace, kSwatchesPanelMenuComponentImpl, kSwatchesPanelPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kSwatchesPanelPrefsObserverImpl, kSwatchesPanelPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kSwatchesPanelPrefsImpl, kSwatchesPanelPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kSwatchesUIDDataImpl, kSwatchesPanelPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kSwatchesGraphicStateObserverImpl, kSwatchesPanelPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kSwatchesObserverImpl, kSwatchesPanelPrefix + 20)
//gap

DECLARE_PMID(kImplementationIDSpace, kSwatchErrorStringServiceImpl, kSwatchesPanelPrefix + 22)

DECLARE_PMID(kImplementationIDSpace, kSwatchOptionsDialogServiceImpl, kSwatchesPanelPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kSwatchesOptionsDialogCreatorImpl, kSwatchesPanelPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kSwatchesOptionsDialogControllerImpl, kSwatchesPanelPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kColorOptionPanelCreatorImpl, kSwatchesPanelPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kColorOptionDialogControllerImpl, kSwatchesPanelPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kColorOptionDlgObserverImpl, kSwatchesPanelPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kTintOptionObserverImpl, kSwatchesPanelPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kSwatchNameEBValidationImpl, kSwatchesPanelPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kNewSwatchesOptionsDialogCreatorImpl, kSwatchesPanelPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kColorGroupNameEBValidationImpl, kSwatchesPanelPrefix + 32)


// gap 30-33
DECLARE_PMID(kImplementationIDSpace, kSPNewButtonDragDropTargetImpl, kSwatchesPanelPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kSPDeleteButtonDragDropTargetImpl, kSwatchesPanelPrefix + 35)

DECLARE_PMID(kImplementationIDSpace, kSwatchesGridPanelImpl, kSwatchesPanelPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kSwatchButtonEHImpl, kSwatchesPanelPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kSwatchesGridPanelEHImpl, kSwatchesPanelPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kGridListControlDataImpl, kSwatchesPanelPrefix + 39)

DECLARE_PMID(kImplementationIDSpace, kSwatchesPanelResizeRuleImpl, kSwatchesPanelPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kSwatchesGridPanelResizeRuleImpl, kSwatchesPanelPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kSwatchesListPanelResizeRuleImpl, kSwatchesPanelPrefix + 42)

DECLARE_PMID(kImplementationIDSpace, kSwatchesZOrderDEHandlerImpl, kSwatchesPanelPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kSwatchesListZOrderDDSourceImpl, kSwatchesPanelPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kSwatchesListZOrderDDTargetImpl, kSwatchesPanelPrefix + 45)

DECLARE_PMID(kImplementationIDSpace, kRenderListItemEHImpl, kSwatchesPanelPrefix + 46)

DECLARE_PMID(kImplementationIDSpace, kSwatchesListPanelImpl, kSwatchesPanelPrefix + 47)

DECLARE_PMID(kImplementationIDSpace, kRenderListViewTipsImpl, kSwatchesPanelPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kSwatchesDEHandlerImpl, kSwatchesPanelPrefix + 49)

DECLARE_PMID(kImplementationIDSpace, kDeleteSwatchDialogImpl, kSwatchesPanelPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kDeleteSwatchDialogObsImpl, kSwatchesPanelPrefix + 51)

//DECLARE_PMID(kImplementationIDSpace, kRenderListItemPanelViewImpl, kSwatchesPanelPrefix + 47)
//DECLARE_PMID(kImplementationIDSpace, kRenderListColorModeViewImpl, kSwatchesPanelPrefix + 48)
//DECLARE_PMID(kImplementationIDSpace, kRenderListColorTypeViewImpl, kSwatchesPanelPrefix + 49)
//DECLARE_PMID(kImplementationIDSpace, kRenderListEditViewImpl, kSwatchesPanelPrefix + 50)

DECLARE_PMID(kImplementationIDSpace, kSwatchesOptionDlgObserverImpl, kSwatchesPanelPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kSwatchesOptionCommandHelperImpl, kSwatchesPanelPrefix + 53)

DECLARE_PMID(kImplementationIDSpace, kGridPanelListObserverImpl, kSwatchesPanelPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kSwatchesListBoxControllerImpl, kSwatchesPanelPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kSwatchesPanelDragDropHelperImpl, kSwatchesPanelPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kSwatchesGridPanelDDSourceImpl, kSwatchesPanelPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kSwatchesGridPanelDDTargetImpl, kSwatchesPanelPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kGridWidgetPanelImpl, kSwatchesPanelPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kGridListControllerImpl, kSwatchesPanelPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kGridScrollBarEHImpl, kSwatchesPanelPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kColorGroupViewTipsImpl, kSwatchesPanelPrefix + 62)

//gap
DECLARE_PMID(kImplementationIDSpace, kAutoSwatchRenderingObjImpl, kSwatchesPanelPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kStrokeFillTintComboObserverImpl, kSwatchesPanelPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kStrokeFillTintGfxStateDefnObserverImpl, kSwatchesPanelPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kStrokeFillTintGfxStateObserverImpl, kSwatchesPanelPrefix + 67)

DECLARE_PMID(kImplementationIDSpace, kColorOptionDialogSwitcherImpl, kSwatchesPanelPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kColorOptionDropDownListEHImpl, kSwatchesPanelPrefix + 69)

DECLARE_PMID(kImplementationIDSpace, kGridListBoxControllerImpl, kSwatchesPanelPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kRenderListBoxEHImpl, kSwatchesPanelPrefix + 71)


DECLARE_PMID(kImplementationIDSpace, kNewInkSetDialogDataImpl, kSwatchesPanelPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kNewInkGroupDialogCreatorImpl, kSwatchesPanelPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kNewInkGroupDialogControllerImpl, kSwatchesPanelPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kNewInkGroupDialogObserverImpl, kSwatchesPanelPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kNewInkGroupPickerPanelCreatorImpl, kSwatchesPanelPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kNewInkGroupPickerDlgControllerImpl, kSwatchesPanelPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kNewInkGroupPickerDlgObserverImpl, kSwatchesPanelPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kNewInkGroupInkListAttachObserverImpl, kSwatchesPanelPrefix + 79)

//	Available

//DECLARE_PMID(kImplementationIDSpace, kPreviewInkGroupButtonObserverImpl, kSwatchesPanelPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kInkValuePopupSliderObserverImpl, kSwatchesPanelPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kNewMixedInkSwatchPanelCreatorImpl, kSwatchesPanelPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kNewMixedInkSwatchDlgControllerImpl, kSwatchesPanelPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kInkGroupInkItemEnableWidgetEHImpl, kSwatchesPanelPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kInkGroupItemTintSliderPanelObserverImpl, kSwatchesPanelPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kNewMixedInkSwatchDlgObserverImpl, kSwatchesPanelPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kNewInkGroupTreeViewWidgetMgrImpl, kSwatchesPanelPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kNewMixedInkSwatchTreeViewWidgetMgrImpl, kSwatchesPanelPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kInkGroupListElementViewImpl, kSwatchesPanelPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kSwatchesPanelDetailControllerImpl, kSwatchesPanelPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kSwatchesDDListSelectionObserverImpl, kSwatchesPanelPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kSwatchesDDListNormalObserverImpl, kSwatchesPanelPrefix + 93)

DECLARE_PMID(kImplementationIDSpace, kInkGroupOptionDialogObserverImpl, kSwatchesPanelPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kInkGroupOptionDialogControllerImpl, kSwatchesPanelPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kInkGroupOptionDialogCreatorImpl, kSwatchesPanelPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kInkGroupOptionTreeViewWidgetMgrImpl, kSwatchesPanelPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kInkListDropDownControlDataImpl, kSwatchesPanelPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kInkListDropDownObserverImpl, kSwatchesPanelPrefix + 99)

DECLARE_PMID(kImplementationIDSpace, kSwatchesListBoxAttributesImpl, kSwatchesPanelPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kInkValuePopupTextValidationImpl, kSwatchesPanelPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kRepeatInkValueIntEditBoxEHImpl, kSwatchesPanelPrefix + 102)

DECLARE_PMID(kImplementationIDSpace, kSwatchesPanelXMLGeneratorImpl, kSwatchesPanelPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kSwatchesPanelSAXHandlerImpl, kSwatchesPanelPrefix + 105)

DECLARE_PMID(kImplementationIDSpace, kSwatchesDDListTipsImpl, kSwatchesPanelPrefix + 106)

DECLARE_PMID(kImplementationIDSpace, kInitialInkValuePSEditBoxEHImpl, kSwatchesPanelPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kInitialInkValuePSAttrImpl, kSwatchesPanelPrefix + 108)

DECLARE_PMID(kImplementationIDSpace, kNoneRenderingObjectDrawerImpl, kSwatchesPanelPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kColorRenderingObjectDrawerImpl, kSwatchesPanelPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kAutoSwatchRenderingObjDrawerImpl, kSwatchesPanelPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kAnySwatchListViewImpl, kSwatchesPanelPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kAnySwatchTipImpl, kSwatchesPanelPrefix + 113)

DECLARE_PMID(kImplementationIDSpace, kSwatchesTreeViewAdapterImpl, kSwatchesPanelPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kSwatchesTreeViewWidgetMgrImpl, kSwatchesPanelPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kSwatchesTreeNodeObserverImpl, kSwatchesPanelPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kSwatchesTreeViewObserverImpl, kSwatchesPanelPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kSwatchesTreeViewDDSourceImpl, kSwatchesPanelPrefix + 119)
DECLARE_PMID(kImplementationIDSpace, kSwatchesTreeViewDDTargetImpl, kSwatchesPanelPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kSwatchListNodeViewImpl, kSwatchesPanelPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kSwatchListNodeEHImpl, kSwatchesPanelPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kSwatchNodeProxyViewImpl, kSwatchesPanelPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kSwatchNodeIconPanelViewImpl, kSwatchesPanelPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kSwatchNodeSwatchNameILEControllerImpl, kSwatchesPanelPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kSwatchNodeSwatchNameILEAttributesImpl, kSwatchesPanelPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kSwatchNodeSwatchNameILEObserverImpl, kSwatchesPanelPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kSwatchNodeProxyWidgetEHImpl, kSwatchesPanelPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kSwatchNodeProxyWidgetDDSourceImpl, kSwatchesPanelPrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kSwatchNodeProxyWidgetDDTargetImpl, kSwatchesPanelPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kSwatchesTreeViewControllerImpl, kSwatchesPanelPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kSwatchesTreeViewEventHandlerImpl, kSwatchesPanelPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kSwatchesTreeViewTypeAheadImpl, kSwatchesPanelPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kEditableSwatchNameChildEditEHImpl, kSwatchesPanelPrefix + 134)

DECLARE_PMID(kImplementationIDSpace, kSPNewColorGroupButtonObserverImpl, kSwatchesPanelPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kColorGroupOptionsDialogControllerImpl, kSwatchesPanelPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kColorGroupOptionsDialogObserverImpl, kSwatchesPanelPrefix + 137)
DECLARE_PMID(kImplementationIDSpace, kNewColorGroupDialogControllerImpl, kSwatchesPanelPrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kSwatchesTreeViewMgrImpl, kSwatchesPanelPrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kSwatchesExportToCCLibrariesButtonTipImpl, kSwatchesPanelPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kSwatchesExportToCCLibrariesButtonObserverImpl, kSwatchesPanelPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kSwatchTouchWidgetServiceImpl, kSwatchesPanelPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kSwatchTouchGridPanelCreatorImpl, kSwatchesPanelPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kSwatchTouchListPanelCreatorImpl, kSwatchesPanelPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kSortSwatchesCmdImpl, kSwatchesPanelPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kPropertiesPanelSwatchesPrefsImpl, kSwatchesPanelPrefix + 146)
DECLARE_PMID(kImplementationIDSpace, kPropertiesPanelSwatchesViewImpl, kSwatchesPanelPrefix + 147)

DECLARE_PMID(kImplementationIDSpace, kLocateColorActionIDOnBoardingIconImpl, kSwatchesPanelPrefix + 148)


// <Message ID>
//---------------------------------------------------------------
// ----- Message IDs -----
//---------------------------------------------------------------
DECLARE_PMID(kMessageIDSpace, kGridPanelListSelectionChangedMessage, kSwatchesPanelPrefix + 1)
DECLARE_PMID(kMessageIDSpace, kGridPanelListSelectionChangedByUserMessage, kSwatchesPanelPrefix + 2)
DECLARE_PMID(kMessageIDSpace, kGridPanelListMasterItemChangedMessage, kSwatchesPanelPrefix + 3)
DECLARE_PMID(kMessageIDSpace, kGridPanelListItemAddedMessage, kSwatchesPanelPrefix + 4)
DECLARE_PMID(kMessageIDSpace, kGridPanelListItemRemovedMessage, kSwatchesPanelPrefix + 5)
DECLARE_PMID(kMessageIDSpace, kGridPanelListSelectionChangedByUserDragMessage, kSwatchesPanelPrefix + 6)

// <Widget ID>
//---------------------------------------------------------------
// ----- Widget IDs -----
//---------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace, kSwatchesPanelWidgetID, kSwatchesPanelPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kSwatchesViewWidgetID, kSwatchesPanelPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kSmallSwatchGridPanelWidgetID, kSwatchesPanelPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kSwatchListPanelWidgetID, kSwatchesPanelPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kRenderListBoxWidgetID, kSwatchesPanelPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kSwatchGridWidgetID, kSwatchesPanelPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kSwatchGridScrollBarWidgetID, kSwatchesPanelPrefix + 7)
// kLargeSwatchGridWidgetID defined below as kSwatchesPanelPrefix + 46

DECLARE_PMID(kWidgetIDSpace, kShowAllButtonWidgetID, kSwatchesPanelPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kShowSolidButtonWidgetID, kSwatchesPanelPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kShowGradientButtonWidgetID, kSwatchesPanelPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kNewSwatchButtonWidgetID, kSwatchesPanelPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kDeleteSwatchButtonWidgetID, kSwatchesPanelPrefix + 12)

DECLARE_PMID(kWidgetIDSpace, kLargeSwatchGridPanelWidgetID, kSwatchesPanelPrefix + 13)

DECLARE_PMID(kWidgetIDSpace, kSPControlStripWidgetID, kSwatchesPanelPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kAutoColorSwatchWidgetID, kSwatchesPanelPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kExportSwatchToCCLibrariesButtonWidgetID, kSwatchesPanelPrefix + 16)
// gap
DECLARE_PMID(kWidgetIDSpace, kSwatchesPanelControlStripIconPopUpWidgetID, kSwatchesPanelPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kSwatchesOptionsDialogWidgetID, kSwatchesPanelPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kSwatchOptionNameStaticWidgetID, kSwatchesPanelPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kSwatchOptionNameWidgetID, kSwatchesPanelPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kSwatchOptionsTitleWidgetID, kSwatchesPanelPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kSwatchOptionsTitleTextWidgetID, kSwatchesPanelPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kColorOptionPanelWidgetID, kSwatchesPanelPrefix + 25)

DECLARE_PMID(kWidgetIDSpace, kColorTypeStaticTextWidgetID, kSwatchesPanelPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kColorTypePopupWidgetID, kSwatchesPanelPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kColorPickerPopupWidgetID, kSwatchesPanelPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kColorPickerTitleGroupWidgetID, kSwatchesPanelPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kDeleteSwatchPopupWidgetID, kSwatchesPanelPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kDeleteSwatchPopupRadioButtonWidgetID, kSwatchesPanelPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kDeleteSwatchUnnamedRadioButtonWidgetID, kSwatchesPanelPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kDeleteSwatchGroupWidgetID, kSwatchesPanelPrefix + 37)

DECLARE_PMID(kWidgetIDSpace, kColorModeStaticTextWidgetID, kSwatchesPanelPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kTintTextWidgetID, kSwatchesPanelPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kTintPerTextWidgetID, kSwatchesPanelPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kSwatchesGridParentWidgetID, kSwatchesPanelPrefix + 41)

DECLARE_PMID(kWidgetIDSpace, kDeleteSwatchesDialogWidgetId, kSwatchesPanelPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kWarningIconWidgetId, kSwatchesPanelPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kRemoveSwatchLabelWidgetId, kSwatchesPanelPrefix + 45)

DECLARE_PMID(kWidgetIDSpace, kLargeSwatchGridWidgetID, kSwatchesPanelPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kSwatchSmallListPanelWidgetID, kSwatchesPanelPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kRenderSmallListBoxWidgetID, kSwatchesPanelPrefix + 48)

DECLARE_PMID(kWidgetIDSpace, kNameWithColorCheckBoxWidgetID, kSwatchesPanelPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kSwatchColorNameStaticTextWidgetID, kSwatchesPanelPrefix + 50)

DECLARE_PMID(kWidgetIDSpace, kStrokeFillStripWidgetID, kSwatchesPanelPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kStrokeFillProxyWidgetID, kSwatchesPanelPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kStrokeFillTintStaticTextWidgetID, kSwatchesPanelPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kStrokeFillTintWidgetID, kSwatchesPanelPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kStrokeFillTintStaticPercentWidgetID, kSwatchesPanelPrefix + 55)

DECLARE_PMID(kWidgetIDSpace, kColorModeSeparatorPanelWidgetID, kSwatchesPanelPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kColorPickerGroupPanelWidgetID, kSwatchesPanelPrefix + 57)

DECLARE_PMID(kWidgetIDSpace, kNewMixedInkGroupDialogWidgetID, kSwatchesPanelPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kNewInkGroupButtonGroupWidgetID, kSwatchesPanelPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kSwatchGenericDialogPanel1WidetID, kSwatchesPanelPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kSwatchGenericDialogPanel2WidetID, kSwatchesPanelPrefix + 61)

DECLARE_PMID(kWidgetIDSpace, kSwatchGenericDialogPanel3WidetID, kSwatchesPanelPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kInkGroupNameLabelWidgetID, kSwatchesPanelPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kInkGroupNameWidgetID, kSwatchesPanelPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kInkGroupCreateTypeLabelWidgetID, kSwatchesPanelPrefix + 65)


DECLARE_PMID(kWidgetIDSpace, kInkGroupPickerGroupPanelWidgetID, kSwatchesPanelPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kInkGroupPickerGroupTitleWidgetID, kSwatchesPanelPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kInkGroupLabelWidgetID, kSwatchesPanelPrefix + 68)

DECLARE_PMID(kWidgetIDSpace, kNewInkGroupPickerPanelWidgetID, kSwatchesPanelPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kNewInkGroupTreePanelWidgetID, kSwatchesPanelPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kNewInkGroupTreeViewWidgetID, kSwatchesPanelPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kNewInkGroupInkListElementWidgetID, kSwatchesPanelPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kInkItemRepeatCountWidgetID, kSwatchesPanelPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kInkItemStartValueWidgetID, kSwatchesPanelPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kInkItemStepValueWidgetID, kSwatchesPanelPrefix + 75)

DECLARE_PMID(kWidgetIDSpace, kNewInkGroupPreviewButtonWidgetID, kSwatchesPanelPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kPreviewInkGroupListBoxWidgetID, kSwatchesPanelPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kPreviewInkGroupInkListElementWidgetID, kSwatchesPanelPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kInkItemPreviewColorProxyWidgetID, kSwatchesPanelPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kInkItemPreviewNameWidgetID, kSwatchesPanelPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kNewInkGroupPreviewlPanelWidgetID, kSwatchesPanelPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kNewInkGroupPreviewSwatchLabelWidgetID, kSwatchesPanelPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kNewInkGroupPreviewSwatchTextWidgetID, kSwatchesPanelPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kNewInkGroupPreviewGroupPanelWidgetID, kSwatchesPanelPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kNewInkGroupPreviewGroupTitleLabelWidgetID, kSwatchesPanelPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kSwatchGenericDialogPanel4WidetID, kSwatchesPanelPrefix + 86)

DECLARE_PMID(kWidgetIDSpace, kNewMixedInkSwatchPanelWidgetID, kSwatchesPanelPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kNewMixedInkSwatchGroupPanelWidgetID, kSwatchesPanelPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kNewMixedInkSwatchGroupTitleWidgetID, kSwatchesPanelPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kNewMixedInkSwatchGroupTitleLabelWidgetID, kSwatchesPanelPrefix + 90)

DECLARE_PMID(kWidgetIDSpace, kNewMixedInkSwatchProxyWidgetID, kSwatchesPanelPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kNewMixedInkSwatchTreePanelWidgetID, kSwatchesPanelPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kNewMixedInkSwatchTreeViewWidgetID, kSwatchesPanelPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kNewMixedInkSwatchInkListElementWidgetID, kSwatchesPanelPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kInkItemEnableWidgetID, kSwatchesPanelPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kInkGroupItemEnableWidgetID, kSwatchesPanelPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kInkItemValuePanelWidgetID, kSwatchesPanelPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kInkItemBorderPanel1WidgetID, kSwatchesPanelPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kInkItemBorderPanel2WidgetID, kSwatchesPanelPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kInkItemBorderPanel3WidgetID, kSwatchesPanelPrefix + 100)

DECLARE_PMID(kWidgetIDSpace, kNewInkGroupTreeLabelPanelWidgetID, kSwatchesPanelPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kInkGroupInitialStaticTextWidgetID, kSwatchesPanelPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kInkGroupRepeatStaticTextWidgetID, kSwatchesPanelPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kInkGroupStepStaticTextWidgetID, kSwatchesPanelPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kInkGroupStaticTextPadWidgetID, kSwatchesPanelPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kNewInkGroupPreviewlPanel1WidgetID, kSwatchesPanelPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kNewInkGroupPreviewlPanel2WidgetID, kSwatchesPanelPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kNewInkGroupIncludedInksInfoWidgetID, kSwatchesPanelPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kNewInkGroupIncludedInksInfoScrollBarWidgetID, kSwatchesPanelPrefix + 109)


//DECLARE_PMID(kWidgetIDSpace, kSwatchesPanelProxyCtrlSetWidgetID, kSwatchesPanelPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kSwatchesKitPanelViewWidgetID, kSwatchesPanelPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kStrokeFillStripSeparatorWidgetID, kSwatchesPanelPrefix +111)
DECLARE_PMID(kWidgetIDSpace, kSwatchesPanelCtrlSetWidgetID, kSwatchesPanelPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kSwatchesKitDockBarViewWidgetID, kSwatchesPanelPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kSwatchesDockBarDDListCtrlSetWidgetID, kSwatchesPanelPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kSwatchesDDListWidgetID, kSwatchesPanelPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kSwatchesDockBarProxyCtrlSetWidgetID, kSwatchesPanelPrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kStrokeFillControlStripStripWidgetID, kSwatchesPanelPrefix + 117)

DECLARE_PMID(kWidgetIDSpace, kMixedInkGroupOptionDialogWidgetID, kSwatchesPanelPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kInkGroupOptionTreePanelWidgetID, kSwatchesPanelPrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kInkGroupOptionTreeViewWidgetID, kSwatchesPanelPrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kInkGroupOptionInkListElementWidgetID, kSwatchesPanelPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kInkGroupItemDropDwonWidgetID, kSwatchesPanelPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kInkGroupOptionConvert2ProcessWidgetID, kSwatchesPanelPrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kAddSwatchButtonWidgetID, kSwatchesPanelPrefix + 124)
DECLARE_PMID(kWidgetIDSpace, kAddSwatchDoneButtonWidgetID, kSwatchesPanelPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kDontShowMixedInkGroupExceedValuesAlertWidgetID, kSwatchesPanelPrefix + 126)
//gap
DECLARE_PMID(kWidgetIDSpace, kAddToCCLibrariesPanelWidgetID, kSwatchesPanelPrefix + 128)
//gap
DECLARE_PMID(kWidgetIDSpace, kSwatchListTreeWidgetID, kSwatchesPanelPrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kSwatchListNodeWidgetID, kSwatchesPanelPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kSwatchListColorNodeWidgetID, kSwatchesPanelPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kSwatchListGradientNodeWidgetID, kSwatchesPanelPrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kSwatchNodeProxyWidgetID, kSwatchesPanelPrefix + 134)
DECLARE_PMID(kWidgetIDSpace, kSwatchNodeNameWidgetID, kSwatchesPanelPrefix + 135)
DECLARE_PMID(kWidgetIDSpace, kSwatchNodeNameILEWidgetID, kSwatchesPanelPrefix + 136)
DECLARE_PMID(kWidgetIDSpace, kSwatchNodeIconStatusPanelWidgetID, kSwatchesPanelPrefix + 137)

DECLARE_PMID(kWidgetIDSpace, kAnySwatchNodeWidgetID, kSwatchesPanelPrefix + 138)
DECLARE_PMID(kWidgetIDSpace, kColorGroupNodeWidgetID, kSwatchesPanelPrefix + 139)
DECLARE_PMID(kWidgetIDSpace, kColorGroupFolderIconWidgetID, kSwatchesPanelPrefix + 142)
DECLARE_PMID(kWidgetIDSpace, kNewColorGroupButtonWidgetID, kSwatchesPanelPrefix + 143)
DECLARE_PMID(kWidgetIDSpace, kColorGroupOptionsDialogWidgetID, kSwatchesPanelPrefix + 144)
DECLARE_PMID(kWidgetIDSpace, kColorGroupOptionsDialogGenericPanelWidgetId, kSwatchesPanelPrefix + 145)
DECLARE_PMID(kWidgetIDSpace, kColorGroupOptionsDialogColorGroupNameWidgetId, kSwatchesPanelPrefix + 146)
DECLARE_PMID(kWidgetIDSpace, kColorGroupOptionsColumn3WidgetID, kSwatchesPanelPrefix + 147)
DECLARE_PMID(kWidgetIDSpace, kColorGroupNodeNameILEWidgetID, kSwatchesPanelPrefix + 148)
DECLARE_PMID(kWidgetIDSpace, kNewColorGroupDialogWidgetID, kSwatchesPanelPrefix + 149)


// EVE Related
DECLARE_PMID(kWidgetIDSpace, kNewSwatchPanelButtonsColWidgetID,			kSwatchesPanelPrefix + 150)
DECLARE_PMID(kWidgetIDSpace, kNewSwatchPanelControlsColWidgetID,		kSwatchesPanelPrefix + 151)
DECLARE_PMID(kWidgetIDSpace, kNewSwatchPanelControlsColRow1WidgetID,	kSwatchesPanelPrefix + 152)
DECLARE_PMID(kWidgetIDSpace, kColorOptionsPanelRow1WidgetID,			kSwatchesPanelPrefix + 153)
DECLARE_PMID(kWidgetIDSpace, kCCLibraryHyperlinkTextWidgetID,			kSwatchesPanelPrefix + 154)
DECLARE_PMID(kWidgetIDSpace, kSelectedSwatchesPopupRadioButtonWidgetID,	kSwatchesPanelPrefix + 155)
DECLARE_PMID(kWidgetIDSpace, kSelectedArtworkPopupRadioButtonWidgetID,	kSwatchesPanelPrefix + 156)
DECLARE_PMID(kWidgetIDSpace, kSwatchesFilterMenuButtonWidgetID,			kSwatchesPanelPrefix + 157)
DECLARE_PMID(kWidgetIDSpace, kSwatchTouchGridViewWidgetId,				kSwatchesPanelPrefix + 158)
DECLARE_PMID(kWidgetIDSpace, kSwatchTouchListViewWidgetId,				kSwatchesPanelPrefix + 159)
DECLARE_PMID(kWidgetIDSpace, kSwatchTouchListPanelWidgetID, kSwatchesPanelPrefix + 160)



// <Service ID>
//---------------------------------------------------------------
// ----- Service IDs -----
//---------------------------------------------------------------
DECLARE_PMID(kServiceIDSpace, kSwatchOptionDialogService, kSwatchesPanelPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kNewMixedInkGroupOptionPanelService, kSwatchesPanelPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kSwatchTouchPanelService, kSwatchesPanelPrefix + 3)

// <Error ID>
// -- Moved to DocFrameworkID.h so they are available to the model.

// <Action ID>
DECLARE_PMID(kActionIDSpace, kSwatchesPanelActionID, kSwatchesPanelPrefix + 1)
DECLARE_PMID(kActionIDSpace, kNewColorSwatchActionID, kSwatchesPanelPrefix + 2)
DECLARE_PMID(kActionIDSpace, kNewTintedSwatchActionID, kSwatchesPanelPrefix + 3)
DECLARE_PMID(kActionIDSpace, kNewGradientSwatchActionID, kSwatchesPanelPrefix + 4)
DECLARE_PMID(kActionIDSpace, kSwatchesSep1ActionID, kSwatchesPanelPrefix + 5)
DECLARE_PMID(kActionIDSpace, kDuplicateSwatchActionID, kSwatchesPanelPrefix + 6)
DECLARE_PMID(kActionIDSpace, kDeleteSwatchActionID, kSwatchesPanelPrefix + 7)
DECLARE_PMID(kActionIDSpace, kSwatchesSep2ActionID, kSwatchesPanelPrefix + 8)
DECLARE_PMID(kActionIDSpace, kSwatchOptionsActionID, kSwatchesPanelPrefix + 9)
DECLARE_PMID(kActionIDSpace, kSwatchesSep3ActionID, kSwatchesPanelPrefix + 10)
DECLARE_PMID(kActionIDSpace, kSelectAllUnusedActionID, kSwatchesPanelPrefix + 11)
DECLARE_PMID(kActionIDSpace, kNameViewActionID, kSwatchesPanelPrefix + 12)
DECLARE_PMID(kActionIDSpace, kLargeSwatchViewActionID, kSwatchesPanelPrefix + 13 )
DECLARE_PMID(kActionIDSpace, kNewSwatchActionID, kSwatchesPanelPrefix + 14) // note - this is used as a message. It's not really an action.
DECLARE_PMID(kActionIDSpace, kSmallSwatchViewActionID, kSwatchesPanelPrefix + 15 )
DECLARE_PMID(kActionIDSpace, kSwatchesSep4ActionID, kSwatchesPanelPrefix + 16 )
DECLARE_PMID(kActionIDSpace, kSwatchesSep5ActionID, kSwatchesPanelPrefix + 17 )
DECLARE_PMID(kActionIDSpace, kSwatchSmallPaletteRowNameViewActionID, kSwatchesPanelPrefix + 18)
DECLARE_PMID(kActionIDSpace, kAddAllUnnamedColorsActionID, kSwatchesPanelPrefix + 19)
DECLARE_PMID(kActionIDSpace, kMergeSwatchesActionID, kSwatchesPanelPrefix + 20)
DECLARE_PMID(kActionIDSpace, kSwatchesSep6ActionID, kSwatchesPanelPrefix + 21)
DECLARE_PMID(kActionIDSpace, kSwatchShowHideOptionActionID, kSwatchesPanelPrefix + 22)
DECLARE_PMID(kActionIDSpace, kNewMixedInkSwatchActionID, kSwatchesPanelPrefix + 23)
DECLARE_PMID(kActionIDSpace, kNewMixedInkGroupActionID, kSwatchesPanelPrefix + 24)
DECLARE_PMID(kActionIDSpace, kLoadSwatchesActionID, kSwatchesPanelPrefix + 25)
DECLARE_PMID(kActionIDSpace, kSwatchesSep7ActionID, kSwatchesPanelPrefix + 26)
DECLARE_PMID(kActionIDSpace, kSaveSwatchesActionID, kSwatchesPanelPrefix + 27)
DECLARE_PMID(kActionIDSpace, kNewColorGroupActionID, kSwatchesPanelPrefix + 28)
DECLARE_PMID(kActionIDSpace, kEditColorGroupActionID, kSwatchesPanelPrefix + 29)
DECLARE_PMID(kActionIDSpace, kUngroupColorGroupActionID, kSwatchesPanelPrefix + 30)
DECLARE_PMID(kActionIDSpace, kShowAllSwatchesActionID, kSwatchesPanelPrefix + 31)
DECLARE_PMID(kActionIDSpace, kShowColorSwatchesActionID, kSwatchesPanelPrefix + 32)
DECLARE_PMID(kActionIDSpace, kShowGradientSwatchesActionID, kSwatchesPanelPrefix + 33)
DECLARE_PMID(kActionIDSpace, kShowColorGroupsActionID, kSwatchesPanelPrefix + 34)
DECLARE_PMID(kActionIDSpace, kSortSwatchesByNameActionID, kSwatchesPanelPrefix + 35)
DECLARE_PMID(kActionIDSpace, kFlyoutSortSwatchesByNameActionID, kSwatchesPanelPrefix + 36)
DECLARE_PMID(kActionIDSpace, kSortSwatchesByColorInfoActionID, kSwatchesPanelPrefix + 37)
DECLARE_PMID(kActionIDSpace, kFlyoutSortSwatchesByColorInfoActionID, kSwatchesPanelPrefix + 38)
DECLARE_PMID(kActionIDSpace, kSortSwatchesVisuallyActionID, kSwatchesPanelPrefix + 39)
DECLARE_PMID(kActionIDSpace, kSwatchesSep8ActionID, kSwatchesPanelPrefix + 40)
DECLARE_PMID(kActionIDSpace, kFindColorActionID, kSwatchesPanelPrefix + 41)
DECLARE_PMID(kActionIDSpace, kSwatchesSep9ActionID, kSwatchesPanelPrefix + 42)
DECLARE_PMID(kActionIDSpace, kNewColorSwatchWithNoGfxUpdateActionID, kSwatchesPanelPrefix + 43)


// Node ID for tree view (space-less)
#define kSwatchNodeID		kSwatchesPanelPrefix + 1

#endif

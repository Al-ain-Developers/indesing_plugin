//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/SwatchLibPanelID.h $
//  
//  Owner: Paul Ronan
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
//  Contains IDs used by the swatch library plug-in
//  
//========================================================================================

#ifndef __SwatchLibPluginID__
#define __SwatchLibPluginID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define	kSwatchLibPanelPrefix					RezLong(0x7B00)		//Defined in "AdobePrefix.h"

#define	kSwatchLibPanelPluginName				"Swatch Library Panel"
DECLARE_PMID(kPlugInIDSpace, kSwatchLibPanelPluginID, kSwatchLibPanelPrefix + 1)

// <Start IDC>
//---------------------------------------------------------------
// <Class ID>
//---------------------------------------------------------------
DECLARE_PMID (kClassIDSpace, kSwatchLibPanelRegisterBoss, kSwatchLibPanelPrefix + 1)
DECLARE_PMID (kClassIDSpace, kSwatchLibPanelWidgetBoss, kSwatchLibPanelPrefix + 2)
DECLARE_PMID (kClassIDSpace, kSwatchLibListBoxBoss, kSwatchLibPanelPrefix + 3)
DECLARE_PMID (kClassIDSpace, kSwatchLibListItemViewBoss, kSwatchLibPanelPrefix + 4)
//gap
DECLARE_PMID (kClassIDSpace, kSwatchLibRenderListBoxBasicBoss, kSwatchLibPanelPrefix + 6)
//gap
DECLARE_PMID (kClassIDSpace, kOpenSwatchLibFileBoss, kSwatchLibPanelPrefix + 10)
//gap

DECLARE_PMID (kClassIDSpace, kSwatchLibWidgetBoss, kSwatchLibPanelPrefix + 14)
DECLARE_PMID (kClassIDSpace, kSwatchLibContainerWidgetBoss, kSwatchLibPanelPrefix + 15)
DECLARE_PMID (kClassIDSpace, kSwatchLibSelectionEditBoxWidgetBoss, kSwatchLibPanelPrefix + 16)
DECLARE_PMID (kClassIDSpace, kLibPanelSwatchProxyWidgetBoss, kSwatchLibPanelPrefix + 17)
DECLARE_PMID (kClassIDSpace, kSwatchLibListBoxWidgetBoss, kSwatchLibPanelPrefix + 18)
DECLARE_PMID (kClassIDSpace, kSwatchLibOtherContainerWidgetBoss, kSwatchLibPanelPrefix + 19)
DECLARE_PMID (kClassIDSpace, kSwatchLibOtherListBoxWidgetBoss, kSwatchLibPanelPrefix + 20)
DECLARE_PMID (kClassIDSpace, kSwatchLibOtherSelectionEditBoxWidgetBoss, kSwatchLibPanelPrefix + 21)

DECLARE_PMID (kClassIDSpace, kSwatchIconSuiteWidgetBoss, kSwatchLibPanelPrefix + 22)


//---------------------------------------------------------------
// <Implementation ID>
//---------------------------------------------------------------
//gap
DECLARE_PMID (kImplementationIDSpace, kSwatchLibPanelResizeRuleImpl, kSwatchLibPanelPrefix + 5)
DECLARE_PMID (kImplementationIDSpace, kSwatchLibraryUserFileListImpl, kSwatchLibPanelPrefix + 6)
DECLARE_PMID (kImplementationIDSpace, kSwatchLibListItemViewImpl, kSwatchLibPanelPrefix + 7)
//gap
DECLARE_PMID (kImplementationIDSpace, kSwatchLibPanelAttrImpl, kSwatchLibPanelPrefix + 10)
//gap
DECLARE_PMID (kImplementationIDSpace, kOpenSwatchLibFileImpl, kSwatchLibPanelPrefix + 14)
//gap

DECLARE_PMID (kImplementationIDSpace, kSwatchLibSwatchUIDObserverImpl, kSwatchLibPanelPrefix + 19)
DECLARE_PMID (kImplementationIDSpace, kTypeaheadItemSelectEditBoxEHImpl, kSwatchLibPanelPrefix + 20)
DECLARE_PMID (kImplementationIDSpace, kSwatchLibraryPanelHelperImpl, kSwatchLibPanelPrefix + 21)
DECLARE_PMID (kImplementationIDSpace, kSwatchLibContainerObserverImpl, kSwatchLibPanelPrefix + 22)
DECLARE_PMID (kImplementationIDSpace, kLibPanelProxyViewImpl, kSwatchLibPanelPrefix + 23)
// gap
DECLARE_PMID (kImplementationIDSpace, kSwatchLibOtherContainerObserverImpl, kSwatchLibPanelPrefix + 25)
DECLARE_PMID (kImplementationIDSpace, kSwatchLibOtherSwatchUIDObserverImpl, kSwatchLibPanelPrefix + 26)
DECLARE_PMID (kImplementationIDSpace, kSwatchLibUtilsImpl, kSwatchLibPanelPrefix + 27)


//---------------------------------------------------------------
// <Interface ID>
//---------------------------------------------------------------
// Define your Interface IIDs here
//gap
DECLARE_PMID (kInterfaceIDSpace, IID_ISWATCHLIBPANELATTR, kSwatchLibPanelPrefix + 2)
DECLARE_PMID (kInterfaceIDSpace, IID_ISWATCHLIBSWATCHUIDOBSERVER, kSwatchLibPanelPrefix + 3)
DECLARE_PMID (kInterfaceIDSpace, IID_ISWATCHLIBRARYPANELHELPER, kSwatchLibPanelPrefix + 4)
DECLARE_PMID (kInterfaceIDSpace, IID_ISWATCHLIBPANELATTACHEDOBSERVER, kSwatchLibPanelPrefix + 5)
DECLARE_PMID (kInterfaceIDSpace, IID_ISWATCHLIBUTILS, kSwatchLibPanelPrefix + 6)
DECLARE_PMID (kInterfaceIDSpace, IID_ISWATCHLIBRARYUSERFILELIST, kSwatchLibPanelPrefix + 7)

//---------------------------------------------------------------
// <Widget ID>
//---------------------------------------------------------------
DECLARE_PMID (kWidgetIDSpace, kSwatchLibResizeWidgetId, kSwatchLibPanelPrefix + 1)
DECLARE_PMID (kWidgetIDSpace, kSwatchLibControlStripWidgetId, kSwatchLibPanelPrefix + 2)
DECLARE_PMID (kWidgetIDSpace, kSwatchLibStatusWidgetId, kSwatchLibPanelPrefix + 3)
DECLARE_PMID (kWidgetIDSpace, kSwatchLibListWidgetId, kSwatchLibPanelPrefix + 4)
DECLARE_PMID (kWidgetIDSpace, kSwatchLibNoPencilWidgetId, kSwatchLibPanelPrefix + 11)

//DECLARE_PMID (kWidgetIDSpace, kSwatchLibContainerWidgetId, kSwatchLibPanelPrefix + 12)	// really the same as kSwatchLibPanelWidgetId, 
DECLARE_PMID (kWidgetIDSpace, kSwatchLibColorProxyWidgetId, kSwatchLibPanelPrefix + 12)
DECLARE_PMID (kWidgetIDSpace, kSwatchLibNameWidgetId, kSwatchLibPanelPrefix + 13)
DECLARE_PMID (kWidgetIDSpace, kSwatchLibSelectionEditBoxWidgetId, kSwatchLibPanelPrefix + 14)
DECLARE_PMID (kWidgetIDSpace, kSwatchLibNameSuffixWidgetId, kSwatchLibPanelPrefix + 15)
DECLARE_PMID (kWidgetIDSpace, kSwatchLibWidgetId, kSwatchLibPanelPrefix + 16)

//	Make this widget defined last since all library panels are assigned an ID starting
//	from it. This is so that the panel's widget ID does not overlap with widgetIDs contained
//	in the same panel.
DECLARE_PMID (kWidgetIDSpace, kSwatchLibPanelWidgetId, kSwatchLibPanelPrefix + 100)

// <Ignore>
//******OWNER IDs (for special useage by the Progress Bar Users)

//---------------------------------------------------------------
//---------------------------------------------------------------
#define	kProgressBarLibraryImport	kSwatchLibPanelPrefix + 1

// <Ignore>
//---------------------------------------------------------------
//	Special Named swatch library signature ID
//---------------------------------------------------------------
#define	kInvalidLibCreatorID				kSwatchLibPanelPrefix
#define	kDICColorLibCreatorID				kSwatchLibPanelPrefix + 1
#define	kFocoltoneLibCreatorID				kSwatchLibPanelPrefix + 2
#define	kHKS_ELibCreatorID					kSwatchLibPanelPrefix + 3
#define	kHKS_KLibCreatorID					kSwatchLibPanelPrefix + 4
#define	kHKS_NLibCreatorID					kSwatchLibPanelPrefix + 5
#define	kHKS_ZLibCreatorID					kSwatchLibPanelPrefix + 6
#define	kPantoneCoatedLibCreatorID			kSwatchLibPanelPrefix + 7
#define	kPantoneProcessLibCreatorID			kSwatchLibPanelPrefix + 8
#define	kPantoneUncoatedLibCreatorID		kSwatchLibPanelPrefix + 9
#define	kTrumatchLibCreatorID				kSwatchLibPanelPrefix + 10
#define	kToyoColorLibCreatorID				kSwatchLibPanelPrefix + 11
#define	kPantoneCoatedNewLibCreatorID		kSwatchLibPanelPrefix + 12
#define	kPantoneProcessNewLibCreatorID		kSwatchLibPanelPrefix + 13
#define	kPantoneUncoatedNewLibCreatorID		kSwatchLibPanelPrefix + 14
#define	kPantoneMatteNewLibCreatorID		kSwatchLibPanelPrefix + 15
#define	kPantoneEuroProcessNewLibCreatorID	kSwatchLibPanelPrefix + 16
#define kANPAColorLibCreatorID				kSwatchLibPanelPrefix + 17
#define kHKS_EProcessLibCreatorID			kSwatchLibPanelPrefix + 18
#define kHKS_KProcessLibCreatorID			kSwatchLibPanelPrefix + 19
#define kHKS_NProcessLibCreatorID			kSwatchLibPanelPrefix + 20
#define kHKS_ZProcessLibCreatorID			kSwatchLibPanelPrefix + 21
#define kPantoneMetallicCoatedLibCreatorID	kSwatchLibPanelPrefix + 22
#define kPantonePastelCoatedLibCreatorID	kSwatchLibPanelPrefix + 23
#define kPantonePastelUncoatedLibCreatorID	kSwatchLibPanelPrefix + 24
#define kPantoneSolidToProcessLibCreatorID	kSwatchLibPanelPrefix + 25
#define kToyoProcessLibCreatorID			kSwatchLibPanelPrefix + 26

//Bug#1495007
//Take care of newly added libraries, and the old ones that were left out
#define kPantoneColorBridgeCMYKECLibCreatorID	kSwatchLibPanelPrefix + 27
#define kPantoneColorBridgeCMYKPCLibCreatorID	kSwatchLibPanelPrefix + 28
#define kPantoneColorBridgeCMYKUPLibCreatorID	kSwatchLibPanelPrefix + 29
#define kToyoColorFinderLibCreatorID			kSwatchLibPanelPrefix + 30
#define kPantoneProcessUncoatedLibCreatorID		kSwatchLibPanelPrefix + 31

// New PANTONE libraries for CS5
#define kPantonePlusCMYKCoatedLibCreatorID	kSwatchLibPanelPrefix + 32
#define kPantonePlusCMYKUncoatedLibCreatorID	kSwatchLibPanelPrefix + 33
#define kPantonePlusColorBridgeCoatedLibCreatorID	kSwatchLibPanelPrefix + 34
#define kPantonePlusColorBridgeUncoatedLibCreatorID	kSwatchLibPanelPrefix + 35
#define kPantonePlusPastelCoatedLibCreatorID	kSwatchLibPanelPrefix + 36
#define kPantonePlusPastelUncoatedLibCreatorID	kSwatchLibPanelPrefix + 37
#define kPantonePlusMetallicCoatedLibCreatorID	kSwatchLibPanelPrefix + 38
#define kPantonePlusSolidCoatedLibCreatorID	kSwatchLibPanelPrefix + 39
#define kPantonePlusSolidUncoatedLibCreatorID	kSwatchLibPanelPrefix + 40

//---------------------------------------------------------------
// <Error ID>
//---------------------------------------------------------------
// Error Codes
// NOTE:  The offset is used to find the corresponding error string
DECLARE_PMID (kErrorIDSpace, kSwatchLibUnknownFormatErr, kSwatchLibPanelPrefix + 1)
DECLARE_PMID (kErrorIDSpace, kSwatchLibCantCreateErr, kSwatchLibPanelPrefix + 2)

//---------------------------------------------------------------
// <Action ID>
//---------------------------------------------------------------
DECLARE_PMID (kActionIDSpace, kFirstOtherLibraryActionID, kSwatchLibPanelPrefix + 2)
//	Ids in this range reserved...
DECLARE_PMID (kActionIDSpace, kLastOtherLibraryActionID, kSwatchLibPanelPrefix + 70)
DECLARE_PMID (kActionIDSpace, kAddToSwatchesActionID, kSwatchLibPanelPrefix + 71)
//	gap
DECLARE_PMID (kActionIDSpace, kLibrarySepActionID, kSwatchLibPanelPrefix + 101)
DECLARE_PMID (kActionIDSpace, kOtherLibraryActionID, kSwatchLibPanelPrefix + 102)
DECLARE_PMID (kActionIDSpace, kSwatchLibSmallPaletteRowsActionID, kSwatchLibPanelPrefix + 103)
DECLARE_PMID (kActionIDSpace, kAddToSwatchPanelActionID, kSwatchLibPanelPrefix + 104)

#endif // __SwatchLibPluginID__






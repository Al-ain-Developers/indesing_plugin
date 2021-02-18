//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/cellpanel/CelPnlID.h $
//  
//  Owner: Adobe Developer Technologies
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
//  Contains common definitions used by the TableCell panel plug-in.
//  
//========================================================================================

#ifndef __CELPNLID_h__
#define __CELPNLID_h__

#include "SDKDef.h"

// Company
#define kCelPnlCompanyKey		kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kCelPnlCompanyValue		kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in
#define kCelPnlTitle			"CellPanel"  	// Basic name of plug-in. Use as part of other keys, not alone.
#define kCelPnlPrefixNumber		0x53500				// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kCelPnlVersion			kSDKDefPluginVersionString				// Version of this plug-in (for the About Box).
#define kCelPnlAuthor			"Adobe Developer Technologies" // Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kCelPnlPrefixNumber above to modify the prefix.)
#define kCelPnlPrefix			RezLong(kCelPnlPrefixNumber)	// The unique numeric prefix for all object model IDs for this plug-in.
#define kCelPnlStringPrefix	SDK_DEF_STRINGIZE(kCelPnlPrefixNumber) // The string equivalent of the unique prefix number for  this plug-in.

START_IDS()

// Plugin ID
DECLARE_PMID(kPlugInIDSpace, kCelPnlPlugInID, kCelPnlPrefix + 0)

// Class (Boss) IDs

// The flowing boss IDs are no longer needed.
//DECLARE_PMID(kClassIDSpace,	kCelPnlPanelRegisterBoss, 			kCelPnlPrefix + 0)
//DECLARE_PMID(kClassIDSpace,	kCelPnlStringRegisterBoss,			kCelPnlPrefix + 1)
//DECLARE_PMID(kClassIDSpace,	kCelPnlMenuRegisterBoss,			kCelPnlPrefix + 2)
//DECLARE_PMID(kClassIDSpace,	kCelPnlActionRegisterBoss,			kCelPnlPrefix + 3)

DECLARE_PMID(kClassIDSpace,	kCelPnlActionComponentBoss,			kCelPnlPrefix + 4)
DECLARE_PMID(kClassIDSpace, kCelPnlPanelWidgetBoss,				kCelPnlPrefix + 5)
DECLARE_PMID(kClassIDSpace,	kCelPnlTextEditBoxWidgetBoss,			kCelPnlPrefix + 6)
DECLARE_PMID(kClassIDSpace,	kTableCellWidgetBoss,				kCelPnlPrefix + 7)

// Implementation IDs
DECLARE_PMID(kImplementationIDSpace,	kCelPnlActionComponentImpl, 		kCelPnlPrefix + 0)
DECLARE_PMID(kImplementationIDSpace,	kCelPnlEditBoxObserverImpl, 		kCelPnlPrefix + 1)
DECLARE_PMID(kImplementationIDSpace,	kCelPnlEditBoxEventHandlerImpl, 	kCelPnlPrefix + 2)
DECLARE_PMID(kImplementationIDSpace,	kTableCellObserverImpl, 		kCelPnlPrefix + 3)
DECLARE_PMID(kImplementationIDSpace,	kTableCellViewImpl, 			kCelPnlPrefix + 4)
DECLARE_PMID(kImplementationIDSpace,	kTableCellEventHImpl, 			kCelPnlPrefix + 5)
DECLARE_PMID(kImplementationIDSpace,	kTableCellDataImpl, 			kCelPnlPrefix + 6)
DECLARE_PMID(kImplementationIDSpace,	kCelPnlPanelViewImpl, 				kCelPnlPrefix + 7)

// Interface IDs
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLECELLDATA,	kCelPnlPrefix + 0)	

// Action IDs
DECLARE_PMID(kActionIDSpace,	kCelPnlActionID,			kCelPnlPrefix + 1)
DECLARE_PMID(kActionIDSpace,	kCelPnlAboutActionID,		kCelPnlPrefix + 2)
DECLARE_PMID(kActionIDSpace,	kCelPnlAboutThisActionID,	kCelPnlPrefix + 3)

END_IDS()

// Palette IDs
#define kPopupPaletteID							kSDKDefDefaultPaletteID

// Resource IDs:
#define kMenuResourceID							kSDKDefMenuResourceID	// Standard ID
#define kPanelResourceID						kSDKDefDialogResourceID
#define kStringsResourceID						kSDKDefStringsResourceID
#define kStringsNoTransResourceID				kSDKDefStringsNoTransResourceID
#define kActionResourceID 						kSDKDefActionResourceID
#define kVersionResourceID 						kSDKDefPluginVersionResourceID
#define kClassResourceID 						kSDKDefClassDescriptionTableResourceID
#define kFactoryListResourceID 					kSDKDefFactoryListResourceID

// Widget IDs:
#define kTableCellPanelWidgetID					kCelPnlPrefix + 0
#define kTableCellEditBoxWidgetID				kCelPnlPrefix + 1
#define kTableCellWidgetID						kCelPnlPrefix + 2
#define kTebleCellGroupWidgetID					kCelPnlPrefix + 3
#define kTableCellScrollWidgetID				kCelPnlPrefix + 4
#define kTableCellHScrollWidgetID				kCelPnlPrefix + 5

// This plug-ins About box
#define kCelPnlMenuAboutMenuKey					kCelPnlStringPrefix "kCelPnlMenuAboutMenuKey"
#define kCelPnlMenuAboutMenuPath				kSDKDefStandardAboutMenuPath kCelPnlCompanyKey

// Menu Paths and String Keys for Show/Hide CellPanel.
#define kCelPnlMenuItemkey 						kCelPnlStringPrefix "kCelPnlMenuItemkey"
#define kCelPnlMenuItemPath						kSDKDefPlugInsStandardMenuPath kCelPnlCompanyKey kSDKDefDelimitMenuPath kCelPnlMenuItemkey

// Menu IDs for Panel:
// Menu Paths and String Keys for Panel Popup menu
#define kCelPnlPopupMenuNameKey					kCelPnlStringPrefix "kCelPnlPopupMenuNameKey"
#define kCelPnlPopupMenuPath					kCelPnlPopupMenuNameKey

// Panels:
#define kCelPnlTitleKey							kCelPnlStringPrefix "kCelPnlTitleKey" 

// Strings:
#define kCelPnlAboutBoxStringKey				kCelPnlStringPrefix "kCelPnlAboutBoxStringKey"

// Initial data format version numbers: the persistent data for this plug-in was introduced in InDesign 1.0J
#define kCelPnlInitialMajorFormat		kSDKDef_1J_PersistMajorVersionNumber
#define kCelPnlInitialMinorFormat		kSDKDef_1J_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kCelPnlLastMajorFormatChange	kCelPnlInitialMajorFormat		// Most recent major format change
#define kCelPnlLastMinorFormatChange	kCelPnlInitialMinorFormat		// Most recent minor format change

#endif // __CELPNLID_h__

// End, CelPnlID.h.



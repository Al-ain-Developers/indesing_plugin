//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/pictureicon/PicIcoID.h $
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
//  Defines IDs used by the PicIco plug-in.
//  
//========================================================================================

#ifndef __PicIcoID_h__
#define __PicIcoID_h__

#ifndef MAC_RESOURCE_INCLUDER

#include "SDKDef.h"
// Company:
#define kPicIcoCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kPicIcoCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kPicIcoPluginName	"PictureIcon"			// Name of this plug-in.
#define kPicIcoPrefixNumber	0x57210 				// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kPicIcoVersion		kSDKDefPluginVersionString					// Version of this plug-in (for the About Box).
#define kPicIcoAuthor		"Adobe Developer Technologies"			// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kPicIcoPrefixNumber above to modify the prefix.)
#define kPicIcoPrefix		RezLong(kPicIcoPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kPicIcoStringPrefix	SDK_DEF_STRINGIZE(kPicIcoPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kPicIcoPluginID, kPicIcoPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kPicIcoActionComponentBoss,	kPicIcoPrefix + 0)
DECLARE_PMID(kClassIDSpace, kPicIcoStringRegisterBoss,	kPicIcoPrefix + 1)
DECLARE_PMID(kClassIDSpace, kPicIcoPanelRegisterBoss,	kPicIcoPrefix + 2)
DECLARE_PMID(kClassIDSpace, kPicIcoMenuRegisterBoss,	kPicIcoPrefix + 3)
DECLARE_PMID(kClassIDSpace, kPicIcoActionRegisterBoss,	kPicIcoPrefix + 4)
DECLARE_PMID(kClassIDSpace, kPicIcoPanelWidgetBoss,		kPicIcoPrefix + 5)
DECLARE_PMID(kClassIDSpace, kPicIcoPictureWidgetBoss,		kPicIcoPrefix + 6)
DECLARE_PMID(kClassIDSpace, kPicIcoRollOverIconButtonObserverBoss,	kPicIcoPrefix + 7)


// InterfaceIDs:
// None in this plug-in.

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kPicIcoActionComponentImpl,		kPicIcoPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kPicIcoPictureWidgetEHImpl,		kPicIcoPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPicIcoRollOverButtonObserverImpl,	kPicIcoPrefix + 2)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kPicIcoAboutActionID,				kPicIcoPrefix + 0)
DECLARE_PMID(kActionIDSpace, kPicIcoPanelWidgetActionID,		kPicIcoPrefix + 1)
DECLARE_PMID(kActionIDSpace, kPicIcoSeparator1ActionID,			kPicIcoPrefix + 2)
DECLARE_PMID(kActionIDSpace, kPicIcoPopupAboutThisActionID,		kPicIcoPrefix + 3)
DECLARE_PMID(kActionIDSpace, kPicIcoRotatePictureActionID,		kPicIcoPrefix + 11)
DECLARE_PMID(kActionIDSpace, kPicIcoRotateIconActionID,			kPicIcoPrefix + 12)
// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kPicIcoPanelWidgetID,					kPicIcoPrefix + 0) 
DECLARE_PMID(kWidgetIDSpace, kPicIcoPictureWidgetId,				kPicIcoPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kPicIcoIconSuiteWidgetId,				kPicIcoPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kPicIcoRollOverIconButtonWidgetID,	kPicIcoPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kPicIcoCustomPictureWidgetId,			kPicIcoPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kPicIcoStaticTextWidgetId,				kPicIcoPrefix + 5)

// "About Plug-ins" sub-menu:
#define kPicIcoAboutMenuKey			kPicIcoStringPrefix "kPicIcoAboutMenuKey"
#define kPicIcoAboutMenuPath		kSDKDefStandardAboutMenuPath kPicIcoCompanyKey

// "Plug-ins" sub-menu:
#define kPicIcoPluginsMenuKey 		kPicIcoStringPrefix "kPicIcoPluginsMenuKey"
#define kPicIcoPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kPicIcoCompanyKey kSDKDefDelimitMenuPath kPicIcoPluginsMenuKey

// Menu item keys:
#define kPicIcoRotatePictureMenuItemKey		kPicIcoStringPrefix "kPicIcoRotatePictureMenuItemKey"
#define kPicIcoRotateIconMenuItemKey		kPicIcoStringPrefix "kPicIcoRotateIconMenuItemKey"

// Other StringKeys:
#define kPicIcoAboutBoxStringKey				kPicIcoStringPrefix "kPicIcoAboutBoxStringKey"
#define kPicIcoPanelTitleKey					kPicIcoStringPrefix	"kPicIcoPanelTitleKey"
#define kPicIcoStaticTextKey					kPicIcoStringPrefix	"kPicIcoStaticTextKey"
#define kPicIcoInternalPopupMenuNameKey			kPicIcoStringPrefix	"kPicIcoInternalPopupMenuNameKey"
#define kPicIcoTargetMenuPath					kPicIcoInternalPopupMenuNameKey
#define kPicIcoMessageKey						kPicIcoStringPrefix	"kPicIcoMessageKey"	


// Menu item positions:
#define kPicIcoRotatePictureMenuItemPosition		1.0
#define kPicIcoRotateIconMenuItemPosition			2.0	
#define	kPicIcoSeparator1MenuItemPosition			10.0
#define kPicIcoAboutThisMenuItemPosition			11.0

#endif //MAC_RESOURCE_INCLUDER

// For the platform resources
// bitmaps

#define kPicIcoTopOutsidePictureRsrcID		101
#define kPicIcoTopInsidePictureRsrcID		102
#define kPicIcoBottomOutsidePictureRsrcID	103
#define kPicIcoBottomInsidePictureRsrcID	104
#define kPicIcoCenterVertPictureRsrcID		105
#define kPicIcoCenterHorzPictureRsrcID		106
#define kPicIcoCenterCompPictureRsrcID		107
#define kPicIcoFirstPictureRsrcID			kPicIcoTopOutsidePictureRsrcID
#define kPicIcoLastPictureRsrcID			kPicIcoCenterCompPictureRsrcID // See PicIco.rc, ...

//Crossflatform icons. Reuse application icon
#define kPicIcoButCapIconRsrcID			kStrokePanelButCapIconID                
#define kPicIcoRoundCapIconRsrcID		kStrokePanelRoundCapIconID                
#define kPicIcoProjectingCapIconRsrcID	kStrokePanelProjectingCapIconID            
#define kPicIcoMiterJoinIconRsrcID		kStrokePanelMiterJoinIconID                
#define kPicIcoRoundedJoinIconRsrcID	kStrokePanelRoundedJoinIconID            
#define kPicIcoBevelJoinIconRsrcID		kStrokePanelBevelJoinIconID                

// PNG specific IDs
#define kPicIcoPNGIconRsrcID 10250
#define kPicIcoPNGIconRollRsrcID 10250

// Initial data format version numbers
#define kPicIcoFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kPicIcoFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kPicIcoCurrentMajorFormatNumber kPicIcoFirstMajorFormatNumber // most recent major format change
#define kPicIcoCurrentMinorFormatNumber kPicIcoFirstMinorFormatNumber // most recent minor format change

#endif // __PicIcoID_h__

// End, PicIcoID.h.



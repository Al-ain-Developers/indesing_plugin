//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hidpi/HiDPIID.h $
//  
//  Owner: Neelabh Sunny
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
//  Defines IDs used by the HiDPI plug-in.
//  
//========================================================================================

#ifndef __HiDPIID_h__
#define __HiDPIID_h__

#include "SDKDef.h"

// Company:
#define kHiDPICompanyKey	kSDKDefPlugInCompanyKey                                 // Company name.
#define kHiDPICompanyValue	kSDKDefPlugInCompanyValue                               // Company name (displayed).

// Plug-in:
#define kHiDPIPluginName	"HiDPI"                                                 // Name of this plug-in.
#define kHiDPIPrefixNumber	0x1D7600                                                 // Unique prefix number for this plug-in
#define kHiDPIVersion		kSDKDefPluginVersionString                              // Version of this plug-in (for the About Box).
#define kHiDPIAuthor		"Adobe Developer Technologies"                          // Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kHiDPIPrefixNumber above to modify the prefix.)
#define kHiDPIPrefix		RezLong(kHiDPIPrefixNumber)                             // The unique numeric prefix for all object model IDs
#define kHiDPIStringPrefix	SDK_DEF_STRINGIZE(kHiDPIPrefixNumber)                   // The string equivalent of the unique prefix number

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kHiDPIPluginID, kHiDPIPrefix + 0)

// ClassIDs:

DECLARE_PMID(kClassIDSpace, kHiDPIActionComponentBoss,	kHiDPIPrefix + 0)
DECLARE_PMID(kClassIDSpace, kHiDPIPanelWidgetBoss,		kHiDPIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kHiDPIWidgetBoss,		kHiDPIPrefix + 2)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kHiDPIActionComponentImpl,		kHiDPIPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kHiDPIControlViewImpl,		kHiDPIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kHiDPIWidgetEventHandlerImpl,		kHiDPIPrefix + 2)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kHiDPIAboutActionID,				kHiDPIPrefix + 0)
DECLARE_PMID(kActionIDSpace, kHiDPIPanelWidgetActionID,		kHiDPIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kHiDPIPopupAboutThisActionID,		kHiDPIPrefix + 2)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kHiDPIPanelWidgetID, kHiDPIPrefix + 0) 
DECLARE_PMID(kWidgetIDSpace, kHiDPIPanelIconWidgetID, kHiDPIPrefix +1 ) 

// "About Plug-ins" sub-menu:
#define kHiDPIAboutMenuKey			kHiDPIStringPrefix "kHiDPIAboutMenuKey_a"
#define kHiDPIAboutMenuPath		kSDKDefStandardAboutMenuPath kHiDPICompanyKey

// "Plug-ins" sub-menu:
#define kHiDPIPluginsMenuKey 		kHiDPIStringPrefix "kHiDPIPluginsMenuKey_b"
#define kHiDPIPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kHiDPICompanyKey kSDKDefDelimitMenuPath kHiDPIPluginsMenuKey

// Other StringKeys:
#define kHiDPIAboutBoxStringKey			kHiDPIStringPrefix "kHiDPIAboutBoxStringKey_e"
#define kHiDPIMouseMoveStringKey			kHiDPIStringPrefix "kHiDPIMouseMoveStringKey_f"

#define kHiDPIPanelTitleKey				kHiDPIStringPrefix	"kHiDPIPanelTitleKey_h"

#define kHiDPIInternalPopupMenuNameKey		kHiDPIStringPrefix	"kHiDPIInternalPopupMenuNameKey_j"
#define kHiDPITargetMenuPath				kHiDPIInternalPopupMenuNameKey

#define kHiDPIAboutThisMenuItemPosition			1.0                                 // Menu item position

#define kHiDPIIconRsrcID    1000  

// Data format version numbers
#define kHiDPIFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kHiDPIFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kHiDPICurrentMajorFormatNumber kHiDPIFirstMajorFormatNumber                 // most recent major format change
#define kHiDPICurrentMinorFormatNumber kHiDPIFirstMinorFormatNumber                 // most recent minor format change

#endif // __HiDPIID_h__

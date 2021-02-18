//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basictextadornment/BscTAID.h $
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
//  Defines IDs used by the BasicTextAdornment plug-in.
//  
//========================================================================================

#ifndef __BscTAID_h__
#define __BscTAID_h__

#include "SDKDef.h"

// Company:
#define kBscTACompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kBscTACompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kBscTAPluginName	"BasicTextAdornment"					// Name of this plug-in.
#define kBscTAPrefixNumber	0x55100 					// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kBscTAVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kBscTAAuthor		"Adobe Developer Technologies"				// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kBscTAPrefixNumber above to modify the prefix.)
#define kBscTAPrefix		RezLong(kBscTAPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kBscTAStringPrefix	SDK_DEF_STRINGIZE(kBscTAPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kBscTAMissingPluginURLValue			kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kBscTAMissingPluginAlertValue		kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kBscTAPluginID, kBscTAPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kBscTAActionComponentBoss,	kBscTAPrefix + 0)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscTAStringRegisterBoss,	kBscTAPrefix + 1)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscTAMenuRegisterBoss,		kBscTAPrefix + 2)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscTAActionRegisterBoss,	kBscTAPrefix + 3)
DECLARE_PMID(kClassIDSpace, kBscTAAttrBoss,			kBscTAPrefix + 4)
DECLARE_PMID(kClassIDSpace, kBscTAAdornmentBoss,	kBscTAPrefix + 5)
DECLARE_PMID(kClassIDSpace, kBscTANewDocResponderBoss,	kBscTAPrefix + 6)
DECLARE_PMID(kClassIDSpace, kBscTAOpenDocResponderBoss,	kBscTAPrefix + 7)
DECLARE_PMID(kClassIDSpace, kBscTAErrorStringServiceBoss,		kBscTAPrefix + 8)   
DECLARE_PMID(kClassIDSpace, kBscTAScriptProviderBoss,			kBscTAPrefix +  9)
 

// InterfaceIDs:
// None in this plug-in.

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kBscTAActionComponentImpl,	kBscTAPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kBscTAAttrReportImpl,	kBscTAPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kBscTAAdornmentImpl,	kBscTAPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kBscTADocResponderImpl,	kBscTAPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kBscTAErrorStringServiceImpl,	kBscTAPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kBscTAScriptProviderImpl,	kBscTAPrefix + 5)


// ActionIDs:
DECLARE_PMID(kActionIDSpace, kBscTAAboutActionID,				kBscTAPrefix + 0)
DECLARE_PMID(kActionIDSpace, kBscTAAddTextAdornmentActionID,	kBscTAPrefix + 1)
DECLARE_PMID(kActionIDSpace, kBscTARemoveTextAdornmentActionID,	kBscTAPrefix + 2)

// WidgetIDs:
//none

//ScriptInfoIDs:
DECLARE_PMID(kScriptInfoIDSpace, kBscTAShadePropertyScriptElement,				kBscTAPrefix + 0)

// ErrorIDs:
DECLARE_PMID(kErrorIDSpace, kBscTAFailureErrorCode,							kBscTAPrefix + 0)
DECLARE_PMID(kErrorIDSpace, kBscTADataAccessErrorCode,				kBscTAPrefix + 1)

// Error string keys:
#define kBscTAFailureErrorCodeStringKey			kBscTAStringPrefix "kBscTAFailureErrorCodeStringKey"
#define kBscTADataAccessErrorCodeStringKey	kBscTAStringPrefix "kBscTADataAccessErrorCodeStringKey"

// "About Plug-ins" sub-menu:
#define kBscTAAboutMenuKey			kBscTAStringPrefix "kBscTAAboutMenuKey"
#define kBscTAAboutMenuPath			kSDKDefStandardAboutMenuPath kBscTACompanyKey

// "Plug-ins" sub-menu:
#define kBscTAPluginsMenuKey 		kBscTAStringPrefix "kBscTAPluginsMenuKey"
#define kBscTAPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kBscTACompanyKey kSDKDefDelimitMenuPath kBscTAPluginsMenuKey

// Menu item keys:
#define kBscTAAddTextAdornmentMenuItemKey		kBscTAStringPrefix "kBscTAAddTextAdornmentMenuItemKey"
#define kBscTARemoveTextAdornmentMenuItemKey	kBscTAStringPrefix "kBscTARemoveTextAdornmentMenuItemKey"

// Other StringKeys:
#define kBscTAAboutBoxStringKey				kBscTAStringPrefix "kBscTAAboutBoxStringKey"
#define kBscTAAddTextAdornmentStringKey		kBscTAStringPrefix "kBscTAAddTextAdornmentStringKey"
#define kBscTARemoveTextAdornmentStringKey	kBscTAStringPrefix "kBscTARemoveTextAdornmentStringKey"
#define kBscTACharAttrDescrStringKey		kBscTAStringPrefix "kBscTACharAttrDescrString"

#define kBscTATargetMenuPath kBscTAPluginsMenuPath

// Menu item positions:
#define kBscTAAddTextAdornmentMenuItemPosition			1.0
#define kBscTARemoveTextAdornmentMenuItemPosition		2.0	

// Initial Data format IDs of the persistent data was first introduced in InDesign 2.0
#define kBscTAInitialMajorFormat		kSDKDef_20_PersistMajorVersionNumber
#define kBscTAInitialMinorFormat		kSDKDef_20_PersistMinorVersionNumber
// Note: The data format has not been changed since InDesign 2.0.

// Format IDs for the PluginVersion resource 
#define kBscTALastMajorFormatChange	kBscTAInitialMajorFormat		// Last major format change
#define kBscTALastMinorFormatChange	kBscTAInitialMinorFormat		// Last minor format change


#endif // __BscTAID_h__
//  Generated by Dolly build 17: template "IfPanelMenu".
// End, BscTAID.h.



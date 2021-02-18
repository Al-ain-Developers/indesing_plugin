//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffect/TranFxID.h $
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
//========================================================================================

#ifndef __TranFxID_h__
#define __TranFxID_h__

#include "SDKDef.h"

// Company:
#define kTranFxCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kTranFxCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kTranFxPluginName	"TransparencyEffect"			// Name of this plug-in.
#define kTranFxPrefixNumber	0x5c1e0 						// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kTranFxVersion		kSDKDefPluginVersionString							// Version of this plug-in (for the About Box).
#define kTranFxAuthor		"Adobe Developer Technologies"	// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kTranFxPrefixNumber above to modify the prefix.)
#define kTranFxPrefix		RezLong(kTranFxPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kTranFxStringPrefix	SDK_DEF_STRINGIZE(kTranFxPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kTranFxMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kTranFxMissingPluginAlertValue		kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kTranFxPluginID, kTranFxPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace,	kTranFxAdornmentBoss,			kTranFxPrefix + 0)
DECLARE_PMID(kClassIDSpace, kTranFxOffsetXAttrBoss,			kTranFxPrefix + 1)
DECLARE_PMID(kClassIDSpace, kTranFxOffsetYAttrBoss,			kTranFxPrefix + 2)
DECLARE_PMID(kClassIDSpace, kTranFxUseBlackAsOpaqueAttrBoss,		kTranFxPrefix + 3)
DECLARE_PMID(kClassIDSpace, kTranFxUseAlphaAttrBoss,		kTranFxPrefix + 4)
DECLARE_PMID(kClassIDSpace, kTranFxUseBlurAttrBoss,			kTranFxPrefix + 5)
// Gap for future expansion of custom graphic attributes.
DECLARE_PMID(kClassIDSpace, kTranFxCloseDocResponderBoss,	kTranFxPrefix + 10)
DECLARE_PMID(kClassIDSpace, kTranFxScriptProviderBoss,		kTranFxPrefix + 11)
DECLARE_PMID(kClassIDSpace, kTranFxErrorStringServiceBoss,	kTranFxPrefix + 12)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANFXSUITE,	kTranFxPrefix + 0)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kTranFxSuiteASBImpl,				kTranFxPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kTranFxSuiteLayoutCSBImpl,			kTranFxPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kTranFxAdornmentImpl,				kTranFxPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kTranFxFlattenerUsageImpl,			kTranFxPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kTranFxGraphicAttributeInfoImpl,	kTranFxPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kTranFxResponderImpl,				kTranFxPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kTranFxScriptProviderImpl,			kTranFxPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kTranFxErrorStringServiceImpl,		kTranFxPrefix + 7)

// ScriptingIDs:
DECLARE_PMID(kScriptInfoIDSpace, kTranFxModeEnumScriptElement,				kTranFxPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kTranFxModePropertyScriptElement,			kTranFxPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kTranFxOffsetXPropertyScriptElement,		kTranFxPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kTranFxOffsetYPropertyScriptElement,		kTranFxPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kTranFxUseBlackAsOpaquePropertyScriptElement,	kTranFxPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kTranFxUseAlphaPropertyScriptElement,		kTranFxPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kTranFxUseBlurPropertyScriptElement,		kTranFxPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kTranFxSettingsObjectScriptElement,		kTranFxPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kTranFxSettingsPropertyScriptElement,		kTranFxPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kTranFxSettingsINXPoliciesMetadataScriptElement,	kTranFxPrefix + 9)


// ErrorIDs:
DECLARE_PMID(kErrorIDSpace, kTranFxGenericFailureErrorCode,				kTranFxPrefix + 0)
// Error StringKeys:
#define kTranFxGenericFailureErrorCodeStringKey					kTranFxStringPrefix "kTranFxGenericFailureErrorCodeStringKey"

// Initial Data format IDs of the persistent data was first introduced in InDesign CS 
#define kTranFxInitialMajorFormat		kSDKDef_30_PersistMajorVersionNumber
#define kTranFxInitialMinorFormat		kSDKDef_30_PersistMinorVersionNumber

// Format IDs for the PluginVersion resource 
#define kTranFxLastMajorFormatChange	kTranFxInitialMajorFormat		// Last major format change
#define kTranFxLastMinorFormatChange	kTranFxInitialMinorFormat		// Last minor format change


// Initial version for VersionedScriptElementInfo resource
#define kTranFxFirstScriptVersion	kCS2ScriptVersion


#endif // __TranFxID_h__

//  Generated by Dolly build 17: template "IfPanelMenu".
// End, TranFxID.h.



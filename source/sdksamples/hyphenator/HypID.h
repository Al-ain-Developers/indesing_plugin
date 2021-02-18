//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hyphenator/HypID.h $
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

#ifndef __HypID_h__
#define __HypID_h__

#include "SDKDef.h"

// Company:
#define kHypCompanyKey		kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kHypCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kHypPluginName		"Hyphenator"			// Name of this plug-in.
#define kHypPrefixNumber	0x67020 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kHypVersion			kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kHypAuthor			"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kHypPrefixNumber above to modify the prefix.)
#define kHypPrefix			RezLong(kHypPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kHypStringPrefix	SDK_DEF_STRINGIZE(kHypPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kHypPluginID, kHypPrefix + 0)

// ClassIDs:
//DECLARE_PMID(kClassIDSpace, kHypActionComponentBoss,		kHypPrefix + 0)// kept here for record keeping purposes (Do not reuse this ID!)
DECLARE_PMID(kClassIDSpace, kHypLinguisticServiceBoss,		kHypPrefix + 4)
DECLARE_PMID(kClassIDSpace, kHypHyphenationServiceBoss,		kHypPrefix + 5)
DECLARE_PMID(kClassIDSpace, kHypServiceProviderBoss,		kHypPrefix + 6)
DECLARE_PMID(kClassIDSpace, kHypScriptProviderBoss,			kHypPrefix + 7)

// InterfaceIDs:

// ImplementationIDs:
//DECLARE_PMID(kImplementationIDSpace, kHypActionComponentImpl,		kHypPrefix + 0)// kept here for record keeping purposes (Do not reuse this ID!)
DECLARE_PMID(kImplementationIDSpace, kHypServiceProviderImpl,		kHypPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kHypHyphenationMgrImpl,		kHypPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kHypHyphenationServiceImpl,	kHypPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kHypPerformanceMetricImpl,		kHypPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kHypScriptProviderImpl,		kHypPrefix + 5)

// performance IDs
DECLARE_PMID(kPerformanceMetricIDSpace,	kHypMetricMaxID,	kHypPrefix + 1)
DECLARE_PMID(kPerformanceMetricIDSpace,	kHypMetricTotalID,	kHypPrefix + 2)

//Script Element IDs
DECLARE_PMID(kScriptInfoIDSpace, kHypMaxPropertyScriptElement, kHypPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kHypTotalPropertyScriptElement, kHypPrefix + 2)

// scripting defs
enum HypScriptIDs
{
	//	en_HypPerformanceMetricsSelector	= 'hppm',
	p_HypMax							= 'hpmx',
	p_HypTotal							= 'hptt',
};

// Linguistic service provider name
#define kHypLinguisticServiceName		kHypStringPrefix "kHypLinguisticServiceName"

// Languages:
//	No new language names are introduced by this plug-in.
//	Check out the notes in the body of HypAdapter.cpp if you need
//	to add languages the application is not aware of.

// Initial data format version numbers
#define kHypFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kHypFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kHypCurrentMajorFormatNumber kHypFirstMajorFormatNumber // most recent major format change
#define kHypCurrentMinorFormatNumber kHypFirstMinorFormatNumber // most recent minor format change

#endif // __HypID_h__

// End, HypID.h.



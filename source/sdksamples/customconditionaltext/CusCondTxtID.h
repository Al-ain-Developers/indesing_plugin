//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltext/CusCondTxtID.h $
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

#ifndef __CusCondTxtID_h__
#define __CusCondTxtID_h__

#include "SDKDef.h"

// Company:
#define kCusCondTxtCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kCusCondTxtCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kCusCondTxtPluginName	"CustomConditionalText"			// Name of this plug-in.
#define kCusCondTxtPrefixNumber	0x12ad00 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kCusCondTxtVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kCusCondTxtAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kCusCondTxtPrefixNumber above to modify the prefix.)
#define kCusCondTxtPrefix		RezLong(kCusCondTxtPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kCusCondTxtStringPrefix	SDK_DEF_STRINGIZE(kCusCondTxtPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kCusCondTxtMissingPluginURLValue	kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kCusCondTxtMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kCusCondTxtPluginID, kCusCondTxtPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kCusCondTxtChangeCmdBoss, kCusCondTxtPrefix + 3)
DECLARE_PMID(kClassIDSpace, kCusCondTxtScriptProviderBoss, kCusCondTxtPrefix + 4)
DECLARE_PMID(kClassIDSpace, kCusCondTxtResponderServiceBoss, kCusCondTxtPrefix + 9)
DECLARE_PMID(kClassIDSpace, kCusCondPrintSetupProviderBoss, kCusCondTxtPrefix + 10)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMCONDITIONTAG, kCusCondTxtPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSCONDTXTPRINTVISIBLE, kCusCondTxtPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSCONDTXTIDMLVISIBLE, kCusCondTxtPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSCONDTXTSUITE, kCusCondTxtPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSCONDTURNOFFSTATE, kCusCondTxtPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSCONDTXTFACADE, kCusCondTxtPrefix + 5)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtTagImpl, kCusCondTxtPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtTagChangeCmdImpl, kCusCondTxtPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtPrintVisibleImpl, kCusCondTxtPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtIdmlVisibleImpl, kCusCondTxtPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtSuiteASBImpl, kCusCondTxtPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtSuiteTextCSBImpl, kCusCondTxtPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtScriptProviderImpl, kCusCondTxtPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtTreeViewHierarchyAdapterImpl, kCusCondTxtPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtServiceProviderImpl, kCusCondTxtPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtResponderImpl, kCusCondTxtPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtTurnOffStateImpl, kCusCondTxtPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtPrintSetupProviderImpl, kCusCondTxtPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtFacadeImpl, kCusCondTxtPrefix + 12)


// ScriptInfoIDs:
DECLARE_PMID(kScriptInfoIDSpace, kCusCondTxtPrintVisibleElement, kCusCondTxtPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kCusCondTxtIdmlVisibleElement, kCusCondTxtPrefix + 1)

// Other StringKeys:
#define kCusCondTxtCommandStringKey 	kCusCondTxtStringPrefix "kCusCondTxtCommandStringKey"


// Initial data format version numbers
#define kCusCondTxtFirstMajorFormatNumber  RezLong(1)
#define kCusCondTxtFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kCusCondTxtCurrentMajorFormatNumber kCusCondTxtFirstMajorFormatNumber
#define kCusCondTxtCurrentMinorFormatNumber kCusCondTxtFirstMinorFormatNumber

#endif // __CusCondTxtID_h__

//  Code generated by DollyXs code generator

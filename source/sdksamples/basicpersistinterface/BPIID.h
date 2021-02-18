//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterface/BPIID.h $
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
//  Defines IDs used by the BPI plug-in.
//  
//========================================================================================

#ifndef __BPIID_h__
#define __BPIID_h__

#include "SDKDef.h"

// Company:
#define kBPICompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kBPICompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kBPIPluginName	"BasicPersistInterface"			// Name of this plug-in.
#define kBPIPrefixNumber	0x58000 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kBPIVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kBPIAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kBPIPrefixNumber above to modify the prefix.)
#define kBPIPrefix		RezLong(kBPIPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kBPIStringPrefix	SDK_DEF_STRINGIZE(kBPIPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kBPIPluginID, kBPIPrefix + 0)

// ClassIDs:
//DECLARE_PMID(kClassIDSpace, kBPIActionComponentBoss,	kBPIPrefix + 0)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBPIStringRegisterBoss,	kBPIPrefix + 1)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBPIPanelRegisterBoss,	kBPIPrefix + 2)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBPIMenuRegisterBoss,		kBPIPrefix + 3)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBPIActionRegisterBoss,	kBPIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kBPISetDataCmdBoss,	kBPIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kBPISuiteRegisterBoss, kBPIPrefix + 9)
DECLARE_PMID(kClassIDSpace, kBPINewDocResponderBoss, kBPIPrefix + 10)
DECLARE_PMID(kClassIDSpace, kBPIOpenDocResponderBoss, kBPIPrefix + 11)
DECLARE_PMID(kClassIDSpace, kBPINewPIResponderBoss,	kBPIPrefix + 12)
DECLARE_PMID(kClassIDSpace, kBPIPrefsScriptProviderBoss, kBPIPrefix + 13)   
DECLARE_PMID(kClassIDSpace, kBPIScriptProviderBoss,	kBPIPrefix + 14)
DECLARE_PMID(kClassIDSpace, kBPIErrorStringServiceBoss,		kBPIPrefix + 15)    
DECLARE_PMID(kClassIDSpace, kBPIConversionProviderBoss,		kBPIPrefix + 16)
    
// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IBPIDATA, kBPIPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_IBPISUITE, kBPIPrefix + 1)	

// ImplementationIDs:
// No dialog widgets really need dynamic handling DECLARE_PMID(kImplementationIDSpace, kBPIDlgObserverImpl, kBPIPrefix + 2)	
DECLARE_PMID(kImplementationIDSpace, kBPISetDataCmdImpl, kBPIPrefix + 3)	
DECLARE_PMID(kImplementationIDSpace, kBPIDataPersistImpl, kBPIPrefix + 4)	
DECLARE_PMID(kImplementationIDSpace, kBPIDataImpl, kBPIPrefix + 5)	
DECLARE_PMID(kImplementationIDSpace, kBPIDocObserverImpl, kBPIPrefix + 7)	
DECLARE_PMID(kImplementationIDSpace, kBPISuiteASBImpl, kBPIPrefix + 8)	
DECLARE_PMID(kImplementationIDSpace, kBPISuiteLayoutCSBImpl, kBPIPrefix + 9)	
DECLARE_PMID(kImplementationIDSpace, kBPISuiteLayoutSelectionExtImpl, kBPIPrefix + 10)	
// The ASB selection extension was not needed DECLARE_PMID(kImplementationIDSpace, kBPISuiteASBSelectionExtImpl, kBPIPrefix + 11)	
DECLARE_PMID(kImplementationIDSpace, kBPISuiteTextCSBImpl, kBPIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kBPISuiteTextSelectionExtImpl, kBPIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kBPISuiteDefaultCSBImpl, kBPIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kBPISuiteDefaultSelectionExtImpl, kBPIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kBPIDefaultResponderImpl, kBPIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kBPIPrefsScriptProviderImpl,		kBPIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kBPIScriptProviderImpl,			kBPIPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kBPIErrorStringServiceImpl,		kBPIPrefix + 19)

//ScriptInfoIDs:
DECLARE_PMID(kScriptInfoIDSpace, kBPIPrefObjectScriptElement,				kBPIPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kBPIPrefObjectPropertyScriptElement,		kBPIPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kBPIDataPropertyScriptElement,				kBPIPrefix + 2)

// ErrorIDs:
DECLARE_PMID(kErrorIDSpace, kBPIFailureErrorCode,			kBPIPrefix + 0)
DECLARE_PMID(kErrorIDSpace, kBPIDataAccessErrorCode,		kBPIPrefix + 1)

// Error string keys:
#define kBPIFailureErrorCodeErrorCodeStringKey		kBPIStringPrefix "kBPIFailureErrorCodeErrorCodeStringKey"
#define kBPIDataAccessErrorCodeStringKey		kBPIStringPrefix "kBPIDataAccessErrorCodeStringKey"

// "About Plug-ins" sub-menu:
#define kBPIAboutMenuKey			kBPIStringPrefix "kBPIAboutMenuKey"
#define kBPIAboutMenuPath			kSDKDefStandardAboutMenuPath kBPICompanyKey

#define kBPICommandStringKey			kBPIStringPrefix "kBPICommandStringKey"

// Other StringKeys:
#define kBPIAboutBoxStringKey				kBPIStringPrefix "kBPIAboutBoxStringKey"
#define kBPIInternalPopupMenuNameKey		kBPIStringPrefix	"kBPIInternalPopupMenuNameKey"
#define kBPINoValidPageItemsSelectedKey		kBPIStringPrefix "kBPINoValidPageItemsSelectedKey"
#define kBPISetBPIDataCmdFailedKey		kBPIStringPrefix "kBPISetBPIDataCmdFailedKey"
#define kBPIDefaultStringKey		kBPIStringPrefix "kBPISetBPIDefaultStringKey"

// Initial data format version numbers: the persistent data for this plug-in
// introduced in pre-release versions of the InDesign 2.0 SDK
#define kBPIInitialMajorFormat		2
#define kBPIInitialMinorFormat		1

// InDesign CS4 format changes
#define kBPIStoreWideStringMajorFormat		kSDKDef_50_PersistMajorVersionNumber
#define kBPIStoreWideStringMinorFormat		1

// Data format version numbers for the PluginVersion resource 
#define kBPILastMajorFormatChange	kBPIStoreWideStringMajorFormat		// Most recent major format change
#define kBPILastMinorFormatChange	kBPIStoreWideStringMinorFormat		// Most recent minor format change

// Schema field IDs:
#define kBPIPersistentVersion 0
#define kBPIData 1

// other constants
#define kBPIDefaultPersistentVersion 1
#define kBPIDefaultData ""

#endif // __BPIID_h__

// End, BPIID.h.





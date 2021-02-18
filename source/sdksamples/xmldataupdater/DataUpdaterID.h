//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdater/DataUpdaterID.h $
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

#ifndef __DataUpdaterID_h__
#define __DataUpdaterID_h__

#include "SDKDef.h"

// Company:
#define kDataUpdaterCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kDataUpdaterCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kDataUpdaterPluginName	"XMLDataUpdater"			// Name of this plug-in.
#define kDataUpdaterPrefixNumber	0xd9a00 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).Corresponding UI plugin 0xd9b00
#define kDataUpdaterVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kDataUpdaterAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kDataUpdaterPrefixNumber above to modify the prefix.)
#define kDataUpdaterPrefix		RezLong(kDataUpdaterPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kDataUpdaterStringPrefix	SDK_DEF_STRINGIZE(kDataUpdaterPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kDataUpdaterMissingPluginURLValue			kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kDataUpdaterMissingPluginAlertValue		kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kDataUpdaterPluginID, kDataUpdaterPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kDataUpdaterErrorStringServiceBoss,		kDataUpdaterPrefix + 1)
DECLARE_PMID(kClassIDSpace, kDataUpdaterExportHandlerBoss,		kDataUpdaterPrefix + 2)
DECLARE_PMID(kClassIDSpace, kDataUpdaterDOMSerializerHandlerBoss,		kDataUpdaterPrefix + 3)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IDATAUPDATERSUITE, kDataUpdaterPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IDATAUPDATERFACADE, kDataUpdaterPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IDATAUPDATERPARSINGCONTEXT, kDataUpdaterPrefix + 3)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kDataUpdaterSuiteASBImpl,					kDataUpdaterPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kDataUpdaterSuiteTextCSBImpl,				kDataUpdaterPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kDataUpdaterFacadeImpl,					kDataUpdaterPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kDataUpdaterErrorStringServiceImpl,		kDataUpdaterPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kDataUpdaterExportHandlerImpl,		kDataUpdaterPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kDataUpdaterDOMSerializerHandlerImpl,		kDataUpdaterPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kDataUpdaterParsingContextImpl,		kDataUpdaterPrefix + 7)


// ErrorIDs:
DECLARE_PMID(kErrorIDSpace, kDataUpdaterFailureErrorCode,						kDataUpdaterPrefix + 0)
DECLARE_PMID(kErrorIDSpace, kDataUpdaterDataAccessErrorCode,					kDataUpdaterPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kDataUpdaterOpenFileErrorCode,						kDataUpdaterPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kDataUpdaterFileFormatErrorCode,					kDataUpdaterPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kDataUpdaterTargetStoryLockedErrorCode,			kDataUpdaterPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kDataUpdaterTargetTextAlreadyTaggedErrorCode,		kDataUpdaterPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kDataUpdaterBadTargetTextLengthErrorCode,			kDataUpdaterPrefix + 6)


// Other StringKeys:
#define kDataUpdaterInsertSequenceStringKey 					kDataUpdaterStringPrefix "kDataUpdaterInsertSequenceStringKey"
#define kDataUpdaterMergeSequenceStringKey 					kDataUpdaterStringPrefix "kDataUpdaterMergeSequenceStringKey"
#define kDataUpdaterInsertAllSequenceStringKey 				kDataUpdaterStringPrefix "kDataUpdaterInsertAllSequenceStringKey"

// Error StringKeys:
#define kDataUpdaterFailureErrorCodeStringKey					kDataUpdaterStringPrefix "kDataUpdaterFailureErrorCodeStringKey"
#define kDataUpdaterDataAccessErrorCodeStringKey				kDataUpdaterStringPrefix "kDataUpdaterDataAccessErrorCodeStringKey"
#define kDataUpdaterOpenFileErrorCodeStringKey					kDataUpdaterStringPrefix "kDataUpdaterOpenFileErrorCodeStringKey"
#define kDataUpdaterFileFormatErrorCodeStringKey				kDataUpdaterStringPrefix "kDataUpdaterFileFormatErrorCodeStringKey"
#define kDataUpdaterTargetStoryLockedErrorCodeStringKey		kDataUpdaterStringPrefix "kDataUpdaterTargetStoryLockedErrorCode"
#define kDataUpdaterTargetTextAlreadyTaggedErrorCodeStringKey	kDataUpdaterStringPrefix "kDataUpdaterTargetTextAlreadyTaggedErrorCode"
#define kDataUpdaterBadTargetTextLengthErrorCodeStringKey		kDataUpdaterStringPrefix "kDataUpdaterBadTargetTextLengthErrorCode"

// Initial data format version numbers
#define kDataUpdaterFirstMajorFormatNumber  kSDKDef_50_PersistMajorVersionNumber
#define kDataUpdaterFirstMinorFormatNumber  kSDKDef_50_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource
#define kDataUpdaterCurrentMajorFormatNumber kDataUpdaterFirstMajorFormatNumber // most recent major format change
#define kDataUpdaterCurrentMinorFormatNumber kDataUpdaterFirstMinorFormatNumber // most recent minor format change



#endif // __DataUpdaterID_h__

// End, DataUpdaterID.h.



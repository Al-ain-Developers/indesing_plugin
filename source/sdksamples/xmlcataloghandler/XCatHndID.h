//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmlcataloghandler/XCatHndID.h $
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

#ifndef __XCatHndID_h__
#define __XCatHndID_h__

#include "SDKDef.h"

// Company:
#define kXCatHndCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kXCatHndCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kXCatHndPluginName	"XMLCatalogHandler"			// Name of this plug-in.
#define kXCatHndPrefixNumber	0x55900 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kXCatHndVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kXCatHndAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kXCatHndPrefixNumber above to modify the prefix.)
#define kXCatHndPrefix		RezLong(kXCatHndPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kXCatHndStringPrefix	SDK_DEF_STRINGIZE(kXCatHndPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kXCatHndPluginID, kXCatHndPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kXCatHndSAXContentHandlerServiceBoss,	kXCatHndPrefix + 0)
DECLARE_PMID(kClassIDSpace, kXCatHndEntityResolverBoss,				kXCatHndPrefix + 1)
DECLARE_PMID(kClassIDSpace, kXCatHndChangeEntityMappingCmdBoss,		kXCatHndPrefix + 2)
DECLARE_PMID(kClassIDSpace, kXCatHndAcquirerFilterServiceBoss,		kXCatHndPrefix + 3)
DECLARE_PMID(kClassIDSpace, kXCatHndStartupShutdownServiceBoss,		kXCatHndPrefix + 4)
DECLARE_PMID(kClassIDSpace, kXCatHndErrorStringServiceBoss,			kXCatHndPrefix + 5)



// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IXCATHNDPARSINGCONTEXT,		kXCatHndPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_IXCATHNDCURRENTCATALOGFILE,	kXCatHndPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IXCATHNDENTITYMAPPING,		kXCatHndPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IXCATHNDFACADE,				kXCatHndPrefix + 4)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kXCatHndSAXContentHandlerImpl,		kXCatHndPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kXCatHndParsingContextImpl,		kXCatHndPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kXCatHndEntityResolverImpl,		kXCatHndPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kXCatHndEntityMappingImpl,			kXCatHndPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kXCatHndChangeEntityMappingCmdImpl,	kXCatHndPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kXCatHndFacadeImpl,				kXCatHndPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kXCatHndAcquirerFilterImpl,		kXCatHndPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kXCatHndStartupShutdownImpl,		kXCatHndPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kXCatHndErrorStringServiceImpl,	kXCatHndPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kXCatHndAcquirerXMLImportPrefsImpl,	kXCatHndPrefix + 9)

// ActionIDs:

// ErrorIDs:

//<ErrorIDs>:
DECLARE_PMID(kErrorIDSpace, kXCatHndFailedLoadingDefaultCatalogErr,		kXCatHndPrefix + 0)
DECLARE_PMID(kErrorIDSpace, kXCatHndNoDefaultCatalogErr,				kXCatHndPrefix + 1)

// Other StringKeys:
#define kXCatHndInvalidCatalogFileKey	kXCatHndStringPrefix "kXCatHndInvalidCatalogFileKey"
#define kXCatHndChangeEntityMappingKey kXCatHndStringPrefix "kXCatHndChangeEntityMappingKey"
#define kXCatHndFailedLoadingDefaultCatalogErrKey	kXCatHndStringPrefix "kXCatHndFailedLoadingDefaultCatalogErrKey"
#define kXCatHndNoDefaultCatalogErrKey	kXCatHndStringPrefix "kXCatHndNoDefaultCatalogErrKey"
// Has to be something that can be an XML element name, so we reverse the order of prefix and str
#define kXCatHndAcquirerXMLImportPrefsKey	"kXCatHndAcquirerXMLImportPrefsKey"  kXCatHndStringPrefix
// Miscellaneous values
#define kXCatHndDefaultXMLCatalogFileName "catalog.xcat"
#define kXCatHndErrorStringTableRsrcID 1301
// Persistence related
// Initial data format 1,0
#define kXCatHndInitialMajorFormat		1
#define kXCatHndInitialMinorFormat		0
// Format IDs for the PluginVersion resource 
#define kXCatHndLastMajorFormatChange	kXCatHndInitialMajorFormat		// Last major format change
#define kXCatHndLastMinorFormatChange	kXCatHndInitialMinorFormat		// Last minor format change
// Info that plug-in binary needs to make its version  details known at OS level
#define kXCatHndVersionStr	SDK_DEF_MAKE_VERSIONSTRING(kSDKDefPlugInMajorVersionNumberForResource, kSDKDefPlugInMinorVersionNumberForResource, kSDKDefPlugInStepVersionNumberForResource, kBuildNumber)

#endif // __XCatHndID_h__

//  Code generated by DollyXS code generator

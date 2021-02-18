//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/TaggedTextFiltersID.h $
//  
//  Owner: Rahul Shinde
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
//  Contains IDs used by the TaggedTextImportFilter plug-in
//  
//========================================================================================

#ifndef __TaggedTextFiltersID__
#define __TaggedTextFiltersID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define kTaggedTextFiltersPrefix	 RezLong(0x8a00)


// Plugin ID 
#define kTaggedTextFiltersPluginName   "Tagged Text Filters" 
DECLARE_PMID(kPlugInIDSpace, kTaggedTextFiltersPluginID, kTaggedTextFiltersPrefix + 1)
//All class IDs and implementation IDs for the plug-in are added in this file

//<Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_ITAGGEDTEXTIMPORTPREFERENCES, kTaggedTextFiltersPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ITAGGEDTEXTPARSERUTILS, kTaggedTextFiltersPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ITAGGEDTEXTERRORLIST, kTaggedTextFiltersPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ITAGGEDTEXTSUITE, kTaggedTextFiltersPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ITAGGEDTEXTEXPORTPREFSSETUP, kTaggedTextFiltersPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ITAGGEDTEXTIMPORTPREFSSETUP, kTaggedTextFiltersPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ITAGGEDTEXTWANRINGHANDLER, kTaggedTextFiltersPrefix + 16)

//<Class ID>
DECLARE_PMID(kClassIDSpace, kTaggedTextImportFilterBoss, kTaggedTextFiltersPrefix + 1)
//gap
DECLARE_PMID(kClassIDSpace, kTaggedTextImportServiceProviderBoss, kTaggedTextFiltersPrefix + 3)
//gap
//gap
//gap
//gap
//gap
//gap
//gap
//gap
DECLARE_PMID(kClassIDSpace, kTaggedTextConversionProviderBoss, kTaggedTextFiltersPrefix + 18)
DECLARE_PMID(kClassIDSpace, kSetTaggedTextImportPrefsCmdBoss, kTaggedTextFiltersPrefix + 19)

// ---- Moved from Tagged Text Filters UI plug-in
DECLARE_PMID(kClassIDSpace, kTaggedTextExportFilterBoss, kTaggedTextFiltersPrefix + 20)
// ---- end move.

//<Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kTaggedTextImportFilter, kTaggedTextFiltersPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextParserUtilsImpl, kTaggedTextFiltersPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextImportServiceProvider, kTaggedTextFiltersPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextImportFilterPreferences, kTaggedTextFiltersPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextErrorListImpl, kTaggedTextFiltersPrefix + 5)
//gap
//gap
//gap
//gap
//gap
//gap
//gap
//gap
//gap
DECLARE_PMID(kImplementationIDSpace, kTaggedTextWarningListWidgetObserver, kTaggedTextFiltersPrefix + 14)

DECLARE_PMID(kImplementationIDSpace, kSetTaggedTextImportPrefsCmdImpl, kTaggedTextFiltersPrefix + 16)

// ---- Moved from Tagged Text Filters UI plug-in
DECLARE_PMID(kImplementationIDSpace, kTaggedTextExportFilter, kTaggedTextFiltersPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextSuiteASBImpl, kTaggedTextFiltersPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextSuiteTextCSBImpl, kTaggedTextFiltersPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextExportPreferences, kTaggedTextFiltersPrefix + 20)
// ---- end move.

DECLARE_PMID(kImplementationIDSpace, kTaggedTextWarningServiceImpl, kTaggedTextFiltersPrefix + 21)

//<Service ID>
DECLARE_PMID(kServiceIDSpace, kTaggedTextWarningService, kTaggedTextFiltersPrefix + 1)

//<Widget ID>

//Resource IDs
#define kTaggedTextFiltersStringsRsrcID					1000
#define kTaggedTextFiltersErrStringsRsrcID				1100
#define kTaggedTextFiltersStringsNoTransRsrcID			1200

#endif // __TaggedTextFiltersID__

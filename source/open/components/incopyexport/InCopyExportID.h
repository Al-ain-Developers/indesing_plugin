//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyexport/InCopyExportID.h $
//  
//  Owner: Jon Pugh
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

#ifndef __InCopyExportID__
#define __InCopyExportID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kInCopyExportPrefix	 RezLong(0x17000)		// Reserved in "AdobePrefix.h"

// <PlugInID>
//------------------------------------------------------------------------------------------------
//	PlugInID
//------------------------------------------------------------------------------------------------
#define kInCopyExportPluginName 			"InCopyExport"
DECLARE_PMID(kPlugInIDSpace, kInCopyExportPluginID,					kInCopyExportPrefix + 1)


// <Class ID>
//------------------------------------------------------------------------------------------------
//	ClassIDs
//------------------------------------------------------------------------------------------------

DECLARE_PMID(kClassIDSpace, kInCopyExportStringRegisterBoss, kInCopyExportPrefix + 1 )
DECLARE_PMID(kClassIDSpace, kInCopyStoryExportBoss, kInCopyExportPrefix + 2 )
// Gap
DECLARE_PMID(kClassIDSpace, kICExportPrefsScriptProviderBoss, kInCopyExportPrefix + 5 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 6 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 7 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 8 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 9 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 10 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 11 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 12 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 13 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 14 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 15 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 16 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 17 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 18 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 19 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 20 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 21 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 22 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 23 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 24 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kInCopyExportPrefix + 25 )


// <Interface ID>
//---------------------------------------------------------------
//	IIDs
//---------------------------------------------------------------

// Moved to InCopyWorkflowID.h
// DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYEXPORTSUITE, kInCopyExportPrefix + 1 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 2 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 3 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 4 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 5 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 6 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 7 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 8 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 9 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 10 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 11 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 12 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 13 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 14 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 15 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 16 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 17 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 18 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 19 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 20 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 21 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 22 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 23 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 24 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kInCopyExportPrefix + 25 )

// <Implementation ID>
//---------------------------------------------------------------
//	ImplementationIDs
//---------------------------------------------------------------

DECLARE_PMID(kImplementationIDSpace, kInCopyStoryExportProviderImpl,	kInCopyExportPrefix + 1 )
// Gap
DECLARE_PMID(kImplementationIDSpace, kICExportSuiteASBImpl, kInCopyExportPrefix + 3 )
DECLARE_PMID(kImplementationIDSpace, kICExportSuiteTextImpl, kInCopyExportPrefix + 4 )
DECLARE_PMID(kImplementationIDSpace, kICExportSuiteLayoutImpl, kInCopyExportPrefix + 5 )
DECLARE_PMID(kImplementationIDSpace, kICExportSuiteDefaultImpl, kInCopyExportPrefix + 6 )
DECLARE_PMID(kImplementationIDSpace, kICExportSuiteTableImpl, kInCopyExportPrefix + 7 )
// Gap
DECLARE_PMID(kImplementationIDSpace, kICExportPrefsScriptProviderImpl, kInCopyExportPrefix + 10 )
// Gap
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kInCopyExportPrefix + 13 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kInCopyExportPrefix + 14 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kInCopyExportPrefix + 15 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kInCopyExportPrefix + 16 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kInCopyExportPrefix + 17 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kInCopyExportPrefix + 18 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kInCopyExportPrefix + 19 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kInCopyExportPrefix + 20 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kInCopyExportPrefix + 21 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kInCopyExportPrefix + 22 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kInCopyExportPrefix + 23 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kInCopyExportPrefix + 24 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kInCopyExportPrefix + 25 )


// <Service ID>
//---------------------------------------------------------------
//	ServiceIDs
//---------------------------------------------------------------

//DECLARE_PMID(kServiceIDSpace, kFancyNewService, kInCopyExportPrefix + 1 )
//DECLARE_PMID(kServiceIDSpace, kFancyNewService, kInCopyExportPrefix + 2 )
//DECLARE_PMID(kServiceIDSpace, kFancyNewService, kInCopyExportPrefix + 3 )
//DECLARE_PMID(kServiceIDSpace, kFancyNewService, kInCopyExportPrefix + 4 )
//DECLARE_PMID(kServiceIDSpace, kFancyNewService, kInCopyExportPrefix + 5 )
//DECLARE_PMID(kServiceIDSpace, kFancyNewService, kInCopyExportPrefix + 6 )
//DECLARE_PMID(kServiceIDSpace, kFancyNewService, kInCopyExportPrefix + 7 )
//DECLARE_PMID(kServiceIDSpace, kFancyNewService, kInCopyExportPrefix + 8 )
//DECLARE_PMID(kServiceIDSpace, kFancyNewService, kInCopyExportPrefix + 9 )
//DECLARE_PMID(kServiceIDSpace, kFancyNewService, kInCopyExportPrefix + 10 )


// <Message ID>
//---------------------------------------------------------------
//	MessageIDs
//---------------------------------------------------------------
//DECLARE_PMID(kMessageIDSpace, kFancyNewMessage, kInCopyExportPrefix + 1 )
//DECLARE_PMID(kMessageIDSpace, kFancyNewMessage, kInCopyExportPrefix + 2 )
//DECLARE_PMID(kMessageIDSpace, kFancyNewMessage, kInCopyExportPrefix + 3 )
//DECLARE_PMID(kMessageIDSpace, kFancyNewMessage, kInCopyExportPrefix + 4 )
//DECLARE_PMID(kMessageIDSpace, kFancyNewMessage, kInCopyExportPrefix + 5 )
//DECLARE_PMID(kMessageIDSpace, kFancyNewMessage, kInCopyExportPrefix + 6 )
//DECLARE_PMID(kMessageIDSpace, kFancyNewMessage, kInCopyExportPrefix + 7 )
//DECLARE_PMID(kMessageIDSpace, kFancyNewMessage, kInCopyExportPrefix + 8 )
//DECLARE_PMID(kMessageIDSpace, kFancyNewMessage, kInCopyExportPrefix + 9 )
//DECLARE_PMID(kMessageIDSpace, kFancyNewMessage, kInCopyExportPrefix + 10 )


// <ScriptInfo ID>
//---------------------------------------------------------------
//	ScriptInfoIDs
//---------------------------------------------------------------
DECLARE_PMID(kScriptInfoIDSpace, kICExportPreferencesObjectScriptElement,	kInCopyExportPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kICExportPreferencesPropertyScriptElement,	kInCopyExportPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kICExportEncodingPropertyScriptElement,	kInCopyExportPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeStyleTablePropertyScriptElement,	kInCopyExportPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeSwatchListPropertyScriptElement,	kInCopyExportPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeXMPPropertyScriptElement,			kInCopyExportPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kICExportEncodingEnumScriptElement,		kInCopyExportPrefix + 7)

// ResourceID's/Indexes
#define kInCopyExportStringsRsrcID				1000
#define kInCopyExportStringsNoTransRsrcID		1200

#endif // __InCopyExportID__








